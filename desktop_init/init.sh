function install_edge() {
  curl https://packages.microsoft.com/keys/microsoft.asc | gpg --dearmor > microsoft.gpg
  sudo install -o root -g root -m 644 microsoft.gpg /etc/apt/trusted.gpg.d/
  sudo sh -c 'echo "deb [arch=amd64] https://packages.microsoft.com/repos/edge stable main" > /etc/apt/sources.list.d/microsoft-edge-dev.list'
  sudo rm microsoft.gpg

  sudo apt update && sudo apt install microsoft-edge-stable
  # sudo apt remove microsoft-edge-stable
}

function install_conda() {
  sudo apt install libgl1-mesa-glx libegl1-mesa libxrandr2 libxrandr2 libxss1 libxcursor1 libxcomposite1 libasound2 libxi6 libxtst6
  wget -P /tmp https://repo.anaconda.com/archive/Anaconda3-2020.02-Linux-x86_64.so
  $(sha256sum /tmp/Anaconda3-2020.02-Linux-x86_64.sh) -eq "2b9f088b2022edb474915d9f69a803d6449d5fdb4c303041f60ac4aefcc208bb  /tmp/Anaconda3-2020.02-Linux-x86_64.sh"
  bash /tmp/Anaconda3-2020.02-Linux-x86_64.sh
}

function setup_git() {
  git config --global user.name "Tyler Townsend"
  git config --global user.email "townsend.ts@outlook.com"
  git config --global core.editor vim
}

setup_git()
install_edge()
install_conda()
