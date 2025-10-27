r"""Wrapper for nanousd.h

Generated with:
/home/anders/code/nanousd/python/.venv/bin/ctypesgen -L../build /home/anders/code/nanousd/python/../nanousd.h -lnanousd -o nanousd/ffi.py

Do not modify this file.
"""

__docformat__ = "restructuredtext"

# Begin preamble for Python

import ctypes
import sys
from ctypes import *  # noqa: F401, F403

_int_types = (ctypes.c_int16, ctypes.c_int32)
if hasattr(ctypes, "c_int64"):
    # Some builds of ctypes apparently do not have ctypes.c_int64
    # defined; it's a pretty good bet that these builds do not
    # have 64-bit pointers.
    _int_types += (ctypes.c_int64,)
for t in _int_types:
    if ctypes.sizeof(t) == ctypes.sizeof(ctypes.c_size_t):
        c_ptrdiff_t = t
del t
del _int_types



class UserString:
    def __init__(self, seq):
        if isinstance(seq, bytes):
            self.data = seq
        elif isinstance(seq, UserString):
            self.data = seq.data[:]
        else:
            self.data = str(seq).encode()

    def __bytes__(self):
        return self.data

    def __str__(self):
        return self.data.decode()

    def __repr__(self):
        return repr(self.data)

    def __int__(self):
        return int(self.data.decode())

    def __long__(self):
        return int(self.data.decode())

    def __float__(self):
        return float(self.data.decode())

    def __complex__(self):
        return complex(self.data.decode())

    def __hash__(self):
        return hash(self.data)

    def __le__(self, string):
        if isinstance(string, UserString):
            return self.data <= string.data
        else:
            return self.data <= string

    def __lt__(self, string):
        if isinstance(string, UserString):
            return self.data < string.data
        else:
            return self.data < string

    def __ge__(self, string):
        if isinstance(string, UserString):
            return self.data >= string.data
        else:
            return self.data >= string

    def __gt__(self, string):
        if isinstance(string, UserString):
            return self.data > string.data
        else:
            return self.data > string

    def __eq__(self, string):
        if isinstance(string, UserString):
            return self.data == string.data
        else:
            return self.data == string

    def __ne__(self, string):
        if isinstance(string, UserString):
            return self.data != string.data
        else:
            return self.data != string

    def __contains__(self, char):
        return char in self.data

    def __len__(self):
        return len(self.data)

    def __getitem__(self, index):
        return self.__class__(self.data[index])

    def __getslice__(self, start, end):
        start = max(start, 0)
        end = max(end, 0)
        return self.__class__(self.data[start:end])

    def __add__(self, other):
        if isinstance(other, UserString):
            return self.__class__(self.data + other.data)
        elif isinstance(other, bytes):
            return self.__class__(self.data + other)
        else:
            return self.__class__(self.data + str(other).encode())

    def __radd__(self, other):
        if isinstance(other, bytes):
            return self.__class__(other + self.data)
        else:
            return self.__class__(str(other).encode() + self.data)

    def __mul__(self, n):
        return self.__class__(self.data * n)

    __rmul__ = __mul__

    def __mod__(self, args):
        return self.__class__(self.data % args)

    # the following methods are defined in alphabetical order:
    def capitalize(self):
        return self.__class__(self.data.capitalize())

    def center(self, width, *args):
        return self.__class__(self.data.center(width, *args))

    def count(self, sub, start=0, end=sys.maxsize):
        return self.data.count(sub, start, end)

    def decode(self, encoding=None, errors=None):  # XXX improve this?
        if encoding:
            if errors:
                return self.__class__(self.data.decode(encoding, errors))
            else:
                return self.__class__(self.data.decode(encoding))
        else:
            return self.__class__(self.data.decode())

    def encode(self, encoding=None, errors=None):  # XXX improve this?
        if encoding:
            if errors:
                return self.__class__(self.data.encode(encoding, errors))
            else:
                return self.__class__(self.data.encode(encoding))
        else:
            return self.__class__(self.data.encode())

    def endswith(self, suffix, start=0, end=sys.maxsize):
        return self.data.endswith(suffix, start, end)

    def expandtabs(self, tabsize=8):
        return self.__class__(self.data.expandtabs(tabsize))

    def find(self, sub, start=0, end=sys.maxsize):
        return self.data.find(sub, start, end)

    def index(self, sub, start=0, end=sys.maxsize):
        return self.data.index(sub, start, end)

    def isalpha(self):
        return self.data.isalpha()

    def isalnum(self):
        return self.data.isalnum()

    def isdecimal(self):
        return self.data.isdecimal()

    def isdigit(self):
        return self.data.isdigit()

    def islower(self):
        return self.data.islower()

    def isnumeric(self):
        return self.data.isnumeric()

    def isspace(self):
        return self.data.isspace()

    def istitle(self):
        return self.data.istitle()

    def isupper(self):
        return self.data.isupper()

    def join(self, seq):
        return self.data.join(seq)

    def ljust(self, width, *args):
        return self.__class__(self.data.ljust(width, *args))

    def lower(self):
        return self.__class__(self.data.lower())

    def lstrip(self, chars=None):
        return self.__class__(self.data.lstrip(chars))

    def partition(self, sep):
        return self.data.partition(sep)

    def replace(self, old, new, maxsplit=-1):
        return self.__class__(self.data.replace(old, new, maxsplit))

    def rfind(self, sub, start=0, end=sys.maxsize):
        return self.data.rfind(sub, start, end)

    def rindex(self, sub, start=0, end=sys.maxsize):
        return self.data.rindex(sub, start, end)

    def rjust(self, width, *args):
        return self.__class__(self.data.rjust(width, *args))

    def rpartition(self, sep):
        return self.data.rpartition(sep)

    def rstrip(self, chars=None):
        return self.__class__(self.data.rstrip(chars))

    def split(self, sep=None, maxsplit=-1):
        return self.data.split(sep, maxsplit)

    def rsplit(self, sep=None, maxsplit=-1):
        return self.data.rsplit(sep, maxsplit)

    def splitlines(self, keepends=0):
        return self.data.splitlines(keepends)

    def startswith(self, prefix, start=0, end=sys.maxsize):
        return self.data.startswith(prefix, start, end)

    def strip(self, chars=None):
        return self.__class__(self.data.strip(chars))

    def swapcase(self):
        return self.__class__(self.data.swapcase())

    def title(self):
        return self.__class__(self.data.title())

    def translate(self, *args):
        return self.__class__(self.data.translate(*args))

    def upper(self):
        return self.__class__(self.data.upper())

    def zfill(self, width):
        return self.__class__(self.data.zfill(width))


class MutableString(UserString):
    """mutable string objects

    Python strings are immutable objects.  This has the advantage, that
    strings may be used as dictionary keys.  If this property isn't needed
    and you insist on changing string values in place instead, you may cheat
    and use MutableString.

    But the purpose of this class is an educational one: to prevent
    people from inventing their own mutable string class derived
    from UserString and than forget thereby to remove (override) the
    __hash__ method inherited from UserString.  This would lead to
    errors that would be very hard to track down.

    A faster and better solution is to rewrite your program using lists."""

    def __init__(self, string=""):
        self.data = string

    def __hash__(self):
        raise TypeError("unhashable type (it is mutable)")

    def __setitem__(self, index, sub):
        if index < 0:
            index += len(self.data)
        if index < 0 or index >= len(self.data):
            raise IndexError
        self.data = self.data[:index] + sub + self.data[index + 1 :]

    def __delitem__(self, index):
        if index < 0:
            index += len(self.data)
        if index < 0 or index >= len(self.data):
            raise IndexError
        self.data = self.data[:index] + self.data[index + 1 :]

    def __setslice__(self, start, end, sub):
        start = max(start, 0)
        end = max(end, 0)
        if isinstance(sub, UserString):
            self.data = self.data[:start] + sub.data + self.data[end:]
        elif isinstance(sub, bytes):
            self.data = self.data[:start] + sub + self.data[end:]
        else:
            self.data = self.data[:start] + str(sub).encode() + self.data[end:]

    def __delslice__(self, start, end):
        start = max(start, 0)
        end = max(end, 0)
        self.data = self.data[:start] + self.data[end:]

    def immutable(self):
        return UserString(self.data)

    def __iadd__(self, other):
        if isinstance(other, UserString):
            self.data += other.data
        elif isinstance(other, bytes):
            self.data += other
        else:
            self.data += str(other).encode()
        return self

    def __imul__(self, n):
        self.data *= n
        return self


class String(MutableString, ctypes.Union):

    _fields_ = [("raw", ctypes.POINTER(ctypes.c_char)), ("data", ctypes.c_char_p)]

    def __init__(self, obj=b""):
        if isinstance(obj, (bytes, UserString)):
            self.data = bytes(obj)
        else:
            self.raw = obj

    def __len__(self):
        return self.data and len(self.data) or 0

    def from_param(cls, obj):
        # Convert None or 0
        if obj is None or obj == 0:
            return cls(ctypes.POINTER(ctypes.c_char)())

        # Convert from String
        elif isinstance(obj, String):
            return obj

        # Convert from bytes
        elif isinstance(obj, bytes):
            return cls(obj)

        # Convert from str
        elif isinstance(obj, str):
            return cls(obj.encode())

        # Convert from c_char_p
        elif isinstance(obj, ctypes.c_char_p):
            return obj

        # Convert from POINTER(ctypes.c_char)
        elif isinstance(obj, ctypes.POINTER(ctypes.c_char)):
            return obj

        # Convert from raw pointer
        elif isinstance(obj, int):
            return cls(ctypes.cast(obj, ctypes.POINTER(ctypes.c_char)))

        # Convert from ctypes.c_char array
        elif isinstance(obj, ctypes.c_char * len(obj)):
            return obj

        # Convert from object
        else:
            return String.from_param(obj._as_parameter_)

    from_param = classmethod(from_param)


def ReturnString(obj, func=None, arguments=None):
    return String.from_param(obj)


# As of ctypes 1.0, ctypes does not support custom error-checking
# functions on callbacks, nor does it support custom datatypes on
# callbacks, so we must ensure that all callbacks return
# primitive datatypes.
#
# Non-primitive return values wrapped with UNCHECKED won't be
# typechecked, and will be converted to ctypes.c_void_p.
def UNCHECKED(type):
    if hasattr(type, "_type_") and isinstance(type._type_, str) and type._type_ != "P":
        return type
    else:
        return ctypes.c_void_p


# ctypes doesn't have direct support for variadic functions, so we have to write
# our own wrapper class
class _variadic_function(object):
    def __init__(self, func, restype, argtypes, errcheck):
        self.func = func
        self.func.restype = restype
        self.argtypes = argtypes
        if errcheck:
            self.func.errcheck = errcheck

    def _as_parameter_(self):
        # So we can pass this variadic function as a function pointer
        return self.func

    def __call__(self, *args):
        fixed_args = []
        i = 0
        for argtype in self.argtypes:
            # Typecheck what we can
            fixed_args.append(argtype.from_param(args[i]))
            i += 1
        return self.func(*fixed_args + list(args[i:]))


def ord_if_char(value):
    """
    Simple helper used for casts to simple builtin types:  if the argument is a
    string type, it will be converted to it's ordinal value.

    This function will raise an exception if the argument is string with more
    than one characters.
    """
    return ord(value) if (isinstance(value, bytes) or isinstance(value, str)) else value

# End preamble

_libs = {}
_libdirs = ['../build']

# Begin loader

"""
Load libraries - appropriately for all our supported platforms
"""
# ----------------------------------------------------------------------------
# Copyright (c) 2008 David James
# Copyright (c) 2006-2008 Alex Holkner
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
#
#  * Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
#  * Redistributions in binary form must reproduce the above copyright
#    notice, this list of conditions and the following disclaimer in
#    the documentation and/or other materials provided with the
#    distribution.
#  * Neither the name of pyglet nor the names of its
#    contributors may be used to endorse or promote products
#    derived from this software without specific prior written
#    permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
# "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
# LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
# FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
# COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
# INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
# BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
# LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
# CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
# LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
# ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
# POSSIBILITY OF SUCH DAMAGE.
# ----------------------------------------------------------------------------

