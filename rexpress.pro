TEMPLATE = subdirs

SUBDIRS = \
          app \
          dock \
          animations \
          dependency_injection

dock.subdir = src/dock
animations.subdir  = src/animations
dependency_injection.subdir = src/dependency_injection
app.subdir  = src/app

app.depends = dock animations dependency_injection
