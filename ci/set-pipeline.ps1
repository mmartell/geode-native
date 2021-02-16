param (
	[string]$target,
	[string]$branch,
	[string]$pipeline,
	[string]${github-owner},
	[string]${github-repository},	
	[string]${google-zone},
	[string]${google-project},
	[string]${google-storage-bucket},
	[string]${google-storage-key},
	[string]$fly,
	[string]$ytt,
	[string]$variants
)

#Write-Host "*************Using target value: $target"
#Write-Host "             prboundParameters target is $PSBoundParameters.ContainsKey('target')"

function printAll {
	Write-Output github-repository
	Write-Output pipeline
}

function printHelp {
	Write-Output "Sets Concourse pipelines for Geode Native builds."
	Write-Output ""
	Write-Output "Options:"
	Write-Output "Parameter                Description                         Default"
	Write-Output '-target                  Fly target.                         "default"'
	Write-Output '-branch                  Branch to build.                    Current checked out branch.'
# --pipeline               Name of pipeline to set.            Based on repository owner name and branch.
# --github-owner           GitHub owner for repository.        Current tracking branch repository owner.
# --github-repository      GitHub repository name.             Current tracking branch repository name.
# --google-zone            Google Compute project.             Current default project.
# --google-project         Google Compute zone.                Concourse worker's zone.
# --google-storage-bucket  Google Compute Storage bucket.      Based on google-project value.
# --google-storage-key     Google Compute Storage key prefix.  Based on pipeline value.
# --fly                    Path to fly executable.             "fly"
# --ytt                    Path to ytt executable.             "ytt"
# --variants               Pipeline variants of publish.       Both release and pr.
# --output                 Rendered pipeline files directory.  Temporary directory.

# # Example:
# # \$ $0 --target=my-target --google-zone=my-zone

# # Environment Variables:
# # All options can be specified via environment variables where hyphens (-) are replaced with underscore (_).

# # Example:
# # \$ target=my-target google_zone=my-zone $0
}

function Get-Owner {
	write-output 'Entered Get-Owner'
	$git_tracking_branch=(git for-each-ref --format='%(upstream:short)' (git symbolic-ref -q HEAD))
	$git_remote = $git_tracking_branch.split("/")[0]
	$git_repository_url=(git remote get-url $git_remote)
	if ($git_repository_url -match '^((https|git)(:\/\/|@)github\.com[\/:])(?<owner>[^\/:]+)\/(?<repo>.+)$') {
		return $Matches["owner"]
	}
}

function Get-Repository {
	write-output 'Entered Get-Repository'
	$git_tracking_branch=(git for-each-ref --format='%(upstream:short)' (git symbolic-ref -q HEAD))
	$git_remote = $git_tracking_branch.split("/")[0]
	$git_repository_url=(git remote get-url $git_remote)
	if ($git_repository_url -match '^((https|git)(:\/\/|@)github\.com[\/:])(?<owner>[^\/:]+)\/(?<repo>.+)$') {
		write-output "   about to return $Matches["repo"]"
		return $Matches["repo"]
	}
}

function Initialize-Param ( $key, $value ) {

	write-output "*** In Initialize-Param with key = $key, value = $value"
	#write-output ('    $PSBoundParameters = ' + $PSBoundParameters)
	# Fetch any values set on the command line
	if ($value -ne "") {
		return $value
	}

	else {

		# Initialize via environment variable if set

		$paramEnv = [Environment]::GetEnvironmentVariable($key)	
		if ($null -ne $paramEnv ) {
			write-output ('*** In Initialize-Param, setting ' + $key + ' via environment variable = ' + $paramKey)
			return $paramEnv
		}

		# Initialize via defaults. Note: There are dependencies here so do not reorder.

		elseif ($key -eq "target") {
			return "default"
		}
		elseif ($key -eq "branch") {
			return (git rev-parse --abbrev-ref HEAD)
		}
		elseif ($key -eq "github-owner") {
			return Get-Owner
		}
		elseif ($key -eq "github-repository") {
			return Get-Repository
		}
		elseif ($key -eq "pipeline") {
			return (${github-owner} + "-" + $branch)
		}
		elseif ($key -eq "google-project") {
			return (gcloud config get-value project)
		}
		elseif ($key -eq "google-zone") {
			return "us-central1-a"
		}
		elseif ($key -eq "google-storage-bucket") {
			return (${google-project} + "-concourse")
		}
		elseif ($key -eq "google-storage-key") {
			return "geode-native/" + $pipeline
		}
		elseif ($key -eq "fly") {
			return "fly"
		}
		elseif ($key -eq "ytt") {
			return "ytt"
		}
		elseif ($key -eq "variants") {
			return "release pr"
		}
		elseif ($key -eq "output") {
			return (New-TemporaryFile | ForEach-Object{ Remove-Item $_; mkdir $_ }) 
		}
		else {
			Write-Output ("****** Error: Invalid parameter " + $key)
		}
	}
}

$target = Initialize-Param "target" $target
Write-Output "target = $target"

$branch = Initialize-Param "branch" $branch
Write-Output "branch = $branch"

${github-owner} = Initialize-Param "github-owner" ${github-owner}
Write-Output "github-owner = ${github-owner}"

${github-repository} = Initialize-Param "github-repository" ${github-repositiory}
Write-Output "github-repository = ${github-repository}"

$pipeline = Initialize-Param "pipeline" $pipeline
Write-Output "pipeline = $pipeline"

${google-zone} = Initialize-Param "google-zone" ${google-zone}
Write-Output "google-zone = ${google-zone}"

${google-project} = Initialize-Param "google-project" ${google-project}
Write-Output "google-project = ${google-project}"

${google-storage-bucket} = Initialize-Param "google-storage-bucket" ${google-storage-bucket}
Write-Output "google-storage-bucket = ${google-storage-bucket}"

${google-storage-key} = Initialize-Param "google-storage-key" ${google-storage-key}
Write-Output "google-storage-key = ${google-storage-key}"

$fly = Initialize-Param "fly" $fly
Write-Output "fly = $fly"

$ytt = Initialize-Param "ytt" $ytt
Write-Output "ytt = $ytt"

$variants = Initialize-Param "variants" $variants
Write-Output "variants = $variants"

$output = Initialize-Param "output" $output
Write-Output "output = $output"

if ($Args[0] -eq "-help") {
    printHelp;
}

foreach ($varint in $variants) {
	$pipeline_suffix = "-" + $variant
	& $ytt `
		-f lib `
		-f base `
		-v "pipeline.name=$pipeline" `
		-v "pipeline.variant=${variant}" `
		-v "repository.branch=${branch}" `
		-v "github.owner=${github-owner}" `
		-v "github.repository=${github-repository}" `
		-v "google.project=${google-project}" `
		-v "google.zone=${google-zone}" `
		-v "google.storage.bucket=${google-storage-bucket}" `
		-v "google.storage.key=${google-storage-key}"
		#> "$output/${variant}.yml"
	& $fly `
		--target=$target `
		set-pipeline `
			"--pipeline=" + $pipeline + $pipeline_suffix `
			"--config=" + $output + "/" + $variant + ".yml"
}