import ctypes
import ctypes.util
import glob
import os.path
import platform
import re
import sys


def _environ_path(name):
    """Split an environment variable into a path-like list elements"""
    if name in os.environ:
        return os.environ[name].split(":")
    return []


class LibraryLoader:
    """
    A base class For loading of libraries ;-)
    Subclasses load libraries for specific platforms.
    """

    # library names formatted specifically for platforms
    name_formats = ["%s"]

    class Lookup:
        """Looking up calling conventions for a platform"""

        mode = ctypes.DEFAULT_MODE

        def __init__(self, path):
            super(LibraryLoader.Lookup, self).__init__()
            self.access = dict(cdecl=ctypes.CDLL(path, self.mode))

        def get(self, name, calling_convention="cdecl"):
            """Return the given name according to the selected calling convention"""
            if calling_convention not in self.access:
                raise LookupError(
                    "Unknown calling convention '{}' for function '{}'".format(
                        calling_convention, name
                    )
                )
            return getattr(self.access[calling_convention], name)

        def has(self, name, calling_convention="cdecl"):
            """Return True if this given calling convention finds the given 'name'"""
            if calling_convention not in self.access:
                return False
            return hasattr(self.access[calling_convention], name)

        def __getattr__(self, name):
            return getattr(self.access["cdecl"], name)

    def __init__(self):
        self.other_dirs = []

    def __call__(self, libname):
        """Given the name of a library, load it."""
        paths = self.getpaths(libname)

        for path in paths:
            # noinspection PyBroadException
            try:
                return self.Lookup(path)
            except Exception:  # pylint: disable=broad-except
                pass

        raise ImportError("Could not load %s." % libname)

    def getpaths(self, libname):
        """Return a list of paths where the library might be found."""
        if os.path.isabs(libname):
            yield libname
        else:
            # search through a prioritized series of locations for the library

            # we first search any specific directories identified by user
            for dir_i in self.other_dirs:
                for fmt in self.name_formats:
                    # dir_i should be absolute already
                    yield os.path.join(dir_i, fmt % libname)

            # check if this code is even stored in a physical file
            try:
                this_file = __file__
            except NameError:
                this_file = None

            # then we search the directory where the generated python interface is stored
            if this_file is not None:
                for fmt in self.name_formats:
                    yield os.path.abspath(os.path.join(os.path.dirname(__file__), fmt % libname))

            # now, use the ctypes tools to try to find the library
            for fmt in self.name_formats:
                path = ctypes.util.find_library(fmt % libname)
                if path:
                    yield path

            # then we search all paths identified as platform-specific lib paths
            for path in self.getplatformpaths(libname):
                yield path

            # Finally, we'll try the users current working directory
            for fmt in self.name_formats:
                yield os.path.abspath(os.path.join(os.path.curdir, fmt % libname))

    def getplatformpaths(self, _libname):  # pylint: disable=no-self-use
        """Return all the library paths available in this platform"""
        return []


# Darwin (Mac OS X)


class DarwinLibraryLoader(LibraryLoader):
    """Library loader for MacOS"""

    name_formats = [
        "lib%s.dylib",
        "lib%s.so",
        "lib%s.bundle",
        "%s.dylib",
        "%s.so",
        "%s.bundle",
        "%s",
    ]

    class Lookup(LibraryLoader.Lookup):
        """
        Looking up library files for this platform (Darwin aka MacOS)
        """

        # Darwin requires dlopen to be called with mode RTLD_GLOBAL instead
        # of the default RTLD_LOCAL.  Without this, you end up with
        # libraries not being loadable, resulting in "Symbol not found"
        # errors
        mode = ctypes.RTLD_GLOBAL

    def getplatformpaths(self, libname):
        if os.path.pathsep in libname:
            names = [libname]
        else:
            names = [fmt % libname for fmt in self.name_formats]

        for directory in self.getdirs(libname):
            for name in names:
                yield os.path.join(directory, name)

    @staticmethod
    def getdirs(libname):
        """Implements the dylib search as specified in Apple documentation:

        http://developer.apple.com/documentation/DeveloperTools/Conceptual/
            DynamicLibraries/Articles/DynamicLibraryUsageGuidelines.html

        Before commencing the standard search, the method first checks
        the bundle's ``Frameworks`` directory if the application is running
        within a bundle (OS X .app).
        """

        dyld_fallback_library_path = _environ_path("DYLD_FALLBACK_LIBRARY_PATH")
        if not dyld_fallback_library_path:
            dyld_fallback_library_path = [
                os.path.expanduser("~/lib"),
                "/usr/local/lib",
                "/usr/lib",
            ]

        dirs = []

        if "/" in libname:
            dirs.extend(_environ_path("DYLD_LIBRARY_PATH"))
        else:
            dirs.extend(_environ_path("LD_LIBRARY_PATH"))
            dirs.extend(_environ_path("DYLD_LIBRARY_PATH"))
            dirs.extend(_environ_path("LD_RUN_PATH"))

        if hasattr(sys, "frozen") and getattr(sys, "frozen") == "macosx_app":
            dirs.append(os.path.join(os.environ["RESOURCEPATH"], "..", "Frameworks"))

        dirs.extend(dyld_fallback_library_path)

        return dirs


# Posix


class PosixLibraryLoader(LibraryLoader):
    """Library loader for POSIX-like systems (including Linux)"""

    _ld_so_cache = None

    _include = re.compile(r"^\s*include\s+(?P<pattern>.*)")

    name_formats = ["lib%s.so", "%s.so", "%s"]

    class _Directories(dict):
        """Deal with directories"""

        def __init__(self):
            dict.__init__(self)
            self.order = 0

        def add(self, directory):
            """Add a directory to our current set of directories"""
            if len(directory) > 1:
                directory = directory.rstrip(os.path.sep)
            # only adds and updates order if exists and not already in set
            if not os.path.exists(directory):
                return
            order = self.setdefault(directory, self.order)
            if order == self.order:
                self.order += 1

        def extend(self, directories):
            """Add a list of directories to our set"""
            for a_dir in directories:
                self.add(a_dir)

        def ordered(self):
            """Sort the list of directories"""
            return (i[0] for i in sorted(self.items(), key=lambda d: d[1]))

    def _get_ld_so_conf_dirs(self, conf, dirs):
        """
        Recursive function to help parse all ld.so.conf files, including proper
        handling of the `include` directive.
        """

        try:
            with open(conf) as fileobj:
                for dirname in fileobj:
                    dirname = dirname.strip()
                    if not dirname:
                        continue

                    match = self._include.match(dirname)
                    if not match:
                        dirs.add(dirname)
                    else:
                        for dir2 in glob.glob(match.group("pattern")):
                            self._get_ld_so_conf_dirs(dir2, dirs)
        except IOError:
            pass

    def _create_ld_so_cache(self):
        # Recreate search path followed by ld.so.  This is going to be
        # slow to build, and incorrect (ld.so uses ld.so.cache, which may
        # not be up-to-date).  Used only as fallback for distros without
        # /sbin/ldconfig.
        #
        # We assume the DT_RPATH and DT_RUNPATH binary sections are omitted.

        directories = self._Directories()
        for name in (
            "LD_LIBRARY_PATH",
            "SHLIB_PATH",  # HP-UX
            "LIBPATH",  # OS/2, AIX
            "LIBRARY_PATH",  # BE/OS
        ):
            if name in os.environ:
                directories.extend(os.environ[name].split(os.pathsep))

        self._get_ld_so_conf_dirs("/etc/ld.so.conf", directories)

        bitage = platform.architecture()[0]

        unix_lib_dirs_list = []
        if bitage.startswith("64"):
            # prefer 64 bit if that is our arch
            unix_lib_dirs_list += ["/lib64", "/usr/lib64"]

        # must include standard libs, since those paths are also used by 64 bit
        # installs
        unix_lib_dirs_list += ["/lib", "/usr/lib"]
        if sys.platform.startswith("linux"):
            # Try and support multiarch work in Ubuntu
            # https://wiki.ubuntu.com/MultiarchSpec
            if bitage.startswith("32"):
                # Assume Intel/AMD x86 compat
                unix_lib_dirs_list += ["/lib/i386-linux-gnu", "/usr/lib/i386-linux-gnu"]
            elif bitage.startswith("64"):
                # Assume Intel/AMD x86 compatible
                unix_lib_dirs_list += [
                    "/lib/x86_64-linux-gnu",
                    "/usr/lib/x86_64-linux-gnu",
                ]
            else:
                # guess...
                unix_lib_dirs_list += glob.glob("/lib/*linux-gnu")
        directories.extend(unix_lib_dirs_list)

        cache = {}
        lib_re = re.compile(r"lib(.*)\.s[ol]")
        # ext_re = re.compile(r"\.s[ol]$")
        for our_dir in directories.ordered():
            try:
                for path in glob.glob("%s/*.s[ol]*" % our_dir):
                    file = os.path.basename(path)

                    # Index by filename
                    cache_i = cache.setdefault(file, set())
                    cache_i.add(path)

                    # Index by library name
                    match = lib_re.match(file)
                    if match:
                        library = match.group(1)
                        cache_i = cache.setdefault(library, set())
                        cache_i.add(path)
            except OSError:
                pass

        self._ld_so_cache = cache

    def getplatformpaths(self, libname):
        if self._ld_so_cache is None:
            self._create_ld_so_cache()

        result = self._ld_so_cache.get(libname, set())
        for i in result:
            # we iterate through all found paths for library, since we may have
            # actually found multiple architectures or other library types that
            # may not load
            yield i


# Windows


class WindowsLibraryLoader(LibraryLoader):
    """Library loader for Microsoft Windows"""

    name_formats = ["%s.dll", "lib%s.dll", "%slib.dll", "%s"]

    class Lookup(LibraryLoader.Lookup):
        """Lookup class for Windows libraries..."""

        def __init__(self, path):
            super(WindowsLibraryLoader.Lookup, self).__init__(path)
            self.access["stdcall"] = ctypes.windll.LoadLibrary(path)


# Platform switching

# If your value of sys.platform does not appear in this dict, please contact
# the Ctypesgen maintainers.

loaderclass = {
    "darwin": DarwinLibraryLoader,
    "cygwin": WindowsLibraryLoader,
    "win32": WindowsLibraryLoader,
    "msys": WindowsLibraryLoader,
}

load_library = loaderclass.get(sys.platform, PosixLibraryLoader)()


def add_library_search_dirs(other_dirs):
    """
    Add libraries to search paths.
    If library paths are relative, convert them to absolute with respect to this
    file's directory
    """
    for path in other_dirs:
        if not os.path.isabs(path):
            path = os.path.abspath(path)
        load_library.other_dirs.append(path)


del loaderclass

# End loader

add_library_search_dirs(['../build'])

# Begin libraries
_libs["nanousd"] = load_library("nanousd")

# 1 libraries
# End libraries

# No modules

enum_nusd_result_e = c_int# /home/anders/code/nanousd/nanousd.h: 14

NUSD_RESULT_OK = 0# /home/anders/code/nanousd/nanousd.h: 14

NUSD_RESULT_INVALID_ATTRIBUTE_PATH = (NUSD_RESULT_OK + 1)# /home/anders/code/nanousd/nanousd.h: 14

NUSD_RESULT_INVALID_RELATIONSHIP_PATH = (NUSD_RESULT_INVALID_ATTRIBUTE_PATH + 1)# /home/anders/code/nanousd/nanousd.h: 14

NUSD_RESULT_INVALID_PRIM_PATH = (NUSD_RESULT_INVALID_RELATIONSHIP_PATH + 1)# /home/anders/code/nanousd/nanousd.h: 14

NUSD_RESULT_WRONG_TYPE = (NUSD_RESULT_INVALID_PRIM_PATH + 1)# /home/anders/code/nanousd/nanousd.h: 14

NUSD_RESULT_CREATE_STAGE_FAILED = (NUSD_RESULT_WRONG_TYPE + 1)# /home/anders/code/nanousd/nanousd.h: 14

