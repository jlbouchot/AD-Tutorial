# What you never dared to ask about algorithmic differentiation

Starting with a [short introduction](https://sed.saclay.inria.fr/demandez-le-programme/2026-03-26.html) at [INRIA Saclay](https://www.inria.fr/fr/centre-inria-de-saclay), this repo reviews the basics of algorithmic differentiation for everyone to get started

The first version presented at INRIA Saclay has been improved upon and details from a previous tutorial at [CSE21](https://www.siam.org/conferences/cm/program/minitutorials/cse21-minitutorials) have been introduced, improving the tutorial for a new presentation at [JDEV26](https://jdev26.sciencesconf.org/).



**Organizers**: [Jean-Luc Bouchot](jlbouchot.github.io) ([INRIA](https://www.inria.fr/)) and [Sri Hari Krishna Narayanan](https://www.anl.gov/profile/sri-hari-krishna-narayanan) ([Argonne National Lab](https://www.anl.gov/))

This tutorial mixes theoretical concepts with some practical applications. 
We gradually work our way from very basic codes to more interesting scientific concepts. 

This tutorial is targeted for AD-neophyte and curious about the subject matter, either coming from a scientific computing or computer science background.
If time permits, more advanced topics can be presented or discussed depending on everyone's needs.

## Technical stack

The earlier examples will be using [Tapenade](https://tapenade.gitlabpages.inria.fr/tapenade/) as a source transform AD tool. 
It uses a Java Run Time environment to run. 
JRE 8 has been exhaustively tested and so have Java SDK up to version 21. There are some known issues with later version of Java and depending on your current setup, some adaptations might be required.
Currently, on Mac Machines, the JRE provided by homebrew works.

Not that some issues may be encountered when using a Mac machine. We try to go over some of these below. 

## Installing Tapenade

### Downloading a precompiled version

Tapenade's [documentation](https://tapenade.gitlabpages.inria.fr/userdoc/build/html/tapenade/faq.html) is a reliable source of information for installing and solving any sort of issue. 
Tapenade requires no strong dependencies and downloading the [tar file](https://tapenade.gitlabpages.inria.fr/tapenade/distrib/tapenade_3.16.tar) from the [README](https://tapenade.gitlabpages.inria.fr/tapenade/distrib/README.html) will do the job for you. 

However to make things easier, we have prepared a little script which will take care of everything for you with regards to downloading tapenade's latest version and a compatible java. Simply download [this script](scripts/install_tapenade.sh) and then 

```bash
chmod +x install_tapenade.sh
./install_tapenade.sh
```

You may parametrize the installation. 
```bash
./install_tapenade.sh --help
```
for the possible options.

Note that you will need to source this file every time you restart a terminal in order to make sure that the `PATH` is correctly set. 
Should you not want to do this, then add the appropriate `export`'s in your `bashrc` file.

### Compiling the sources

```bash
git clone git@gitlab.inria.fr:tapenade/tapenade.git
cd tapenade
./gradlew
```

You need `gradle` version `<=8.2` for this. There are some known issues with higher versions. 


## Tapenade without tapenade

### Using Tapenade online

If you are experiencing trouble in using Tapenade on your machine, feel free to test things on [Tapenade's servlet](http://www-tapenade.inria.fr:8080/tapenade/index.jsp). It is possible that your browser refuses to open the page due to a certificate being outdated. Either allow it explicitely, or try removing the `s` in the `http` address, or use another browser. 

### Using Tapenade in a Docker image

It is also possible to run tapenade in an interactive Docker image.

First build the image
```bash
docker build -f docker/Dockerfile.tap -t tapenade .
```

This could take a bit of time to download the bsae image the first time. 
Then you can run a session via 
```bash
docker run -it -v .:/tapdir  tapenade
```

Few hints if you're not overly familiar with Docker:

- `-v` maps the content of a directory on your host system to a directory inside the container. Here `tapdir` is the default working directory for this image. Typically run your command from the hands on directory.
- `-it` is to use Docker in interactive mode.

## Known issues

### Tapenade for C issues in Mac

Tapenade requires a `C` preprocessor before parsing the code. 
Unfortunately, there are some divergences in the `cpp` commands from Linux to Mac. 
A fix for this has yet to be found as Mac's preprocessor is not currently compatible with Tapenade's `C` parser. 
A solution to this is to prevent Tapenade from calling the preprocessor via by adding
```bash
-cpp "#none#"
```
to all your Tapenade calls. This will have negative side effects on big projects!

Another possibility is to embed Linux's `C` preprocessor `cpp` within a Docker and call Docker on the fly in place of the preprocessor. 
This is still ongoing. 

Of course, this strategy requires to have a docker daemon running.

### Tapenade for Fortran issues in Mac

Tapenade's `Fortran` parser is generated in `C` on the fly and compiled when compiling Tapenade. 
The pipeline runs on a single machine and therefore the fortran parser is, by default, compiled for a single linux machine. 
To remedy this problem, you can try [downloading this archive](mac/mac_ARM.zip) containing all precompiled files useful for the current version of Tapenade on a Mac/ARM 64bit architecture. 
There is not guarantee that it will work, but it might. 

```bash
unzip mac_ARM.zip
cp * PATH/TO/TAPENADE/bin/mac/
```

Should this not work, you may also try to compile the parser on your own using this [compilation script](mac/compile_ARM).

Note that you will need to adapt the variables for it to work and the compilation requires the (automatically generated) file [tablesil.c](mac/tablesil.c) in the `build/generated-src/c/main/front` folder of tapenade. 
The script has only been tested on Mac with ARM processor and it might need to be adapted based on your needs. 
Once compiled, you can verify that the processor *works* by running
```bash
./fortranParser --version
```

### What are adXXX.h ?

Tapenade requires some auxiliary (hand coded) libraries for handling various cases such as 
* Concurrent / parallel programming
* adding context
* handling memory for saving states
* and many more

These libraries are coded in the `ADFirstAidKit/` folder which you should see within Tapenade's root folder. 
Should this not be the case, you can download all utility tools via 

```bash
wget tapenade.inria.fr:8080/tapenade/ADFirstAidKit.tar
tar vxf ADFirstAidKit.tar
```

Make sure to adapt the compilation script of your differentiated code to the actual path of the `ADFirstAidKit`.



