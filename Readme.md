# Devupload [ ![Codeship Status for dev-harsh1998/devupload](https://app.codeship.com/projects/9fbb3a80-9408-0136-80de-523f16cd0e8f/status?branch=master)](https://app.codeship.com/projects/304609)

[![Codacy Badge](https://api.codacy.com/project/badge/Grade/6034a261cd064590a40030810b8ac0bd)](https://app.codacy.com/app/dev-harsh1998/devupload?utm_source=github.com&utm_medium=referral&utm_content=dev-harsh1998/devupload&utm_campaign=Badge_Grade_Dashboard)

devupload is a command line utility built as a wrapper around cURL & [Transfer](https://github.com/dev-harsh198/Transfer) for the purpose to ease the uploading of files to various available free file host services. It abstracts away all the manual cURL & Transfer syntax to make usage effortless.

## How to use?

```
$ devupload -a my[rom:kernel].[zip:img:extntion]
$ devupload -b my[rom:kernel].[zip:img:extntion]
$ devupload -t my[rom:kernel].[zip:img:extntion]

parameter '-a' will trigger upload to https://androidfilehost.com
parameter '-b' will trigger upload to https://basketbuild.com
parameter '-t' will trigger upload to https://transfer.sh

example :- $ devupload -a aosp-9-20180829-jerry.zip

```

## Installation 
You can simply install devupload by following these instructions, make sure you have `git` and `curl` installed.

```
# Clone the repository.
git clone https://github.com/dev-harsh1998/devupload
# Navigate to cloned directory.
cd devupload
# Compile latest binary on your own machine!!.
make devupload
# Install it for direct access.
sudo make install
```


BOOM! Easy right? There you are done you have successfully built and installed devupload on your machine.

## Supported Platforms
- Linux x86
- Linux x86_64
- macOS

## Issue or feature request?

Please write about issues and feature request [here](https://github.com/dev-harsh1998/devupload).