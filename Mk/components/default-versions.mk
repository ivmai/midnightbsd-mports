# $MidnightBSD$ 
#
# Provide default versions for ports with multiple versions selectable
# by the user.
#
# Users who want to override these defaults can easily do so by defining
# DEFAULT_VERSIONS in their make.conf as follows:
#
#   DEFAULT_VERSIONS=	perl5=5.18 ruby=2.0

.if !defined(_INCLUDE_BSD_DEFAULT_VERSIONS_MK)
_INCLUDE_BSD_DEFAULT_VERSIONS_MK=	yes

.for lang in ${DEFAULT_VERSIONS}
_l=		${lang:C/=.*//g}
${_l:tu}_DEFAULT=	${lang:C/.*=//g}
.endfor

APACHE_DEFAULT?=	2.4
FPC_DEFAULT?=		2.6.4
GCC_DEFAULT?=		4.8
LUA_DEFAULT?=		5.2
MYSQL_DEFAULT?=		5.6
PERL5_DEFAULT?=		5.18
PGSQL_DEFAULT?=		9.3
PHP_DEFAULT?=		5.4
PYTHON_DEFAULT?=	2.7
PYTHON2_DEFAULT?=	2.7
PYTHON3_DEFAULT?=	3.3
RUBY_DEFAULT?=		2.2
TCLTK_DEFAULT?=		8.6

# Version of lang/gcc.  Do not override!
LANG_GCC_IS=		4.8

.endif