NUSD_RESULT_OPEN_STAGE_FAILED = (NUSD_RESULT_CREATE_STAGE_FAILED + 1)# /home/anders/code/nanousd/nanousd.h: 14

NUSD_RESULT_DEFINE_PRIM_FAILED = (NUSD_RESULT_OPEN_STAGE_FAILED + 1)# /home/anders/code/nanousd/nanousd.h: 14

NUSD_RESULT_INVALID_PROPERTY_PATH = (NUSD_RESULT_DEFINE_PRIM_FAILED + 1)# /home/anders/code/nanousd/nanousd.h: 14

NUSD_RESULT_INVALID_PROPERTY_TYPE = (NUSD_RESULT_INVALID_PROPERTY_PATH + 1)# /home/anders/code/nanousd/nanousd.h: 14

NUSD_RESULT_CREATE_RELATIONSHIP_FAILED = (NUSD_RESULT_INVALID_PROPERTY_TYPE + 1)# /home/anders/code/nanousd/nanousd.h: 14

NUSD_RESULT_CREATE_ATTRIBUTE_FAILED = (NUSD_RESULT_CREATE_RELATIONSHIP_FAILED + 1)# /home/anders/code/nanousd/nanousd.h: 14

nusd_result_t = c_int# /home/anders/code/nanousd/nanousd.h: 29

nusd_stage_t = POINTER(None)# /home/anders/code/nanousd/nanousd.h: 31

# /home/anders/code/nanousd/nanousd.h: 33
class struct_nusd_prim_iterator_s(Structure):
    pass

nusd_prim_iterator_t = POINTER(struct_nusd_prim_iterator_s)# /home/anders/code/nanousd/nanousd.h: 33

# /home/anders/code/nanousd/nanousd.h: 34
class struct_nusd_property_iterator_s(Structure):
    pass

nusd_property_iterator_t = POINTER(struct_nusd_property_iterator_s)# /home/anders/code/nanousd/nanousd.h: 34

# /home/anders/code/nanousd/nanousd.h: 35
class struct_nusd_attribute_iterator_s(Structure):
    pass

nusd_attribute_iterator_t = POINTER(struct_nusd_attribute_iterator_s)# /home/anders/code/nanousd/nanousd.h: 35

# /home/anders/code/nanousd/nanousd.h: 36
class struct_nusd_relationship_iterator_s(Structure):
    pass

nusd_relationship_iterator_t = POINTER(struct_nusd_relationship_iterator_s)# /home/anders/code/nanousd/nanousd.h: 36

# /home/anders/code/nanousd/nanousd.h: 37
class struct_nusd_relationship_targets_iterator_s(Structure):
    pass

nusd_relationship_targets_iterator_t = POINTER(struct_nusd_relationship_targets_iterator_s)# /home/anders/code/nanousd/nanousd.h: 37

# /home/anders/code/nanousd/nanousd.h: 38
class struct_nusd_token_array_s(Structure):
    pass

nusd_token_array_t = POINTER(struct_nusd_token_array_s)# /home/anders/code/nanousd/nanousd.h: 38

# /home/anders/code/nanousd/nanousd.h: 39
class struct_nusd_float_array_s(Structure):
    pass

nusd_float_array_t = POINTER(struct_nusd_float_array_s)# /home/anders/code/nanousd/nanousd.h: 39

# /home/anders/code/nanousd/nanousd.h: 40
class struct_nusd_float2_array_s(Structure):
    pass

nusd_float2_array_t = POINTER(struct_nusd_float2_array_s)# /home/anders/code/nanousd/nanousd.h: 40

# /home/anders/code/nanousd/nanousd.h: 41
class struct_nusd_float3_array_s(Structure):
    pass

nusd_float3_array_t = POINTER(struct_nusd_float3_array_s)# /home/anders/code/nanousd/nanousd.h: 41

# /home/anders/code/nanousd/nanousd.h: 42
class struct_nusd_float4_array_s(Structure):
    pass

nusd_float4_array_t = POINTER(struct_nusd_float4_array_s)# /home/anders/code/nanousd/nanousd.h: 42

# /home/anders/code/nanousd/nanousd.h: 43
class struct_nusd_double_array_s(Structure):
    pass

nusd_double_array_t = POINTER(struct_nusd_double_array_s)# /home/anders/code/nanousd/nanousd.h: 43

# /home/anders/code/nanousd/nanousd.h: 44
class struct_nusd_double2_array_s(Structure):
    pass

nusd_double2_array_t = POINTER(struct_nusd_double2_array_s)# /home/anders/code/nanousd/nanousd.h: 44

# /home/anders/code/nanousd/nanousd.h: 45
class struct_nusd_double3_array_s(Structure):
    pass

nusd_double3_array_t = POINTER(struct_nusd_double3_array_s)# /home/anders/code/nanousd/nanousd.h: 45

# /home/anders/code/nanousd/nanousd.h: 46
class struct_nusd_double4_array_s(Structure):
    pass

nusd_double4_array_t = POINTER(struct_nusd_double4_array_s)# /home/anders/code/nanousd/nanousd.h: 46

# /home/anders/code/nanousd/nanousd.h: 47
class struct_nusd_int_array_s(Structure):
    pass

nusd_int_array_t = POINTER(struct_nusd_int_array_s)# /home/anders/code/nanousd/nanousd.h: 47

# /home/anders/code/nanousd/nanousd.h: 48
class struct_nusd_int2_array_s(Structure):
    pass

nusd_int2_array_t = POINTER(struct_nusd_int2_array_s)# /home/anders/code/nanousd/nanousd.h: 48

# /home/anders/code/nanousd/nanousd.h: 49
class struct_nusd_int3_array_s(Structure):
    pass

nusd_int3_array_t = POINTER(struct_nusd_int3_array_s)# /home/anders/code/nanousd/nanousd.h: 49

# /home/anders/code/nanousd/nanousd.h: 50
class struct_nusd_int4_array_s(Structure):
    pass

nusd_int4_array_t = POINTER(struct_nusd_int4_array_s)# /home/anders/code/nanousd/nanousd.h: 50

# /home/anders/code/nanousd/nanousd.h: 51
class struct_nusd_int64_array_s(Structure):
    pass

nusd_int64_array_t = POINTER(struct_nusd_int64_array_s)# /home/anders/code/nanousd/nanousd.h: 51

# /home/anders/code/nanousd/nanousd.h: 53
class struct_nusd_bool_array_s(Structure):
    pass

nusd_bool_array_t = POINTER(struct_nusd_bool_array_s)# /home/anders/code/nanousd/nanousd.h: 53

nusd_type_t = String# /home/anders/code/nanousd/nanousd.h: 55

# /home/anders/code/nanousd/nanousd.h: 57
try:
    NUSD_TYPE_ASSET = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_ASSET")
except:
    pass

# /home/anders/code/nanousd/nanousd.h: 58
try:
    NUSD_TYPE_ASSETARRAY = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_ASSETARRAY")
except:
    pass

# /home/anders/code/nanousd/nanousd.h: 59
try:
    NUSD_TYPE_BOOL = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_BOOL")
except:
    pass

# /home/anders/code/nanousd/nanousd.h: 60
try:
    NUSD_TYPE_BOOLARRAY = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_BOOLARRAY")
except:
    pass

# /home/anders/code/nanousd/nanousd.h: 61
try:
    NUSD_TYPE_COLOR3D = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_COLOR3D")
except:
    pass

# /home/anders/code/nanousd/nanousd.h: 62
try:
    NUSD_TYPE_COLOR3DARRAY = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_COLOR3DARRAY")
except:
    pass

# /home/anders/code/nanousd/nanousd.h: 63
try:
    NUSD_TYPE_COLOR3F = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_COLOR3F")
except:
    pass

# /home/anders/code/nanousd/nanousd.h: 64
try:
    NUSD_TYPE_COLOR3FARRAY = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_COLOR3FARRAY")
except:
    pass

# /home/anders/code/nanousd/nanousd.h: 65
try:
    NUSD_TYPE_COLOR3H = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_COLOR3H")
except:
    pass

# /home/anders/code/nanousd/nanousd.h: 66
try:
    NUSD_TYPE_COLOR3HARRAY = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_COLOR3HARRAY")
except:
    pass

# /home/anders/code/nanousd/nanousd.h: 67
try:
    NUSD_TYPE_COLOR4D = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_COLOR4D")
except:
    pass

# /home/anders/code/nanousd/nanousd.h: 68
try:
    NUSD_TYPE_COLOR4DARRAY = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_COLOR4DARRAY")
except:
    pass

# /home/anders/code/nanousd/nanousd.h: 69
try:
    NUSD_TYPE_COLOR4F = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_COLOR4F")
except:
    pass

# /home/anders/code/nanousd/nanousd.h: 70
try:
    NUSD_TYPE_COLOR4FARRAY = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_COLOR4FARRAY")
except:
    pass

# /home/anders/code/nanousd/nanousd.h: 71
try:
    NUSD_TYPE_COLOR4H = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_COLOR4H")
except:
    pass

# /home/anders/code/nanousd/nanousd.h: 72
try:
    NUSD_TYPE_COLOR4HARRAY = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_COLOR4HARRAY")
except:
    pass

# /home/anders/code/nanousd/nanousd.h: 73
try:
    NUSD_TYPE_DOUBLE = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_DOUBLE")
except:
    pass

# /home/anders/code/nanousd/nanousd.h: 74
try:
    NUSD_TYPE_DOUBLE2 = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_DOUBLE2")
except:
    pass

# /home/anders/code/nanousd/nanousd.h: 75
try:
    NUSD_TYPE_DOUBLE2ARRAY = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_DOUBLE2ARRAY")
except:
    pass

# /home/anders/code/nanousd/nanousd.h: 76
try:
    NUSD_TYPE_DOUBLE3 = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_DOUBLE3")
except:
    pass

# /home/anders/code/nanousd/nanousd.h: 77
try:
    NUSD_TYPE_DOUBLE3ARRAY = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_DOUBLE3ARRAY")
except:
    pass

# /home/anders/code/nanousd/nanousd.h: 78
try:
    NUSD_TYPE_DOUBLE4 = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_DOUBLE4")
except:
    pass

# /home/anders/code/nanousd/nanousd.h: 79
try:
    NUSD_TYPE_DOUBLE4ARRAY = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_DOUBLE4ARRAY")
except:
    pass

# /home/anders/code/nanousd/nanousd.h: 80
try:
    NUSD_TYPE_DOUBLEARRAY = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_DOUBLEARRAY")
except:
    pass

# /home/anders/code/nanousd/nanousd.h: 81
try:
    NUSD_TYPE_FIND = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_FIND")
except:
    pass

# /home/anders/code/nanousd/nanousd.h: 82
try:
    NUSD_TYPE_FLOAT = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_FLOAT")
except:
    pass

# /home/anders/code/nanousd/nanousd.h: 83
try:
    NUSD_TYPE_FLOAT2 = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_FLOAT2")
except:
    pass

# /home/anders/code/nanousd/nanousd.h: 84
try:
    NUSD_TYPE_FLOAT2ARRAY = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_FLOAT2ARRAY")
except:
    pass

# /home/anders/code/nanousd/nanousd.h: 85
try:
    NUSD_TYPE_FLOAT3 = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_FLOAT3")
except:
    pass

# /home/anders/code/nanousd/nanousd.h: 86
try:
    NUSD_TYPE_FLOAT3ARRAY = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_FLOAT3ARRAY")
except:
    pass

# /home/anders/code/nanousd/nanousd.h: 87
try:
    NUSD_TYPE_FLOAT4 = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_FLOAT4")
except:
    pass

# /home/anders/code/nanousd/nanousd.h: 88
try:
    NUSD_TYPE_FLOAT4ARRAY = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_FLOAT4ARRAY")
except:
    pass

# /home/anders/code/nanousd/nanousd.h: 89
try:
    NUSD_TYPE_FLOATARRAY = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_FLOATARRAY")
except:
    pass

# /home/anders/code/nanousd/nanousd.h: 90
try:
    NUSD_TYPE_FRAME4D = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_FRAME4D")
