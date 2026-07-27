# Yocto Project (Lichee Pi Nano)
Using [yocto](https://www.yoctoproject.org/development/technical-overview/) to easy create an images for [Lichee Pi Nano board](https://hshop.vn/sipeed-lichee-nano-f1c100s-arm926ejs-linux-development-board) following those torials:

## Requirements
* Ubuntu 22.04.5 LTS
* Lichee Pi Nano board
* USB to TTL
* SD card reader & micro SD card
* Led & jumper wire (For testing GPIO)

## How to run
#### 1) First make sure to following packages are installed in system

```bash
sudo apt-get install gawk wget diffstat unzip texinfo gcc-multilib build-essential chrpath socat libsdl1.2-dev xterm emscripten libmpc-dev libgmp3-dev mtd-utils
```
**Note:** More informations can be found on Yocto reference manual

#### 2) Download necessary Yocto packaged listed below. Be sure to be in root of home folder.
```bash
mkdir yocto
cd yocto
mkdir build
git clone https://git.yoctoproject.org/poky --depth 1 -b dunfell
cd poky
git clone https://git.openembedded.org/meta-openembedded --depth 1 -b dunfell
```

#### Optional
```bash
git clone https://github.com/meta-qt5/meta-qt5.git --depth 1 -b dunfell
git clone https://github.com/voloviq/meta-licheepinano --depth 1 -b dunfell
```

#### 3) Select directory to build Linux 
```bash
source oe-init-build-env ~/yocto/build/licheepinano
```

#### 4) Modify bblayers.conf(located in ~/yocto/build/licheepinano/conf)
```bash
nano conf/bblayers.conf
```
```bash
BBLAYERS ?= " \\\
  ${HOME}/yocto/poky/meta \\\
  ${HOME}/yocto/poky/meta-poky \\\
  ${HOME}/yocto/poky/meta-openembedded/meta-oe \\\
  ${HOME}/yocto/poky/meta-openembedded/meta-networking \\\
  ${HOME}/yocto/poky/meta-openembedded/meta-python \\\
"
```
#### Optional
```bash
  ${HOME}/yocto/poky/meta-qt5 \\\
  ${HOME}/yocto/poky/meta-licheepinano \\\
```
**Note:** Please adapt PATH of conf/bblayers.conf if necessary. 

#### 5) Modify local.conf(located in ~/yocto/build/licheepinano/conf) file
```bash
nano conf/local.conf
```
- Modify line with "MACHINE ??" to add "licheepinano-sdcard" or for SPI NOR Flash "licheepinano-spinor"
```bash
MACHINE ??= "licheepinano-sdcard" #if you use sdcard
```
- Add at the end or You can file then replace it but hard to config later
```bash
DL_DIR = "${HOME}/yocto/downloads" <br>
SSTATE_DIR = "${HOME}/yocto/sstate-cache" <br>
TMPDIR = "${HOME}/yocto/tmp" <br>
RM_OLD_IMAGE = "1" <br>
INHERIT += "rm_work" <br>
```
#### Optional (Fix multiple definition of yylloc)
```bash
BUILD_CFLAGS += "-fcommon"
BUILD_CXXFLAGS += "-fcommon"
```
- For spi flash change DISTRO ?= "poky" to DISTRO ?= "licheepinano-tiny" <br>

**Note:** Please adapt rest of conf/local.conf parameters if necessary. <br>
#### 6) Build objects
When using SPI NOR Flash use following image (choose one of them)

- core image minimal (An lightweight operating system containing only the basic commands required for the machine to boot up) <br>
```bash
bitbake core-image-minimal
```

- console image (Similar to minimal version but have more software, libraries, and utility tools) <br>
```bash
bitbake console-image
```
- qt5 image (Operating system includes Qt5 graphics platform. If your project requires connecting an LCD screen) <br>
```bash
bitbake qt5-image
```

- qt5 toolchain sdk (This provides a SDK that allows you to write interface software on your PC and then cross-compile it on the Lichee Pi Nano board) <br>
```bash
bitbake meta-toolchain-qt5
```

#### 7) After compilation images appears in
Nano version <br>
	~/yocto/tmp/deploy/images/licheepinano <br>
  
#### For SD CARD
#### 8.1) Insert SD CARD into dedicated CARD slot and issue following command to write an image
**Note:** Be 100% sure to provide a valid device name (**of=/dev/sde/mmcblk0**). Wrong name "/dev/sde/mmcblk0" dameage Your system file ! <br> 
You can check using this command (Look through the list for a drive with a capacity matching your memory card (e.g., 8GB, 16GB, 32GB))
```bash
lsblk
```
Change the `of=/dev/mmcblk0` part in the command below to the correct drive 
```bash
sudo dd if=~/yocto/tmp/deploy/images/licheepinano-sdcard/core-image-minimal-licheepinano-sdcard.sunxi-sdimg of=/dev/mmcblk0 bs=1024 # you can add "status=progress" to follow the progress 
```
<img alt="image" src="https://github.com/user-attachments/assets/fab2cb8a-c9f8-4312-9f61-b6c6cd7bceeb"/>
#### 9.1) Install Serial software (Picocom) and set up board
1) Install picocom <br>
```bash
sudo apt install picocom
```
2) Set up <br>
- Laptop <-> USB to TTL <-> Lichee Pi Nano
	GND <-> GND
	TXD <-> U0RX
	RXD <-> U0TX
