TEMPLATE = subdirs

SUBDIRS = \
          app \
          dock \
          animations \

dock.subdir = src/dock
animations.subdir  = src/animations
app.subdir  = src/app

app.depends = dock animations
