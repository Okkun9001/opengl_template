#Steps
## Generate header in project dir
```
cd my-project
glad --api gl:core=4.6 --out-path glad
```

## Include in compiling:
```
gcc -I./glad/include -c main_opengl.c
```

# References
- https://en.wikipedia.org/wiki/Netpbms
- https://learnopengl.com/Advanced-OpenGL/Depth-testing

# Compile commands generated with bear:
```
bear -- make {additional commands}
```
