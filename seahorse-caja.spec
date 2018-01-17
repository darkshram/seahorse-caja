Name:           seahorse-caja
Version:        %{VERSION}
Release:        1%{?dist}
Summary:        PGP encryption and signing for caja
License:        GPLv2+
URL:            https://github.com/darkshram/seahorse-caja/
Source0:        https://github.com/darkshram/seahorse-caja/archive/%{version}/seahorse-caja-%{version}.tar.xz

BuildRequires:  desktop-file-utils
BuildRequires:  gnupg2
BuildRequires:  intltool
BuildRequires:  pkgconfig(cryptui-0.0)
BuildRequires:  pkgconfig(dbus-glib-1)
BuildRequires:  pkgconfig(gck-1)
BuildRequires:  pkgconfig(gcr-3)
BuildRequires:  pkgconfig(gcr-base-3)
BuildRequires:  pkgconfig(gcr-ui-3)
BuildRequires:  pkgconfig(gtk+-3.0)
BuildRequires:  pkgconfig(libcaja-extension) >= 1.17.0
BuildRequires:  pkgconfig(libnotify)

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
update-desktop-database &> /dev/null || :
%if 0%{?fedora} < 24 || %{?rhel} < 8
if [ $1 -eq 0 ] ; then
    glib-compile-schemas %{_datadir}/glib-2.0/schemas &> /dev/null || :
fi
%endif

%posttrans
update-desktop-database &> /dev/null || :
%if 0%{?fedora} < 24 || %{?rhel} < 8
glib-compile-schemas %{_datadir}/glib-2.0/schemas &> /dev/null || :
%endif

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
* Tue Oct 17 2017 Joel Barrios <http://www.alcancelibre.org/> - 1.18.1-1
- glib-compile-schemas not required in Fedora >= 24 and RHEL >= 8. We keep them
  because AlcanceLibre.org maintains a Fedora based distro which requires them.

* Wed Sep 20 2017 Joel Barrios <http://www.alcancelibre.org/> - 1.18.0-1
- initial packaging for ALDOS, based on seahorse-nautilus.