except:
    pass

# /home/anders/code/nanousd/nanousd.h: 91
try:
    NUSD_TYPE_FRAME4DARRAY = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_FRAME4DARRAY")
except:
    pass

# /home/anders/code/nanousd/nanousd.h: 92
try:
    NUSD_TYPE_GROUP = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_GROUP")
except:
    pass

# /home/anders/code/nanousd/nanousd.h: 93
try:
    NUSD_TYPE_HALF = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_HALF")
except:
    pass

# /home/anders/code/nanousd/nanousd.h: 94
try:
    NUSD_TYPE_HALF2 = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_HALF2")
except:
    pass

# /home/anders/code/nanousd/nanousd.h: 95
try:
    NUSD_TYPE_HALF2ARRAY = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_HALF2ARRAY")
except:
    pass

# /home/anders/code/nanousd/nanousd.h: 96
try:
    NUSD_TYPE_HALF3 = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_HALF3")
except:
    pass

# /home/anders/code/nanousd/nanousd.h: 97
try:
    NUSD_TYPE_HALF3ARRAY = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_HALF3ARRAY")
except:
    pass

# /home/anders/code/nanousd/nanousd.h: 98
try:
    NUSD_TYPE_HALF4 = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_HALF4")
except:
    pass

# /home/anders/code/nanousd/nanousd.h: 99
try:
    NUSD_TYPE_HALF4ARRAY = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_HALF4ARRAY")
except:
    pass

# /home/anders/code/nanousd/nanousd.h: 100
try:
    NUSD_TYPE_HALFARRAY = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_HALFARRAY")
except:
    pass

# /home/anders/code/nanousd/nanousd.h: 101
try:
    NUSD_TYPE_INT = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_INT")
except:
    pass

# /home/anders/code/nanousd/nanousd.h: 102
try:
    NUSD_TYPE_INT2 = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_INT2")
except:
    pass

# /home/anders/code/nanousd/nanousd.h: 103
try:
    NUSD_TYPE_INT2ARRAY = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_INT2ARRAY")
except:
    pass

# /home/anders/code/nanousd/nanousd.h: 104
try:
    NUSD_TYPE_INT3 = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_INT3")
except:
    pass

# /home/anders/code/nanousd/nanousd.h: 105
try:
    NUSD_TYPE_INT3ARRAY = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_INT3ARRAY")
except:
    pass

# /home/anders/code/nanousd/nanousd.h: 106
try:
    NUSD_TYPE_INT4 = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_INT4")
except:
    pass

# /home/anders/code/nanousd/nanousd.h: 107
try:
    NUSD_TYPE_INT4ARRAY = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_INT4ARRAY")
except:
    pass

# /home/anders/code/nanousd/nanousd.h: 108
try:
    NUSD_TYPE_INT64 = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_INT64")
except:
    pass

# /home/anders/code/nanousd/nanousd.h: 109
try:
    NUSD_TYPE_INT64ARRAY = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_INT64ARRAY")
except:
    pass

# /home/anders/code/nanousd/nanousd.h: 110
try:
    NUSD_TYPE_INTARRAY = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_INTARRAY")
except:
    pass

# /home/anders/code/nanousd/nanousd.h: 111
try:
    NUSD_TYPE_MATRIX2D = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_MATRIX2D")
except:
    pass

# /home/anders/code/nanousd/nanousd.h: 112
try:
    NUSD_TYPE_MATRIX2DARRAY = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_MATRIX2DARRAY")
except:
    pass

# /home/anders/code/nanousd/nanousd.h: 113
try:
    NUSD_TYPE_MATRIX3D = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_MATRIX3D")
except:
    pass

# /home/anders/code/nanousd/nanousd.h: 114
try:
    NUSD_TYPE_MATRIX3DARRAY = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_MATRIX3DARRAY")
except:
    pass

# /home/anders/code/nanousd/nanousd.h: 115
try:
    NUSD_TYPE_MATRIX4D = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_MATRIX4D")
except:
    pass

# /home/anders/code/nanousd/nanousd.h: 116
try:
    NUSD_TYPE_MATRIX4DARRAY = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_MATRIX4DARRAY")
except:
    pass

# /home/anders/code/nanousd/nanousd.h: 117
try:
    NUSD_TYPE_NORMAL3D = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_NORMAL3D")
except:
    pass

# /home/anders/code/nanousd/nanousd.h: 118
try:
    NUSD_TYPE_NORMAL3DARRAY = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_NORMAL3DARRAY")
except:
    pass

# /home/anders/code/nanousd/nanousd.h: 119
try:
    NUSD_TYPE_NORMAL3F = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_NORMAL3F")
except:
    pass

# /home/anders/code/nanousd/nanousd.h: 120
try:
    NUSD_TYPE_NORMAL3FARRAY = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_NORMAL3FARRAY")
except:
    pass

# /home/anders/code/nanousd/nanousd.h: 121
try:
    NUSD_TYPE_NORMAL3H = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_NORMAL3H")
except:
    pass

# /home/anders/code/nanousd/nanousd.h: 122
try:
    NUSD_TYPE_NORMAL3HARRAY = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_NORMAL3HARRAY")
except:
    pass

# /home/anders/code/nanousd/nanousd.h: 123
try:
    NUSD_TYPE_OPAQUE = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_OPAQUE")
except:
    pass

# /home/anders/code/nanousd/nanousd.h: 124
try:
    NUSD_TYPE_PATHEXPRESSION = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_PATHEXPRESSION")
except:
    pass

# /home/anders/code/nanousd/nanousd.h: 125
try:
    NUSD_TYPE_PATHEXPRESSIONARRAY = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_PATHEXPRESSIONARRAY")
except:
    pass

# /home/anders/code/nanousd/nanousd.h: 126
try:
    NUSD_TYPE_POINT3D = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_POINT3D")
except:
    pass

# /home/anders/code/nanousd/nanousd.h: 127
try:
    NUSD_TYPE_POINT3DARRAY = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_POINT3DARRAY")
except:
    pass

# /home/anders/code/nanousd/nanousd.h: 128
try:
    NUSD_TYPE_POINT3F = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_POINT3F")
except:
    pass

# /home/anders/code/nanousd/nanousd.h: 129
try:
    NUSD_TYPE_POINT3FARRAY = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_POINT3FARRAY")
except:
    pass

# /home/anders/code/nanousd/nanousd.h: 130
try:
    NUSD_TYPE_POINT3H = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_POINT3H")
except:
    pass

# /home/anders/code/nanousd/nanousd.h: 131
try:
    NUSD_TYPE_POINT3HARRAY = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_POINT3HARRAY")
except:
    pass

# /home/anders/code/nanousd/nanousd.h: 132
try:
    NUSD_TYPE_QUATD = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_QUATD")
except:
    pass

# /home/anders/code/nanousd/nanousd.h: 133
try:
    NUSD_TYPE_QUATDARRAY = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_QUATDARRAY")
except:
    pass

# /home/anders/code/nanousd/nanousd.h: 134
try:
    NUSD_TYPE_QUATF = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_QUATF")
except:
    pass

# /home/anders/code/nanousd/nanousd.h: 135
try:
    NUSD_TYPE_QUATFARRAY = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_QUATFARRAY")
except:
    pass

# /home/anders/code/nanousd/nanousd.h: 136
try:
    NUSD_TYPE_QUATH = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_QUATH")
except:
    pass

# /home/anders/code/nanousd/nanousd.h: 137
try:
    NUSD_TYPE_QUATHARRAY = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_QUATHARRAY")
except:
    pass

# /home/anders/code/nanousd/nanousd.h: 138
try:
    NUSD_TYPE_STRING = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_STRING")
except:
    pass

# /home/anders/code/nanousd/nanousd.h: 139
try:
    NUSD_TYPE_STRINGARRAY = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_STRINGARRAY")
except:
    pass

# /home/anders/code/nanousd/nanousd.h: 140
try:
    NUSD_TYPE_TEXCOORD2D = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_TEXCOORD2D")
except:
    pass

# /home/anders/code/nanousd/nanousd.h: 141
try:
    NUSD_TYPE_TEXCOORD2DARRAY = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_TEXCOORD2DARRAY")
except:
    pass

# /home/anders/code/nanousd/nanousd.h: 142
try:
    NUSD_TYPE_TEXCOORD2F = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_TEXCOORD2F")
except:
    pass

# /home/anders/code/nanousd/nanousd.h: 143
try:
    NUSD_TYPE_TEXCOORD2FARRAY = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_TEXCOORD2FARRAY")
except:
    pass

# /home/anders/code/nanousd/nanousd.h: 144
try:
    NUSD_TYPE_TEXCOORD2H = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_TEXCOORD2H")
except:
    pass

# /home/anders/code/nanousd/nanousd.h: 145
try:
    NUSD_TYPE_TEXCOORD2HARRAY = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_TEXCOORD2HARRAY")
except:
    pass

# /home/anders/code/nanousd/nanousd.h: 146
try:
    NUSD_TYPE_TEXCOORD3D = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_TEXCOORD3D")
except:
    pass

# /home/anders/code/nanousd/nanousd.h: 147
try:
    NUSD_TYPE_TEXCOORD3DARRAY = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_TEXCOORD3DARRAY")
except:
    pass

# /home/anders/code/nanousd/nanousd.h: 148
try:
    NUSD_TYPE_TEXCOORD3F = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_TEXCOORD3F")
except:
    pass

# /home/anders/code/nanousd/nanousd.h: 149
try:
    NUSD_TYPE_TEXCOORD3FARRAY = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_TEXCOORD3FARRAY")
except:
    pass

# /home/anders/code/nanousd/nanousd.h: 150
try:
    NUSD_TYPE_TEXCOORD3H = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_TEXCOORD3H")
except:
    pass

# /home/anders/code/nanousd/nanousd.h: 151
try:
    NUSD_TYPE_TEXCOORD3HARRAY = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_TEXCOORD3HARRAY")
except:
    pass

# /home/anders/code/nanousd/nanousd.h: 152
try:
    NUSD_TYPE_TIMECODE = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_TIMECODE")
except:
    pass

# /home/anders/code/nanousd/nanousd.h: 153
try:
    NUSD_TYPE_TIMECODEARRAY = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_TIMECODEARRAY")
except:
    pass

# /home/anders/code/nanousd/nanousd.h: 154
try:
    NUSD_TYPE_TOKEN = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_TOKEN")
except:
    pass

# /home/anders/code/nanousd/nanousd.h: 155
try:
    NUSD_TYPE_TOKENARRAY = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_TOKENARRAY")
except:
    pass

# /home/anders/code/nanousd/nanousd.h: 156
try:
    NUSD_TYPE_UCHAR = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_UCHAR")
except:
    pass

# /home/anders/code/nanousd/nanousd.h: 157
try:
    NUSD_TYPE_UCHARARRAY = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_UCHARARRAY")
except:
    pass

# /home/anders/code/nanousd/nanousd.h: 158
try:
    NUSD_TYPE_UINT = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_UINT")
except:
    pass

# /home/anders/code/nanousd/nanousd.h: 159
try:
    NUSD_TYPE_UINT64 = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_UINT64")
except:
    pass

# /home/anders/code/nanousd/nanousd.h: 160
try:
    NUSD_TYPE_UINT64ARRAY = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_UINT64ARRAY")
except:
    pass

# /home/anders/code/nanousd/nanousd.h: 161
try:
    NUSD_TYPE_UINTARRAY = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_UINTARRAY")
except:
    pass

# /home/anders/code/nanousd/nanousd.h: 162
try:
    NUSD_TYPE_VECTOR3D = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_VECTOR3D")
except:
    pass

# /home/anders/code/nanousd/nanousd.h: 163
try:
    NUSD_TYPE_VECTOR3DARRAY = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_VECTOR3DARRAY")
except:
    pass

# /home/anders/code/nanousd/nanousd.h: 164
try:
    NUSD_TYPE_VECTOR3F = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_VECTOR3F")
except:
    pass

