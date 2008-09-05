::
:: This uploads the current documentation
:: and examples to the production server.
::

@echo off

echo LOVE Documentation Uploader
echo.
echo Authorization required

set /p username=Username:
set /p password=Password:

echo.
echo -----------------------------
echo Documentation
echo -----------------------------
echo.

echo.
echo Cleaning directories ...
echo.

:: Clean the diff directory.
rm -Rf diff

::
:: Documentation
::

:: Make sure directories exist.
lmkdir -p current current/docs diff diff/docs
touch current/doc-exclude.txt

echo Generating exclusion list ...
:: Check the files against the last upload.
chdir docs
md5sum -c ../current/doc-current.md5 | grep "OK" | cut -d: -f1 > ../current/doc-exclude.txt
chdir ..

echo.

echo Copying files ...
:: Copy modified files to current and diff.
XCOPY docs current\docs\ /E /Y /Q /EXCLUDE:current\doc-exclude.txt
XCOPY docs diff\docs\ /E /Y /Q /EXCLUDE:current\doc-exclude.txt

echo.

echo Generating md5sums ...
:: Make an exclusion list for next time.
chdir current/docs
md5sum * > ../doc-current.md5
chdir ../..

echo.

echo Creating .zip archive ...
:: Make a zip.
zip -r diff/love-docs-current.zip docs > diff/docs_log.txt

echo.

echo Uploading zipped documentation ...
:: Upload the zip.
ncftpput -m -u %username% -p %password% ftp.tehlol.com /public_html/love2d/ddocs/ diff/love-docs-current.zip

echo.

echo Uploading documentation ...
:: Upload them.
ncftpput -R -m -u %username% -p %password% ftp.tehlol.com /public_html/love2d diff/docs

echo.

::
:: Examples
::

echo -----------------------------
echo EXAMPLES
echo -----------------------------
echo.

echo Creating directories ...

:: Recreate dirs.
lmkdir -p diff/examples current/examples
touch current/examples-exclude.txt

echo.

echo Generating exclusion list ...
:: Check the files against the last upload.
chdir examples
md5sum -c ../current/examples-current.md5 | grep "OK" | cut -d: -f1 > ../current/examples-exclude.txt
chdir ..

echo.

echo Copying files ...

:: Copy all files from examples
XCOPY examples current\examples\ /E /Y /Q /EXCLUDE:current\examples-exclude.txt
XCOPY examples diff\examples\ /E /Y /Q /EXCLUDE:current\examples-exclude.txt

echo.

echo Generating md5sums ...

:: Generate the md5sums for the examples
chdir current/examples
md5sum * > ../examples-current.md5
chdir ../..

echo.

echo Creating .love ...

:: Make example.love.
chdir examples
zip -r -9 ../diff/examples.love * > ../examples_log.txt
chdir ..

echo.

echo Uploading examples ...

:: Upload examples.
ncftpput -R -m -u %username% -p %password% ftp.tehlol.com /public_html/love2d diff/examples

echo.

echo Uploading examples.love

:: Upload examples.love.
ncftpput -R -m -u %username% -p %password% ftp.tehlol.com /public_html/love2d/examples diff/examples.love

echo.

pause