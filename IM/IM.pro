TEMPLATE = subdirs

SUBDIRS = \
    main \
    messenger \
    unit-tests

main.depends = messenger

unit-tests.depends = messenger