# /home/anders/code/nanousd/nanousd.h: 165
try:
    NUSD_TYPE_VECTOR3FARRAY = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_VECTOR3FARRAY")
except:
    pass

# /home/anders/code/nanousd/nanousd.h: 166
try:
    NUSD_TYPE_VECTOR3H = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_VECTOR3H")
except:
    pass

# /home/anders/code/nanousd/nanousd.h: 167
try:
    NUSD_TYPE_VECTOR3HARRAY = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_VECTOR3HARRAY")
except:
    pass

# /home/anders/code/nanousd/nanousd.h: 169
try:
    NUSD_TYPE_RELATIONSHIP = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_RELATIONSHIP")
except:
    pass

enum_nusd_property_type_e = c_int# /home/anders/code/nanousd/nanousd.h: 172

NUSD_PROPERTY_TYPE_ATTRIBUTE = 0# /home/anders/code/nanousd/nanousd.h: 172

NUSD_PROPERTY_TYPE_RELATIONSHIP = (NUSD_PROPERTY_TYPE_ATTRIBUTE + 1)# /home/anders/code/nanousd/nanousd.h: 172

nusd_property_type_t = c_int# /home/anders/code/nanousd/nanousd.h: 176

# /home/anders/code/nanousd/nanousd.h: 179
if _libs["nanousd"].has("nusd_stage_open", "cdecl"):
    nusd_stage_open = _libs["nanousd"].get("nusd_stage_open", "cdecl")
    nusd_stage_open.argtypes = [String, POINTER(nusd_stage_t)]
    nusd_stage_open.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd.h: 182
if _libs["nanousd"].has("nusd_stage_create_new", "cdecl"):
    nusd_stage_create_new = _libs["nanousd"].get("nusd_stage_create_new", "cdecl")
    nusd_stage_create_new.argtypes = [String, POINTER(nusd_stage_t)]
    nusd_stage_create_new.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd.h: 185
if _libs["nanousd"].has("nusd_stage_create_in_memory", "cdecl"):
    nusd_stage_create_in_memory = _libs["nanousd"].get("nusd_stage_create_in_memory", "cdecl")
    nusd_stage_create_in_memory.argtypes = [String, POINTER(nusd_stage_t)]
    nusd_stage_create_in_memory.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd.h: 188
if _libs["nanousd"].has("nusd_stage_save", "cdecl"):
    nusd_stage_save = _libs["nanousd"].get("nusd_stage_save", "cdecl")
    nusd_stage_save.argtypes = [nusd_stage_t]
    nusd_stage_save.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd.h: 192
if _libs["nanousd"].has("nusd_stage_save_as", "cdecl"):
    nusd_stage_save_as = _libs["nanousd"].get("nusd_stage_save_as", "cdecl")
    nusd_stage_save_as.argtypes = [nusd_stage_t, String]
    nusd_stage_save_as.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd.h: 195
if _libs["nanousd"].has("nusd_stage_destroy", "cdecl"):
    nusd_stage_destroy = _libs["nanousd"].get("nusd_stage_destroy", "cdecl")
    nusd_stage_destroy.argtypes = [nusd_stage_t]
    nusd_stage_destroy.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd.h: 199
if _libs["nanousd"].has("nusd_stage_define_prim", "cdecl"):
    nusd_stage_define_prim = _libs["nanousd"].get("nusd_stage_define_prim", "cdecl")
    nusd_stage_define_prim.argtypes = [nusd_stage_t, String, String]
    nusd_stage_define_prim.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd.h: 203
if _libs["nanousd"].has("nusd_stage_path_is_valid_prim", "cdecl"):
    nusd_stage_path_is_valid_prim = _libs["nanousd"].get("nusd_stage_path_is_valid_prim", "cdecl")
    nusd_stage_path_is_valid_prim.argtypes = [nusd_stage_t, String]
    nusd_stage_path_is_valid_prim.restype = c_bool

# /home/anders/code/nanousd/nanousd.h: 206
if _libs["nanousd"].has("nusd_stage_traverse", "cdecl"):
    nusd_stage_traverse = _libs["nanousd"].get("nusd_stage_traverse", "cdecl")
    nusd_stage_traverse.argtypes = [nusd_stage_t, POINTER(nusd_prim_iterator_t)]
    nusd_stage_traverse.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd.h: 209
if _libs["nanousd"].has("nusd_prim_iterator_next", "cdecl"):
    nusd_prim_iterator_next = _libs["nanousd"].get("nusd_prim_iterator_next", "cdecl")
    nusd_prim_iterator_next.argtypes = [nusd_prim_iterator_t, POINTER(POINTER(c_char))]
    nusd_prim_iterator_next.restype = c_bool

# /home/anders/code/nanousd/nanousd.h: 212
if _libs["nanousd"].has("nusd_prim_iterator_destroy", "cdecl"):
    nusd_prim_iterator_destroy = _libs["nanousd"].get("nusd_prim_iterator_destroy", "cdecl")
    nusd_prim_iterator_destroy.argtypes = [nusd_prim_iterator_t]
    nusd_prim_iterator_destroy.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd.h: 215
if _libs["nanousd"].has("nusd_prim_get_properties", "cdecl"):
    nusd_prim_get_properties = _libs["nanousd"].get("nusd_prim_get_properties", "cdecl")
    nusd_prim_get_properties.argtypes = [nusd_stage_t, String, POINTER(nusd_property_iterator_t)]
    nusd_prim_get_properties.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd.h: 218
if _libs["nanousd"].has("nusd_prim_create_property", "cdecl"):
    nusd_prim_create_property = _libs["nanousd"].get("nusd_prim_create_property", "cdecl")
    nusd_prim_create_property.argtypes = [nusd_stage_t, String, String, nusd_type_t]
    nusd_prim_create_property.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd.h: 221
if _libs["nanousd"].has("nusd_property_iterator_next", "cdecl"):
    nusd_property_iterator_next = _libs["nanousd"].get("nusd_property_iterator_next", "cdecl")
    nusd_property_iterator_next.argtypes = [nusd_property_iterator_t, POINTER(POINTER(c_char)), POINTER(nusd_type_t)]
    nusd_property_iterator_next.restype = c_bool

# /home/anders/code/nanousd/nanousd.h: 224
if _libs["nanousd"].has("nusd_property_iterator_destroy", "cdecl"):
    nusd_property_iterator_destroy = _libs["nanousd"].get("nusd_property_iterator_destroy", "cdecl")
    nusd_property_iterator_destroy.argtypes = [nusd_property_iterator_t]
    nusd_property_iterator_destroy.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd.h: 227
if _libs["nanousd"].has("nusd_property_get_type", "cdecl"):
    nusd_property_get_type = _libs["nanousd"].get("nusd_property_get_type", "cdecl")
    nusd_property_get_type.argtypes = [nusd_stage_t, String, POINTER(nusd_type_t)]
    nusd_property_get_type.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd.h: 230
if _libs["nanousd"].has("nusd_prim_get_attributes", "cdecl"):
    nusd_prim_get_attributes = _libs["nanousd"].get("nusd_prim_get_attributes", "cdecl")
    nusd_prim_get_attributes.argtypes = [nusd_stage_t, String, POINTER(nusd_attribute_iterator_t)]
    nusd_prim_get_attributes.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd.h: 233
if _libs["nanousd"].has("nusd_attribute_iterator_next", "cdecl"):
    nusd_attribute_iterator_next = _libs["nanousd"].get("nusd_attribute_iterator_next", "cdecl")
    nusd_attribute_iterator_next.argtypes = [nusd_attribute_iterator_t, POINTER(POINTER(c_char))]
    nusd_attribute_iterator_next.restype = c_bool

# /home/anders/code/nanousd/nanousd.h: 236
if _libs["nanousd"].has("nusd_attribute_iterator_destroy", "cdecl"):
    nusd_attribute_iterator_destroy = _libs["nanousd"].get("nusd_attribute_iterator_destroy", "cdecl")
    nusd_attribute_iterator_destroy.argtypes = [nusd_attribute_iterator_t]
    nusd_attribute_iterator_destroy.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd.h: 239
if _libs["nanousd"].has("nusd_attribute_get_token", "cdecl"):
    nusd_attribute_get_token = _libs["nanousd"].get("nusd_attribute_get_token", "cdecl")
    nusd_attribute_get_token.argtypes = [nusd_stage_t, String, POINTER(POINTER(c_char))]
    nusd_attribute_get_token.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd.h: 242
if _libs["nanousd"].has("nusd_attribute_get_token_array", "cdecl"):
    nusd_attribute_get_token_array = _libs["nanousd"].get("nusd_attribute_get_token_array", "cdecl")
    nusd_attribute_get_token_array.argtypes = [nusd_stage_t, String, POINTER(nusd_token_array_t)]
    nusd_attribute_get_token_array.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd.h: 246
if _libs["nanousd"].has("nusd_attribute_get_float", "cdecl"):
    nusd_attribute_get_float = _libs["nanousd"].get("nusd_attribute_get_float", "cdecl")
    nusd_attribute_get_float.argtypes = [nusd_stage_t, String, POINTER(c_float)]
    nusd_attribute_get_float.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd.h: 249
if _libs["nanousd"].has("nusd_attribute_get_float_array", "cdecl"):
    nusd_attribute_get_float_array = _libs["nanousd"].get("nusd_attribute_get_float_array", "cdecl")
    nusd_attribute_get_float_array.argtypes = [nusd_stage_t, String, POINTER(nusd_float_array_t)]
    nusd_attribute_get_float_array.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd.h: 252
if _libs["nanousd"].has("nusd_float_array_size", "cdecl"):
    nusd_float_array_size = _libs["nanousd"].get("nusd_float_array_size", "cdecl")
    nusd_float_array_size.argtypes = [nusd_float_array_t]
    nusd_float_array_size.restype = c_size_t

# /home/anders/code/nanousd/nanousd.h: 255
if _libs["nanousd"].has("nusd_float_array_data", "cdecl"):
    nusd_float_array_data = _libs["nanousd"].get("nusd_float_array_data", "cdecl")
    nusd_float_array_data.argtypes = [nusd_float_array_t]
    nusd_float_array_data.restype = POINTER(c_float)

# /home/anders/code/nanousd/nanousd.h: 258
if _libs["nanousd"].has("nusd_float_array_destroy", "cdecl"):
    nusd_float_array_destroy = _libs["nanousd"].get("nusd_float_array_destroy", "cdecl")
    nusd_float_array_destroy.argtypes = [nusd_float_array_t]
    nusd_float_array_destroy.restype = None

# /home/anders/code/nanousd/nanousd.h: 261
if _libs["nanousd"].has("nusd_attribute_get_float2", "cdecl"):
    nusd_attribute_get_float2 = _libs["nanousd"].get("nusd_attribute_get_float2", "cdecl")
    nusd_attribute_get_float2.argtypes = [nusd_stage_t, String, POINTER(c_float)]
    nusd_attribute_get_float2.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd.h: 264
if _libs["nanousd"].has("nusd_attribute_get_float2_array", "cdecl"):
    nusd_attribute_get_float2_array = _libs["nanousd"].get("nusd_attribute_get_float2_array", "cdecl")
    nusd_attribute_get_float2_array.argtypes = [nusd_stage_t, String, POINTER(nusd_float2_array_t)]
    nusd_attribute_get_float2_array.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd.h: 267
if _libs["nanousd"].has("nusd_float2_array_size", "cdecl"):
    nusd_float2_array_size = _libs["nanousd"].get("nusd_float2_array_size", "cdecl")
    nusd_float2_array_size.argtypes = [nusd_float2_array_t]
    nusd_float2_array_size.restype = c_size_t

# /home/anders/code/nanousd/nanousd.h: 270
if _libs["nanousd"].has("nusd_float2_array_data", "cdecl"):
    nusd_float2_array_data = _libs["nanousd"].get("nusd_float2_array_data", "cdecl")
    nusd_float2_array_data.argtypes = [nusd_float2_array_t]
    nusd_float2_array_data.restype = POINTER(c_float)

