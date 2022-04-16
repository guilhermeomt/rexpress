TEMPLATE = subdirs

SUBDIRS = \
        animations \
        src \
        dock

src.depends = dock
src.depends = animations
