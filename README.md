# Five Minute Microservices

<!-- markdown-toc start - Don't edit this section. Run M-x markdown-toc-refresh-toc -->
**Table of Contents**

- [Five Minute Microservices](#five-minute-microservices)
- [Benchmarks](#benchmarks)
- [Usage](#usage)
- [Project Layout](#project-layout)
- [Requirements](#requirements)
- [Version 0.0.x](#version-00x)
- [Version 0.1.x](#version-01x)
- [License](#license)
- [Copyright](#copyright)

<!-- markdown-toc end -->


Will serve to be an awesome guide on different languages /
implementations and their ease of use in whipping up a minimal
HTTP based microservice in that language.

# Benchmarks

[[Benchmarks](BENCH.md)]

# Usage

Try out an API before or after using it by running something such as:

```sh
make -C php/vanilla start
```

Change the name as you see fit (must match a directory).

# Project Layout

The top level will consist of overall project information, similar to
this file, as well as eventual benchmarks/responses of the versions.

Sub-directories will be broken down by language, and then by framework
or 'vanilla' if no framework is used.

# Requirements

Each subsequent version must support all features in the lower
versions.  As time goes on, I'll expand the sub-directories to include
more functionality/features, but start in a phased approach, as a
broader coverage of languages will be more useful than a heavy
in-depth guide of languages.

The languages must run their own web server - requiring something like
mod_cgi interaction is too much host OS overhead/setup required.

No system's port should conflict with any other system's port in use.

# Version 0.0.x

Must support:

- A /version endpoint which will return a JSON version string "0.0.1"
- An automated installation/binary check from GNU Make (can chain with language installers)

# Version 0.1.x

Must support:

- POST method to /add that will take a JSON object such as: `{"a":1,
  "b":2}` and return the sum of them as an object as such: `{"a":1,
  "b": 2, "sum": 3}`.

# License

AGPLv3 or later (GNU Affero Public License)

# Copyright

Matthew Carter <m@ahungry.com>
