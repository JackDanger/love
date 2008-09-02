::
:: This uploads the current documentation
:: and examples to the production server.
::

set /p username=Username:
set /p password=Password: 

:: Clean the directory.
rm -Rf temp
mkdir temp

::
:: Documentation
::

:: Recreate dirs.
mkdir "temp/docs"

:: Copy all files from docs.
XCOPY docs temp\docs\ /E /Q

:: Make a zip.
zip -r temp/love-docs-current.zip docs > temp/docs_log.txt

:: Upload the zip.
ncftpput -m -u %username% -p %password% ftp.tehlol.com /public_html/love2d/ddocs/ temp/love-docs-current.zip

:: Upload them.
ncftpput -R -m -u %username% -p %password% ftp.tehlol.com /public_html/love2d temp/docs

::
:: Examples
::

:: Recreate dirs.
mkdir "temp/examples"

:: Copy all files from examples
XCOPY examples temp\examples\ /E /Q

:: Make example.love.
chdir temp/examples
zip -r -9 ../examples.love * > ../examples_log.txt
chdir ../../

:: Upload examples.
ncftpput -R -m -u %username% -p %password% ftp.tehlol.com /public_html/love2d temp/examples

:: Upload example.love.
ncftpput -R -m -u %username% -p %password% ftp.tehlol.com /public_html/love2d/examples temp/examples.love

pause