# /home/anders/code/nanousd/nanousd.h: 273
if _libs["nanousd"].has("nusd_float2_array_destroy", "cdecl"):
    nusd_float2_array_destroy = _libs["nanousd"].get("nusd_float2_array_destroy", "cdecl")
    nusd_float2_array_destroy.argtypes = [nusd_float2_array_t]
    nusd_float2_array_destroy.restype = None

# /home/anders/code/nanousd/nanousd.h: 276
if _libs["nanousd"].has("nusd_attribute_get_float3", "cdecl"):
    nusd_attribute_get_float3 = _libs["nanousd"].get("nusd_attribute_get_float3", "cdecl")
    nusd_attribute_get_float3.argtypes = [nusd_stage_t, String, POINTER(c_float)]
    nusd_attribute_get_float3.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd.h: 279
if _libs["nanousd"].has("nusd_attribute_get_float3_array", "cdecl"):
    nusd_attribute_get_float3_array = _libs["nanousd"].get("nusd_attribute_get_float3_array", "cdecl")
    nusd_attribute_get_float3_array.argtypes = [nusd_stage_t, String, POINTER(nusd_float3_array_t)]
    nusd_attribute_get_float3_array.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd.h: 282
if _libs["nanousd"].has("nusd_float3_array_size", "cdecl"):
    nusd_float3_array_size = _libs["nanousd"].get("nusd_float3_array_size", "cdecl")
    nusd_float3_array_size.argtypes = [nusd_float3_array_t]
    nusd_float3_array_size.restype = c_size_t

# /home/anders/code/nanousd/nanousd.h: 285
if _libs["nanousd"].has("nusd_float3_array_data", "cdecl"):
    nusd_float3_array_data = _libs["nanousd"].get("nusd_float3_array_data", "cdecl")
    nusd_float3_array_data.argtypes = [nusd_float3_array_t]
    nusd_float3_array_data.restype = POINTER(c_float)

# /home/anders/code/nanousd/nanousd.h: 288
if _libs["nanousd"].has("nusd_float3_array_destroy", "cdecl"):
    nusd_float3_array_destroy = _libs["nanousd"].get("nusd_float3_array_destroy", "cdecl")
    nusd_float3_array_destroy.argtypes = [nusd_float3_array_t]
    nusd_float3_array_destroy.restype = None

# /home/anders/code/nanousd/nanousd.h: 291
if _libs["nanousd"].has("nusd_attribute_get_float4", "cdecl"):
    nusd_attribute_get_float4 = _libs["nanousd"].get("nusd_attribute_get_float4", "cdecl")
    nusd_attribute_get_float4.argtypes = [nusd_stage_t, String, POINTER(c_float)]
    nusd_attribute_get_float4.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd.h: 294
if _libs["nanousd"].has("nusd_attribute_get_float4_array", "cdecl"):
    nusd_attribute_get_float4_array = _libs["nanousd"].get("nusd_attribute_get_float4_array", "cdecl")
    nusd_attribute_get_float4_array.argtypes = [nusd_stage_t, String, POINTER(nusd_float4_array_t)]
    nusd_attribute_get_float4_array.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd.h: 297
if _libs["nanousd"].has("nusd_float4_array_size", "cdecl"):
    nusd_float4_array_size = _libs["nanousd"].get("nusd_float4_array_size", "cdecl")
    nusd_float4_array_size.argtypes = [nusd_float4_array_t]
    nusd_float4_array_size.restype = c_size_t

# /home/anders/code/nanousd/nanousd.h: 300
if _libs["nanousd"].has("nusd_float4_array_data", "cdecl"):
    nusd_float4_array_data = _libs["nanousd"].get("nusd_float4_array_data", "cdecl")
    nusd_float4_array_data.argtypes = [nusd_float4_array_t]
    nusd_float4_array_data.restype = POINTER(c_float)

# /home/anders/code/nanousd/nanousd.h: 303
if _libs["nanousd"].has("nusd_float4_array_destroy", "cdecl"):
    nusd_float4_array_destroy = _libs["nanousd"].get("nusd_float4_array_destroy", "cdecl")
    nusd_float4_array_destroy.argtypes = [nusd_float4_array_t]
    nusd_float4_array_destroy.restype = None

# /home/anders/code/nanousd/nanousd.h: 306
if _libs["nanousd"].has("nusd_attribute_set_float", "cdecl"):
    nusd_attribute_set_float = _libs["nanousd"].get("nusd_attribute_set_float", "cdecl")
    nusd_attribute_set_float.argtypes = [nusd_stage_t, String, c_float]
    nusd_attribute_set_float.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd.h: 309
if _libs["nanousd"].has("nusd_attribute_set_float_array", "cdecl"):
    nusd_attribute_set_float_array = _libs["nanousd"].get("nusd_attribute_set_float_array", "cdecl")
    nusd_attribute_set_float_array.argtypes = [nusd_stage_t, String, POINTER(c_float), c_size_t]
    nusd_attribute_set_float_array.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd.h: 312
if _libs["nanousd"].has("nusd_attribute_set_float2", "cdecl"):
    nusd_attribute_set_float2 = _libs["nanousd"].get("nusd_attribute_set_float2", "cdecl")
    nusd_attribute_set_float2.argtypes = [nusd_stage_t, String, POINTER(c_float)]
    nusd_attribute_set_float2.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd.h: 315
if _libs["nanousd"].has("nusd_attribute_set_float2_array", "cdecl"):
    nusd_attribute_set_float2_array = _libs["nanousd"].get("nusd_attribute_set_float2_array", "cdecl")
    nusd_attribute_set_float2_array.argtypes = [nusd_stage_t, String, POINTER(c_float), c_size_t]
    nusd_attribute_set_float2_array.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd.h: 318
if _libs["nanousd"].has("nusd_attribute_set_float3", "cdecl"):
    nusd_attribute_set_float3 = _libs["nanousd"].get("nusd_attribute_set_float3", "cdecl")
    nusd_attribute_set_float3.argtypes = [nusd_stage_t, String, POINTER(c_float)]
    nusd_attribute_set_float3.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd.h: 321
if _libs["nanousd"].has("nusd_attribute_set_float3_array", "cdecl"):
    nusd_attribute_set_float3_array = _libs["nanousd"].get("nusd_attribute_set_float3_array", "cdecl")
    nusd_attribute_set_float3_array.argtypes = [nusd_stage_t, String, POINTER(c_float), c_size_t]
    nusd_attribute_set_float3_array.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd.h: 324
if _libs["nanousd"].has("nusd_attribute_set_float4", "cdecl"):
    nusd_attribute_set_float4 = _libs["nanousd"].get("nusd_attribute_set_float4", "cdecl")
    nusd_attribute_set_float4.argtypes = [nusd_stage_t, String, POINTER(c_float)]
    nusd_attribute_set_float4.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd.h: 327
if _libs["nanousd"].has("nusd_attribute_set_float4_array", "cdecl"):
    nusd_attribute_set_float4_array = _libs["nanousd"].get("nusd_attribute_set_float4_array", "cdecl")
    nusd_attribute_set_float4_array.argtypes = [nusd_stage_t, String, POINTER(c_float), c_size_t]
    nusd_attribute_set_float4_array.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd.h: 331
if _libs["nanousd"].has("nusd_attribute_get_double", "cdecl"):
    nusd_attribute_get_double = _libs["nanousd"].get("nusd_attribute_get_double", "cdecl")
    nusd_attribute_get_double.argtypes = [nusd_stage_t, String, POINTER(c_double)]
    nusd_attribute_get_double.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd.h: 334
if _libs["nanousd"].has("nusd_attribute_get_double_array", "cdecl"):
    nusd_attribute_get_double_array = _libs["nanousd"].get("nusd_attribute_get_double_array", "cdecl")
    nusd_attribute_get_double_array.argtypes = [nusd_stage_t, String, POINTER(nusd_double_array_t)]
    nusd_attribute_get_double_array.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd.h: 337
if _libs["nanousd"].has("nusd_double_array_size", "cdecl"):
    nusd_double_array_size = _libs["nanousd"].get("nusd_double_array_size", "cdecl")
    nusd_double_array_size.argtypes = [nusd_double_array_t]
    nusd_double_array_size.restype = c_size_t

# /home/anders/code/nanousd/nanousd.h: 340
if _libs["nanousd"].has("nusd_double_array_data", "cdecl"):
    nusd_double_array_data = _libs["nanousd"].get("nusd_double_array_data", "cdecl")
    nusd_double_array_data.argtypes = [nusd_double_array_t]
    nusd_double_array_data.restype = POINTER(c_double)

# /home/anders/code/nanousd/nanousd.h: 343
if _libs["nanousd"].has("nusd_double_array_destroy", "cdecl"):
    nusd_double_array_destroy = _libs["nanousd"].get("nusd_double_array_destroy", "cdecl")
    nusd_double_array_destroy.argtypes = [nusd_double_array_t]
    nusd_double_array_destroy.restype = None

# /home/anders/code/nanousd/nanousd.h: 346
if _libs["nanousd"].has("nusd_attribute_get_double2", "cdecl"):
    nusd_attribute_get_double2 = _libs["nanousd"].get("nusd_attribute_get_double2", "cdecl")
    nusd_attribute_get_double2.argtypes = [nusd_stage_t, String, POINTER(c_double)]
    nusd_attribute_get_double2.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd.h: 349
if _libs["nanousd"].has("nusd_attribute_get_double2_array", "cdecl"):
    nusd_attribute_get_double2_array = _libs["nanousd"].get("nusd_attribute_get_double2_array", "cdecl")
    nusd_attribute_get_double2_array.argtypes = [nusd_stage_t, String, POINTER(nusd_double2_array_t)]
    nusd_attribute_get_double2_array.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd.h: 352
if _libs["nanousd"].has("nusd_double2_array_size", "cdecl"):
    nusd_double2_array_size = _libs["nanousd"].get("nusd_double2_array_size", "cdecl")
    nusd_double2_array_size.argtypes = [nusd_double2_array_t]
    nusd_double2_array_size.restype = c_size_t

# /home/anders/code/nanousd/nanousd.h: 355
if _libs["nanousd"].has("nusd_double2_array_data", "cdecl"):
    nusd_double2_array_data = _libs["nanousd"].get("nusd_double2_array_data", "cdecl")
    nusd_double2_array_data.argtypes = [nusd_double2_array_t]
    nusd_double2_array_data.restype = POINTER(c_double)

# /home/anders/code/nanousd/nanousd.h: 358
if _libs["nanousd"].has("nusd_double2_array_destroy", "cdecl"):
    nusd_double2_array_destroy = _libs["nanousd"].get("nusd_double2_array_destroy", "cdecl")
    nusd_double2_array_destroy.argtypes = [nusd_double2_array_t]
    nusd_double2_array_destroy.restype = None

# /home/anders/code/nanousd/nanousd.h: 361
if _libs["nanousd"].has("nusd_attribute_get_double3", "cdecl"):
    nusd_attribute_get_double3 = _libs["nanousd"].get("nusd_attribute_get_double3", "cdecl")
    nusd_attribute_get_double3.argtypes = [nusd_stage_t, String, POINTER(c_double)]
    nusd_attribute_get_double3.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd.h: 364
if _libs["nanousd"].has("nusd_attribute_get_double3_array", "cdecl"):
    nusd_attribute_get_double3_array = _libs["nanousd"].get("nusd_attribute_get_double3_array", "cdecl")
    nusd_attribute_get_double3_array.argtypes = [nusd_stage_t, String, POINTER(nusd_double3_array_t)]
    nusd_attribute_get_double3_array.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd.h: 367
if _libs["nanousd"].has("nusd_double3_array_size", "cdecl"):
    nusd_double3_array_size = _libs["nanousd"].get("nusd_double3_array_size", "cdecl")
    nusd_double3_array_size.argtypes = [nusd_double3_array_t]
    nusd_double3_array_size.restype = c_size_t

# /home/anders/code/nanousd/nanousd.h: 370
if _libs["nanousd"].has("nusd_double3_array_data", "cdecl"):
    nusd_double3_array_data = _libs["nanousd"].get("nusd_double3_array_data", "cdecl")
    nusd_double3_array_data.argtypes = [nusd_double3_array_t]
    nusd_double3_array_data.restype = POINTER(c_double)

