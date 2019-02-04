# fux_videoglitch

## Compile

```sh
docker run --rm -v ${PWD}:/usr/local/src/dist constructionsincongrues/fux_videoglitch
```

`fux_videoglitch.pd_linux` is built in current directory. The `ubuntu:18.04` image is used to build the binary.

## Development

### Get sources

```sh
git clone git@github.com:badgeek/fux_videoglitch.git
```

### Build Docker image

```sh
# With default image name
make docker-image

# With a custom image name
make docker-image DOCKER_IMAGE=<repo/imagename>
```

### Publish Docker image

```sh
# With default image name
make docker-push

# With a custom image name
make docker-push DOCKER_IMAGE=<repo/imagename>
```

### Attach to container

```sh
make docker-attach
```

### Compile fux_videoglitch

```sh
make docker-compile
```
