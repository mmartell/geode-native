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

<#
.SYNOPSIS

Sets Concourse pipelines for Geode Native builds.

.DESCRIPTION

A longer description of your script.

.PARAMETER --target
Fly target

.PARAMETER branch
Branch to build

.EXAMPLE
    YourScript.ps1 -SomeParameter 'thing' -OtherParameter 1

    Does something. Have as many examples as you think useful.
#>


# $GFSH_PATH = ""
# if (Get-Command gfsh -ErrorAction SilentlyContinue)
# {
#     $GFSH_PATH = "gfsh"
# }
# else
# {
#     if (-not (Test-Path env:GEODE_HOME))
#     {
#         Write-Host "Could not find gfsh.  Please set the GEODE_HOME path. e.g. "
#         Write-Host "(Powershell) `$env:GEODE_HOME = <path to Geode>"
#         Write-Host " OR"
#         Write-Host "(Command-line) set %GEODE_HOME% = <path to Geode>"
#     }
#     else
#     {
#         $GFSH_PATH = "$env:GEODE_HOME\bin\gfsh.bat"
#     }
# }

# if ($GFSH_PATH -ne "")
# {
#    $expression = "$GFSH_PATH " + `
# 	     "-e 'start locator --name=locator --dir=$PSScriptRoot\locator' " + `
# 	     "-e 'deploy --jar=$PSScriptRoot/../../utilities/example.jar' " + `
# 		 "-e 'start server --name=server --dir=$PSScriptRoot\server' " + `
#          "-e 'create region --name=photosMetaData --type=PARTITION' " + `
# 		 "-e 'execute function --id=InstantiateDataSerializable --member=server'";
#    Invoke-Expression $expression
# }

### Parameters (override defaults by passing in, e.g. -branch=)

param (
	[string]$branch = (git rev-parse --abbrev-ref HEAD),
	[string]$pipeline = "Based on repository owner name and branch"
	#[string]$github-owner = "Current tracking branch repository owner"
)

function printHelp() {
# $0 Usage:
# $myInvocation.ScriptName
	Write-Output "Sets Concourse pipelines for Geode Native builds."
	Write-Output ""
	Write-Output "Options:"
	Write-Output "Parameter                Description                         Default"
	Write-Output "--target                 Fly target.                         "default""
# --branch                 Branch to build.                    Current checked out branch.
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

#   if ($Args[0] -eq "--help") {
# 	write-output "here's arg 0: $($args[0])"
#   }

$git_tracking_branch=(git for-each-ref --format='%(upstream:short)' (git symbolic-ref -q HEAD))
write-output "git_tracking_branch = " $git_tracking_branch

#git_remote=${git_remote:-$(echo ${git_tracking_branch} | cut -d/ -f1)}
#git_repository_url=${git_repository_url:-$(git remote get-url ${git_remote})}

while ($Args.Count -gt 0 ) {
  if ($Args[0] -eq "--help") {
	write-output "here's arg 0: $($args[0])"

    printHelp;
#     exit 0;
#   elif [[ $1 == *"--"*"="* ]]; then
#     param="${1%%=*}"
#     param="${param#--}"
#     declare ${param//[^[:word:]]/_}="${1#--*=}"
#   elif [[ $1 == *"--"* ]]; then
#     param="${1/--/}"
#     declare ${param//[^[:word:]]/_}="${2}"
#     shift
#   fi
  }
}

<#
ytt=${ytt:-ytt}
fly=${fly:-fly}

target=${target:-default}
output=${output:-$(mktemp -d)}

branch=${branch:-$(git rev-parse --abbrev-ref HEAD)}
git_tracking_branch=${git_tracking_branch:-$(git for-each-ref --format='%(upstream:short)' $(git symbolic-ref -q HEAD))}
git_remote=${git_remote:-$(echo ${git_tracking_branch} | cut -d/ -f1)}
git_repository_url=${git_repository_url:-$(git remote get-url ${git_remote})}

if [[ ${git_repository_url} =~ ^((https|git)(:\/\/|@)github\.com[\/:])([^\/:]+)\/(.+).git$ ]]; then
  github_owner=${github_owner:-${BASH_REMATCH[4]}}
  github_repository=${github_repository:-${BASH_REMATCH[5]}}
fi

pipeline=${pipeline:-${github_owner}-${branch}}
pipeline=${pipeline//[^[:word:]-]/-}

google_project=${google_project:-$(gcloud config get-value project)}
google_zone=${google_zone:-'$(curl "http://metadata.google.internal/computeMetadata/v1/instance/zone" -H "Metadata-Flavor: Google" -s | cut -d / -f 4)'}
google_storage_bucket=${google_storage_bucket:-${google_project}-concourse}
google_storage_key=${google_storage_key:-geode-native/${pipeline}}

variants=${variants:-"release pr"}
variants_release=${variant_release:-""}

for variant in ${variants}; do
  eval pipeline_suffix=\${variants_${variant}-"-${variant}"}

  bash -c "${ytt} \"\$@\"" ytt \
    --file lib \
    --file base \
    --file ${variant} \
    --data-value "pipeline.name=${pipeline}" \
    --data-value "pipeline.variant=${variant}" \
    --data-value "repository.branch=${branch}" \
    --data-value "github.owner=${github_owner}" \
    --data-value "github.repository=${github_repository}" \
    --data-value "google.project=${google_project}" \
    --data-value "google.zone=${google_zone}" \
    --data-value "google.storage.bucket=${google_storage_bucket}" \
    --data-value "google.storage.key=${google_storage_key}" \
    > "${output}/${variant}.yml"


  bash -c "${fly} \"\$@\"" fly --target=${target} \
    set-pipeline \
      "--pipeline=${pipeline}${pipeline_suffix}" \
      "--config=${output}/${variant}.yml"

done
#>