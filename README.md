# SamplerIDE

Open pippeting robot controller and method editor

## Features

This software allows you to create protocols, execute them on hardware and control your robot

* Visual protocol development environment
* Cross-platform software
* ...

**Note that this software is in early WIP**

## System requirements

* Windows 10+ / MacOS 11+ / Linux with GCC >= 11
* Qt6 framework installed with qserialport module

## Development build

You can download the latest Windows CI build from Github Actions:

Go to the Actions tab, open the latest build and download the artifact

## Build for yourself

Install cmake and Qt6 framework with qserialport module

```bash
git clone https://github.com/sampleride/sampleride

cd sampleride

mkdir build

cd build

cmake ..

make -j<number of cpu cores>
```
