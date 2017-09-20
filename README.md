# seahorse-caja
Seahorse caja is an extension for caja which allows encryption
and decryption of OpenPGP files using GnuPG. It is integrated
into the caja right-click menu, but can also be used from the
command line.

Homepage: https://github.com/darkshram/seahorse-caja/

To build you will need:

* caja-devel (built with Gtk3)
* dbus-glib-devel
* gcr-devel
* gnupg2
* gpgme-devel
* gtk3-devel
* intltool
* libcryptui-devel
* libgnome-keyring-devel
* libnotify-devel

Then execute:

autoreconf -fi
./configure
make
make install

