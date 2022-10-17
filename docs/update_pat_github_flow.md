# Overview
How to manage and use Personal Access Tokens(PAT) for github.

# Linux
Create a new PAT under github's developer settings.

Then when performing an operation on github that requires creds,

```
username = <github username>
password = <PAT>
```

After completing a successful auth, run
```
git config --global credential.helper store
```
located in folder ~/.git-credentials

cache will keep in memory