# /home/anders/code/nanousd/nanousd.h: 373
if _libs["nanousd"].has("nusd_double3_array_destroy", "cdecl"):
    nusd_double3_array_destroy = _libs["nanousd"].get("nusd_double3_array_destroy", "cdecl")
    nusd_double3_array_destroy.argtypes = [nusd_double3_array_t]
    nusd_double3_array_destroy.restype = None

# /home/anders/code/nanousd/nanousd.h: 376
if _libs["nanousd"].has("nusd_attribute_get_double4", "cdecl"):
    nusd_attribute_get_double4 = _libs["nanousd"].get("nusd_attribute_get_double4", "cdecl")
    nusd_attribute_get_double4.argtypes = [nusd_stage_t, String, POINTER(c_double)]
    nusd_attribute_get_double4.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd.h: 379
if _libs["nanousd"].has("nusd_attribute_get_double4_array", "cdecl"):
    nusd_attribute_get_double4_array = _libs["nanousd"].get("nusd_attribute_get_double4_array", "cdecl")
    nusd_attribute_get_double4_array.argtypes = [nusd_stage_t, String, POINTER(nusd_double4_array_t)]
    nusd_attribute_get_double4_array.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd.h: 382
if _libs["nanousd"].has("nusd_double4_array_size", "cdecl"):
    nusd_double4_array_size = _libs["nanousd"].get("nusd_double4_array_size", "cdecl")
    nusd_double4_array_size.argtypes = [nusd_double4_array_t]
    nusd_double4_array_size.restype = c_size_t

# /home/anders/code/nanousd/nanousd.h: 385
if _libs["nanousd"].has("nusd_double4_array_data", "cdecl"):
    nusd_double4_array_data = _libs["nanousd"].get("nusd_double4_array_data", "cdecl")
    nusd_double4_array_data.argtypes = [nusd_double4_array_t]
    nusd_double4_array_data.restype = POINTER(c_double)

# /home/anders/code/nanousd/nanousd.h: 388
if _libs["nanousd"].has("nusd_double4_array_destroy", "cdecl"):
    nusd_double4_array_destroy = _libs["nanousd"].get("nusd_double4_array_destroy", "cdecl")
    nusd_double4_array_destroy.argtypes = [nusd_double4_array_t]
    nusd_double4_array_destroy.restype = None

# /home/anders/code/nanousd/nanousd.h: 393
if _libs["nanousd"].has("nusd_attribute_get_int", "cdecl"):
    nusd_attribute_get_int = _libs["nanousd"].get("nusd_attribute_get_int", "cdecl")
    nusd_attribute_get_int.argtypes = [nusd_stage_t, String, POINTER(c_int)]
    nusd_attribute_get_int.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd.h: 396
if _libs["nanousd"].has("nusd_attribute_get_int_array", "cdecl"):
    nusd_attribute_get_int_array = _libs["nanousd"].get("nusd_attribute_get_int_array", "cdecl")
    nusd_attribute_get_int_array.argtypes = [nusd_stage_t, String, POINTER(nusd_int_array_t)]
    nusd_attribute_get_int_array.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd.h: 399
if _libs["nanousd"].has("nusd_int_array_size", "cdecl"):
    nusd_int_array_size = _libs["nanousd"].get("nusd_int_array_size", "cdecl")
    nusd_int_array_size.argtypes = [nusd_int_array_t]
    nusd_int_array_size.restype = c_size_t

# /home/anders/code/nanousd/nanousd.h: 402
if _libs["nanousd"].has("nusd_int_array_data", "cdecl"):
    nusd_int_array_data = _libs["nanousd"].get("nusd_int_array_data", "cdecl")
    nusd_int_array_data.argtypes = [nusd_int_array_t]
    nusd_int_array_data.restype = POINTER(c_int)

# /home/anders/code/nanousd/nanousd.h: 405
if _libs["nanousd"].has("nusd_int_array_destroy", "cdecl"):
    nusd_int_array_destroy = _libs["nanousd"].get("nusd_int_array_destroy", "cdecl")
    nusd_int_array_destroy.argtypes = [nusd_int_array_t]
    nusd_int_array_destroy.restype = None

# /home/anders/code/nanousd/nanousd.h: 408
if _libs["nanousd"].has("nusd_attribute_get_int2", "cdecl"):
    nusd_attribute_get_int2 = _libs["nanousd"].get("nusd_attribute_get_int2", "cdecl")
    nusd_attribute_get_int2.argtypes = [nusd_stage_t, String, POINTER(c_int)]
    nusd_attribute_get_int2.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd.h: 411
if _libs["nanousd"].has("nusd_attribute_get_int2_array", "cdecl"):
    nusd_attribute_get_int2_array = _libs["nanousd"].get("nusd_attribute_get_int2_array", "cdecl")
    nusd_attribute_get_int2_array.argtypes = [nusd_stage_t, String, POINTER(nusd_int2_array_t)]
    nusd_attribute_get_int2_array.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd.h: 414
if _libs["nanousd"].has("nusd_int2_array_size", "cdecl"):
    nusd_int2_array_size = _libs["nanousd"].get("nusd_int2_array_size", "cdecl")
    nusd_int2_array_size.argtypes = [nusd_int2_array_t]
    nusd_int2_array_size.restype = c_size_t

# /home/anders/code/nanousd/nanousd.h: 417
if _libs["nanousd"].has("nusd_int2_array_data", "cdecl"):
    nusd_int2_array_data = _libs["nanousd"].get("nusd_int2_array_data", "cdecl")
    nusd_int2_array_data.argtypes = [nusd_int2_array_t]
    nusd_int2_array_data.restype = POINTER(c_int)

# /home/anders/code/nanousd/nanousd.h: 420
if _libs["nanousd"].has("nusd_int2_array_destroy", "cdecl"):
    nusd_int2_array_destroy = _libs["nanousd"].get("nusd_int2_array_destroy", "cdecl")
    nusd_int2_array_destroy.argtypes = [nusd_int2_array_t]
    nusd_int2_array_destroy.restype = None

# /home/anders/code/nanousd/nanousd.h: 423
if _libs["nanousd"].has("nusd_attribute_get_int3", "cdecl"):
    nusd_attribute_get_int3 = _libs["nanousd"].get("nusd_attribute_get_int3", "cdecl")
    nusd_attribute_get_int3.argtypes = [nusd_stage_t, String, POINTER(c_int)]
    nusd_attribute_get_int3.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd.h: 426
if _libs["nanousd"].has("nusd_attribute_get_int3_array", "cdecl"):
    nusd_attribute_get_int3_array = _libs["nanousd"].get("nusd_attribute_get_int3_array", "cdecl")
    nusd_attribute_get_int3_array.argtypes = [nusd_stage_t, String, POINTER(nusd_int3_array_t)]
    nusd_attribute_get_int3_array.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd.h: 429
if _libs["nanousd"].has("nusd_int3_array_size", "cdecl"):
    nusd_int3_array_size = _libs["nanousd"].get("nusd_int3_array_size", "cdecl")
    nusd_int3_array_size.argtypes = [nusd_int3_array_t]
    nusd_int3_array_size.restype = c_size_t

# /home/anders/code/nanousd/nanousd.h: 432
if _libs["nanousd"].has("nusd_int3_array_data", "cdecl"):
    nusd_int3_array_data = _libs["nanousd"].get("nusd_int3_array_data", "cdecl")
    nusd_int3_array_data.argtypes = [nusd_int3_array_t]
    nusd_int3_array_data.restype = POINTER(c_int)

# /home/anders/code/nanousd/nanousd.h: 435
if _libs["nanousd"].has("nusd_int3_array_destroy", "cdecl"):
    nusd_int3_array_destroy = _libs["nanousd"].get("nusd_int3_array_destroy", "cdecl")
    nusd_int3_array_destroy.argtypes = [nusd_int3_array_t]
    nusd_int3_array_destroy.restype = None

# /home/anders/code/nanousd/nanousd.h: 438
if _libs["nanousd"].has("nusd_attribute_get_int4", "cdecl"):
    nusd_attribute_get_int4 = _libs["nanousd"].get("nusd_attribute_get_int4", "cdecl")
    nusd_attribute_get_int4.argtypes = [nusd_stage_t, String, POINTER(c_int)]
    nusd_attribute_get_int4.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd.h: 441
if _libs["nanousd"].has("nusd_attribute_get_int4_array", "cdecl"):
    nusd_attribute_get_int4_array = _libs["nanousd"].get("nusd_attribute_get_int4_array", "cdecl")
    nusd_attribute_get_int4_array.argtypes = [nusd_stage_t, String, POINTER(nusd_int4_array_t)]
    nusd_attribute_get_int4_array.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd.h: 444
if _libs["nanousd"].has("nusd_int4_array_size", "cdecl"):
    nusd_int4_array_size = _libs["nanousd"].get("nusd_int4_array_size", "cdecl")
    nusd_int4_array_size.argtypes = [nusd_int4_array_t]
    nusd_int4_array_size.restype = c_size_t

# /home/anders/code/nanousd/nanousd.h: 447
if _libs["nanousd"].has("nusd_int4_array_data", "cdecl"):
    nusd_int4_array_data = _libs["nanousd"].get("nusd_int4_array_data", "cdecl")
    nusd_int4_array_data.argtypes = [nusd_int4_array_t]
    nusd_int4_array_data.restype = POINTER(c_int)

# /home/anders/code/nanousd/nanousd.h: 450
if _libs["nanousd"].has("nusd_int4_array_destroy", "cdecl"):
    nusd_int4_array_destroy = _libs["nanousd"].get("nusd_int4_array_destroy", "cdecl")
    nusd_int4_array_destroy.argtypes = [nusd_int4_array_t]
    nusd_int4_array_destroy.restype = None

# /home/anders/code/nanousd/nanousd.h: 454
for _lib in _libs.values():
    if not _lib.has("nusd_attribute_get_int64", "cdecl"):
        continue
    nusd_attribute_get_int64 = _lib.get("nusd_attribute_get_int64", "cdecl")
    nusd_attribute_get_int64.argtypes = [nusd_stage_t, String, POINTER(c_int64)]
    nusd_attribute_get_int64.restype = nusd_result_t
    break

# /home/anders/code/nanousd/nanousd.h: 457
for _lib in _libs.values():
    if not _lib.has("nusd_attribute_get_int64_array", "cdecl"):
        continue
    nusd_attribute_get_int64_array = _lib.get("nusd_attribute_get_int64_array", "cdecl")
    nusd_attribute_get_int64_array.argtypes = [nusd_stage_t, String, POINTER(nusd_int64_array_t)]
    nusd_attribute_get_int64_array.restype = nusd_result_t
    break

# /home/anders/code/nanousd/nanousd.h: 460
for _lib in _libs.values():
    if not _lib.has("nusd_int64_array_size", "cdecl"):
        continue
    nusd_int64_array_size = _lib.get("nusd_int64_array_size", "cdecl")
    nusd_int64_array_size.argtypes = [nusd_int64_array_t]
    nusd_int64_array_size.restype = c_size_t
    break

# /home/anders/code/nanousd/nanousd.h: 463
for _lib in _libs.values():
    if not _lib.has("nusd_int64_array_data", "cdecl"):
        continue
    nusd_int64_array_data = _lib.get("nusd_int64_array_data", "cdecl")
    nusd_int64_array_data.argtypes = [nusd_int64_array_t]
    nusd_int64_array_data.restype = POINTER(c_int64)
    break

# /home/anders/code/nanousd/nanousd.h: 466
for _lib in _libs.values():
    if not _lib.has("nusd_int64_array_destroy", "cdecl"):
        continue
    nusd_int64_array_destroy = _lib.get("nusd_int64_array_destroy", "cdecl")
    nusd_int64_array_destroy.argtypes = [nusd_int64_array_t]
    nusd_int64_array_destroy.restype = None
    break

