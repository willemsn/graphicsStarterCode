# Graphics Starter Code

This code is used as a starter set for generating images with computer graphics.  It doesn't do much out of the box other than to generate a PNG image for you.


## Installing VCPkg

This code relies on VCpkg [https://learn.microsoft.com/en-us/vcpkg/get_started/get-started?pivots=shell-cmd](VCPkg from Microsoft) to install the necessary packages we'll need for graphics.  VCPkg is a C++ package manager that helps reduce the burden of building C++ code that relies on external frameworks.  You will need VCPkg to easily build this code.

### Installing VCPkg

You will want to follow the instructions on this page for VCPkg and Getting Started [https://learn.microsoft.com/en-us/vcpkg/get_started/get-started?pivots=shell-cmd](https://learn.microsoft.com/en-us/vcpkg/get_started/get-started?pivots=shell-cmd).

Before VCPkg, you will need to make sure CMake, git and a C++ compiler are on your machine.  See machine/OS-specific information below for more details.

When you install VCPkg, you should be able to follow the instructions for all systems (macos, Linux, Windows).  You will clone the vcpkg repository and then run a setup script in it.  You do not need to run this as sudo nor as an administrator.  The biggest thing you will need to make sure you do is set the environment variables. On Windows, you can add environment variables in the Settings.

For Linux, you'll want to set the environment variable in your shell resource file.  For instance if you're running the csh, this would go in ~/.cshrc:
~~~~
setenv VCPKG_ROOT /path/to/vcpkg
~~~~

For macos, with the zsh, you can place something like this in the ~/.zprofile config file:
~~~~
# add the path to vcpkg
export VCPKG_ROOT="/path/to/vcpkg"
export PATH="$PATH:$VCPKG_ROOT"
~~~~

## Building the Code

Once VCPkg is installed, clone this repository.  You should then be able to use cmake to generate the build environment for you.

~~~~
git clone git@github.com:willemsn/graphicsStarterCode.git
cd graphicsStarterCode
cmake --preset=default
~~~~

## Prerequisites for Different Systems

Before VCPkg can do its thing, you'll certainly need a development environment setup.  Be sure to have cmake, git and a C++ compiler ready. The sections below provide some guidance for different systems.

### Linux

On Ubuntu Linux, you'll need cmake, git and the build tools.  The command to install these packages follows:

~~~~
sudo apt-get cmake git build-essential
~~~~

### macos

For the mac, you will certainly need Xcode installed. You can get this from Apple's App Store.  The developer command line tools (along with git) should get installed when this happens.

After this, you will want to install Brew [https://brew.sh/](https://brew.sh/).  Brew is a package installer for macos that works well for installing a large variety of external packages and development libraries. With it, you can will install cmake (and many other tools you might find useful). After you install brew, you can install packages with the following command:

~~~~
brew install <packageName>
~~~~

typed at the command line of the Terminal.

### Windows 10/11

I use Git Bash fairly extensively as my main console on Windows.  You will probably find it useful:

* Git Bash [https://git-scm.com/downloads](https://git-scm.com/downloads)

You'll want a C++ compiler.  You can get Microsoft's C++ compiler with Visual Studio 2022 Community Edition.  VS 2022 does come with it's own CMake system but you may want to install the latest CMake too.

#### VS 2022 Environment

* Visual Studio Community Edition 2022
* CMake [https://cmake.org/download/](https://cmake.org/download/)

~~~~
cmake --build . --config Release
~~~~

## Try out the examples

After it builds, you can try executing the code. Before you do that, you're going to need to copy the DLLs in the C:\CS4212Libs\bin folder to where your executables are located. Alternatively, you can copy the DLLs into the Windows system folders. At some point, we could configure the CMake project to do this for us.  Also, don't forget to make sure that any OpenGL Shading Language files (*.glsl) are also in the appropriate locations.  If all works, you'll be able to see some images, triangles or whatever you're developing!

~~~~
OpenGL/Release/glfwExample
~~~~

or

~~~~
examples/Release/test_pngWrite
~~~~
