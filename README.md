run it via nix

```nix run "github:alexzsk/strlx-port-for-nix"```

to install on NixOS in a flake:
```nix
# flake.nix
{
  inputs = {
    strlx.url = "github:alexzsk/strlx-port-for-nix";
  };
}
```