# /home/anders/code/nanousd/nanousd.h: 470
if _libs["nanousd"].has("nusd_attribute_set_int", "cdecl"):
    nusd_attribute_set_int = _libs["nanousd"].get("nusd_attribute_set_int", "cdecl")
    nusd_attribute_set_int.argtypes = [nusd_stage_t, String, c_int]
    nusd_attribute_set_int.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd.h: 473
if _libs["nanousd"].has("nusd_attribute_set_int_array", "cdecl"):
    nusd_attribute_set_int_array = _libs["nanousd"].get("nusd_attribute_set_int_array", "cdecl")
    nusd_attribute_set_int_array.argtypes = [nusd_stage_t, String, POINTER(c_int), c_size_t]
    nusd_attribute_set_int_array.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd.h: 476
if _libs["nanousd"].has("nusd_attribute_set_int2", "cdecl"):
    nusd_attribute_set_int2 = _libs["nanousd"].get("nusd_attribute_set_int2", "cdecl")
    nusd_attribute_set_int2.argtypes = [nusd_stage_t, String, POINTER(c_int)]
    nusd_attribute_set_int2.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd.h: 479
if _libs["nanousd"].has("nusd_attribute_set_int2_array", "cdecl"):
    nusd_attribute_set_int2_array = _libs["nanousd"].get("nusd_attribute_set_int2_array", "cdecl")
    nusd_attribute_set_int2_array.argtypes = [nusd_stage_t, String, POINTER(c_int), c_size_t]
    nusd_attribute_set_int2_array.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd.h: 482
if _libs["nanousd"].has("nusd_attribute_set_int3", "cdecl"):
    nusd_attribute_set_int3 = _libs["nanousd"].get("nusd_attribute_set_int3", "cdecl")
    nusd_attribute_set_int3.argtypes = [nusd_stage_t, String, POINTER(c_int)]
    nusd_attribute_set_int3.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd.h: 485
if _libs["nanousd"].has("nusd_attribute_set_int3_array", "cdecl"):
    nusd_attribute_set_int3_array = _libs["nanousd"].get("nusd_attribute_set_int3_array", "cdecl")
    nusd_attribute_set_int3_array.argtypes = [nusd_stage_t, String, POINTER(c_int), c_size_t]
    nusd_attribute_set_int3_array.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd.h: 488
if _libs["nanousd"].has("nusd_attribute_set_int4", "cdecl"):
    nusd_attribute_set_int4 = _libs["nanousd"].get("nusd_attribute_set_int4", "cdecl")
    nusd_attribute_set_int4.argtypes = [nusd_stage_t, String, POINTER(c_int)]
    nusd_attribute_set_int4.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd.h: 491
if _libs["nanousd"].has("nusd_attribute_set_int4_array", "cdecl"):
    nusd_attribute_set_int4_array = _libs["nanousd"].get("nusd_attribute_set_int4_array", "cdecl")
    nusd_attribute_set_int4_array.argtypes = [nusd_stage_t, String, POINTER(c_int), c_size_t]
    nusd_attribute_set_int4_array.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd.h: 495
for _lib in _libs.values():
    if not _lib.has("nusd_attribute_set_int64", "cdecl"):
        continue
    nusd_attribute_set_int64 = _lib.get("nusd_attribute_set_int64", "cdecl")
    nusd_attribute_set_int64.argtypes = [nusd_stage_t, String, c_int64]
    nusd_attribute_set_int64.restype = nusd_result_t
    break

# /home/anders/code/nanousd/nanousd.h: 498
for _lib in _libs.values():
    if not _lib.has("nusd_attribute_set_int64_array", "cdecl"):
        continue
    nusd_attribute_set_int64_array = _lib.get("nusd_attribute_set_int64_array", "cdecl")
    nusd_attribute_set_int64_array.argtypes = [nusd_stage_t, String, POINTER(c_int64), c_size_t]
    nusd_attribute_set_int64_array.restype = nusd_result_t
    break

# /home/anders/code/nanousd/nanousd.h: 502
if _libs["nanousd"].has("nusd_attribute_get_bool", "cdecl"):
    nusd_attribute_get_bool = _libs["nanousd"].get("nusd_attribute_get_bool", "cdecl")
    nusd_attribute_get_bool.argtypes = [nusd_stage_t, String, POINTER(c_bool)]
    nusd_attribute_get_bool.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd.h: 505
if _libs["nanousd"].has("nusd_attribute_get_bool_array", "cdecl"):
    nusd_attribute_get_bool_array = _libs["nanousd"].get("nusd_attribute_get_bool_array", "cdecl")
    nusd_attribute_get_bool_array.argtypes = [nusd_stage_t, String, POINTER(nusd_bool_array_t)]
    nusd_attribute_get_bool_array.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd.h: 508
if _libs["nanousd"].has("nusd_bool_array_size", "cdecl"):
    nusd_bool_array_size = _libs["nanousd"].get("nusd_bool_array_size", "cdecl")
    nusd_bool_array_size.argtypes = [nusd_bool_array_t]
    nusd_bool_array_size.restype = c_size_t

# /home/anders/code/nanousd/nanousd.h: 511
if _libs["nanousd"].has("nusd_bool_array_data", "cdecl"):
    nusd_bool_array_data = _libs["nanousd"].get("nusd_bool_array_data", "cdecl")
    nusd_bool_array_data.argtypes = [nusd_bool_array_t]
    nusd_bool_array_data.restype = POINTER(c_bool)

# /home/anders/code/nanousd/nanousd.h: 514
if _libs["nanousd"].has("nusd_bool_array_destroy", "cdecl"):
    nusd_bool_array_destroy = _libs["nanousd"].get("nusd_bool_array_destroy", "cdecl")
    nusd_bool_array_destroy.argtypes = [nusd_bool_array_t]
    nusd_bool_array_destroy.restype = None

# /home/anders/code/nanousd/nanousd.h: 519
if _libs["nanousd"].has("nusd_token_array_size", "cdecl"):
    nusd_token_array_size = _libs["nanousd"].get("nusd_token_array_size", "cdecl")
    nusd_token_array_size.argtypes = [nusd_token_array_t]
    nusd_token_array_size.restype = c_size_t

# /home/anders/code/nanousd/nanousd.h: 522
if _libs["nanousd"].has("nusd_token_array_index", "cdecl"):
    nusd_token_array_index = _libs["nanousd"].get("nusd_token_array_index", "cdecl")
    nusd_token_array_index.argtypes = [nusd_token_array_t, c_size_t]
    nusd_token_array_index.restype = c_char_p

# /home/anders/code/nanousd/nanousd.h: 525
if _libs["nanousd"].has("nusd_token_array_destroy", "cdecl"):
    nusd_token_array_destroy = _libs["nanousd"].get("nusd_token_array_destroy", "cdecl")
    nusd_token_array_destroy.argtypes = [nusd_token_array_t]
    nusd_token_array_destroy.restype = None

# /home/anders/code/nanousd/nanousd.h: 528
if _libs["nanousd"].has("nusd_prim_get_relationships", "cdecl"):
    nusd_prim_get_relationships = _libs["nanousd"].get("nusd_prim_get_relationships", "cdecl")
    nusd_prim_get_relationships.argtypes = [nusd_stage_t, String, POINTER(nusd_relationship_iterator_t)]
    nusd_prim_get_relationships.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd.h: 531
if _libs["nanousd"].has("nusd_relationship_iterator_next", "cdecl"):
    nusd_relationship_iterator_next = _libs["nanousd"].get("nusd_relationship_iterator_next", "cdecl")
    nusd_relationship_iterator_next.argtypes = [nusd_relationship_iterator_t, POINTER(POINTER(c_char))]
    nusd_relationship_iterator_next.restype = c_bool

# /home/anders/code/nanousd/nanousd.h: 534
if _libs["nanousd"].has("nusd_relationship_iterator_destroy", "cdecl"):
    nusd_relationship_iterator_destroy = _libs["nanousd"].get("nusd_relationship_iterator_destroy", "cdecl")
    nusd_relationship_iterator_destroy.argtypes = [nusd_relationship_iterator_t]
    nusd_relationship_iterator_destroy.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd.h: 537
if _libs["nanousd"].has("nusd_relationship_get_targets", "cdecl"):
    nusd_relationship_get_targets = _libs["nanousd"].get("nusd_relationship_get_targets", "cdecl")
    nusd_relationship_get_targets.argtypes = [nusd_stage_t, String, POINTER(nusd_relationship_targets_iterator_t), POINTER(c_size_t)]
    nusd_relationship_get_targets.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd.h: 540
if _libs["nanousd"].has("nusd_relationship_targets_iterator_next", "cdecl"):
    nusd_relationship_targets_iterator_next = _libs["nanousd"].get("nusd_relationship_targets_iterator_next", "cdecl")
    nusd_relationship_targets_iterator_next.argtypes = [nusd_relationship_targets_iterator_t, POINTER(POINTER(c_char))]
    nusd_relationship_targets_iterator_next.restype = c_bool

# /home/anders/code/nanousd/nanousd.h: 543
if _libs["nanousd"].has("nusd_relationship_targets_iterator_destroy", "cdecl"):
    nusd_relationship_targets_iterator_destroy = _libs["nanousd"].get("nusd_relationship_targets_iterator_destroy", "cdecl")
    nusd_relationship_targets_iterator_destroy.argtypes = [nusd_relationship_targets_iterator_t]
    nusd_relationship_targets_iterator_destroy.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd.h: 546
if _libs["nanousd"].has("nusd_path_get_name", "cdecl"):
    nusd_path_get_name = _libs["nanousd"].get("nusd_path_get_name", "cdecl")
    nusd_path_get_name.argtypes = [String]
    nusd_path_get_name.restype = c_char_p

nusd_prim_iterator_s = struct_nusd_prim_iterator_s# /home/anders/code/nanousd/nanousd.h: 33

nusd_property_iterator_s = struct_nusd_property_iterator_s# /home/anders/code/nanousd/nanousd.h: 34

nusd_attribute_iterator_s = struct_nusd_attribute_iterator_s# /home/anders/code/nanousd/nanousd.h: 35

nusd_relationship_iterator_s = struct_nusd_relationship_iterator_s# /home/anders/code/nanousd/nanousd.h: 36

nusd_relationship_targets_iterator_s = struct_nusd_relationship_targets_iterator_s# /home/anders/code/nanousd/nanousd.h: 37

nusd_token_array_s = struct_nusd_token_array_s# /home/anders/code/nanousd/nanousd.h: 38

nusd_float_array_s = struct_nusd_float_array_s# /home/anders/code/nanousd/nanousd.h: 39

nusd_float2_array_s = struct_nusd_float2_array_s# /home/anders/code/nanousd/nanousd.h: 40

nusd_float3_array_s = struct_nusd_float3_array_s# /home/anders/code/nanousd/nanousd.h: 41

nusd_float4_array_s = struct_nusd_float4_array_s# /home/anders/code/nanousd/nanousd.h: 42

nusd_double_array_s = struct_nusd_double_array_s# /home/anders/code/nanousd/nanousd.h: 43

nusd_double2_array_s = struct_nusd_double2_array_s# /home/anders/code/nanousd/nanousd.h: 44

nusd_double3_array_s = struct_nusd_double3_array_s# /home/anders/code/nanousd/nanousd.h: 45

nusd_double4_array_s = struct_nusd_double4_array_s# /home/anders/code/nanousd/nanousd.h: 46

nusd_int_array_s = struct_nusd_int_array_s# /home/anders/code/nanousd/nanousd.h: 47

nusd_int2_array_s = struct_nusd_int2_array_s# /home/anders/code/nanousd/nanousd.h: 48

nusd_int3_array_s = struct_nusd_int3_array_s# /home/anders/code/nanousd/nanousd.h: 49

nusd_int4_array_s = struct_nusd_int4_array_s# /home/anders/code/nanousd/nanousd.h: 50

nusd_int64_array_s = struct_nusd_int64_array_s# /home/anders/code/nanousd/nanousd.h: 51

nusd_bool_array_s = struct_nusd_bool_array_s# /home/anders/code/nanousd/nanousd.h: 53

# No inserted files

# No prefix-stripping