- Run the command:
```bash
sudo picocom -b 115200 /dev/ttyUSB0
```
- When the terminal is ready <br>
<img src="https://github.com/user-attachments/assets/d992c58b-a87a-4866-a7a5-933a06490943" />
- Connect the USB (micro USB) wire from Lichee Pi Nano to laptop then type `root` <br>
<img src="https://github.com/user-attachments/assets/b5a0336c-ec50-44b7-8a76-a2bc48d72a8f" />
<br>3) Handle GPIO using pin E3 (Step 10) <br>

#### For SPI Flash
#### 8.2) SPI NOR Flash update tool compilation (if valid sunxi-tools installed go to point 9)
```bash
git clone https://github.com/Icenowy/sunxi-tools.git -b f1c100s-spiflash
```
```bash
sudo apt-get install libz libusb-1.0-0-dev
```
```bash
make
```
```bash
sudo make install
```

#### 9.2) Flash SPI NOR flash
To enter into bootlader mode it is necessary to erase u-boot section from spi nor flash.<br>
To do this it is necessary to stop booting U-Boot and enter following commands.<br>
**sf probe 0**<br>
**sf erase 0 70000**<br>
**sunxi-fel -p spiflash-write 0 ~/yocto/tmp/deploy/images/licheepinano-spinor/core-image-minimal-licheepinano-spinor.sunxi-spinor**<br>

#### 11) How to handle GPIO from userfs - example (used PE3 as GPIO)<br>
1. Take a GPIO for instance E3 <br>
```bash
echo 131 > /sys/class/gpio/export
```
2. Set as out or in<br>
```bash
echo "out" > /sys/class/gpio/gpio131/direction
```
3. Set GPIO state if configured as ouput<br>
```bash
echo 1 > /sys/class/gpio/gpio131/value
echo 0 > /sys/class/gpio/gpio131/value
```
## Error
- Run "bitbake core-image-minimal" after turn off the terminal 
<img alt="image" src="https://github.com/user-attachments/assets/bd0f26b1-d1e4-4c07-9478-bd5dd25390c3" /> <br>
You must run "source oe-init-build-env ~/yocto/build/licheepinano" before run any commands if you open new terminal

- If you failed into some error like this
```bash
Summary: 1 task failed:
  /home/nghieu/yocto/poky/meta-licheepinano/recipes-kernel/linux/linux-suniv_5.2.bb:do_compile
Summary: There were 48 WARNING messages shown.
Summary: There were 2 ERROR messages shown, returning a non-zero exit code.
```
You can try to fix by using these commands
```bash
nano ~/yocto/poky/meta-licheepinano/recipes-kernel/linux/linux-suniv_5.2.bb
```
```bash
do_configure_prepend() {
    sed -i 's/YYLTYPE yylloc;/extern YYLTYPE yylloc;/g' ${S}/scripts/dtc/dtc-lexer.l
    sed -i 's/YYLTYPE yylloc;/extern YYLTYPE yylloc;/g' ${S}/scripts/dtc/dtc-lexer.lex.c_shipped 2>/dev/null || true
}
```

## References
- Build image using yocto [meta-licheepinano](https://github.com/voloviq/meta-licheepinano)
- Build image using buildroot [fanning.vn](https://fanning.vn/study_licheepinano/markdown.html)
