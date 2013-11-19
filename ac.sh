rm -rf autom4te.cache &> /dev/null
#autoconf -f -v -o configure configure.in
#autoconf --warnings=all -d -f -v -o configure configure.in
autoconf -o configure configure.in

#
# Fix up silly error where Autoconf uses functions before they are defined.
#
cp configure configure.bak
rm configure

cat > configure << EOF
#!/bin/sh

as_fn_set_status ()
{
  return $1
}

as_fn_exit ()
{
  set +e
  as_fn_set_status $1
  exit $1
}
EOF

tail -n +2 configure.bak >> configure 

chmod 755 ./configure
