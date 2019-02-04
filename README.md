# fux_videoglitch

## Compile

```sh
docker run --rm -v ${PWD}:/usr/local/src constructionsincongrues/fux_videoglitch
```

`fux_videoglitch.pd_linux` is built in current directory. The `ubuntu:18.04` image is used to build the binary.

## Development

### Get sources

```sh
git clone git@github.com:badgeek/fux_videoglitch.git
```

### Build Docker image

```sh
make docker-image
```

### Attach to container

```sh
make docker-attach
```

### Compile fux_videoglitch

```sh
make docker-compile
```
