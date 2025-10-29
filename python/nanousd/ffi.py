r"""Wrapper for nanousd.h

Generated with:
/home/anders/code/nanousd/python/.venv/bin/ctypesgen -L../build -lnanousd -o nanousd/ffi.py /home/anders/code/nanousd/python/../nanousd.h /home/anders/code/nanousd/python/../nanousd-types.h /home/anders/code/nanousd/python/../nanousd-arrays.h /home/anders/code/nanousd/python/../nanousd-iterators.h /home/anders/code/nanousd/python/../nanousd-properties.h /home/anders/code/nanousd/python/../nanousd-cameras.h /home/anders/code/nanousd/python/../nanousd-materials.h

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

__uint64_t = c_ulong# /usr/include/x86_64-linux-gnu/bits/types.h: 45

uint64_t = __uint64_t# /usr/include/x86_64-linux-gnu/bits/stdint-uintn.h: 27

enum_nusd_result_e = c_int# /home/anders/code/nanousd/nanousd-types.h: 16

NUSD_RESULT_OK = 0# /home/anders/code/nanousd/nanousd-types.h: 16

NUSD_RESULT_INVALID_ATTRIBUTE_PATH = (NUSD_RESULT_OK + 1)# /home/anders/code/nanousd/nanousd-types.h: 16

NUSD_RESULT_INVALID_RELATIONSHIP_PATH = (NUSD_RESULT_INVALID_ATTRIBUTE_PATH + 1)# /home/anders/code/nanousd/nanousd-types.h: 16

NUSD_RESULT_INVALID_PRIM_PATH = (NUSD_RESULT_INVALID_RELATIONSHIP_PATH + 1)# /home/anders/code/nanousd/nanousd-types.h: 16

NUSD_RESULT_WRONG_TYPE = (NUSD_RESULT_INVALID_PRIM_PATH + 1)# /home/anders/code/nanousd/nanousd-types.h: 16

NUSD_RESULT_CREATE_STAGE_FAILED = (NUSD_RESULT_WRONG_TYPE + 1)# /home/anders/code/nanousd/nanousd-types.h: 16

NUSD_RESULT_OPEN_STAGE_FAILED = (NUSD_RESULT_CREATE_STAGE_FAILED + 1)# /home/anders/code/nanousd/nanousd-types.h: 16

NUSD_RESULT_DEFINE_PRIM_FAILED = (NUSD_RESULT_OPEN_STAGE_FAILED + 1)# /home/anders/code/nanousd/nanousd-types.h: 16

NUSD_RESULT_INVALID_PROPERTY_PATH = (NUSD_RESULT_DEFINE_PRIM_FAILED + 1)# /home/anders/code/nanousd/nanousd-types.h: 16

NUSD_RESULT_INVALID_PROPERTY_TYPE = (NUSD_RESULT_INVALID_PROPERTY_PATH + 1)# /home/anders/code/nanousd/nanousd-types.h: 16

NUSD_RESULT_CREATE_RELATIONSHIP_FAILED = (NUSD_RESULT_INVALID_PROPERTY_TYPE + 1)# /home/anders/code/nanousd/nanousd-types.h: 16

NUSD_RESULT_CREATE_ATTRIBUTE_FAILED = (NUSD_RESULT_CREATE_RELATIONSHIP_FAILED + 1)# /home/anders/code/nanousd/nanousd-types.h: 16

NUSD_RESULT_NULL_PARAMETER = (NUSD_RESULT_CREATE_ATTRIBUTE_FAILED + 1)# /home/anders/code/nanousd/nanousd-types.h: 16

NUSD_RESULT_CONNECTION_FAILED = (NUSD_RESULT_NULL_PARAMETER + 1)# /home/anders/code/nanousd/nanousd-types.h: 16

nusd_result_t = c_int# /home/anders/code/nanousd/nanousd-types.h: 32

nusd_type_t = String# /home/anders/code/nanousd/nanousd-types.h: 34

nusd_colorspace_t = String# /home/anders/code/nanousd/nanousd-types.h: 35

nusd_stage_t = POINTER(None)# /home/anders/code/nanousd/nanousd-types.h: 36

# /home/anders/code/nanousd/nanousd-types.h: 37
class struct_nusd_asset_path_s(Structure):
    pass

nusd_asset_path_t = POINTER(struct_nusd_asset_path_s)# /home/anders/code/nanousd/nanousd-types.h: 37

# /home/anders/code/nanousd/nanousd-types.h: 39
try:
    NUSD_TYPE_ASSET = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_ASSET")
except:
    pass

# /home/anders/code/nanousd/nanousd-types.h: 40
try:
    NUSD_TYPE_ASSETARRAY = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_ASSETARRAY")
except:
    pass

# /home/anders/code/nanousd/nanousd-types.h: 41
try:
    NUSD_TYPE_BOOL = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_BOOL")
except:
    pass

# /home/anders/code/nanousd/nanousd-types.h: 42
try:
    NUSD_TYPE_BOOLARRAY = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_BOOLARRAY")
except:
    pass

# /home/anders/code/nanousd/nanousd-types.h: 43
try:
    NUSD_TYPE_COLOR3D = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_COLOR3D")
except:
    pass

# /home/anders/code/nanousd/nanousd-types.h: 44
try:
    NUSD_TYPE_COLOR3DARRAY = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_COLOR3DARRAY")
except:
    pass

# /home/anders/code/nanousd/nanousd-types.h: 45
try:
    NUSD_TYPE_COLOR3F = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_COLOR3F")
except:
    pass

# /home/anders/code/nanousd/nanousd-types.h: 46
try:
    NUSD_TYPE_COLOR3FARRAY = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_COLOR3FARRAY")
except:
    pass

# /home/anders/code/nanousd/nanousd-types.h: 47
try:
    NUSD_TYPE_COLOR3H = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_COLOR3H")
except:
    pass

# /home/anders/code/nanousd/nanousd-types.h: 48
try:
    NUSD_TYPE_COLOR3HARRAY = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_COLOR3HARRAY")
except:
    pass

# /home/anders/code/nanousd/nanousd-types.h: 49
try:
    NUSD_TYPE_COLOR4D = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_COLOR4D")
except:
    pass

# /home/anders/code/nanousd/nanousd-types.h: 50
try:
    NUSD_TYPE_COLOR4DARRAY = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_COLOR4DARRAY")
except:
    pass

# /home/anders/code/nanousd/nanousd-types.h: 51
try:
    NUSD_TYPE_COLOR4F = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_COLOR4F")
except:
    pass

# /home/anders/code/nanousd/nanousd-types.h: 52
try:
    NUSD_TYPE_COLOR4FARRAY = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_COLOR4FARRAY")
except:
    pass

# /home/anders/code/nanousd/nanousd-types.h: 53
try:
    NUSD_TYPE_COLOR4H = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_COLOR4H")
except:
    pass

# /home/anders/code/nanousd/nanousd-types.h: 54
try:
    NUSD_TYPE_COLOR4HARRAY = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_COLOR4HARRAY")
except:
    pass

# /home/anders/code/nanousd/nanousd-types.h: 55
try:
    NUSD_TYPE_DOUBLE = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_DOUBLE")
except:
    pass

# /home/anders/code/nanousd/nanousd-types.h: 56
try:
    NUSD_TYPE_DOUBLE2 = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_DOUBLE2")
except:
    pass

# /home/anders/code/nanousd/nanousd-types.h: 57
try:
    NUSD_TYPE_DOUBLE2ARRAY = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_DOUBLE2ARRAY")
except:
    pass

# /home/anders/code/nanousd/nanousd-types.h: 58
try:
    NUSD_TYPE_DOUBLE3 = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_DOUBLE3")
except:
    pass

# /home/anders/code/nanousd/nanousd-types.h: 59
try:
    NUSD_TYPE_DOUBLE3ARRAY = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_DOUBLE3ARRAY")
except:
    pass

# /home/anders/code/nanousd/nanousd-types.h: 60
try:
    NUSD_TYPE_DOUBLE4 = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_DOUBLE4")
except:
    pass

# /home/anders/code/nanousd/nanousd-types.h: 61
try:
    NUSD_TYPE_DOUBLE4ARRAY = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_DOUBLE4ARRAY")
except:
    pass

# /home/anders/code/nanousd/nanousd-types.h: 62
try:
    NUSD_TYPE_DOUBLEARRAY = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_DOUBLEARRAY")
except:
    pass

# /home/anders/code/nanousd/nanousd-types.h: 63
try:
    NUSD_TYPE_FIND = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_FIND")
except:
    pass

# /home/anders/code/nanousd/nanousd-types.h: 64
try:
    NUSD_TYPE_FLOAT = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_FLOAT")
except:
    pass

# /home/anders/code/nanousd/nanousd-types.h: 65
try:
    NUSD_TYPE_FLOAT2 = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_FLOAT2")
except:
    pass

# /home/anders/code/nanousd/nanousd-types.h: 66
try:
    NUSD_TYPE_FLOAT2ARRAY = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_FLOAT2ARRAY")
except:
    pass

# /home/anders/code/nanousd/nanousd-types.h: 67
try:
    NUSD_TYPE_FLOAT3 = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_FLOAT3")
except:
    pass

# /home/anders/code/nanousd/nanousd-types.h: 68
try:
    NUSD_TYPE_FLOAT3ARRAY = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_FLOAT3ARRAY")
except:
    pass

# /home/anders/code/nanousd/nanousd-types.h: 69
try:
    NUSD_TYPE_FLOAT4 = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_FLOAT4")
except:
    pass

# /home/anders/code/nanousd/nanousd-types.h: 70
try:
    NUSD_TYPE_FLOAT4ARRAY = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_FLOAT4ARRAY")
except:
    pass

# /home/anders/code/nanousd/nanousd-types.h: 71
try:
    NUSD_TYPE_FLOATARRAY = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_FLOATARRAY")
except:
    pass

# /home/anders/code/nanousd/nanousd-types.h: 72
try:
    NUSD_TYPE_FRAME4D = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_FRAME4D")
except:
    pass

# /home/anders/code/nanousd/nanousd-types.h: 73
try:
    NUSD_TYPE_FRAME4DARRAY = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_FRAME4DARRAY")
except:
    pass

# /home/anders/code/nanousd/nanousd-types.h: 74
try:
    NUSD_TYPE_GROUP = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_GROUP")
except:
    pass

# /home/anders/code/nanousd/nanousd-types.h: 75
try:
    NUSD_TYPE_HALF = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_HALF")
except:
    pass

# /home/anders/code/nanousd/nanousd-types.h: 76
try:
    NUSD_TYPE_HALF2 = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_HALF2")
except:
    pass

# /home/anders/code/nanousd/nanousd-types.h: 77
try:
    NUSD_TYPE_HALF2ARRAY = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_HALF2ARRAY")
except:
    pass

# /home/anders/code/nanousd/nanousd-types.h: 78
try:
    NUSD_TYPE_HALF3 = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_HALF3")
except:
    pass

# /home/anders/code/nanousd/nanousd-types.h: 79
try:
    NUSD_TYPE_HALF3ARRAY = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_HALF3ARRAY")
except:
    pass

# /home/anders/code/nanousd/nanousd-types.h: 80
try:
    NUSD_TYPE_HALF4 = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_HALF4")
except:
    pass

# /home/anders/code/nanousd/nanousd-types.h: 81
try:
    NUSD_TYPE_HALF4ARRAY = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_HALF4ARRAY")
except:
    pass

# /home/anders/code/nanousd/nanousd-types.h: 82
try:
    NUSD_TYPE_HALFARRAY = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_HALFARRAY")
except:
    pass

# /home/anders/code/nanousd/nanousd-types.h: 83
try:
    NUSD_TYPE_INT = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_INT")
except:
    pass

# /home/anders/code/nanousd/nanousd-types.h: 84
try:
    NUSD_TYPE_INT2 = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_INT2")
except:
    pass

# /home/anders/code/nanousd/nanousd-types.h: 85
try:
    NUSD_TYPE_INT2ARRAY = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_INT2ARRAY")
except:
    pass

# /home/anders/code/nanousd/nanousd-types.h: 86
try:
    NUSD_TYPE_INT3 = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_INT3")
except:
    pass

# /home/anders/code/nanousd/nanousd-types.h: 87
try:
    NUSD_TYPE_INT3ARRAY = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_INT3ARRAY")
except:
    pass

# /home/anders/code/nanousd/nanousd-types.h: 88
try:
    NUSD_TYPE_INT4 = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_INT4")
except:
    pass

# /home/anders/code/nanousd/nanousd-types.h: 89
try:
    NUSD_TYPE_INT4ARRAY = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_INT4ARRAY")
except:
    pass

# /home/anders/code/nanousd/nanousd-types.h: 90
try:
    NUSD_TYPE_INT64 = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_INT64")
except:
    pass

# /home/anders/code/nanousd/nanousd-types.h: 91
try:
    NUSD_TYPE_INT64ARRAY = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_INT64ARRAY")
except:
    pass

# /home/anders/code/nanousd/nanousd-types.h: 92
try:
    NUSD_TYPE_INTARRAY = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_INTARRAY")
except:
    pass

# /home/anders/code/nanousd/nanousd-types.h: 93
try:
    NUSD_TYPE_MATRIX2D = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_MATRIX2D")
except:
    pass

# /home/anders/code/nanousd/nanousd-types.h: 94
try:
    NUSD_TYPE_MATRIX2DARRAY = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_MATRIX2DARRAY")
except:
    pass

# /home/anders/code/nanousd/nanousd-types.h: 95
try:
    NUSD_TYPE_MATRIX3D = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_MATRIX3D")
except:
    pass

# /home/anders/code/nanousd/nanousd-types.h: 96
try:
    NUSD_TYPE_MATRIX3DARRAY = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_MATRIX3DARRAY")
except:
    pass

# /home/anders/code/nanousd/nanousd-types.h: 97
try:
    NUSD_TYPE_MATRIX4D = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_MATRIX4D")
except:
    pass

# /home/anders/code/nanousd/nanousd-types.h: 98
try:
    NUSD_TYPE_MATRIX4DARRAY = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_MATRIX4DARRAY")
except:
    pass

# /home/anders/code/nanousd/nanousd-types.h: 99
try:
    NUSD_TYPE_NORMAL3D = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_NORMAL3D")
except:
    pass

# /home/anders/code/nanousd/nanousd-types.h: 100
try:
    NUSD_TYPE_NORMAL3DARRAY = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_NORMAL3DARRAY")
except:
    pass

# /home/anders/code/nanousd/nanousd-types.h: 101
try:
    NUSD_TYPE_NORMAL3F = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_NORMAL3F")
except:
    pass

# /home/anders/code/nanousd/nanousd-types.h: 102
try:
    NUSD_TYPE_NORMAL3FARRAY = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_NORMAL3FARRAY")
except:
    pass

# /home/anders/code/nanousd/nanousd-types.h: 103
try:
    NUSD_TYPE_NORMAL3H = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_NORMAL3H")
except:
    pass

# /home/anders/code/nanousd/nanousd-types.h: 104
try:
    NUSD_TYPE_NORMAL3HARRAY = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_NORMAL3HARRAY")
except:
    pass

# /home/anders/code/nanousd/nanousd-types.h: 105
try:
    NUSD_TYPE_OPAQUE = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_OPAQUE")
except:
    pass

# /home/anders/code/nanousd/nanousd-types.h: 106
try:
    NUSD_TYPE_PATHEXPRESSION = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_PATHEXPRESSION")
except:
    pass

# /home/anders/code/nanousd/nanousd-types.h: 107
try:
    NUSD_TYPE_PATHEXPRESSIONARRAY = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_PATHEXPRESSIONARRAY")
except:
    pass

# /home/anders/code/nanousd/nanousd-types.h: 108
try:
    NUSD_TYPE_POINT3D = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_POINT3D")
except:
    pass

# /home/anders/code/nanousd/nanousd-types.h: 109
try:
    NUSD_TYPE_POINT3DARRAY = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_POINT3DARRAY")
except:
    pass

# /home/anders/code/nanousd/nanousd-types.h: 110
try:
    NUSD_TYPE_POINT3F = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_POINT3F")
except:
    pass

# /home/anders/code/nanousd/nanousd-types.h: 111
try:
    NUSD_TYPE_POINT3FARRAY = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_POINT3FARRAY")
except:
    pass

# /home/anders/code/nanousd/nanousd-types.h: 112
try:
    NUSD_TYPE_POINT3H = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_POINT3H")
except:
    pass

# /home/anders/code/nanousd/nanousd-types.h: 113
try:
    NUSD_TYPE_POINT3HARRAY = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_POINT3HARRAY")
except:
    pass

# /home/anders/code/nanousd/nanousd-types.h: 114
try:
    NUSD_TYPE_QUATD = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_QUATD")
except:
    pass

# /home/anders/code/nanousd/nanousd-types.h: 115
try:
    NUSD_TYPE_QUATDARRAY = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_QUATDARRAY")
except:
    pass

# /home/anders/code/nanousd/nanousd-types.h: 116
try:
    NUSD_TYPE_QUATF = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_QUATF")
except:
    pass

# /home/anders/code/nanousd/nanousd-types.h: 117
try:
    NUSD_TYPE_QUATFARRAY = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_QUATFARRAY")
except:
    pass

# /home/anders/code/nanousd/nanousd-types.h: 118
try:
    NUSD_TYPE_QUATH = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_QUATH")
except:
    pass

# /home/anders/code/nanousd/nanousd-types.h: 119
try:
    NUSD_TYPE_QUATHARRAY = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_QUATHARRAY")
except:
    pass

# /home/anders/code/nanousd/nanousd-types.h: 120
try:
    NUSD_TYPE_STRING = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_STRING")
except:
    pass

# /home/anders/code/nanousd/nanousd-types.h: 121
try:
    NUSD_TYPE_STRINGARRAY = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_STRINGARRAY")
except:
    pass

# /home/anders/code/nanousd/nanousd-types.h: 122
try:
    NUSD_TYPE_TEXCOORD2D = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_TEXCOORD2D")
except:
    pass

# /home/anders/code/nanousd/nanousd-types.h: 123
try:
    NUSD_TYPE_TEXCOORD2DARRAY = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_TEXCOORD2DARRAY")
except:
    pass

# /home/anders/code/nanousd/nanousd-types.h: 124
try:
    NUSD_TYPE_TEXCOORD2F = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_TEXCOORD2F")
except:
    pass

# /home/anders/code/nanousd/nanousd-types.h: 125
try:
    NUSD_TYPE_TEXCOORD2FARRAY = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_TEXCOORD2FARRAY")
except:
    pass

# /home/anders/code/nanousd/nanousd-types.h: 126
try:
    NUSD_TYPE_TEXCOORD2H = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_TEXCOORD2H")
except:
    pass

# /home/anders/code/nanousd/nanousd-types.h: 127
try:
    NUSD_TYPE_TEXCOORD2HARRAY = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_TEXCOORD2HARRAY")
except:
    pass

# /home/anders/code/nanousd/nanousd-types.h: 128
try:
    NUSD_TYPE_TEXCOORD3D = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_TEXCOORD3D")
except:
    pass

# /home/anders/code/nanousd/nanousd-types.h: 129
try:
    NUSD_TYPE_TEXCOORD3DARRAY = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_TEXCOORD3DARRAY")
except:
    pass

# /home/anders/code/nanousd/nanousd-types.h: 130
try:
    NUSD_TYPE_TEXCOORD3F = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_TEXCOORD3F")
except:
    pass

# /home/anders/code/nanousd/nanousd-types.h: 131
try:
    NUSD_TYPE_TEXCOORD3FARRAY = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_TEXCOORD3FARRAY")
except:
    pass

# /home/anders/code/nanousd/nanousd-types.h: 132
try:
    NUSD_TYPE_TEXCOORD3H = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_TEXCOORD3H")
except:
    pass

# /home/anders/code/nanousd/nanousd-types.h: 133
try:
    NUSD_TYPE_TEXCOORD3HARRAY = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_TEXCOORD3HARRAY")
except:
    pass

# /home/anders/code/nanousd/nanousd-types.h: 134
try:
    NUSD_TYPE_TIMECODE = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_TIMECODE")
except:
    pass

# /home/anders/code/nanousd/nanousd-types.h: 135
try:
    NUSD_TYPE_TIMECODEARRAY = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_TIMECODEARRAY")
except:
    pass

# /home/anders/code/nanousd/nanousd-types.h: 136
try:
    NUSD_TYPE_TOKEN = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_TOKEN")
except:
    pass

# /home/anders/code/nanousd/nanousd-types.h: 137
try:
    NUSD_TYPE_TOKENARRAY = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_TOKENARRAY")
except:
    pass

# /home/anders/code/nanousd/nanousd-types.h: 138
try:
    NUSD_TYPE_UCHAR = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_UCHAR")
except:
    pass

# /home/anders/code/nanousd/nanousd-types.h: 139
try:
    NUSD_TYPE_UCHARARRAY = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_UCHARARRAY")
except:
    pass

# /home/anders/code/nanousd/nanousd-types.h: 140
try:
    NUSD_TYPE_UINT = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_UINT")
except:
    pass

# /home/anders/code/nanousd/nanousd-types.h: 141
try:
    NUSD_TYPE_UINT64 = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_UINT64")
except:
    pass

# /home/anders/code/nanousd/nanousd-types.h: 142
try:
    NUSD_TYPE_UINT64ARRAY = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_UINT64ARRAY")
except:
    pass

# /home/anders/code/nanousd/nanousd-types.h: 143
try:
    NUSD_TYPE_UINTARRAY = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_UINTARRAY")
except:
    pass

# /home/anders/code/nanousd/nanousd-types.h: 144
try:
    NUSD_TYPE_VECTOR3D = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_VECTOR3D")
except:
    pass

# /home/anders/code/nanousd/nanousd-types.h: 145
try:
    NUSD_TYPE_VECTOR3DARRAY = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_VECTOR3DARRAY")
except:
    pass

# /home/anders/code/nanousd/nanousd-types.h: 146
try:
    NUSD_TYPE_VECTOR3F = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_VECTOR3F")
except:
    pass

# /home/anders/code/nanousd/nanousd-types.h: 147
try:
    NUSD_TYPE_VECTOR3FARRAY = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_VECTOR3FARRAY")
except:
    pass

# /home/anders/code/nanousd/nanousd-types.h: 148
try:
    NUSD_TYPE_VECTOR3H = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_VECTOR3H")
except:
    pass

# /home/anders/code/nanousd/nanousd-types.h: 149
try:
    NUSD_TYPE_VECTOR3HARRAY = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_VECTOR3HARRAY")
except:
    pass

# /home/anders/code/nanousd/nanousd-types.h: 151
try:
    NUSD_TYPE_RELATIONSHIP = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_TYPE_RELATIONSHIP")
except:
    pass

# /home/anders/code/nanousd/nanousd-types.h: 153
try:
    NUSD_COLORSPACE_LINEAR_AP1 = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_COLORSPACE_LINEAR_AP1")
except:
    pass

# /home/anders/code/nanousd/nanousd-types.h: 154
try:
    NUSD_COLORSPACE_LINEAR_AP0 = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_COLORSPACE_LINEAR_AP0")
except:
    pass

# /home/anders/code/nanousd/nanousd-types.h: 155
for _lib in _libs.values():
    try:
        NUSD_COLORSPACE_LINEAR_REC709 = (nusd_type_t).in_dll(_lib, "NUSD_COLORSPACE_LINEAR_REC709")
        break
    except:
        pass

# /home/anders/code/nanousd/nanousd-types.h: 156
for _lib in _libs.values():
    try:
        NUSD_COLORSPACE_LINEAR_P3D65 = (nusd_type_t).in_dll(_lib, "NUSD_COLORSPACE_LINEAR_P3D65")
        break
    except:
        pass

# /home/anders/code/nanousd/nanousd-types.h: 157
for _lib in _libs.values():
    try:
        NUSD_COLORSPACE_LINEAR_REC2020 = (nusd_type_t).in_dll(_lib, "NUSD_COLORSPACE_LINEAR_REC2020")
        break
    except:
        pass

# /home/anders/code/nanousd/nanousd-types.h: 158
for _lib in _libs.values():
    try:
        NUSD_COLORSPACE_LINEAR_ADOBERGB = (nusd_type_t).in_dll(_lib, "NUSD_COLORSPACE_LINEAR_ADOBERGB")
        break
    except:
        pass

# /home/anders/code/nanousd/nanousd-types.h: 159
for _lib in _libs.values():
    try:
        NUSD_COLORSPACE_LINEAR_CIEXYZD65 = (nusd_type_t).in_dll(_lib, "NUSD_COLORSPACE_LINEAR_CIEXYZD65")
        break
    except:
        pass

# /home/anders/code/nanousd/nanousd-types.h: 160
for _lib in _libs.values():
    try:
        NUSD_COLORSPACE_LINEAR_DISPLAYP3 = (nusd_type_t).in_dll(_lib, "NUSD_COLORSPACE_LINEAR_DISPLAYP3")
        break
    except:
        pass

# /home/anders/code/nanousd/nanousd-types.h: 161
for _lib in _libs.values():
    try:
        NUSD_COLORSPACE_SRGB_REC709 = (nusd_type_t).in_dll(_lib, "NUSD_COLORSPACE_SRGB_REC709")
        break
    except:
        pass

# /home/anders/code/nanousd/nanousd-types.h: 162
for _lib in _libs.values():
    try:
        NUSD_COLORSPACE_G22_REC709 = (nusd_type_t).in_dll(_lib, "NUSD_COLORSPACE_G22_REC709")
        break
    except:
        pass

# /home/anders/code/nanousd/nanousd-types.h: 163
for _lib in _libs.values():
    try:
        NUSD_COLORSPACE_G18_REC709 = (nusd_type_t).in_dll(_lib, "NUSD_COLORSPACE_G18_REC709")
        break
    except:
        pass

# /home/anders/code/nanousd/nanousd-types.h: 164
try:
    NUSD_COLORSPACE_SRGB_AP1 = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_COLORSPACE_SRGB_AP1")
except:
    pass

# /home/anders/code/nanousd/nanousd-types.h: 165
for _lib in _libs.values():
    try:
        NUSD_COLORSPACE_G22_AP1 = (nusd_type_t).in_dll(_lib, "NUSD_COLORSPACE_G22_AP1")
        break
    except:
        pass

# /home/anders/code/nanousd/nanousd-types.h: 166
for _lib in _libs.values():
    try:
        NUSD_COLORSPACE_G22_ADOBERGB = (nusd_type_t).in_dll(_lib, "NUSD_COLORSPACE_G22_ADOBERGB")
        break
    except:
        pass

# /home/anders/code/nanousd/nanousd-types.h: 167
for _lib in _libs.values():
    try:
        NUSD_COLORSPACE_IDENTITY = (nusd_type_t).in_dll(_lib, "NUSD_COLORSPACE_IDENTITY")
        break
    except:
        pass

# /home/anders/code/nanousd/nanousd-types.h: 168
for _lib in _libs.values():
    try:
        NUSD_COLORSPACE_DATA = (nusd_type_t).in_dll(_lib, "NUSD_COLORSPACE_DATA")
        break
    except:
        pass

# /home/anders/code/nanousd/nanousd-types.h: 169
for _lib in _libs.values():
    try:
        NUSD_COLORSPACE_RAW = (nusd_type_t).in_dll(_lib, "NUSD_COLORSPACE_RAW")
        break
    except:
        pass

# /home/anders/code/nanousd/nanousd-types.h: 170
try:
    NUSD_COLORSPACE_SRGB = (nusd_type_t).in_dll(_libs["nanousd"], "NUSD_COLORSPACE_SRGB")
except:
    pass

# /home/anders/code/nanousd/nanousd-types.h: 171
for _lib in _libs.values():
    try:
        NUSD_COLORSPACE_UNKNOWN = (nusd_type_t).in_dll(_lib, "NUSD_COLORSPACE_UNKNOWN")
        break
    except:
        pass

# /home/anders/code/nanousd/nanousd-types.h: 172
for _lib in _libs.values():
    try:
        NUSD_COLORSPACE_CIEXYZ = (nusd_type_t).in_dll(_lib, "NUSD_COLORSPACE_CIEXYZ")
        break
    except:
        pass

# /home/anders/code/nanousd/nanousd-iterators.h: 17
class struct_nusd_prim_iterator_s(Structure):
    pass

nusd_prim_iterator_t = POINTER(struct_nusd_prim_iterator_s)# /home/anders/code/nanousd/nanousd-iterators.h: 17

# /home/anders/code/nanousd/nanousd-iterators.h: 18
class struct_nusd_property_iterator_s(Structure):
    pass

nusd_property_iterator_t = POINTER(struct_nusd_property_iterator_s)# /home/anders/code/nanousd/nanousd-iterators.h: 18

# /home/anders/code/nanousd/nanousd-iterators.h: 19
class struct_nusd_attribute_iterator_s(Structure):
    pass

nusd_attribute_iterator_t = POINTER(struct_nusd_attribute_iterator_s)# /home/anders/code/nanousd/nanousd-iterators.h: 19

# /home/anders/code/nanousd/nanousd-iterators.h: 20
class struct_nusd_relationship_iterator_s(Structure):
    pass

nusd_relationship_iterator_t = POINTER(struct_nusd_relationship_iterator_s)# /home/anders/code/nanousd/nanousd-iterators.h: 20

# /home/anders/code/nanousd/nanousd-iterators.h: 21
class struct_nusd_relationship_targets_iterator_s(Structure):
    pass

nusd_relationship_targets_iterator_t = POINTER(struct_nusd_relationship_targets_iterator_s)# /home/anders/code/nanousd/nanousd-iterators.h: 21

# /home/anders/code/nanousd/nanousd-iterators.h: 22
class struct_nusd_token_array_iterator_s(Structure):
    pass

nusd_token_array_iterator_t = POINTER(struct_nusd_token_array_iterator_s)# /home/anders/code/nanousd/nanousd-iterators.h: 22

# /home/anders/code/nanousd/nanousd-iterators.h: 23
class struct_nusd_asset_path_array_iterator_s(Structure):
    pass

nusd_asset_path_array_iterator_t = POINTER(struct_nusd_asset_path_array_iterator_s)# /home/anders/code/nanousd/nanousd-iterators.h: 23

# /home/anders/code/nanousd/nanousd-iterators.h: 36
if _libs["nanousd"].has("nusd_prim_iterator_next", "cdecl"):
    nusd_prim_iterator_next = _libs["nanousd"].get("nusd_prim_iterator_next", "cdecl")
    nusd_prim_iterator_next.argtypes = [nusd_prim_iterator_t, POINTER(POINTER(c_char))]
    nusd_prim_iterator_next.restype = c_bool

# /home/anders/code/nanousd/nanousd-iterators.h: 48
if _libs["nanousd"].has("nusd_prim_iterator_destroy", "cdecl"):
    nusd_prim_iterator_destroy = _libs["nanousd"].get("nusd_prim_iterator_destroy", "cdecl")
    nusd_prim_iterator_destroy.argtypes = [nusd_prim_iterator_t]
    nusd_prim_iterator_destroy.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd-iterators.h: 64
if _libs["nanousd"].has("nusd_property_iterator_next", "cdecl"):
    nusd_property_iterator_next = _libs["nanousd"].get("nusd_property_iterator_next", "cdecl")
    nusd_property_iterator_next.argtypes = [nusd_property_iterator_t, POINTER(POINTER(c_char)), POINTER(nusd_type_t)]
    nusd_property_iterator_next.restype = c_bool

# /home/anders/code/nanousd/nanousd-iterators.h: 76
if _libs["nanousd"].has("nusd_property_iterator_destroy", "cdecl"):
    nusd_property_iterator_destroy = _libs["nanousd"].get("nusd_property_iterator_destroy", "cdecl")
    nusd_property_iterator_destroy.argtypes = [nusd_property_iterator_t]
    nusd_property_iterator_destroy.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd-iterators.h: 89
if _libs["nanousd"].has("nusd_attribute_iterator_next", "cdecl"):
    nusd_attribute_iterator_next = _libs["nanousd"].get("nusd_attribute_iterator_next", "cdecl")
    nusd_attribute_iterator_next.argtypes = [nusd_attribute_iterator_t, POINTER(POINTER(c_char))]
    nusd_attribute_iterator_next.restype = c_bool

# /home/anders/code/nanousd/nanousd-iterators.h: 101
if _libs["nanousd"].has("nusd_attribute_iterator_destroy", "cdecl"):
    nusd_attribute_iterator_destroy = _libs["nanousd"].get("nusd_attribute_iterator_destroy", "cdecl")
    nusd_attribute_iterator_destroy.argtypes = [nusd_attribute_iterator_t]
    nusd_attribute_iterator_destroy.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd-iterators.h: 114
if _libs["nanousd"].has("nusd_relationship_iterator_next", "cdecl"):
    nusd_relationship_iterator_next = _libs["nanousd"].get("nusd_relationship_iterator_next", "cdecl")
    nusd_relationship_iterator_next.argtypes = [nusd_relationship_iterator_t, POINTER(POINTER(c_char))]
    nusd_relationship_iterator_next.restype = c_bool

# /home/anders/code/nanousd/nanousd-iterators.h: 126
if _libs["nanousd"].has("nusd_relationship_iterator_destroy", "cdecl"):
    nusd_relationship_iterator_destroy = _libs["nanousd"].get("nusd_relationship_iterator_destroy", "cdecl")
    nusd_relationship_iterator_destroy.argtypes = [nusd_relationship_iterator_t]
    nusd_relationship_iterator_destroy.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd-iterators.h: 139
if _libs["nanousd"].has("nusd_relationship_targets_iterator_next", "cdecl"):
    nusd_relationship_targets_iterator_next = _libs["nanousd"].get("nusd_relationship_targets_iterator_next", "cdecl")
    nusd_relationship_targets_iterator_next.argtypes = [nusd_relationship_targets_iterator_t, POINTER(POINTER(c_char))]
    nusd_relationship_targets_iterator_next.restype = c_bool

# /home/anders/code/nanousd/nanousd-iterators.h: 151
if _libs["nanousd"].has("nusd_relationship_targets_iterator_destroy", "cdecl"):
    nusd_relationship_targets_iterator_destroy = _libs["nanousd"].get("nusd_relationship_targets_iterator_destroy", "cdecl")
    nusd_relationship_targets_iterator_destroy.argtypes = [nusd_relationship_targets_iterator_t]
    nusd_relationship_targets_iterator_destroy.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd-iterators.h: 164
if _libs["nanousd"].has("nusd_token_array_iterator_next", "cdecl"):
    nusd_token_array_iterator_next = _libs["nanousd"].get("nusd_token_array_iterator_next", "cdecl")
    nusd_token_array_iterator_next.argtypes = [nusd_token_array_iterator_t, POINTER(POINTER(c_char))]
    nusd_token_array_iterator_next.restype = c_bool

# /home/anders/code/nanousd/nanousd-iterators.h: 175
if _libs["nanousd"].has("nusd_token_array_iterator_size", "cdecl"):
    nusd_token_array_iterator_size = _libs["nanousd"].get("nusd_token_array_iterator_size", "cdecl")
    nusd_token_array_iterator_size.argtypes = [nusd_token_array_iterator_t]
    nusd_token_array_iterator_size.restype = c_size_t

# /home/anders/code/nanousd/nanousd-iterators.h: 187
if _libs["nanousd"].has("nusd_token_array_iterator_destroy", "cdecl"):
    nusd_token_array_iterator_destroy = _libs["nanousd"].get("nusd_token_array_iterator_destroy", "cdecl")
    nusd_token_array_iterator_destroy.argtypes = [nusd_token_array_iterator_t]
    nusd_token_array_iterator_destroy.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd-iterators.h: 200
if _libs["nanousd"].has("nusd_asset_path_array_iterator_next", "cdecl"):
    nusd_asset_path_array_iterator_next = _libs["nanousd"].get("nusd_asset_path_array_iterator_next", "cdecl")
    nusd_asset_path_array_iterator_next.argtypes = [nusd_asset_path_array_iterator_t, POINTER(POINTER(c_char))]
    nusd_asset_path_array_iterator_next.restype = c_bool

# /home/anders/code/nanousd/nanousd-iterators.h: 211
if _libs["nanousd"].has("nusd_asset_path_array_iterator_size", "cdecl"):
    nusd_asset_path_array_iterator_size = _libs["nanousd"].get("nusd_asset_path_array_iterator_size", "cdecl")
    nusd_asset_path_array_iterator_size.argtypes = [nusd_asset_path_array_iterator_t]
    nusd_asset_path_array_iterator_size.restype = c_size_t

# /home/anders/code/nanousd/nanousd-iterators.h: 223
if _libs["nanousd"].has("nusd_asset_path_array_iterator_destroy", "cdecl"):
    nusd_asset_path_array_iterator_destroy = _libs["nanousd"].get("nusd_asset_path_array_iterator_destroy", "cdecl")
    nusd_asset_path_array_iterator_destroy.argtypes = [nusd_asset_path_array_iterator_t]
    nusd_asset_path_array_iterator_destroy.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd-arrays.h: 10
class struct_nusd_bool_array_s(Structure):
    pass

nusd_bool_array_t = POINTER(struct_nusd_bool_array_s)# /home/anders/code/nanousd/nanousd-arrays.h: 10

# /home/anders/code/nanousd/nanousd-arrays.h: 12
class struct_nusd_float_array_s(Structure):
    pass

nusd_float_array_t = POINTER(struct_nusd_float_array_s)# /home/anders/code/nanousd/nanousd-arrays.h: 12

# /home/anders/code/nanousd/nanousd-arrays.h: 13
class struct_nusd_float2_array_s(Structure):
    pass

nusd_float2_array_t = POINTER(struct_nusd_float2_array_s)# /home/anders/code/nanousd/nanousd-arrays.h: 13

# /home/anders/code/nanousd/nanousd-arrays.h: 14
class struct_nusd_float3_array_s(Structure):
    pass

nusd_float3_array_t = POINTER(struct_nusd_float3_array_s)# /home/anders/code/nanousd/nanousd-arrays.h: 14

# /home/anders/code/nanousd/nanousd-arrays.h: 15
class struct_nusd_float4_array_s(Structure):
    pass

nusd_float4_array_t = POINTER(struct_nusd_float4_array_s)# /home/anders/code/nanousd/nanousd-arrays.h: 15

# /home/anders/code/nanousd/nanousd-arrays.h: 17
class struct_nusd_double_array_s(Structure):
    pass

nusd_double_array_t = POINTER(struct_nusd_double_array_s)# /home/anders/code/nanousd/nanousd-arrays.h: 17

# /home/anders/code/nanousd/nanousd-arrays.h: 18
class struct_nusd_double2_array_s(Structure):
    pass

nusd_double2_array_t = POINTER(struct_nusd_double2_array_s)# /home/anders/code/nanousd/nanousd-arrays.h: 18

# /home/anders/code/nanousd/nanousd-arrays.h: 19
class struct_nusd_double3_array_s(Structure):
    pass

nusd_double3_array_t = POINTER(struct_nusd_double3_array_s)# /home/anders/code/nanousd/nanousd-arrays.h: 19

# /home/anders/code/nanousd/nanousd-arrays.h: 20
class struct_nusd_double4_array_s(Structure):
    pass

nusd_double4_array_t = POINTER(struct_nusd_double4_array_s)# /home/anders/code/nanousd/nanousd-arrays.h: 20

# /home/anders/code/nanousd/nanousd-arrays.h: 22
class struct_nusd_int_array_s(Structure):
    pass

nusd_int_array_t = POINTER(struct_nusd_int_array_s)# /home/anders/code/nanousd/nanousd-arrays.h: 22

# /home/anders/code/nanousd/nanousd-arrays.h: 23
class struct_nusd_int2_array_s(Structure):
    pass

nusd_int2_array_t = POINTER(struct_nusd_int2_array_s)# /home/anders/code/nanousd/nanousd-arrays.h: 23

# /home/anders/code/nanousd/nanousd-arrays.h: 24
class struct_nusd_int3_array_s(Structure):
    pass

nusd_int3_array_t = POINTER(struct_nusd_int3_array_s)# /home/anders/code/nanousd/nanousd-arrays.h: 24

# /home/anders/code/nanousd/nanousd-arrays.h: 25
class struct_nusd_int4_array_s(Structure):
    pass

nusd_int4_array_t = POINTER(struct_nusd_int4_array_s)# /home/anders/code/nanousd/nanousd-arrays.h: 25

# /home/anders/code/nanousd/nanousd-arrays.h: 26
class struct_nusd_int64_array_s(Structure):
    pass

nusd_int64_array_t = POINTER(struct_nusd_int64_array_s)# /home/anders/code/nanousd/nanousd-arrays.h: 26

# /home/anders/code/nanousd/nanousd-arrays.h: 28
class struct_nusd_matrix2d_array_s(Structure):
    pass

nusd_matrix2d_array_t = POINTER(struct_nusd_matrix2d_array_s)# /home/anders/code/nanousd/nanousd-arrays.h: 28

# /home/anders/code/nanousd/nanousd-arrays.h: 29
class struct_nusd_matrix3d_array_s(Structure):
    pass

nusd_matrix3d_array_t = POINTER(struct_nusd_matrix3d_array_s)# /home/anders/code/nanousd/nanousd-arrays.h: 29

# /home/anders/code/nanousd/nanousd-arrays.h: 30
class struct_nusd_matrix4d_array_s(Structure):
    pass

nusd_matrix4d_array_t = POINTER(struct_nusd_matrix4d_array_s)# /home/anders/code/nanousd/nanousd-arrays.h: 30

# /home/anders/code/nanousd/nanousd-arrays.h: 32
class struct_nusd_uint_array_s(Structure):
    pass

nusd_uint_array_t = POINTER(struct_nusd_uint_array_s)# /home/anders/code/nanousd/nanousd-arrays.h: 32

# /home/anders/code/nanousd/nanousd-arrays.h: 33
class struct_nusd_uint64_array_s(Structure):
    pass

nusd_uint64_array_t = POINTER(struct_nusd_uint64_array_s)# /home/anders/code/nanousd/nanousd-arrays.h: 33

# /home/anders/code/nanousd/nanousd-arrays.h: 34
class struct_nusd_uchar_array_s(Structure):
    pass

nusd_uchar_array_t = POINTER(struct_nusd_uchar_array_s)# /home/anders/code/nanousd/nanousd-arrays.h: 34

# /home/anders/code/nanousd/nanousd-arrays.h: 44
if _libs["nanousd"].has("nusd_bool_array_size", "cdecl"):
    nusd_bool_array_size = _libs["nanousd"].get("nusd_bool_array_size", "cdecl")
    nusd_bool_array_size.argtypes = [nusd_bool_array_t]
    nusd_bool_array_size.restype = c_size_t

# /home/anders/code/nanousd/nanousd-arrays.h: 56
if _libs["nanousd"].has("nusd_bool_array_data", "cdecl"):
    nusd_bool_array_data = _libs["nanousd"].get("nusd_bool_array_data", "cdecl")
    nusd_bool_array_data.argtypes = [nusd_bool_array_t]
    nusd_bool_array_data.restype = POINTER(c_bool)

# /home/anders/code/nanousd/nanousd-arrays.h: 65
if _libs["nanousd"].has("nusd_bool_array_destroy", "cdecl"):
    nusd_bool_array_destroy = _libs["nanousd"].get("nusd_bool_array_destroy", "cdecl")
    nusd_bool_array_destroy.argtypes = [nusd_bool_array_t]
    nusd_bool_array_destroy.restype = None

# /home/anders/code/nanousd/nanousd-arrays.h: 75
if _libs["nanousd"].has("nusd_float_array_size", "cdecl"):
    nusd_float_array_size = _libs["nanousd"].get("nusd_float_array_size", "cdecl")
    nusd_float_array_size.argtypes = [nusd_float_array_t]
    nusd_float_array_size.restype = c_size_t

# /home/anders/code/nanousd/nanousd-arrays.h: 87
if _libs["nanousd"].has("nusd_float_array_data", "cdecl"):
    nusd_float_array_data = _libs["nanousd"].get("nusd_float_array_data", "cdecl")
    nusd_float_array_data.argtypes = [nusd_float_array_t]
    nusd_float_array_data.restype = POINTER(c_float)

# /home/anders/code/nanousd/nanousd-arrays.h: 96
if _libs["nanousd"].has("nusd_float_array_destroy", "cdecl"):
    nusd_float_array_destroy = _libs["nanousd"].get("nusd_float_array_destroy", "cdecl")
    nusd_float_array_destroy.argtypes = [nusd_float_array_t]
    nusd_float_array_destroy.restype = None

# /home/anders/code/nanousd/nanousd-arrays.h: 106
if _libs["nanousd"].has("nusd_float2_array_size", "cdecl"):
    nusd_float2_array_size = _libs["nanousd"].get("nusd_float2_array_size", "cdecl")
    nusd_float2_array_size.argtypes = [nusd_float2_array_t]
    nusd_float2_array_size.restype = c_size_t

# /home/anders/code/nanousd/nanousd-arrays.h: 118
if _libs["nanousd"].has("nusd_float2_array_data", "cdecl"):
    nusd_float2_array_data = _libs["nanousd"].get("nusd_float2_array_data", "cdecl")
    nusd_float2_array_data.argtypes = [nusd_float2_array_t]
    nusd_float2_array_data.restype = POINTER(c_float)

# /home/anders/code/nanousd/nanousd-arrays.h: 127
if _libs["nanousd"].has("nusd_float2_array_destroy", "cdecl"):
    nusd_float2_array_destroy = _libs["nanousd"].get("nusd_float2_array_destroy", "cdecl")
    nusd_float2_array_destroy.argtypes = [nusd_float2_array_t]
    nusd_float2_array_destroy.restype = None

# /home/anders/code/nanousd/nanousd-arrays.h: 137
if _libs["nanousd"].has("nusd_float3_array_size", "cdecl"):
    nusd_float3_array_size = _libs["nanousd"].get("nusd_float3_array_size", "cdecl")
    nusd_float3_array_size.argtypes = [nusd_float3_array_t]
    nusd_float3_array_size.restype = c_size_t

# /home/anders/code/nanousd/nanousd-arrays.h: 149
if _libs["nanousd"].has("nusd_float3_array_data", "cdecl"):
    nusd_float3_array_data = _libs["nanousd"].get("nusd_float3_array_data", "cdecl")
    nusd_float3_array_data.argtypes = [nusd_float3_array_t]
    nusd_float3_array_data.restype = POINTER(c_float)

# /home/anders/code/nanousd/nanousd-arrays.h: 158
if _libs["nanousd"].has("nusd_float3_array_destroy", "cdecl"):
    nusd_float3_array_destroy = _libs["nanousd"].get("nusd_float3_array_destroy", "cdecl")
    nusd_float3_array_destroy.argtypes = [nusd_float3_array_t]
    nusd_float3_array_destroy.restype = None

# /home/anders/code/nanousd/nanousd-arrays.h: 168
if _libs["nanousd"].has("nusd_float4_array_size", "cdecl"):
    nusd_float4_array_size = _libs["nanousd"].get("nusd_float4_array_size", "cdecl")
    nusd_float4_array_size.argtypes = [nusd_float4_array_t]
    nusd_float4_array_size.restype = c_size_t

# /home/anders/code/nanousd/nanousd-arrays.h: 180
if _libs["nanousd"].has("nusd_float4_array_data", "cdecl"):
    nusd_float4_array_data = _libs["nanousd"].get("nusd_float4_array_data", "cdecl")
    nusd_float4_array_data.argtypes = [nusd_float4_array_t]
    nusd_float4_array_data.restype = POINTER(c_float)

# /home/anders/code/nanousd/nanousd-arrays.h: 189
if _libs["nanousd"].has("nusd_float4_array_destroy", "cdecl"):
    nusd_float4_array_destroy = _libs["nanousd"].get("nusd_float4_array_destroy", "cdecl")
    nusd_float4_array_destroy.argtypes = [nusd_float4_array_t]
    nusd_float4_array_destroy.restype = None

# /home/anders/code/nanousd/nanousd-arrays.h: 199
if _libs["nanousd"].has("nusd_double_array_size", "cdecl"):
    nusd_double_array_size = _libs["nanousd"].get("nusd_double_array_size", "cdecl")
    nusd_double_array_size.argtypes = [nusd_double_array_t]
    nusd_double_array_size.restype = c_size_t

# /home/anders/code/nanousd/nanousd-arrays.h: 211
if _libs["nanousd"].has("nusd_double_array_data", "cdecl"):
    nusd_double_array_data = _libs["nanousd"].get("nusd_double_array_data", "cdecl")
    nusd_double_array_data.argtypes = [nusd_double_array_t]
    nusd_double_array_data.restype = POINTER(c_double)

# /home/anders/code/nanousd/nanousd-arrays.h: 220
if _libs["nanousd"].has("nusd_double_array_destroy", "cdecl"):
    nusd_double_array_destroy = _libs["nanousd"].get("nusd_double_array_destroy", "cdecl")
    nusd_double_array_destroy.argtypes = [nusd_double_array_t]
    nusd_double_array_destroy.restype = None

# /home/anders/code/nanousd/nanousd-arrays.h: 230
if _libs["nanousd"].has("nusd_double2_array_size", "cdecl"):
    nusd_double2_array_size = _libs["nanousd"].get("nusd_double2_array_size", "cdecl")
    nusd_double2_array_size.argtypes = [nusd_double2_array_t]
    nusd_double2_array_size.restype = c_size_t

# /home/anders/code/nanousd/nanousd-arrays.h: 242
if _libs["nanousd"].has("nusd_double2_array_data", "cdecl"):
    nusd_double2_array_data = _libs["nanousd"].get("nusd_double2_array_data", "cdecl")
    nusd_double2_array_data.argtypes = [nusd_double2_array_t]
    nusd_double2_array_data.restype = POINTER(c_double)

# /home/anders/code/nanousd/nanousd-arrays.h: 251
if _libs["nanousd"].has("nusd_double2_array_destroy", "cdecl"):
    nusd_double2_array_destroy = _libs["nanousd"].get("nusd_double2_array_destroy", "cdecl")
    nusd_double2_array_destroy.argtypes = [nusd_double2_array_t]
    nusd_double2_array_destroy.restype = None

# /home/anders/code/nanousd/nanousd-arrays.h: 261
if _libs["nanousd"].has("nusd_double3_array_size", "cdecl"):
    nusd_double3_array_size = _libs["nanousd"].get("nusd_double3_array_size", "cdecl")
    nusd_double3_array_size.argtypes = [nusd_double3_array_t]
    nusd_double3_array_size.restype = c_size_t

# /home/anders/code/nanousd/nanousd-arrays.h: 273
if _libs["nanousd"].has("nusd_double3_array_data", "cdecl"):
    nusd_double3_array_data = _libs["nanousd"].get("nusd_double3_array_data", "cdecl")
    nusd_double3_array_data.argtypes = [nusd_double3_array_t]
    nusd_double3_array_data.restype = POINTER(c_double)

# /home/anders/code/nanousd/nanousd-arrays.h: 282
if _libs["nanousd"].has("nusd_double3_array_destroy", "cdecl"):
    nusd_double3_array_destroy = _libs["nanousd"].get("nusd_double3_array_destroy", "cdecl")
    nusd_double3_array_destroy.argtypes = [nusd_double3_array_t]
    nusd_double3_array_destroy.restype = None

# /home/anders/code/nanousd/nanousd-arrays.h: 292
if _libs["nanousd"].has("nusd_double4_array_size", "cdecl"):
    nusd_double4_array_size = _libs["nanousd"].get("nusd_double4_array_size", "cdecl")
    nusd_double4_array_size.argtypes = [nusd_double4_array_t]
    nusd_double4_array_size.restype = c_size_t

# /home/anders/code/nanousd/nanousd-arrays.h: 304
if _libs["nanousd"].has("nusd_double4_array_data", "cdecl"):
    nusd_double4_array_data = _libs["nanousd"].get("nusd_double4_array_data", "cdecl")
    nusd_double4_array_data.argtypes = [nusd_double4_array_t]
    nusd_double4_array_data.restype = POINTER(c_double)

# /home/anders/code/nanousd/nanousd-arrays.h: 313
if _libs["nanousd"].has("nusd_double4_array_destroy", "cdecl"):
    nusd_double4_array_destroy = _libs["nanousd"].get("nusd_double4_array_destroy", "cdecl")
    nusd_double4_array_destroy.argtypes = [nusd_double4_array_t]
    nusd_double4_array_destroy.restype = None

# /home/anders/code/nanousd/nanousd-arrays.h: 323
if _libs["nanousd"].has("nusd_int_array_size", "cdecl"):
    nusd_int_array_size = _libs["nanousd"].get("nusd_int_array_size", "cdecl")
    nusd_int_array_size.argtypes = [nusd_int_array_t]
    nusd_int_array_size.restype = c_size_t

# /home/anders/code/nanousd/nanousd-arrays.h: 335
if _libs["nanousd"].has("nusd_int_array_data", "cdecl"):
    nusd_int_array_data = _libs["nanousd"].get("nusd_int_array_data", "cdecl")
    nusd_int_array_data.argtypes = [nusd_int_array_t]
    nusd_int_array_data.restype = POINTER(c_int)

# /home/anders/code/nanousd/nanousd-arrays.h: 344
if _libs["nanousd"].has("nusd_int_array_destroy", "cdecl"):
    nusd_int_array_destroy = _libs["nanousd"].get("nusd_int_array_destroy", "cdecl")
    nusd_int_array_destroy.argtypes = [nusd_int_array_t]
    nusd_int_array_destroy.restype = None

# /home/anders/code/nanousd/nanousd-arrays.h: 354
if _libs["nanousd"].has("nusd_int2_array_size", "cdecl"):
    nusd_int2_array_size = _libs["nanousd"].get("nusd_int2_array_size", "cdecl")
    nusd_int2_array_size.argtypes = [nusd_int2_array_t]
    nusd_int2_array_size.restype = c_size_t

# /home/anders/code/nanousd/nanousd-arrays.h: 366
if _libs["nanousd"].has("nusd_int2_array_data", "cdecl"):
    nusd_int2_array_data = _libs["nanousd"].get("nusd_int2_array_data", "cdecl")
    nusd_int2_array_data.argtypes = [nusd_int2_array_t]
    nusd_int2_array_data.restype = POINTER(c_int)

# /home/anders/code/nanousd/nanousd-arrays.h: 375
if _libs["nanousd"].has("nusd_int2_array_destroy", "cdecl"):
    nusd_int2_array_destroy = _libs["nanousd"].get("nusd_int2_array_destroy", "cdecl")
    nusd_int2_array_destroy.argtypes = [nusd_int2_array_t]
    nusd_int2_array_destroy.restype = None

# /home/anders/code/nanousd/nanousd-arrays.h: 385
if _libs["nanousd"].has("nusd_int3_array_size", "cdecl"):
    nusd_int3_array_size = _libs["nanousd"].get("nusd_int3_array_size", "cdecl")
    nusd_int3_array_size.argtypes = [nusd_int3_array_t]
    nusd_int3_array_size.restype = c_size_t

# /home/anders/code/nanousd/nanousd-arrays.h: 397
if _libs["nanousd"].has("nusd_int3_array_data", "cdecl"):
    nusd_int3_array_data = _libs["nanousd"].get("nusd_int3_array_data", "cdecl")
    nusd_int3_array_data.argtypes = [nusd_int3_array_t]
    nusd_int3_array_data.restype = POINTER(c_int)

# /home/anders/code/nanousd/nanousd-arrays.h: 406
if _libs["nanousd"].has("nusd_int3_array_destroy", "cdecl"):
    nusd_int3_array_destroy = _libs["nanousd"].get("nusd_int3_array_destroy", "cdecl")
    nusd_int3_array_destroy.argtypes = [nusd_int3_array_t]
    nusd_int3_array_destroy.restype = None

# /home/anders/code/nanousd/nanousd-arrays.h: 416
if _libs["nanousd"].has("nusd_int4_array_size", "cdecl"):
    nusd_int4_array_size = _libs["nanousd"].get("nusd_int4_array_size", "cdecl")
    nusd_int4_array_size.argtypes = [nusd_int4_array_t]
    nusd_int4_array_size.restype = c_size_t

# /home/anders/code/nanousd/nanousd-arrays.h: 428
if _libs["nanousd"].has("nusd_int4_array_data", "cdecl"):
    nusd_int4_array_data = _libs["nanousd"].get("nusd_int4_array_data", "cdecl")
    nusd_int4_array_data.argtypes = [nusd_int4_array_t]
    nusd_int4_array_data.restype = POINTER(c_int)

# /home/anders/code/nanousd/nanousd-arrays.h: 437
if _libs["nanousd"].has("nusd_int4_array_destroy", "cdecl"):
    nusd_int4_array_destroy = _libs["nanousd"].get("nusd_int4_array_destroy", "cdecl")
    nusd_int4_array_destroy.argtypes = [nusd_int4_array_t]
    nusd_int4_array_destroy.restype = None

# /home/anders/code/nanousd/nanousd-arrays.h: 447
if _libs["nanousd"].has("nusd_int64_array_size", "cdecl"):
    nusd_int64_array_size = _libs["nanousd"].get("nusd_int64_array_size", "cdecl")
    nusd_int64_array_size.argtypes = [nusd_int64_array_t]
    nusd_int64_array_size.restype = c_size_t

# /home/anders/code/nanousd/nanousd-arrays.h: 459
if _libs["nanousd"].has("nusd_int64_array_data", "cdecl"):
    nusd_int64_array_data = _libs["nanousd"].get("nusd_int64_array_data", "cdecl")
    nusd_int64_array_data.argtypes = [nusd_int64_array_t]
    nusd_int64_array_data.restype = POINTER(c_int64)

# /home/anders/code/nanousd/nanousd-arrays.h: 468
if _libs["nanousd"].has("nusd_int64_array_destroy", "cdecl"):
    nusd_int64_array_destroy = _libs["nanousd"].get("nusd_int64_array_destroy", "cdecl")
    nusd_int64_array_destroy.argtypes = [nusd_int64_array_t]
    nusd_int64_array_destroy.restype = None

# /home/anders/code/nanousd/nanousd-arrays.h: 478
if _libs["nanousd"].has("nusd_matrix2d_array_size", "cdecl"):
    nusd_matrix2d_array_size = _libs["nanousd"].get("nusd_matrix2d_array_size", "cdecl")
    nusd_matrix2d_array_size.argtypes = [nusd_matrix2d_array_t]
    nusd_matrix2d_array_size.restype = c_size_t

# /home/anders/code/nanousd/nanousd-arrays.h: 490
if _libs["nanousd"].has("nusd_matrix2d_array_data", "cdecl"):
    nusd_matrix2d_array_data = _libs["nanousd"].get("nusd_matrix2d_array_data", "cdecl")
    nusd_matrix2d_array_data.argtypes = [nusd_matrix2d_array_t]
    nusd_matrix2d_array_data.restype = POINTER(c_double)

# /home/anders/code/nanousd/nanousd-arrays.h: 499
if _libs["nanousd"].has("nusd_matrix2d_array_destroy", "cdecl"):
    nusd_matrix2d_array_destroy = _libs["nanousd"].get("nusd_matrix2d_array_destroy", "cdecl")
    nusd_matrix2d_array_destroy.argtypes = [nusd_matrix2d_array_t]
    nusd_matrix2d_array_destroy.restype = None

# /home/anders/code/nanousd/nanousd-arrays.h: 509
if _libs["nanousd"].has("nusd_matrix3d_array_size", "cdecl"):
    nusd_matrix3d_array_size = _libs["nanousd"].get("nusd_matrix3d_array_size", "cdecl")
    nusd_matrix3d_array_size.argtypes = [nusd_matrix3d_array_t]
    nusd_matrix3d_array_size.restype = c_size_t

# /home/anders/code/nanousd/nanousd-arrays.h: 521
if _libs["nanousd"].has("nusd_matrix3d_array_data", "cdecl"):
    nusd_matrix3d_array_data = _libs["nanousd"].get("nusd_matrix3d_array_data", "cdecl")
    nusd_matrix3d_array_data.argtypes = [nusd_matrix3d_array_t]
    nusd_matrix3d_array_data.restype = POINTER(c_double)

# /home/anders/code/nanousd/nanousd-arrays.h: 530
if _libs["nanousd"].has("nusd_matrix3d_array_destroy", "cdecl"):
    nusd_matrix3d_array_destroy = _libs["nanousd"].get("nusd_matrix3d_array_destroy", "cdecl")
    nusd_matrix3d_array_destroy.argtypes = [nusd_matrix3d_array_t]
    nusd_matrix3d_array_destroy.restype = None

# /home/anders/code/nanousd/nanousd-arrays.h: 540
if _libs["nanousd"].has("nusd_matrix4d_array_size", "cdecl"):
    nusd_matrix4d_array_size = _libs["nanousd"].get("nusd_matrix4d_array_size", "cdecl")
    nusd_matrix4d_array_size.argtypes = [nusd_matrix4d_array_t]
    nusd_matrix4d_array_size.restype = c_size_t

# /home/anders/code/nanousd/nanousd-arrays.h: 552
if _libs["nanousd"].has("nusd_matrix4d_array_data", "cdecl"):
    nusd_matrix4d_array_data = _libs["nanousd"].get("nusd_matrix4d_array_data", "cdecl")
    nusd_matrix4d_array_data.argtypes = [nusd_matrix4d_array_t]
    nusd_matrix4d_array_data.restype = POINTER(c_double)

# /home/anders/code/nanousd/nanousd-arrays.h: 561
if _libs["nanousd"].has("nusd_matrix4d_array_destroy", "cdecl"):
    nusd_matrix4d_array_destroy = _libs["nanousd"].get("nusd_matrix4d_array_destroy", "cdecl")
    nusd_matrix4d_array_destroy.argtypes = [nusd_matrix4d_array_t]
    nusd_matrix4d_array_destroy.restype = None

# /home/anders/code/nanousd/nanousd-arrays.h: 571
if _libs["nanousd"].has("nusd_uchar_array_size", "cdecl"):
    nusd_uchar_array_size = _libs["nanousd"].get("nusd_uchar_array_size", "cdecl")
    nusd_uchar_array_size.argtypes = [nusd_uchar_array_t]
    nusd_uchar_array_size.restype = c_size_t

# /home/anders/code/nanousd/nanousd-arrays.h: 582
if _libs["nanousd"].has("nusd_uchar_array_data", "cdecl"):
    nusd_uchar_array_data = _libs["nanousd"].get("nusd_uchar_array_data", "cdecl")
    nusd_uchar_array_data.argtypes = [nusd_uchar_array_t]
    nusd_uchar_array_data.restype = POINTER(c_ubyte)

# /home/anders/code/nanousd/nanousd-arrays.h: 591
if _libs["nanousd"].has("nusd_uchar_array_destroy", "cdecl"):
    nusd_uchar_array_destroy = _libs["nanousd"].get("nusd_uchar_array_destroy", "cdecl")
    nusd_uchar_array_destroy.argtypes = [nusd_uchar_array_t]
    nusd_uchar_array_destroy.restype = None

# /home/anders/code/nanousd/nanousd-arrays.h: 601
if _libs["nanousd"].has("nusd_uint_array_size", "cdecl"):
    nusd_uint_array_size = _libs["nanousd"].get("nusd_uint_array_size", "cdecl")
    nusd_uint_array_size.argtypes = [nusd_uint_array_t]
    nusd_uint_array_size.restype = c_size_t

# /home/anders/code/nanousd/nanousd-arrays.h: 612
if _libs["nanousd"].has("nusd_uint_array_data", "cdecl"):
    nusd_uint_array_data = _libs["nanousd"].get("nusd_uint_array_data", "cdecl")
    nusd_uint_array_data.argtypes = [nusd_uint_array_t]
    nusd_uint_array_data.restype = POINTER(c_uint)

# /home/anders/code/nanousd/nanousd-arrays.h: 621
if _libs["nanousd"].has("nusd_uint_array_destroy", "cdecl"):
    nusd_uint_array_destroy = _libs["nanousd"].get("nusd_uint_array_destroy", "cdecl")
    nusd_uint_array_destroy.argtypes = [nusd_uint_array_t]
    nusd_uint_array_destroy.restype = None

# /home/anders/code/nanousd/nanousd-arrays.h: 631
if _libs["nanousd"].has("nusd_uint64_array_size", "cdecl"):
    nusd_uint64_array_size = _libs["nanousd"].get("nusd_uint64_array_size", "cdecl")
    nusd_uint64_array_size.argtypes = [nusd_uint64_array_t]
    nusd_uint64_array_size.restype = c_size_t

# /home/anders/code/nanousd/nanousd-arrays.h: 642
if _libs["nanousd"].has("nusd_uint64_array_data", "cdecl"):
    nusd_uint64_array_data = _libs["nanousd"].get("nusd_uint64_array_data", "cdecl")
    nusd_uint64_array_data.argtypes = [nusd_uint64_array_t]
    nusd_uint64_array_data.restype = POINTER(uint64_t)

# /home/anders/code/nanousd/nanousd-arrays.h: 651
if _libs["nanousd"].has("nusd_uint64_array_destroy", "cdecl"):
    nusd_uint64_array_destroy = _libs["nanousd"].get("nusd_uint64_array_destroy", "cdecl")
    nusd_uint64_array_destroy.argtypes = [nusd_uint64_array_t]
    nusd_uint64_array_destroy.restype = None

# /home/anders/code/nanousd/nanousd-properties.h: 34
if _libs["nanousd"].has("nusd_property_get_type", "cdecl"):
    nusd_property_get_type = _libs["nanousd"].get("nusd_property_get_type", "cdecl")
    nusd_property_get_type.argtypes = [nusd_stage_t, String, POINTER(nusd_type_t)]
    nusd_property_get_type.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd-properties.h: 54
if _libs["nanousd"].has("nusd_attribute_get_token", "cdecl"):
    nusd_attribute_get_token = _libs["nanousd"].get("nusd_attribute_get_token", "cdecl")
    nusd_attribute_get_token.argtypes = [nusd_stage_t, String, c_double, POINTER(POINTER(c_char))]
    nusd_attribute_get_token.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd-properties.h: 74
if _libs["nanousd"].has("nusd_attribute_get_token_array", "cdecl"):
    nusd_attribute_get_token_array = _libs["nanousd"].get("nusd_attribute_get_token_array", "cdecl")
    nusd_attribute_get_token_array.argtypes = [nusd_stage_t, String, c_double, POINTER(nusd_token_array_iterator_t)]
    nusd_attribute_get_token_array.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd-properties.h: 94
if _libs["nanousd"].has("nusd_attribute_get_float", "cdecl"):
    nusd_attribute_get_float = _libs["nanousd"].get("nusd_attribute_get_float", "cdecl")
    nusd_attribute_get_float.argtypes = [nusd_stage_t, String, c_double, POINTER(c_float)]
    nusd_attribute_get_float.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd-properties.h: 114
if _libs["nanousd"].has("nusd_attribute_get_float_array", "cdecl"):
    nusd_attribute_get_float_array = _libs["nanousd"].get("nusd_attribute_get_float_array", "cdecl")
    nusd_attribute_get_float_array.argtypes = [nusd_stage_t, String, c_double, POINTER(nusd_float_array_t)]
    nusd_attribute_get_float_array.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd-properties.h: 133
if _libs["nanousd"].has("nusd_attribute_get_float2", "cdecl"):
    nusd_attribute_get_float2 = _libs["nanousd"].get("nusd_attribute_get_float2", "cdecl")
    nusd_attribute_get_float2.argtypes = [nusd_stage_t, String, c_double, POINTER(c_float)]
    nusd_attribute_get_float2.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd-properties.h: 153
if _libs["nanousd"].has("nusd_attribute_get_float2_array", "cdecl"):
    nusd_attribute_get_float2_array = _libs["nanousd"].get("nusd_attribute_get_float2_array", "cdecl")
    nusd_attribute_get_float2_array.argtypes = [nusd_stage_t, String, c_double, POINTER(nusd_float2_array_t)]
    nusd_attribute_get_float2_array.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd-properties.h: 172
if _libs["nanousd"].has("nusd_attribute_get_float3", "cdecl"):
    nusd_attribute_get_float3 = _libs["nanousd"].get("nusd_attribute_get_float3", "cdecl")
    nusd_attribute_get_float3.argtypes = [nusd_stage_t, String, c_double, POINTER(c_float)]
    nusd_attribute_get_float3.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd-properties.h: 192
if _libs["nanousd"].has("nusd_attribute_get_float3_array", "cdecl"):
    nusd_attribute_get_float3_array = _libs["nanousd"].get("nusd_attribute_get_float3_array", "cdecl")
    nusd_attribute_get_float3_array.argtypes = [nusd_stage_t, String, c_double, POINTER(nusd_float3_array_t)]
    nusd_attribute_get_float3_array.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd-properties.h: 211
if _libs["nanousd"].has("nusd_attribute_get_float4", "cdecl"):
    nusd_attribute_get_float4 = _libs["nanousd"].get("nusd_attribute_get_float4", "cdecl")
    nusd_attribute_get_float4.argtypes = [nusd_stage_t, String, c_double, POINTER(c_float)]
    nusd_attribute_get_float4.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd-properties.h: 231
if _libs["nanousd"].has("nusd_attribute_get_float4_array", "cdecl"):
    nusd_attribute_get_float4_array = _libs["nanousd"].get("nusd_attribute_get_float4_array", "cdecl")
    nusd_attribute_get_float4_array.argtypes = [nusd_stage_t, String, c_double, POINTER(nusd_float4_array_t)]
    nusd_attribute_get_float4_array.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd-properties.h: 248
if _libs["nanousd"].has("nusd_attribute_set_float", "cdecl"):
    nusd_attribute_set_float = _libs["nanousd"].get("nusd_attribute_set_float", "cdecl")
    nusd_attribute_set_float.argtypes = [nusd_stage_t, String, c_float, c_double]
    nusd_attribute_set_float.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd-properties.h: 268
if _libs["nanousd"].has("nusd_attribute_set_float_array", "cdecl"):
    nusd_attribute_set_float_array = _libs["nanousd"].get("nusd_attribute_set_float_array", "cdecl")
    nusd_attribute_set_float_array.argtypes = [nusd_stage_t, String, POINTER(c_float), c_size_t, c_double]
    nusd_attribute_set_float_array.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd-properties.h: 286
if _libs["nanousd"].has("nusd_attribute_set_float2", "cdecl"):
    nusd_attribute_set_float2 = _libs["nanousd"].get("nusd_attribute_set_float2", "cdecl")
    nusd_attribute_set_float2.argtypes = [nusd_stage_t, String, POINTER(c_float), c_double]
    nusd_attribute_set_float2.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd-properties.h: 306
if _libs["nanousd"].has("nusd_attribute_set_float2_array", "cdecl"):
    nusd_attribute_set_float2_array = _libs["nanousd"].get("nusd_attribute_set_float2_array", "cdecl")
    nusd_attribute_set_float2_array.argtypes = [nusd_stage_t, String, POINTER(c_float), c_size_t, c_double]
    nusd_attribute_set_float2_array.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd-properties.h: 324
if _libs["nanousd"].has("nusd_attribute_set_float3", "cdecl"):
    nusd_attribute_set_float3 = _libs["nanousd"].get("nusd_attribute_set_float3", "cdecl")
    nusd_attribute_set_float3.argtypes = [nusd_stage_t, String, POINTER(c_float), c_double]
    nusd_attribute_set_float3.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd-properties.h: 344
if _libs["nanousd"].has("nusd_attribute_set_float3_array", "cdecl"):
    nusd_attribute_set_float3_array = _libs["nanousd"].get("nusd_attribute_set_float3_array", "cdecl")
    nusd_attribute_set_float3_array.argtypes = [nusd_stage_t, String, POINTER(c_float), c_size_t, c_double]
    nusd_attribute_set_float3_array.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd-properties.h: 362
if _libs["nanousd"].has("nusd_attribute_set_float4", "cdecl"):
    nusd_attribute_set_float4 = _libs["nanousd"].get("nusd_attribute_set_float4", "cdecl")
    nusd_attribute_set_float4.argtypes = [nusd_stage_t, String, POINTER(c_float), c_double]
    nusd_attribute_set_float4.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd-properties.h: 382
if _libs["nanousd"].has("nusd_attribute_set_float4_array", "cdecl"):
    nusd_attribute_set_float4_array = _libs["nanousd"].get("nusd_attribute_set_float4_array", "cdecl")
    nusd_attribute_set_float4_array.argtypes = [nusd_stage_t, String, POINTER(c_float), c_size_t, c_double]
    nusd_attribute_set_float4_array.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd-properties.h: 402
if _libs["nanousd"].has("nusd_attribute_get_double", "cdecl"):
    nusd_attribute_get_double = _libs["nanousd"].get("nusd_attribute_get_double", "cdecl")
    nusd_attribute_get_double.argtypes = [nusd_stage_t, String, c_double, POINTER(c_double)]
    nusd_attribute_get_double.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd-properties.h: 422
if _libs["nanousd"].has("nusd_attribute_get_double_array", "cdecl"):
    nusd_attribute_get_double_array = _libs["nanousd"].get("nusd_attribute_get_double_array", "cdecl")
    nusd_attribute_get_double_array.argtypes = [nusd_stage_t, String, c_double, POINTER(nusd_double_array_t)]
    nusd_attribute_get_double_array.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd-properties.h: 441
if _libs["nanousd"].has("nusd_attribute_get_double2", "cdecl"):
    nusd_attribute_get_double2 = _libs["nanousd"].get("nusd_attribute_get_double2", "cdecl")
    nusd_attribute_get_double2.argtypes = [nusd_stage_t, String, c_double, POINTER(c_double)]
    nusd_attribute_get_double2.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd-properties.h: 461
if _libs["nanousd"].has("nusd_attribute_get_double2_array", "cdecl"):
    nusd_attribute_get_double2_array = _libs["nanousd"].get("nusd_attribute_get_double2_array", "cdecl")
    nusd_attribute_get_double2_array.argtypes = [nusd_stage_t, String, c_double, POINTER(nusd_double2_array_t)]
    nusd_attribute_get_double2_array.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd-properties.h: 481
if _libs["nanousd"].has("nusd_attribute_get_double3", "cdecl"):
    nusd_attribute_get_double3 = _libs["nanousd"].get("nusd_attribute_get_double3", "cdecl")
    nusd_attribute_get_double3.argtypes = [nusd_stage_t, String, c_double, POINTER(c_double)]
    nusd_attribute_get_double3.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd-properties.h: 502
if _libs["nanousd"].has("nusd_attribute_get_double3_array", "cdecl"):
    nusd_attribute_get_double3_array = _libs["nanousd"].get("nusd_attribute_get_double3_array", "cdecl")
    nusd_attribute_get_double3_array.argtypes = [nusd_stage_t, String, c_double, POINTER(nusd_double3_array_t)]
    nusd_attribute_get_double3_array.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd-properties.h: 522
if _libs["nanousd"].has("nusd_attribute_get_double4", "cdecl"):
    nusd_attribute_get_double4 = _libs["nanousd"].get("nusd_attribute_get_double4", "cdecl")
    nusd_attribute_get_double4.argtypes = [nusd_stage_t, String, c_double, POINTER(c_double)]
    nusd_attribute_get_double4.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd-properties.h: 543
if _libs["nanousd"].has("nusd_attribute_get_double4_array", "cdecl"):
    nusd_attribute_get_double4_array = _libs["nanousd"].get("nusd_attribute_get_double4_array", "cdecl")
    nusd_attribute_get_double4_array.argtypes = [nusd_stage_t, String, c_double, POINTER(nusd_double4_array_t)]
    nusd_attribute_get_double4_array.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd-properties.h: 563
if _libs["nanousd"].has("nusd_attribute_set_double", "cdecl"):
    nusd_attribute_set_double = _libs["nanousd"].get("nusd_attribute_set_double", "cdecl")
    nusd_attribute_set_double.argtypes = [nusd_stage_t, String, c_double, c_double]
    nusd_attribute_set_double.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd-properties.h: 585
if _libs["nanousd"].has("nusd_attribute_set_double_array", "cdecl"):
    nusd_attribute_set_double_array = _libs["nanousd"].get("nusd_attribute_set_double_array", "cdecl")
    nusd_attribute_set_double_array.argtypes = [nusd_stage_t, String, POINTER(c_double), c_size_t, c_double]
    nusd_attribute_set_double_array.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd-properties.h: 605
if _libs["nanousd"].has("nusd_attribute_set_double2", "cdecl"):
    nusd_attribute_set_double2 = _libs["nanousd"].get("nusd_attribute_set_double2", "cdecl")
    nusd_attribute_set_double2.argtypes = [nusd_stage_t, String, POINTER(c_double), c_double]
    nusd_attribute_set_double2.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd-properties.h: 627
if _libs["nanousd"].has("nusd_attribute_set_double2_array", "cdecl"):
    nusd_attribute_set_double2_array = _libs["nanousd"].get("nusd_attribute_set_double2_array", "cdecl")
    nusd_attribute_set_double2_array.argtypes = [nusd_stage_t, String, POINTER(c_double), c_size_t, c_double]
    nusd_attribute_set_double2_array.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd-properties.h: 647
if _libs["nanousd"].has("nusd_attribute_set_double3", "cdecl"):
    nusd_attribute_set_double3 = _libs["nanousd"].get("nusd_attribute_set_double3", "cdecl")
    nusd_attribute_set_double3.argtypes = [nusd_stage_t, String, POINTER(c_double), c_double]
    nusd_attribute_set_double3.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd-properties.h: 669
if _libs["nanousd"].has("nusd_attribute_set_double3_array", "cdecl"):
    nusd_attribute_set_double3_array = _libs["nanousd"].get("nusd_attribute_set_double3_array", "cdecl")
    nusd_attribute_set_double3_array.argtypes = [nusd_stage_t, String, POINTER(c_double), c_size_t, c_double]
    nusd_attribute_set_double3_array.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd-properties.h: 689
if _libs["nanousd"].has("nusd_attribute_set_double4", "cdecl"):
    nusd_attribute_set_double4 = _libs["nanousd"].get("nusd_attribute_set_double4", "cdecl")
    nusd_attribute_set_double4.argtypes = [nusd_stage_t, String, POINTER(c_double), c_double]
    nusd_attribute_set_double4.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd-properties.h: 711
if _libs["nanousd"].has("nusd_attribute_set_double4_array", "cdecl"):
    nusd_attribute_set_double4_array = _libs["nanousd"].get("nusd_attribute_set_double4_array", "cdecl")
    nusd_attribute_set_double4_array.argtypes = [nusd_stage_t, String, POINTER(c_double), c_size_t, c_double]
    nusd_attribute_set_double4_array.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd-properties.h: 732
if _libs["nanousd"].has("nusd_attribute_get_int", "cdecl"):
    nusd_attribute_get_int = _libs["nanousd"].get("nusd_attribute_get_int", "cdecl")
    nusd_attribute_get_int.argtypes = [nusd_stage_t, String, c_double, POINTER(c_int)]
    nusd_attribute_get_int.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd-properties.h: 753
if _libs["nanousd"].has("nusd_attribute_get_int_array", "cdecl"):
    nusd_attribute_get_int_array = _libs["nanousd"].get("nusd_attribute_get_int_array", "cdecl")
    nusd_attribute_get_int_array.argtypes = [nusd_stage_t, String, c_double, POINTER(nusd_int_array_t)]
    nusd_attribute_get_int_array.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd-properties.h: 773
if _libs["nanousd"].has("nusd_attribute_get_int2", "cdecl"):
    nusd_attribute_get_int2 = _libs["nanousd"].get("nusd_attribute_get_int2", "cdecl")
    nusd_attribute_get_int2.argtypes = [nusd_stage_t, String, c_double, POINTER(c_int)]
    nusd_attribute_get_int2.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd-properties.h: 794
if _libs["nanousd"].has("nusd_attribute_get_int2_array", "cdecl"):
    nusd_attribute_get_int2_array = _libs["nanousd"].get("nusd_attribute_get_int2_array", "cdecl")
    nusd_attribute_get_int2_array.argtypes = [nusd_stage_t, String, c_double, POINTER(nusd_int2_array_t)]
    nusd_attribute_get_int2_array.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd-properties.h: 814
if _libs["nanousd"].has("nusd_attribute_get_int3", "cdecl"):
    nusd_attribute_get_int3 = _libs["nanousd"].get("nusd_attribute_get_int3", "cdecl")
    nusd_attribute_get_int3.argtypes = [nusd_stage_t, String, c_double, POINTER(c_int)]
    nusd_attribute_get_int3.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd-properties.h: 835
if _libs["nanousd"].has("nusd_attribute_get_int3_array", "cdecl"):
    nusd_attribute_get_int3_array = _libs["nanousd"].get("nusd_attribute_get_int3_array", "cdecl")
    nusd_attribute_get_int3_array.argtypes = [nusd_stage_t, String, c_double, POINTER(nusd_int3_array_t)]
    nusd_attribute_get_int3_array.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd-properties.h: 855
if _libs["nanousd"].has("nusd_attribute_get_int4", "cdecl"):
    nusd_attribute_get_int4 = _libs["nanousd"].get("nusd_attribute_get_int4", "cdecl")
    nusd_attribute_get_int4.argtypes = [nusd_stage_t, String, c_double, POINTER(c_int)]
    nusd_attribute_get_int4.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd-properties.h: 876
if _libs["nanousd"].has("nusd_attribute_get_int4_array", "cdecl"):
    nusd_attribute_get_int4_array = _libs["nanousd"].get("nusd_attribute_get_int4_array", "cdecl")
    nusd_attribute_get_int4_array.argtypes = [nusd_stage_t, String, c_double, POINTER(nusd_int4_array_t)]
    nusd_attribute_get_int4_array.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd-properties.h: 897
if _libs["nanousd"].has("nusd_attribute_get_int64", "cdecl"):
    nusd_attribute_get_int64 = _libs["nanousd"].get("nusd_attribute_get_int64", "cdecl")
    nusd_attribute_get_int64.argtypes = [nusd_stage_t, String, c_double, POINTER(c_int64)]
    nusd_attribute_get_int64.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd-properties.h: 918
if _libs["nanousd"].has("nusd_attribute_get_int64_array", "cdecl"):
    nusd_attribute_get_int64_array = _libs["nanousd"].get("nusd_attribute_get_int64_array", "cdecl")
    nusd_attribute_get_int64_array.argtypes = [nusd_stage_t, String, c_double, POINTER(nusd_int64_array_t)]
    nusd_attribute_get_int64_array.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd-properties.h: 938
if _libs["nanousd"].has("nusd_attribute_set_int", "cdecl"):
    nusd_attribute_set_int = _libs["nanousd"].get("nusd_attribute_set_int", "cdecl")
    nusd_attribute_set_int.argtypes = [nusd_stage_t, String, c_int, c_double]
    nusd_attribute_set_int.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd-properties.h: 960
if _libs["nanousd"].has("nusd_attribute_set_int_array", "cdecl"):
    nusd_attribute_set_int_array = _libs["nanousd"].get("nusd_attribute_set_int_array", "cdecl")
    nusd_attribute_set_int_array.argtypes = [nusd_stage_t, String, POINTER(c_int), c_size_t, c_double]
    nusd_attribute_set_int_array.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd-properties.h: 980
if _libs["nanousd"].has("nusd_attribute_set_int2", "cdecl"):
    nusd_attribute_set_int2 = _libs["nanousd"].get("nusd_attribute_set_int2", "cdecl")
    nusd_attribute_set_int2.argtypes = [nusd_stage_t, String, POINTER(c_int), c_double]
    nusd_attribute_set_int2.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd-properties.h: 1002
if _libs["nanousd"].has("nusd_attribute_set_int2_array", "cdecl"):
    nusd_attribute_set_int2_array = _libs["nanousd"].get("nusd_attribute_set_int2_array", "cdecl")
    nusd_attribute_set_int2_array.argtypes = [nusd_stage_t, String, POINTER(c_int), c_size_t, c_double]
    nusd_attribute_set_int2_array.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd-properties.h: 1022
if _libs["nanousd"].has("nusd_attribute_set_int3", "cdecl"):
    nusd_attribute_set_int3 = _libs["nanousd"].get("nusd_attribute_set_int3", "cdecl")
    nusd_attribute_set_int3.argtypes = [nusd_stage_t, String, POINTER(c_int), c_double]
    nusd_attribute_set_int3.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd-properties.h: 1044
if _libs["nanousd"].has("nusd_attribute_set_int3_array", "cdecl"):
    nusd_attribute_set_int3_array = _libs["nanousd"].get("nusd_attribute_set_int3_array", "cdecl")
    nusd_attribute_set_int3_array.argtypes = [nusd_stage_t, String, POINTER(c_int), c_size_t, c_double]
    nusd_attribute_set_int3_array.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd-properties.h: 1064
if _libs["nanousd"].has("nusd_attribute_set_int4", "cdecl"):
    nusd_attribute_set_int4 = _libs["nanousd"].get("nusd_attribute_set_int4", "cdecl")
    nusd_attribute_set_int4.argtypes = [nusd_stage_t, String, POINTER(c_int), c_double]
    nusd_attribute_set_int4.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd-properties.h: 1086
if _libs["nanousd"].has("nusd_attribute_set_int4_array", "cdecl"):
    nusd_attribute_set_int4_array = _libs["nanousd"].get("nusd_attribute_set_int4_array", "cdecl")
    nusd_attribute_set_int4_array.argtypes = [nusd_stage_t, String, POINTER(c_int), c_size_t, c_double]
    nusd_attribute_set_int4_array.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd-properties.h: 1106
if _libs["nanousd"].has("nusd_attribute_set_int64", "cdecl"):
    nusd_attribute_set_int64 = _libs["nanousd"].get("nusd_attribute_set_int64", "cdecl")
    nusd_attribute_set_int64.argtypes = [nusd_stage_t, String, c_int64, c_double]
    nusd_attribute_set_int64.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd-properties.h: 1128
if _libs["nanousd"].has("nusd_attribute_set_int64_array", "cdecl"):
    nusd_attribute_set_int64_array = _libs["nanousd"].get("nusd_attribute_set_int64_array", "cdecl")
    nusd_attribute_set_int64_array.argtypes = [nusd_stage_t, String, POINTER(c_int64), c_size_t, c_double]
    nusd_attribute_set_int64_array.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd-properties.h: 1149
if _libs["nanousd"].has("nusd_attribute_get_bool", "cdecl"):
    nusd_attribute_get_bool = _libs["nanousd"].get("nusd_attribute_get_bool", "cdecl")
    nusd_attribute_get_bool.argtypes = [nusd_stage_t, String, c_double, POINTER(c_bool)]
    nusd_attribute_get_bool.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd-properties.h: 1170
if _libs["nanousd"].has("nusd_attribute_get_bool_array", "cdecl"):
    nusd_attribute_get_bool_array = _libs["nanousd"].get("nusd_attribute_get_bool_array", "cdecl")
    nusd_attribute_get_bool_array.argtypes = [nusd_stage_t, String, c_double, POINTER(nusd_bool_array_t)]
    nusd_attribute_get_bool_array.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd-properties.h: 1191
if _libs["nanousd"].has("nusd_attribute_get_matrix2d", "cdecl"):
    nusd_attribute_get_matrix2d = _libs["nanousd"].get("nusd_attribute_get_matrix2d", "cdecl")
    nusd_attribute_get_matrix2d.argtypes = [nusd_stage_t, String, c_double, POINTER(c_double)]
    nusd_attribute_get_matrix2d.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd-properties.h: 1212
if _libs["nanousd"].has("nusd_attribute_get_matrix2d_array", "cdecl"):
    nusd_attribute_get_matrix2d_array = _libs["nanousd"].get("nusd_attribute_get_matrix2d_array", "cdecl")
    nusd_attribute_get_matrix2d_array.argtypes = [nusd_stage_t, String, c_double, POINTER(nusd_matrix2d_array_t)]
    nusd_attribute_get_matrix2d_array.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd-properties.h: 1233
if _libs["nanousd"].has("nusd_attribute_get_matrix3d", "cdecl"):
    nusd_attribute_get_matrix3d = _libs["nanousd"].get("nusd_attribute_get_matrix3d", "cdecl")
    nusd_attribute_get_matrix3d.argtypes = [nusd_stage_t, String, c_double, POINTER(c_double)]
    nusd_attribute_get_matrix3d.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd-properties.h: 1254
if _libs["nanousd"].has("nusd_attribute_get_matrix3d_array", "cdecl"):
    nusd_attribute_get_matrix3d_array = _libs["nanousd"].get("nusd_attribute_get_matrix3d_array", "cdecl")
    nusd_attribute_get_matrix3d_array.argtypes = [nusd_stage_t, String, c_double, POINTER(nusd_matrix3d_array_t)]
    nusd_attribute_get_matrix3d_array.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd-properties.h: 1275
if _libs["nanousd"].has("nusd_attribute_get_matrix4d", "cdecl"):
    nusd_attribute_get_matrix4d = _libs["nanousd"].get("nusd_attribute_get_matrix4d", "cdecl")
    nusd_attribute_get_matrix4d.argtypes = [nusd_stage_t, String, c_double, POINTER(c_double)]
    nusd_attribute_get_matrix4d.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd-properties.h: 1296
if _libs["nanousd"].has("nusd_attribute_get_matrix4d_array", "cdecl"):
    nusd_attribute_get_matrix4d_array = _libs["nanousd"].get("nusd_attribute_get_matrix4d_array", "cdecl")
    nusd_attribute_get_matrix4d_array.argtypes = [nusd_stage_t, String, c_double, POINTER(nusd_matrix4d_array_t)]
    nusd_attribute_get_matrix4d_array.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd-properties.h: 1316
if _libs["nanousd"].has("nusd_attribute_set_bool", "cdecl"):
    nusd_attribute_set_bool = _libs["nanousd"].get("nusd_attribute_set_bool", "cdecl")
    nusd_attribute_set_bool.argtypes = [nusd_stage_t, String, c_bool, c_double]
    nusd_attribute_set_bool.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd-properties.h: 1338
if _libs["nanousd"].has("nusd_attribute_set_bool_array", "cdecl"):
    nusd_attribute_set_bool_array = _libs["nanousd"].get("nusd_attribute_set_bool_array", "cdecl")
    nusd_attribute_set_bool_array.argtypes = [nusd_stage_t, String, POINTER(c_bool), c_size_t, c_double]
    nusd_attribute_set_bool_array.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd-properties.h: 1359
if _libs["nanousd"].has("nusd_attribute_set_matrix2d", "cdecl"):
    nusd_attribute_set_matrix2d = _libs["nanousd"].get("nusd_attribute_set_matrix2d", "cdecl")
    nusd_attribute_set_matrix2d.argtypes = [nusd_stage_t, String, POINTER(c_double), c_double]
    nusd_attribute_set_matrix2d.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd-properties.h: 1381
if _libs["nanousd"].has("nusd_attribute_set_matrix2d_array", "cdecl"):
    nusd_attribute_set_matrix2d_array = _libs["nanousd"].get("nusd_attribute_set_matrix2d_array", "cdecl")
    nusd_attribute_set_matrix2d_array.argtypes = [nusd_stage_t, String, POINTER(c_double), c_size_t, c_double]
    nusd_attribute_set_matrix2d_array.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd-properties.h: 1402
if _libs["nanousd"].has("nusd_attribute_set_matrix3d", "cdecl"):
    nusd_attribute_set_matrix3d = _libs["nanousd"].get("nusd_attribute_set_matrix3d", "cdecl")
    nusd_attribute_set_matrix3d.argtypes = [nusd_stage_t, String, POINTER(c_double), c_double]
    nusd_attribute_set_matrix3d.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd-properties.h: 1424
if _libs["nanousd"].has("nusd_attribute_set_matrix3d_array", "cdecl"):
    nusd_attribute_set_matrix3d_array = _libs["nanousd"].get("nusd_attribute_set_matrix3d_array", "cdecl")
    nusd_attribute_set_matrix3d_array.argtypes = [nusd_stage_t, String, POINTER(c_double), c_size_t, c_double]
    nusd_attribute_set_matrix3d_array.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd-properties.h: 1445
if _libs["nanousd"].has("nusd_attribute_set_matrix4d", "cdecl"):
    nusd_attribute_set_matrix4d = _libs["nanousd"].get("nusd_attribute_set_matrix4d", "cdecl")
    nusd_attribute_set_matrix4d.argtypes = [nusd_stage_t, String, POINTER(c_double), c_double]
    nusd_attribute_set_matrix4d.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd-properties.h: 1467
if _libs["nanousd"].has("nusd_attribute_set_matrix4d_array", "cdecl"):
    nusd_attribute_set_matrix4d_array = _libs["nanousd"].get("nusd_attribute_set_matrix4d_array", "cdecl")
    nusd_attribute_set_matrix4d_array.argtypes = [nusd_stage_t, String, POINTER(c_double), c_size_t, c_double]
    nusd_attribute_set_matrix4d_array.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd-properties.h: 1488
if _libs["nanousd"].has("nusd_attribute_get_uint", "cdecl"):
    nusd_attribute_get_uint = _libs["nanousd"].get("nusd_attribute_get_uint", "cdecl")
    nusd_attribute_get_uint.argtypes = [nusd_stage_t, String, c_double, POINTER(c_uint)]
    nusd_attribute_get_uint.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd-properties.h: 1509
if _libs["nanousd"].has("nusd_attribute_get_uint_array", "cdecl"):
    nusd_attribute_get_uint_array = _libs["nanousd"].get("nusd_attribute_get_uint_array", "cdecl")
    nusd_attribute_get_uint_array.argtypes = [nusd_stage_t, String, c_double, POINTER(nusd_uint_array_t)]
    nusd_attribute_get_uint_array.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd-properties.h: 1530
if _libs["nanousd"].has("nusd_attribute_get_uint64", "cdecl"):
    nusd_attribute_get_uint64 = _libs["nanousd"].get("nusd_attribute_get_uint64", "cdecl")
    nusd_attribute_get_uint64.argtypes = [nusd_stage_t, String, c_double, POINTER(uint64_t)]
    nusd_attribute_get_uint64.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd-properties.h: 1551
if _libs["nanousd"].has("nusd_attribute_get_uint64_array", "cdecl"):
    nusd_attribute_get_uint64_array = _libs["nanousd"].get("nusd_attribute_get_uint64_array", "cdecl")
    nusd_attribute_get_uint64_array.argtypes = [nusd_stage_t, String, c_double, POINTER(nusd_uint64_array_t)]
    nusd_attribute_get_uint64_array.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd-properties.h: 1572
if _libs["nanousd"].has("nusd_attribute_get_uchar", "cdecl"):
    nusd_attribute_get_uchar = _libs["nanousd"].get("nusd_attribute_get_uchar", "cdecl")
    nusd_attribute_get_uchar.argtypes = [nusd_stage_t, String, c_double, POINTER(c_ubyte)]
    nusd_attribute_get_uchar.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd-properties.h: 1593
if _libs["nanousd"].has("nusd_attribute_get_uchar_array", "cdecl"):
    nusd_attribute_get_uchar_array = _libs["nanousd"].get("nusd_attribute_get_uchar_array", "cdecl")
    nusd_attribute_get_uchar_array.argtypes = [nusd_stage_t, String, c_double, POINTER(nusd_uchar_array_t)]
    nusd_attribute_get_uchar_array.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd-properties.h: 1613
if _libs["nanousd"].has("nusd_attribute_set_uint", "cdecl"):
    nusd_attribute_set_uint = _libs["nanousd"].get("nusd_attribute_set_uint", "cdecl")
    nusd_attribute_set_uint.argtypes = [nusd_stage_t, String, c_uint, c_double]
    nusd_attribute_set_uint.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd-properties.h: 1635
if _libs["nanousd"].has("nusd_attribute_set_uint_array", "cdecl"):
    nusd_attribute_set_uint_array = _libs["nanousd"].get("nusd_attribute_set_uint_array", "cdecl")
    nusd_attribute_set_uint_array.argtypes = [nusd_stage_t, String, POINTER(c_uint), c_size_t, c_double]
    nusd_attribute_set_uint_array.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd-properties.h: 1655
if _libs["nanousd"].has("nusd_attribute_set_uint64", "cdecl"):
    nusd_attribute_set_uint64 = _libs["nanousd"].get("nusd_attribute_set_uint64", "cdecl")
    nusd_attribute_set_uint64.argtypes = [nusd_stage_t, String, uint64_t, c_double]
    nusd_attribute_set_uint64.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd-properties.h: 1677
if _libs["nanousd"].has("nusd_attribute_set_uint64_array", "cdecl"):
    nusd_attribute_set_uint64_array = _libs["nanousd"].get("nusd_attribute_set_uint64_array", "cdecl")
    nusd_attribute_set_uint64_array.argtypes = [nusd_stage_t, String, POINTER(uint64_t), c_size_t, c_double]
    nusd_attribute_set_uint64_array.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd-properties.h: 1697
if _libs["nanousd"].has("nusd_attribute_set_uchar", "cdecl"):
    nusd_attribute_set_uchar = _libs["nanousd"].get("nusd_attribute_set_uchar", "cdecl")
    nusd_attribute_set_uchar.argtypes = [nusd_stage_t, String, c_ubyte, c_double]
    nusd_attribute_set_uchar.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd-properties.h: 1719
if _libs["nanousd"].has("nusd_attribute_set_uchar_array", "cdecl"):
    nusd_attribute_set_uchar_array = _libs["nanousd"].get("nusd_attribute_set_uchar_array", "cdecl")
    nusd_attribute_set_uchar_array.argtypes = [nusd_stage_t, String, POINTER(c_ubyte), c_size_t, c_double]
    nusd_attribute_set_uchar_array.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd-properties.h: 1738
if _libs["nanousd"].has("nusd_attribute_set_token", "cdecl"):
    nusd_attribute_set_token = _libs["nanousd"].get("nusd_attribute_set_token", "cdecl")
    nusd_attribute_set_token.argtypes = [nusd_stage_t, String, String, c_double]
    nusd_attribute_set_token.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd-properties.h: 1759
if _libs["nanousd"].has("nusd_attribute_set_token_array", "cdecl"):
    nusd_attribute_set_token_array = _libs["nanousd"].get("nusd_attribute_set_token_array", "cdecl")
    nusd_attribute_set_token_array.argtypes = [nusd_stage_t, String, POINTER(POINTER(c_char)), c_size_t, c_double]
    nusd_attribute_set_token_array.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd-properties.h: 1776
if _libs["nanousd"].has("nusd_relationship_get_targets", "cdecl"):
    nusd_relationship_get_targets = _libs["nanousd"].get("nusd_relationship_get_targets", "cdecl")
    nusd_relationship_get_targets.argtypes = [nusd_stage_t, String, POINTER(nusd_relationship_targets_iterator_t), POINTER(c_size_t)]
    nusd_relationship_get_targets.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd-properties.h: 1795
if _libs["nanousd"].has("nusd_attribute_get_asset", "cdecl"):
    nusd_attribute_get_asset = _libs["nanousd"].get("nusd_attribute_get_asset", "cdecl")
    nusd_attribute_get_asset.argtypes = [nusd_stage_t, String, c_double, POINTER(nusd_asset_path_t)]
    nusd_attribute_get_asset.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd-properties.h: 1814
if _libs["nanousd"].has("nusd_attribute_get_asset_array", "cdecl"):
    nusd_attribute_get_asset_array = _libs["nanousd"].get("nusd_attribute_get_asset_array", "cdecl")
    nusd_attribute_get_asset_array.argtypes = [nusd_stage_t, String, c_double, POINTER(nusd_asset_path_array_iterator_t)]
    nusd_attribute_get_asset_array.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd-properties.h: 1833
if _libs["nanousd"].has("nusd_attribute_set_asset", "cdecl"):
    nusd_attribute_set_asset = _libs["nanousd"].get("nusd_attribute_set_asset", "cdecl")
    nusd_attribute_set_asset.argtypes = [nusd_stage_t, String, String, c_double]
    nusd_attribute_set_asset.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd-properties.h: 1854
if _libs["nanousd"].has("nusd_attribute_set_asset_array", "cdecl"):
    nusd_attribute_set_asset_array = _libs["nanousd"].get("nusd_attribute_set_asset_array", "cdecl")
    nusd_attribute_set_asset_array.argtypes = [nusd_stage_t, String, POINTER(POINTER(c_char)), c_size_t, c_double]
    nusd_attribute_set_asset_array.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd-properties.h: 1866
if _libs["nanousd"].has("nusd_attribute_set_color_space", "cdecl"):
    nusd_attribute_set_color_space = _libs["nanousd"].get("nusd_attribute_set_color_space", "cdecl")
    nusd_attribute_set_color_space.argtypes = [nusd_stage_t, String, nusd_colorspace_t]
    nusd_attribute_set_color_space.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd-properties.h: 1879
if _libs["nanousd"].has("nusd_attribute_get_color_space", "cdecl"):
    nusd_attribute_get_color_space = _libs["nanousd"].get("nusd_attribute_get_color_space", "cdecl")
    nusd_attribute_get_color_space.argtypes = [nusd_stage_t, String, POINTER(nusd_colorspace_t)]
    nusd_attribute_get_color_space.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd.h: 35
if _libs["nanousd"].has("nusd_stage_open", "cdecl"):
    nusd_stage_open = _libs["nanousd"].get("nusd_stage_open", "cdecl")
    nusd_stage_open.argtypes = [String, POINTER(nusd_stage_t)]
    nusd_stage_open.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd.h: 51
if _libs["nanousd"].has("nusd_stage_create_new", "cdecl"):
    nusd_stage_create_new = _libs["nanousd"].get("nusd_stage_create_new", "cdecl")
    nusd_stage_create_new.argtypes = [String, POINTER(nusd_stage_t)]
    nusd_stage_create_new.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd.h: 67
if _libs["nanousd"].has("nusd_stage_create_in_memory", "cdecl"):
    nusd_stage_create_in_memory = _libs["nanousd"].get("nusd_stage_create_in_memory", "cdecl")
    nusd_stage_create_in_memory.argtypes = [String, POINTER(nusd_stage_t)]
    nusd_stage_create_in_memory.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd.h: 79
if _libs["nanousd"].has("nusd_stage_save", "cdecl"):
    nusd_stage_save = _libs["nanousd"].get("nusd_stage_save", "cdecl")
    nusd_stage_save.argtypes = [nusd_stage_t]
    nusd_stage_save.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd.h: 92
if _libs["nanousd"].has("nusd_stage_save_as", "cdecl"):
    nusd_stage_save_as = _libs["nanousd"].get("nusd_stage_save_as", "cdecl")
    nusd_stage_save_as.argtypes = [nusd_stage_t, String]
    nusd_stage_save_as.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd.h: 104
if _libs["nanousd"].has("nusd_stage_destroy", "cdecl"):
    nusd_stage_destroy = _libs["nanousd"].get("nusd_stage_destroy", "cdecl")
    nusd_stage_destroy.argtypes = [nusd_stage_t]
    nusd_stage_destroy.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd.h: 120
if _libs["nanousd"].has("nusd_stage_define_prim", "cdecl"):
    nusd_stage_define_prim = _libs["nanousd"].get("nusd_stage_define_prim", "cdecl")
    nusd_stage_define_prim.argtypes = [nusd_stage_t, String, String]
    nusd_stage_define_prim.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd.h: 133
if _libs["nanousd"].has("nusd_stage_path_is_valid_prim", "cdecl"):
    nusd_stage_path_is_valid_prim = _libs["nanousd"].get("nusd_stage_path_is_valid_prim", "cdecl")
    nusd_stage_path_is_valid_prim.argtypes = [nusd_stage_t, String]
    nusd_stage_path_is_valid_prim.restype = c_bool

# /home/anders/code/nanousd/nanousd.h: 148
if _libs["nanousd"].has("nusd_stage_traverse", "cdecl"):
    nusd_stage_traverse = _libs["nanousd"].get("nusd_stage_traverse", "cdecl")
    nusd_stage_traverse.argtypes = [nusd_stage_t, POINTER(nusd_prim_iterator_t)]
    nusd_stage_traverse.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd.h: 174
if _libs["nanousd"].has("nusd_prim_get_properties", "cdecl"):
    nusd_prim_get_properties = _libs["nanousd"].get("nusd_prim_get_properties", "cdecl")
    nusd_prim_get_properties.argtypes = [nusd_stage_t, String, POINTER(nusd_property_iterator_t)]
    nusd_prim_get_properties.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd.h: 190
if _libs["nanousd"].has("nusd_prim_get_attributes", "cdecl"):
    nusd_prim_get_attributes = _libs["nanousd"].get("nusd_prim_get_attributes", "cdecl")
    nusd_prim_get_attributes.argtypes = [nusd_stage_t, String, POINTER(nusd_attribute_iterator_t)]
    nusd_prim_get_attributes.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd.h: 206
if _libs["nanousd"].has("nusd_prim_get_relationships", "cdecl"):
    nusd_prim_get_relationships = _libs["nanousd"].get("nusd_prim_get_relationships", "cdecl")
    nusd_prim_get_relationships.argtypes = [nusd_stage_t, String, POINTER(nusd_relationship_iterator_t)]
    nusd_prim_get_relationships.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd.h: 226
if _libs["nanousd"].has("nusd_prim_create_property", "cdecl"):
    nusd_prim_create_property = _libs["nanousd"].get("nusd_prim_create_property", "cdecl")
    nusd_prim_create_property.argtypes = [nusd_stage_t, String, String, nusd_type_t]
    nusd_prim_create_property.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd.h: 247
if _libs["nanousd"].has("nusd_prim_set_transform", "cdecl"):
    nusd_prim_set_transform = _libs["nanousd"].get("nusd_prim_set_transform", "cdecl")
    nusd_prim_set_transform.argtypes = [nusd_stage_t, String, POINTER(c_double), c_double]
    nusd_prim_set_transform.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd.h: 270
if _libs["nanousd"].has("nusd_prim_compute_local_to_world_transform", "cdecl"):
    nusd_prim_compute_local_to_world_transform = _libs["nanousd"].get("nusd_prim_compute_local_to_world_transform", "cdecl")
    nusd_prim_compute_local_to_world_transform.argtypes = [nusd_stage_t, String, c_double, POINTER(c_double)]
    nusd_prim_compute_local_to_world_transform.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd.h: 286
if _libs["nanousd"].has("nusd_path_get_name", "cdecl"):
    nusd_path_get_name = _libs["nanousd"].get("nusd_path_get_name", "cdecl")
    nusd_path_get_name.argtypes = [String]
    nusd_path_get_name.restype = c_char_p

# /home/anders/code/nanousd/nanousd.h: 298
if _libs["nanousd"].has("nusd_asset_path_get_asset_path", "cdecl"):
    nusd_asset_path_get_asset_path = _libs["nanousd"].get("nusd_asset_path_get_asset_path", "cdecl")
    nusd_asset_path_get_asset_path.argtypes = [nusd_asset_path_t]
    nusd_asset_path_get_asset_path.restype = c_char_p

# /home/anders/code/nanousd/nanousd.h: 307
if _libs["nanousd"].has("nusd_asset_path_destroy", "cdecl"):
    nusd_asset_path_destroy = _libs["nanousd"].get("nusd_asset_path_destroy", "cdecl")
    nusd_asset_path_destroy.argtypes = [nusd_asset_path_t]
    nusd_asset_path_destroy.restype = None

# /home/anders/code/nanousd/nanousd-cameras.h: 31
if _libs["nanousd"].has("nusd_camera_define", "cdecl"):
    nusd_camera_define = _libs["nanousd"].get("nusd_camera_define", "cdecl")
    nusd_camera_define.argtypes = [nusd_stage_t, String]
    nusd_camera_define.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd-cameras.h: 50
if _libs["nanousd"].has("nusd_camera_set_fov_w", "cdecl"):
    nusd_camera_set_fov_w = _libs["nanousd"].get("nusd_camera_set_fov_w", "cdecl")
    nusd_camera_set_fov_w.argtypes = [nusd_stage_t, String, c_float, c_double]
    nusd_camera_set_fov_w.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd-cameras.h: 75
if _libs["nanousd"].has("nusd_camera_set_exposure", "cdecl"):
    nusd_camera_set_exposure = _libs["nanousd"].get("nusd_camera_set_exposure", "cdecl")
    nusd_camera_set_exposure.argtypes = [nusd_stage_t, String, c_float, c_float, c_float, c_float, c_float, c_double]
    nusd_camera_set_exposure.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd-cameras.h: 96
if _libs["nanousd"].has("nusd_camera_set_clipping_range", "cdecl"):
    nusd_camera_set_clipping_range = _libs["nanousd"].get("nusd_camera_set_clipping_range", "cdecl")
    nusd_camera_set_clipping_range.argtypes = [nusd_stage_t, String, c_float, c_float, c_double]
    nusd_camera_set_clipping_range.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd-cameras.h: 118
if _libs["nanousd"].has("nusd_camera_set_aperture", "cdecl"):
    nusd_camera_set_aperture = _libs["nanousd"].get("nusd_camera_set_aperture", "cdecl")
    nusd_camera_set_aperture.argtypes = [nusd_stage_t, String, c_float, c_float, c_double]
    nusd_camera_set_aperture.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd-materials.h: 32
if _libs["nanousd"].has("nusd_material_define", "cdecl"):
    nusd_material_define = _libs["nanousd"].get("nusd_material_define", "cdecl")
    nusd_material_define.argtypes = [nusd_stage_t, String]
    nusd_material_define.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd-materials.h: 50
if _libs["nanousd"].has("nusd_shader_define", "cdecl"):
    nusd_shader_define = _libs["nanousd"].get("nusd_shader_define", "cdecl")
    nusd_shader_define.argtypes = [nusd_stage_t, String, String]
    nusd_shader_define.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd-materials.h: 72
if _libs["nanousd"].has("nusd_shader_create_input", "cdecl"):
    nusd_shader_create_input = _libs["nanousd"].get("nusd_shader_create_input", "cdecl")
    nusd_shader_create_input.argtypes = [nusd_stage_t, String, String, nusd_type_t]
    nusd_shader_create_input.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd-materials.h: 94
if _libs["nanousd"].has("nusd_shader_create_output", "cdecl"):
    nusd_shader_create_output = _libs["nanousd"].get("nusd_shader_create_output", "cdecl")
    nusd_shader_create_output.argtypes = [nusd_stage_t, String, String, nusd_type_t]
    nusd_shader_create_output.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd-materials.h: 114
if _libs["nanousd"].has("nusd_shader_connect", "cdecl"):
    nusd_shader_connect = _libs["nanousd"].get("nusd_shader_connect", "cdecl")
    nusd_shader_connect.argtypes = [nusd_stage_t, String, String]
    nusd_shader_connect.restype = nusd_result_t

# /home/anders/code/nanousd/nanousd-types.h: 10
try:
    NUSD_TIMECODE_DEFAULT = 0.0
except:
    pass

nusd_asset_path_s = struct_nusd_asset_path_s# /home/anders/code/nanousd/nanousd-types.h: 37

nusd_prim_iterator_s = struct_nusd_prim_iterator_s# /home/anders/code/nanousd/nanousd-iterators.h: 17

nusd_property_iterator_s = struct_nusd_property_iterator_s# /home/anders/code/nanousd/nanousd-iterators.h: 18

nusd_attribute_iterator_s = struct_nusd_attribute_iterator_s# /home/anders/code/nanousd/nanousd-iterators.h: 19

nusd_relationship_iterator_s = struct_nusd_relationship_iterator_s# /home/anders/code/nanousd/nanousd-iterators.h: 20

nusd_relationship_targets_iterator_s = struct_nusd_relationship_targets_iterator_s# /home/anders/code/nanousd/nanousd-iterators.h: 21

nusd_token_array_iterator_s = struct_nusd_token_array_iterator_s# /home/anders/code/nanousd/nanousd-iterators.h: 22

nusd_asset_path_array_iterator_s = struct_nusd_asset_path_array_iterator_s# /home/anders/code/nanousd/nanousd-iterators.h: 23

nusd_bool_array_s = struct_nusd_bool_array_s# /home/anders/code/nanousd/nanousd-arrays.h: 10

nusd_float_array_s = struct_nusd_float_array_s# /home/anders/code/nanousd/nanousd-arrays.h: 12

nusd_float2_array_s = struct_nusd_float2_array_s# /home/anders/code/nanousd/nanousd-arrays.h: 13

nusd_float3_array_s = struct_nusd_float3_array_s# /home/anders/code/nanousd/nanousd-arrays.h: 14

nusd_float4_array_s = struct_nusd_float4_array_s# /home/anders/code/nanousd/nanousd-arrays.h: 15

nusd_double_array_s = struct_nusd_double_array_s# /home/anders/code/nanousd/nanousd-arrays.h: 17

nusd_double2_array_s = struct_nusd_double2_array_s# /home/anders/code/nanousd/nanousd-arrays.h: 18

nusd_double3_array_s = struct_nusd_double3_array_s# /home/anders/code/nanousd/nanousd-arrays.h: 19

nusd_double4_array_s = struct_nusd_double4_array_s# /home/anders/code/nanousd/nanousd-arrays.h: 20

nusd_int_array_s = struct_nusd_int_array_s# /home/anders/code/nanousd/nanousd-arrays.h: 22

nusd_int2_array_s = struct_nusd_int2_array_s# /home/anders/code/nanousd/nanousd-arrays.h: 23

nusd_int3_array_s = struct_nusd_int3_array_s# /home/anders/code/nanousd/nanousd-arrays.h: 24

nusd_int4_array_s = struct_nusd_int4_array_s# /home/anders/code/nanousd/nanousd-arrays.h: 25

nusd_int64_array_s = struct_nusd_int64_array_s# /home/anders/code/nanousd/nanousd-arrays.h: 26

nusd_matrix2d_array_s = struct_nusd_matrix2d_array_s# /home/anders/code/nanousd/nanousd-arrays.h: 28

nusd_matrix3d_array_s = struct_nusd_matrix3d_array_s# /home/anders/code/nanousd/nanousd-arrays.h: 29

nusd_matrix4d_array_s = struct_nusd_matrix4d_array_s# /home/anders/code/nanousd/nanousd-arrays.h: 30

nusd_uint_array_s = struct_nusd_uint_array_s# /home/anders/code/nanousd/nanousd-arrays.h: 32

nusd_uint64_array_s = struct_nusd_uint64_array_s# /home/anders/code/nanousd/nanousd-arrays.h: 33

nusd_uchar_array_s = struct_nusd_uchar_array_s# /home/anders/code/nanousd/nanousd-arrays.h: 34

# No inserted files

# No prefix-stripping

