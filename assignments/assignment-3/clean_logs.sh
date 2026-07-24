#!/bin/bash
sed -i -E '
/^#/d
s/\b[0-9]{4}-[0-9]{4}-[0-9]{4}-[0-9]{4}\b/XXXX-XXXX-XXXX-XXXX/g
s/\b[0-9]{16}\b/XXXX-XXXX-XXXX-XXXX/g
s/HTTP\/1\.0/HTTP\/1.1/g
' server_access.log
