#!/bin/bash
sed -i '' -E '
/^#/d
s/[0-9]{4}-[0-9]{4}-[0-9]{4}-[0-9]{4}/XXXX-XXXX-XXXX-XXXX/g
s/[0-9]{16}/XXXX-XXXX-XXXX-XXXX/g
s/HTTP\/1\.0/HTTP\/1.1/g
' server_access.log
