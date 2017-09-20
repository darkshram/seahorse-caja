Name:           seahorse-caja
Version:        1.18.0
Release:        1%{?dist}
Summary:        PGP encryption and signing for caja
License:        GPLv2+
URL:            https://github.com/darkshram/seahorse-caja/
Source0:        https://github.com/darkshram/seahorse-caja/archive/%{version}/seahorse-caja-%{version}.tar.xz

BuildRequires:  gtk3-devel
BuildRequires:  desktop-file-utils
BuildRequires:  gcr-devel
BuildRequires:  gnupg2
BuildRequires:  gpgme-devel >= 1.0
BuildRequires:  caja-devel >= 1.17.0
BuildRequires:  libgnome-keyring-devel
BuildRequires:  dbus-glib-devel
BuildRequires:  libcryptui-devel
BuildRequires:  libnotify-devel
BuildRequires:  intltool

Obsoletes: seahorse-plugins < 3.0

# Needs caja built with gtk3.
Requires:       caja >= 1.17.0

%description
Seahorse caja is an extension for caja which allows encryption
and decryption of OpenPGP files using GnuPG.

%prep
%setup -q

%build
autoreconf -fi
%configure --disable-silent-rules --disable-gpg-check
make %{?_smp_mflags}

%install
%make_install

desktop-file-validate %{buildroot}%{_datadir}/applications/mate-seahorse-pgp-encrypted.desktop
desktop-file-validate %{buildroot}%{_datadir}/applications/mate-seahorse-pgp-keys.desktop
desktop-file-validate %{buildroot}%{_datadir}/applications/mate-seahorse-pgp-signature.desktop

find %{buildroot} -type f -name "*.la" -exec rm -f {} ';'
find %{buildroot} -type f -name "*.a" -exec rm -f {} ';'

%find_lang %{name}

%postun
if [ $1 -eq 0 ] ; then
    glib-compile-schemas %{_datadir}/glib-2.0/schemas &> /dev/null || :
fi

%posttrans
glib-compile-schemas %{_datadir}/glib-2.0/schemas &> /dev/null || :

%files -f %{name}.lang
%license COPYING
%doc AUTHORS NEWS README.md THANKS
%{_bindir}/mate-seahorse-tool
%{_libdir}/caja/extensions-2.0/libcaja-seahorse.so
%{_datadir}/applications/*.desktop
%{_datadir}/glib-2.0/schemas/org.mate.seahorse.caja.*gschema.xml
%{_datadir}/seahorse-caja/
%{_mandir}/man1/mate-seahorse-tool.1*

%changelog
* Wed Sep 20 2017 Joel Barrios <http://www.alcancelibre.org/> - 1.18.0-1
- initial packaging for ALDOS.
