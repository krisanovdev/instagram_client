mkdir Props

conan install . --profile .\Profiles\debug.txt || goto :error
copy conanbuildinfo.props .\Props\conanbuildinfoDebug.props

conan install . --profile .\Profiles\release.txt || goto :error
copy conanbuildinfo.props .\Props\conanbuildinfoRelease.props

del conanbuildinfo.props
del conanbuildinfo.txt
del conaninfo.txt

PAUSE

:error
exit