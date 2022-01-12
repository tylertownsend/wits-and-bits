```
sudo apt install openjdk-11-jdk
```

```
sudo snap install android-sudio --classic
```

Kill android studio when frozen
```bash
ps -eo pid,cmd | grep -Ev "^ {0,1}([0-9]*) grep.*" | grep -E 'java.*android-studio' | sed -re 's/ {0,1}([0-9]*) .*/\1/' | head -n1 | xargs kill -9
```

https://linuxconfig.org/how-to-install-android-studio-on-ubuntu-20-04-focal-fossa-linux#:~:text=Software%20Requirements%20and%20Linux%20Command%20Line%20Conventions%20,given%20linux%20commands%20to%20be%20%20...%20