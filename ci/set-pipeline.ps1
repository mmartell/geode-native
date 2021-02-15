#!/usr/bin/env bash
# Licensed to the Apache Software Foundation (ASF) under one or more
# contributor license agreements.  See the NOTICE file distributed with
# this work for additional information regarding copyright ownership.
# The ASF licenses this file to You under the Apache License, Version 2.0
# (the "License"); you may not use this file except in compliance with
# the License.  You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

#set -euo pipefail

# 1) Invoke command with params
# 2) Process command line params with defaults (Param block)
# 3) Merge in any environment variables and any computed defaults that
# 4) 	couldn't be handled in Param blcok
# 5) Render the yaml
# 6) Deploty the rendered pipeline via fly command
<#
.SYNOPSIS

Sets Concourse pipelines for Geode Native builds.

.DESCRIPTION

A longer description of your script.

.PARAMETER target
Fly target

.PARAMETER branch
Branch to build

.EXAMPLE
    YourScript.ps1 -SomeParameter 'thing' -OtherParameter 1

    Does something. Have as many examples as you think useful.
#>

#param (
#	[string]${target},
#	[string]$branch,
#	[string]$pipeline,
#	[string]${github-owner},
#	[string]${github-repository},	
#	[string]${google-zone},
#	[string]${google-project},
#	[string]${google-storage-bucket},
#	[string]${google-storage-key},
#	[string]$fly,
#	[string]$ytt,
#	[string]$variants
#)

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
	#write-output 'Entered Get-Owner'
	$git_tracking_branch=(git for-each-ref --format='%(upstream:short)' (git symbolic-ref -q HEAD))
	$git_remote = $git_tracking_branch.split("/")[0]
	$git_repository_url=(git remote get-url $git_remote)
	if ($git_repository_url -match '^((https|git)(:\/\/|@)github\.com[\/:])(?<owner>[^\/:]+)\/(?<repo>.+)$') {
		return $Matches["owner"]
	}
}

function Get-Repository {
	$git_tracking_branch=(git for-each-ref --format='%(upstream:short)' (git symbolic-ref -q HEAD))
	$git_remote = $git_tracking_branch.split("/")[0]
	$git_repository_url=(git remote get-url $git_remote)
	if ($git_repository_url -match '^((https|git)(:\/\/|@)github\.com[\/:])(?<owner>[^\/:]+)\/(?<repo>.+)$') {
		return $Matches["repo"]
	}
}

function Initialize-Param ( $paramKey ) {

	#write-output ('*** In Initialize-Param, $paramKey = ' + $paramKey)

	# Fetch any values set on the command line

	if ($PSBoundParameters.ContainsKey($paramKey)) {
		return $PSBoundParameters[$paramKey]
	}
	else {

		# Initialize via environment variable if set

		$paramEnv = [Environment]::GetEnvironmentVariable($paramKey)	
		if ($null -ne $paramEnv ) {
			write-output ('*** In Initialize-Param, setting ' + $paramKey + ' via environment variable = ' + $paramKey)
			return $paramEnv
		}

		# Initialize via defaults. Note: There are dependencies here so do not reorder.

		elseif ($paramKey -eq "target") {
			return "default"
		}
		elseif ($paramKey -eq "branch") {
			return (git rev-parse --abbrev-ref HEAD)
		}
		elseif ($paramKey -eq "github-owner") {
			return Get-Owner
		}
		elseif ($paramKey -eq "github-repository") {
			return Get-Repository
		}
		elseif ($paramKey -eq "pipeline") {
			return (${github-owner} + "-" + $branch)
		}
		elseif ($paramKey -eq "google-project") {
			return (gcloud config get-value project)
		}
		elseif ($paramKey -eq "google-zone") {
			return "us-central1-a"
		}
		elseif ($paramKey -eq "google-storage-bucket") {
			return (${google-project} + "-concourse")
		}
		elseif ($paramKey -eq "google-storage-key") {
			return "geode-native/" + $pipeline
		}
		elseif ($paramKey -eq "fly") {
			return "fly"
		}
		elseif ($paramKey -eq "ytt") {
			return "ytt"
		}
		elseif ($paramKey -eq "variants") {
			return "release pr"
		}
		elseif ($paramKey -eq "output") {
			return (New-TemporaryFile | ForEach-Object{ Remove-Item $_; mkdir $_ }) 
		}
		else {
			Write-Output ("****** Error: Invalid parameter " + $paramKey)
		}
	}
}

$target = Initialize-Param "target"
Write-Output ("target = " + $target)

$branch = Initialize-Param "branch"
Write-Output ("branch = " + $branch)

${github-owner} = Initialize-Param "github-owner"
Write-Output ("github-owner = " + ${github-owner})

${github-repository} = Initialize-Param "github-repository"
Write-Output ("github-repository = " +${github-repository})

$pipeline = Initialize-Param "pipeline"
Write-Output ("pipeline = " + $pipeline)

${google-zone} = Initialize-Param "google-zone"
Write-Output ("google-zone = " + ${google-zone})

${google-project} = Initialize-Param "google-project"
Write-Output ("google-project = " + ${google-project})

${google-storage-bucket} = Initialize-Param "google-storage-bucket"
Write-Output ("google-storage-bucket = " + ${google-storage-bucket})

${google-storage-key} = Initialize-Param "google-storage-key"
Write-Output ("google-storage-key = " + ${google-storage-key})

$fly = Initialize-Param "fly"
Write-Output ("fly = " + $fly)

$ytt = Initialize-Param "ytt"
Write-Output ("ytt = " + $ytt)

$variants = Initialize-Param "variants"
Write-Output ("variants = " + $variants)

$output = Initialize-Param "output"
Write-Output ("output = " + $output)

if ($Args[0] -eq "-help") {
    printHelp;
}

foreach ($varint in $variants) {
	$pipeline_suffix = "-" + $variant
	& $ytt `
		--file lib `
		--file base `
		--file ${variant} `
		--data-value "pipeline.name=$pipeline" `
		--data-value "pipeline.variant=${variant}" `
		--data-value "repository.branch=${branch}" `
		--data-value "github.owner=${github-owner}" `
		--data-value "github.repository=${github-repository}" `
		--data-value "google.project=${google-project}" `
		--data-value "google.zone=${google-zone}" `
		--data-value "google.storage.bucket=${google-storage-bucket}" `
		--data-value "google.storage.key=${google-storage-key}"
		> "$output/${variant}.yml"
	& $fly `
		--target=$target `
		set-pipeline `
			"--pipeline=" + $pipeline + $pipeline_suffix `
			"--config=" + $output + "/" + $variant + ".yml"
}