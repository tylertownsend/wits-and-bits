# Overview
When installing Ubuntu 20.04, I encountered some issues with the desktop manager. When I would log into my account, i would get a black screen followed by some random pixelization on one side of the screen. This doc provides a link and some notes to troubleshoot for future reference.

# Problem
What is assumed to be the issue is a loop when logging in where the desktop manager is unable to load.

## NVIDA Solution
After following ref 2, it was deteremined the Nvidia graphics card was causing issues. To resolve, purge the current drivers for Nvidia
```
sudo apt purge ~nnvidia
sudo apt autoremove
sudo apt clean
```

After the purging is complete, fully upgrade the system:
```
sudo apt update
sudo apt full-upgrade
```

Then search for the drivers you need. If you need to find the Graphics Card information run
```
sudo lspci -v | less
```

What you need to do is find the latest supported drivers for the OS, for this case, use `nvidia-driver-470`

```
sudo apt install nvidia-driver-470
```

Recommended driver for nvidia 515.48
```
```

```
nvidia-smi
```

# References
[1]. [Black Screen After Installing No Booting](https://newbedev.com/ubuntu-20-04-black-screen-after-installing-no-booting)
[2]. [Login Loop Ubuntu](https://support.system76.com/articles/login-loop-ubuntu/)
[3]. [Nvidia Driver 470](https://askubuntu.com/questions/1370843/how-to-properly-install-nvidia-470-drivers-on-ubuntu-20-04)
[4]. [Nvidia Driver 470 Does not Load Correctly on Ubuntu 20.04](https://forums.developer.nvidia.com/t/nvidia-driver-470-does-not-load-correctly-on-ubuntu-20-04/189630)
