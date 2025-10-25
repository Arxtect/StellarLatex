#define EXTERN extern
#include "xetexd.h"

void 
println ( void ) 
{
  println_regmem 
  switch ( selector ) 
  {case 19 : 
    {
      putc ('\n',  stdout );
      putc ('\n',  logfile );
      termoffset = 0 ;
      fileoffset = 0 ;
    } 
    break ;
  case 18 : 
    {
      putc ('\n',  logfile );
      fileoffset = 0 ;
    } 
    break ;
  case 17 : 
    {
      putc ('\n',  stdout );
      termoffset = 0 ;
    } 
    break ;
  case 16 : 
  case 20 : 
  case 21 : 
    ;
    break ;
    default: 
    putc ('\n',  writefile [selector ]);
    break ;
  } 
} 
void 
zprintrawchar ( UnicodeScalar s , boolean incroffset ) 
{
  /* 10 */ printrawchar_regmem 
  switch ( selector ) 
  {case 19 : 
    {
      putc ( Xchr (s ),  stdout );
      putc ( Xchr (s ),  logfile );
      if ( incroffset ) 
      {
	incr ( termoffset ) ;
	incr ( fileoffset ) ;
      } 
      if ( termoffset == maxprintline ) 
      {
	putc ('\n',  stdout );
	termoffset = 0 ;
      } 
      if ( fileoffset == maxprintline ) 
      {
	putc ('\n',  logfile );
	fileoffset = 0 ;
      } 
    } 
    break ;
  case 18 : 
    {
      putc ( Xchr (s ),  logfile );
      if ( incroffset ) 
      incr ( fileoffset ) ;
      if ( fileoffset == maxprintline ) 
      println () ;
    } 
    break ;
  case 17 : 
    {
      putc ( Xchr (s ),  stdout );
      if ( incroffset ) 
      incr ( termoffset ) ;
      if ( termoffset == maxprintline ) 
      println () ;
    } 
    break ;
  case 16 : 
    ;
    break ;
  case 20 : 
    if ( tally < trickcount ) 
    trickbuf [tally % errorline ]= s ;
    break ;
  case 21 : 
    {
      if ( poolptr < poolsize ) 
      {
	if ( ( s > 65535L ) ) 
	{
	  strpool [poolptr ]= ( s - 65536L ) / 1024 + 55296L ;
	  incr ( poolptr ) ;
	  strpool [poolptr ]= ( s ) % 1024 + 56320L ;
	  incr ( poolptr ) ;
	} 
	else {
	    
	  strpool [poolptr ]= s ;
	  incr ( poolptr ) ;
	} 
      } 
    } 
    break ;
    default: 
    putc ( Xchr (s ),  writefile [selector ]);
    break ;
  } 
  incr ( tally ) ;
} 
void 
zprintchar ( integer s ) 
{
  /* 10 */ printchar_regmem 
  smallnumber l  ;
  if ( ( selector > 20 ) && ( ! doingspecial ) ) 
  {
    if ( s >= 65536L ) 
    {
      printrawchar ( 55296L + ( s - 65536L ) / 1024 , true ) ;
      printrawchar ( 56320L + ( s - 65536L ) % 1024 , true ) ;
    } 
    else printrawchar ( s , true ) ;
    return ;
  } 
  if ( s == eqtb [7892313L ].cint ) {
      
    if ( selector < 20 ) 
    {
      println () ;
      return ;
    } 
  } 
  if ( ( s < 32 ) && ( eightbitp == 0 ) && ( ! doingspecial ) ) 
  {
    printrawchar ( 94 , true ) ;
    printrawchar ( 94 , true ) ;
    printrawchar ( s + 64 , true ) ;
  } 
  else if ( s < 127 ) 
  printrawchar ( s , true ) ;
  else if ( ( s == 127 ) ) 
  {
    if ( ( eightbitp == 0 ) && ( ! doingspecial ) ) 
    {
      printrawchar ( 94 , true ) ;
      printrawchar ( 94 , true ) ;
      printrawchar ( 63 , true ) ;
    } 
    else printrawchar ( s , true ) ;
  } 
  else if ( ( s < 160 ) && ( eightbitp == 0 ) && ( ! doingspecial ) ) 
  {
    printrawchar ( 94 , true ) ;
    printrawchar ( 94 , true ) ;
    l = ( s % 256 ) / 16 ;
    if ( l < 10 ) 
    printrawchar ( l + 48 , true ) ;
    else printrawchar ( l + 87 , true ) ;
    l = s % 16 ;
    if ( l < 10 ) 
    printrawchar ( l + 48 , true ) ;
    else printrawchar ( l + 87 , true ) ;
  } 
  else if ( selector == 20 ) 
  printrawchar ( s , true ) ;
  else {
      
    if ( s < 2048 ) 
    {
      printrawchar ( 192 + s / 64 , false ) ;
      printrawchar ( 128 + s % 64 , true ) ;
    } 
    else if ( s < 65536L ) 
    {
      printrawchar ( 224 + ( s / 4096 ) , false ) ;
      printrawchar ( 128 + ( s % 4096 ) / 64 , false ) ;
      printrawchar ( 128 + ( s % 64 ) , true ) ;
    } 
    else {
	
      printrawchar ( 240 + ( s / 262144L ) , false ) ;
      printrawchar ( 128 + ( s % 262144L ) / 4096 , false ) ;
      printrawchar ( 128 + ( s % 4096 ) / 64 , false ) ;
      printrawchar ( 128 + ( s % 64 ) , true ) ;
    } 
  } 
} 
void 
zprint ( integer s ) 
{
  /* 10 */ print_regmem 
  poolpointer j  ;
  integer nl  ;
  if ( s >= strptr ) 
  s = 65541L ;
  else if ( s < 65535L ) {
      
    if ( s < 0 ) 
    s = 65541L ;
    else {
	
      if ( selector > 20 ) 
      {
	printchar ( s ) ;
	return ;
      } 
      if ( ( s == eqtb [7892313L ].cint ) ) {
	  
	if ( selector < 20 ) 
	{
	  println () ;
	  return ;
	} 
      } 
      nl = eqtb [7892313L ].cint ;
      eqtb [7892313L ].cint = -1 ;
      printchar ( s ) ;
      eqtb [7892313L ].cint = nl ;
      return ;
    } 
  } 
  j = strstart [( s ) - 65536L ];
  while ( j < strstart [( s + 1 ) - 65536L ]) {
      
    if ( ( strpool [j ]>= 55296L ) && ( strpool [j ]<= 56319L ) && ( j + 1 
    < strstart [( s + 1 ) - 65536L ]) && ( strpool [j + 1 ]>= 56320L ) && 
    ( strpool [j + 1 ]<= 57343L ) ) 
    {
      printchar ( 65536L + ( strpool [j ]- 55296L ) * 1024 + strpool [j + 1 
      ]- 56320L ) ;
      j = j + 2 ;
    } 
    else {
	
      printchar ( strpool [j ]) ;
      incr ( j ) ;
    } 
  } 
} 
void 
zprintnl ( strnumber s ) 
{
  printnl_regmem 
  if ( ( selector < 16 ) || ( ( termoffset > 0 ) && ( odd ( selector ) ) ) || 
  ( ( fileoffset > 0 ) && ( selector >= 18 ) ) ) 
  println () ;
  print ( s ) ;
} 
void 
zprintesc ( strnumber s ) 
{
  printesc_regmem 
  integer c  ;
  c = eqtb [7892309L ].cint ;
  if ( c >= 0 ) {
      
    if ( c <= 1114111L ) 
    printchar ( c ) ;
  } 
  print ( s ) ;
} 
void 
zprintthedigs ( eightbits k ) 
{
  printthedigs_regmem 
  while ( k > 0 ) {
      
    decr ( k ) ;
    if ( dig [k ]< 10 ) 
    printchar ( 48 + dig [k ]) ;
    else printchar ( 55 + dig [k ]) ;
  } 
} 
void 
zprintint ( integer n ) 
{
  printint_regmem 
  unsigned char k  ;
  integer m  ;
  k = 0 ;
  if ( n < 0 ) 
  {
    printchar ( 45 ) ;
    if ( n > -100000000L ) 
    n = - (integer) n ;
    else {
	
      m = -1 - n ;
      n = m / 10 ;
      m = ( m % 10 ) + 1 ;
      k = 1 ;
      if ( m < 10 ) 
      dig [0 ]= m ;
      else {
	  
	dig [0 ]= 0 ;
	incr ( n ) ;
      } 
    } 
  } 
  do {
      dig [k ]= n % 10 ;
    n = n / 10 ;
    incr ( k ) ;
  } while ( ! ( n == 0 ) ) ;
  printthedigs ( k ) ;
} 
void 
zprintcs ( integer p ) 
{
  printcs_regmem 
  if ( p < 1179650L ) {
      
    if ( p >= 1114113L ) {
	
      if ( p == 1179649L ) 
      {
	printesc ( 65818L ) ;
	printesc ( 65819L ) ;
	printchar ( 32 ) ;
      } 
      else {
	  
	printesc ( p - 1114113L ) ;
	if ( eqtb [1207592L + p - 1114113L ].hh .v.RH == 11 ) 
	printchar ( 32 ) ;
      } 
    } 
    else if ( p < 1 ) 
    printesc ( 65820L ) ;
    else printchar ( p - 1 ) ;
  } 
  else if ( ( ( p >= 1205763L ) && ( p <= 9006998L ) ) || ( p > eqtbtop ) ) 
  printesc ( 65820L ) ;
  else if ( ( hash [p ].v.RH >= strptr ) ) 
  printesc ( 65821L ) ;
  else {
      
    if ( ( p >= 1194662L ) && ( p < 1196762L ) ) 
    printesc ( prim [p - 1194662L ].v.RH - 1 ) ;
    else printesc ( hash [p ].v.RH ) ;
    printchar ( 32 ) ;
  } 
} 
void 
zsprintcs ( halfword p ) 
{
  sprintcs_regmem 
  if ( p < 1179650L ) {
      
    if ( p < 1114113L ) 
    printchar ( p - 1 ) ;
    else if ( p < 1179649L ) 
    printesc ( p - 1114113L ) ;
    else {
	
      printesc ( 65818L ) ;
      printesc ( 65819L ) ;
    } 
  } 
  else if ( ( p >= 1194662L ) && ( p < 1196762L ) ) 
  printesc ( prim [p - 1194662L ].v.RH - 1 ) ;
  else printesc ( hash [p ].v.RH ) ;
} 
void 
zprintfilename ( integer n , integer a , integer e ) 
{
  printfilename_regmem 
  boolean mustquote  ;
  integer quotechar  ;
  poolpointer j  ;
  mustquote = false ;
  quotechar = 0 ;
  if ( a != 0 ) 
  {
    j = strstart [( a ) - 65536L ];
    while ( ( ( ! mustquote ) || ( quotechar == 0 ) ) && ( j < strstart [( a 
    + 1 ) - 65536L ]) ) {
	
      if ( strpool [j ]== 32 ) 
      mustquote = true ;
      else if ( ( strpool [j ]== 34 ) || ( strpool [j ]== 39 ) ) 
      {
	mustquote = true ;
	quotechar = 73 - strpool [j ];
      } 
      incr ( j ) ;
    } 
  } 
  if ( n != 0 ) 
  {
    j = strstart [( n ) - 65536L ];
    while ( ( ( ! mustquote ) || ( quotechar == 0 ) ) && ( j < strstart [( n 
    + 1 ) - 65536L ]) ) {
	
      if ( strpool [j ]== 32 ) 
      mustquote = true ;
      else if ( ( strpool [j ]== 34 ) || ( strpool [j ]== 39 ) ) 
      {
	mustquote = true ;
	quotechar = 73 - strpool [j ];
      } 
      incr ( j ) ;
    } 
  } 
  if ( e != 0 ) 
  {
    j = strstart [( e ) - 65536L ];
    while ( ( ( ! mustquote ) || ( quotechar == 0 ) ) && ( j < strstart [( e 
    + 1 ) - 65536L ]) ) {
	
      if ( strpool [j ]== 32 ) 
      mustquote = true ;
      else if ( ( strpool [j ]== 34 ) || ( strpool [j ]== 39 ) ) 
      {
	mustquote = true ;
	quotechar = 73 - strpool [j ];
      } 
      incr ( j ) ;
    } 
  } 
  if ( mustquote ) 
  {
    if ( quotechar == 0 ) 
    quotechar = 34 ;
    printchar ( quotechar ) ;
  } 
  if ( a != 0 ) 
  {register integer for_end; j = strstart [( a ) - 65536L ];for_end = 
  strstart [( a + 1 ) - 65536L ]- 1 ; if ( j <= for_end) do 
    {
      if ( strpool [j ]== quotechar ) 
      {
	print ( quotechar ) ;
	quotechar = 73 - quotechar ;
	print ( quotechar ) ;
      } 
      if ( ( strpool [j ]>= 55296L ) && ( strpool [j ]<= 56319L ) && ( j + 
      1 < strstart [( a + 1 ) - 65536L ]) && ( strpool [j + 1 ]>= 56320L ) 
      && ( strpool [j + 1 ]<= 57343L ) ) 
      {
	printchar ( 65536L + ( strpool [j ]- 55296L ) * 1024 + strpool [j + 
	1 ]- 56320L ) ;
	incr ( j ) ;
      } 
      else print ( strpool [j ]) ;
    } 
  while ( j++ < for_end ) ;} 
  if ( n != 0 ) 
  {register integer for_end; j = strstart [( n ) - 65536L ];for_end = 
  strstart [( n + 1 ) - 65536L ]- 1 ; if ( j <= for_end) do 
    {
      if ( strpool [j ]== quotechar ) 
      {
	print ( quotechar ) ;
	quotechar = 73 - quotechar ;
	print ( quotechar ) ;
      } 
      if ( ( strpool [j ]>= 55296L ) && ( strpool [j ]<= 56319L ) && ( j + 
      1 < strstart [( n + 1 ) - 65536L ]) && ( strpool [j + 1 ]>= 56320L ) 
      && ( strpool [j + 1 ]<= 57343L ) ) 
      {
	printchar ( 65536L + ( strpool [j ]- 55296L ) * 1024 + strpool [j + 
	1 ]- 56320L ) ;
	incr ( j ) ;
      } 
      else print ( strpool [j ]) ;
    } 
  while ( j++ < for_end ) ;} 
  if ( e != 0 ) 
  {register integer for_end; j = strstart [( e ) - 65536L ];for_end = 
  strstart [( e + 1 ) - 65536L ]- 1 ; if ( j <= for_end) do 
    {
      if ( strpool [j ]== quotechar ) 
      {
	print ( quotechar ) ;
	quotechar = 73 - quotechar ;
	print ( quotechar ) ;
      } 
      if ( ( strpool [j ]>= 55296L ) && ( strpool [j ]<= 56319L ) && ( j + 
      1 < strstart [( e + 1 ) - 65536L ]) && ( strpool [j + 1 ]>= 56320L ) 
      && ( strpool [j + 1 ]<= 57343L ) ) 
      {
	printchar ( 65536L + ( strpool [j ]- 55296L ) * 1024 + strpool [j + 
	1 ]- 56320L ) ;
	incr ( j ) ;
      } 
      else print ( strpool [j ]) ;
    } 
  while ( j++ < for_end ) ;} 
  if ( quotechar != 0 ) 
  printchar ( quotechar ) ;
} 
void 
zprintsize ( integer s ) 
{
  printsize_regmem 
  if ( s == 0 ) 
  printesc ( 65713L ) ;
  else if ( s == 256 ) 
  printesc ( 65714L ) ;
  else printesc ( 65715L ) ;
} 
void 
zprintwritewhatsit ( strnumber s , halfword p ) 
{
  printwritewhatsit_regmem 
  printesc ( s ) ;
  if ( mem [p + 1 ].hh .v.LH < 16 ) 
  printint ( mem [p + 1 ].hh .v.LH ) ;
  else if ( mem [p + 1 ].hh .v.LH == 16 ) 
  printchar ( 42 ) ;
  else printchar ( 45 ) ;
} 
void 
zprintnativeword ( halfword p ) 
{
  printnativeword_regmem 
  integer i, c, cc  ;
  {register integer for_end; i = 0 ;for_end = mem [p + 4 ].qqqq .b2 - 1 
  ; if ( i <= for_end) do 
    {
      c = getnativechar ( p , i ) ;
      if ( ( c >= 55296L ) && ( c <= 56319L ) ) 
      {
	if ( i < mem [p + 4 ].qqqq .b2 - 1 ) 
	{
	  cc = getnativechar ( p , i + 1 ) ;
	  if ( ( cc >= 56320L ) && ( cc <= 57343L ) ) 
	  {
	    c = 65536L + ( c - 55296L ) * 1024 + ( cc - 56320L ) ;
	    printchar ( c ) ;
	    incr ( i ) ;
	  } 
	  else print ( 46 ) ;
	} 
	else print ( 46 ) ;
      } 
      else printchar ( c ) ;
    } 
  while ( i++ < for_end ) ;} 
} 
void 
zprintsanum ( halfword q ) 
{
  printsanum_regmem 
  halfword n  ;
  if ( mem [q ].hh.b0 < 128 ) 
  n = mem [q + 1 ].hh .v.RH ;
  else {
      
    n = mem [q ].hh.b0 % 64 ;
    q = mem [q ].hh .v.RH ;
    n = n + 64 * mem [q ].hh.b0 ;
    q = mem [q ].hh .v.RH ;
    n = n + 64 * 64 * ( mem [q ].hh.b0 + 64 * mem [mem [q ].hh .v.RH ]
    .hh.b0 ) ;
  } 
  printint ( n ) ;
} 
void 
zprintcsnames ( integer hstart , integer hfinish ) 
{
  printcsnames_regmem 
  integer c, h  ;
  fprintf ( stderr , "%s%ld%s%ld%c\n",  "fmtdebug:csnames from " , (long)hstart , " to " , (long)hfinish ,   ':' ) ;
  {register integer for_end; h = hstart ;for_end = hfinish ; if ( h <= 
  for_end) do 
    {
      if ( hash [h ].v.RH > 0 ) 
      {
	{register integer for_end; c = strstart [( hash [h ].v.RH ) - 
	65536L ];for_end = strstart [( hash [h ].v.RH + 1 ) - 65536L ]- 
	1 ; if ( c <= for_end) do 
	  {
	    putbyte ( strpool [c ], stderr ) ;
	  } 
	while ( c++ < for_end ) ;} 
	{ putc ( '|' ,  stderr );  putc ( '\n',  stderr ); }
      } 
    } 
  while ( h++ < for_end ) ;} 
} 
void 
printfileline ( void ) 
{
  printfileline_regmem 
  integer level  ;
  level = inopen ;
  while ( ( level > 0 ) && ( fullsourcefilenamestack [level ]== 0 ) ) decr ( 
  level ) ;
  if ( level == 0 ) 
  printnl ( 65544L ) ;
  else {
      
    printnl ( 65545L ) ;
    print ( fullsourcefilenamestack [level ]) ;
    print ( 58 ) ;
    if ( level == inopen ) 
    printint ( line ) ;
    else printint ( linestack [level + 1 ]) ;
    print ( 65595L ) ;
  } 
} 
#ifdef TEXMF_DEBUG
#endif /* TEXMF_DEBUG */
void 
jumpout ( void ) 
{
  jumpout_regmem 
  closefilesandterminate () ;
  {
    fflush ( stdout ) ;
    readyalready = 0 ;
    if ( ( history != 0 ) && ( history != 1 ) ) 
    uexit ( 1 ) ;
    else uexit ( 0 ) ;
  } 
} 
void 
error ( void ) 
{
  /* 22 10 */ error_regmem 
  UnicodeScalar c  ;
  integer s1, s2, s3, s4  ;
  if ( history < 2 ) 
  history = 2 ;
  printchar ( 46 ) ;
  showcontext () ;
  if ( ( haltonerrorp ) ) 
  {
    if ( ( haltingonerrorp ) ) 
    {
      fflush ( stdout ) ;
      readyalready = 0 ;
      if ( ( history != 0 ) && ( history != 1 ) ) 
      uexit ( 1 ) ;
      else uexit ( 0 ) ;
    } 
    haltingonerrorp = true ;
    if ( interaction > 0 ) 
    decr ( selector ) ;
    if ( useerrhelp ) 
    {
      println () ;
      giveerrhelp () ;
    } 
    else while ( helpptr > 0 ) {
	
      decr ( helpptr ) ;
      printnl ( helpline [helpptr ]) ;
    } 
    println () ;
    if ( interaction > 0 ) 
    incr ( selector ) ;
    println () ;
    history = 3 ;
    jumpout () ;
  } 
  if ( interaction == 3 ) 
  while ( true ) {
      
    lab22: if ( interaction != 3 ) 
    return ;
    clearforerrorprompt () ;
    {
      ;
      print ( 65548L ) ;
      terminput () ;
    } 
    if ( last == first ) 
    return ;
    c = buffer [first ];
    if ( c >= 97 ) 
    c = c - 32 ;
    switch ( c ) 
    {case 48 : 
    case 49 : 
    case 50 : 
    case 51 : 
    case 52 : 
    case 53 : 
    case 54 : 
    case 55 : 
    case 56 : 
    case 57 : 
      if ( deletionsallowed ) 
      {
	s1 = curtok ;
	s2 = curcmd ;
	s3 = curchr ;
	s4 = alignstate ;
	alignstate = 1000000L ;
	OKtointerrupt = false ;
	if ( ( last > first + 1 ) && ( buffer [first + 1 ]>= 48 ) && ( 
	buffer [first + 1 ]<= 57 ) ) 
	c = c * 10 + buffer [first + 1 ]- 48 * 11 ;
	else c = c - 48 ;
	while ( c > 0 ) {
	    
	  gettoken () ;
	  decr ( c ) ;
	} 
	curtok = s1 ;
	curcmd = s2 ;
	curchr = s3 ;
	alignstate = s4 ;
	OKtointerrupt = true ;
	{
	  helpptr = 2 ;
	  helpline [1 ]= 65561L ;
	  helpline [0 ]= 65562L ;
	} 
	showcontext () ;
	goto lab22 ;
      } 
      break ;
	;
#ifdef TEXMF_DEBUG
    case 68 : 
      {
	debughelp () ;
	goto lab22 ;
      } 
      break ;
#endif /* TEXMF_DEBUG */
    case 69 : 
      if ( baseptr > 0 ) {
	  
	if ( inputstack [baseptr ].namefield >= 256 ) 
	{
	  editnamestart = strstart [( inputstack [baseptr ].namefield ) - 
	  65536L ];
	  editnamelength = strstart [( inputstack [baseptr ].namefield + 1 
	  ) - 65536L ]- strstart [( inputstack [baseptr ].namefield ) - 
	  65536L ];
	  editline = line ;
	  jumpout () ;
	} 
      } 
      break ;
    case 72 : 
      {
	if ( useerrhelp ) 
	{
	  giveerrhelp () ;
	  useerrhelp = false ;
	} 
	else {
	    
	  if ( helpptr == 0 ) 
	  {
	    helpptr = 2 ;
	    helpline [1 ]= 65563L ;
	    helpline [0 ]= 65564L ;
	  } 
	  do {
	      decr ( helpptr ) ;
	    print ( helpline [helpptr ]) ;
	    println () ;
	  } while ( ! ( helpptr == 0 ) ) ;
	} 
	{
	  helpptr = 4 ;
	  helpline [3 ]= 65565L ;
	  helpline [2 ]= 65564L ;
	  helpline [1 ]= 65566L ;
	  helpline [0 ]= 65567L ;
	} 
	goto lab22 ;
      } 
      break ;
    case 73 : 
      {
	beginfilereading () ;
	if ( last > first + 1 ) 
	{
	  curinput .locfield = first + 1 ;
	  buffer [first ]= 32 ;
	} 
	else {
	    
	  {
	    ;
	    print ( 65560L ) ;
	    terminput () ;
	  } 
	  curinput .locfield = first ;
	} 
	first = last ;
	curinput .limitfield = last - 1 ;
	return ;
      } 
      break ;
    case 81 : 
    case 82 : 
    case 83 : 
      {
	errorcount = 0 ;
	interaction = 0 + c - 81 ;
	print ( 65555L ) ;
	switch ( c ) 
	{case 81 : 
	  {
	    printesc ( 65556L ) ;
	    decr ( selector ) ;
	  } 
	  break ;
	case 82 : 
	  printesc ( 65557L ) ;
	  break ;
	case 83 : 
	  printesc ( 65558L ) ;
	  break ;
	} 
	print ( 65559L ) ;
	println () ;
	fflush ( stdout ) ;
	return ;
      } 
      break ;
    case 88 : 
      {
	interaction = 2 ;
	jumpout () ;
      } 
      break ;
      default: 
      ;
      break ;
    } 
    {
      print ( 65549L ) ;
      printnl ( 65550L ) ;
      printnl ( 65551L ) ;
      if ( baseptr > 0 ) {
	  
	if ( inputstack [baseptr ].namefield >= 256 ) 
	print ( 65552L ) ;
      } 
      if ( deletionsallowed ) 
      printnl ( 65553L ) ;
      printnl ( 65554L ) ;
    } 
  } 
  incr ( errorcount ) ;
  if ( errorcount == 100 ) 
  {
    printnl ( 65547L ) ;
    history = 3 ;
    jumpout () ;
  } 
  if ( interaction > 0 ) 
  decr ( selector ) ;
  if ( useerrhelp ) 
  {
    println () ;
    giveerrhelp () ;
  } 
  else while ( helpptr > 0 ) {
      
    decr ( helpptr ) ;
    printnl ( helpline [helpptr ]) ;
  } 
  println () ;
  if ( interaction > 0 ) 
  incr ( selector ) ;
  println () ;
} 
void 
zfatalerror ( strnumber s ) 
{
  fatalerror_regmem 
  normalizeselector () ;
  {
    if ( interaction == 3 ) 
    ;
    if ( filelineerrorstylep ) 
    printfileline () ;
    else printnl ( 65544L ) ;
    print ( 65569L ) ;
  } 
  {
    helpptr = 1 ;
    helpline [0 ]= s ;
  } 
  {
    if ( interaction == 3 ) 
    interaction = 2 ;
    if ( logopened ) 
    error () ;
	;
#ifdef TEXMF_DEBUG
    if ( interaction > 0 ) 
    debughelp () ;
#endif /* TEXMF_DEBUG */
    history = 3 ;
    jumpout () ;
  } 
} 
void 
zoverflow ( strnumber s , integer n ) 
{
  overflow_regmem 
  normalizeselector () ;
  {
    if ( interaction == 3 ) 
    ;
    if ( filelineerrorstylep ) 
    printfileline () ;
    else printnl ( 65544L ) ;
    print ( 65570L ) ;
  } 
  print ( s ) ;
  printchar ( 61 ) ;
  printint ( n ) ;
  printchar ( 93 ) ;
  {
    helpptr = 2 ;
    helpline [1 ]= 65571L ;
    helpline [0 ]= 65572L ;
  } 
  {
    if ( interaction == 3 ) 
    interaction = 2 ;
    if ( logopened ) 
    error () ;
	;
#ifdef TEXMF_DEBUG
    if ( interaction > 0 ) 
    debughelp () ;
#endif /* TEXMF_DEBUG */
    history = 3 ;
    jumpout () ;
  } 
} 
void 
zconfusion ( strnumber s ) 
{
  confusion_regmem 
  normalizeselector () ;
  if ( history < 2 ) 
  {
    {
      if ( interaction == 3 ) 
      ;
      if ( filelineerrorstylep ) 
      printfileline () ;
      else printnl ( 65544L ) ;
      print ( 65573L ) ;
    } 
    print ( s ) ;
    printchar ( 41 ) ;
    {
      helpptr = 1 ;
      helpline [0 ]= 65574L ;
    } 
  } 
  else {
      
    {
      if ( interaction == 3 ) 
      ;
      if ( filelineerrorstylep ) 
      printfileline () ;
      else printnl ( 65544L ) ;
      print ( 65575L ) ;
    } 
    {
      helpptr = 2 ;
      helpline [1 ]= 65576L ;
      helpline [0 ]= 65577L ;
    } 
  } 
  {
    if ( interaction == 3 ) 
    interaction = 2 ;
    if ( logopened ) 
    error () ;
	;
#ifdef TEXMF_DEBUG
    if ( interaction > 0 ) 
    debughelp () ;
#endif /* TEXMF_DEBUG */
    history = 3 ;
    jumpout () ;
  } 
} 
boolean 
initterminal ( void ) 
{
  /* 10 */ register boolean Result; initterminal_regmem 
  topenin () ;
  if ( last > first ) 
  {
    curinput .locfield = first ;
    while ( ( curinput .locfield < last ) && ( buffer [curinput .locfield ]
    == ' ' ) ) incr ( curinput .locfield ) ;
    if ( curinput .locfield < last ) 
    {
      Result = true ;
      return Result ;
    } 
  } 
  while ( true ) {
      
    ;
    Fputs ( stdout ,  "**" ) ;
    fflush ( stdout ) ;
    if ( ! inputln ( termin , true ) ) 
    {
      putc ('\n',  stdout );
      fprintf ( stdout , "%s\n",  "! End of file on the terminal... why?" ) ;
      Result = false ;
      return Result ;
    } 
    curinput .locfield = first ;
    while ( ( curinput .locfield < last ) && ( buffer [curinput .locfield ]
    == 32 ) ) incr ( curinput .locfield ) ;
    if ( curinput .locfield < last ) 
    {
      Result = true ;
      return Result ;
    } 
    fprintf ( stdout , "%s\n",  "Please type the name of your input file." ) ;
  } 
  return Result ;
} 
integer 
zlength ( strnumber s ) 
{
  register integer Result; length_regmem 
  if ( ( s >= 65536L ) ) 
  Result = strstart [( s + 1 ) - 65536L ]- strstart [( s ) - 65536L ];
  else if ( ( s >= 32 ) && ( s < 127 ) ) 
  Result = 1 ;
  else if ( ( s <= 127 ) ) 
  Result = 3 ;
  else if ( ( s < 256 ) ) 
  Result = 4 ;
  else Result = 8 ;
  return Result ;
} 
strnumber 
makestring ( void ) 
{
  register strnumber Result; makestring_regmem 
  if ( strptr == maxstrings ) 
  overflow ( 65540L , maxstrings - initstrptr ) ;
  incr ( strptr ) ;
  strstart [( strptr ) - 65536L ]= poolptr ;
  Result = strptr - 1 ;
  return Result ;
} 
void 
zappendstr ( strnumber s ) 
{
  appendstr_regmem 
  integer i  ;
  poolpointer j  ;
  i = length ( s ) ;
  {
    if ( poolptr + i > poolsize ) 
    overflow ( 65539L , poolsize - initpoolptr ) ;
  } 
  j = strstart [( s ) - 65536L ];
  while ( ( i > 0 ) ) {
      
    {
      if ( ( strpool [j ]> 65535L ) ) 
      {
	strpool [poolptr ]= ( strpool [j ]- 65536L ) / 1024 + 55296L ;
	incr ( poolptr ) ;
	strpool [poolptr ]= ( strpool [j ]) % 1024 + 56320L ;
	incr ( poolptr ) ;
      } 
      else {
	  
	strpool [poolptr ]= strpool [j ];
	incr ( poolptr ) ;
      } 
    } 
    incr ( j ) ;
    decr ( i ) ;
  } 
} 
boolean 
zstreqbuf ( strnumber s , integer k ) 
{
  /* 45 */ register boolean Result; streqbuf_regmem 
  poolpointer j  ;
  boolean result  ;
  j = strstart [( s ) - 65536L ];
  while ( j < strstart [( s + 1 ) - 65536L ]) {
      
    if ( buffer [k ]>= 65536L ) {
	
      if ( strpool [j ]!= 55296L + ( buffer [k ]- 65536L ) / 1024 ) 
      {
	result = false ;
	goto lab45 ;
      } 
      else if ( strpool [j + 1 ]!= 56320L + ( buffer [k ]- 65536L ) % 1024 
      ) 
      {
	result = false ;
	goto lab45 ;
      } 
      else incr ( j ) ;
    } 
    else if ( strpool [j ]!= buffer [k ]) 
    {
      result = false ;
      goto lab45 ;
    } 
    incr ( j ) ;
    incr ( k ) ;
  } 
  result = true ;
  lab45: Result = result ;
  return Result ;
} 
boolean 
zstreqstr ( strnumber s , strnumber t ) 
{
  /* 45 */ register boolean Result; streqstr_regmem 
  poolpointer j, k  ;
  boolean result  ;
  result = false ;
  if ( length ( s ) != length ( t ) ) 
  goto lab45 ;
  if ( ( length ( s ) == 1 ) ) 
  {
    if ( s < 65536L ) 
    {
      if ( t < 65536L ) 
      {
	if ( s != t ) 
	goto lab45 ;
      } 
      else {
	  
	if ( s != strpool [strstart [( t ) - 65536L ]]) 
	goto lab45 ;
      } 
    } 
    else {
	
      if ( t < 65536L ) 
      {
	if ( strpool [strstart [( s ) - 65536L ]]!= t ) 
	goto lab45 ;
      } 
      else {
	  
	if ( strpool [strstart [( s ) - 65536L ]]!= strpool [strstart [( 
	t ) - 65536L ]]) 
	goto lab45 ;
      } 
    } 
  } 
  else {
      
    j = strstart [( s ) - 65536L ];
    k = strstart [( t ) - 65536L ];
    while ( j < strstart [( s + 1 ) - 65536L ]) {
	
      if ( strpool [j ]!= strpool [k ]) 
      goto lab45 ;
      incr ( j ) ;
      incr ( k ) ;
    } 
  } 
  result = true ;
  lab45: Result = result ;
  return Result ;
} 
strnumber 
zsearchstring ( strnumber search ) 
{
  /* 40 */ register strnumber Result; searchstring_regmem 
  strnumber result  ;
  strnumber s  ;
  integer len  ;
  result = 0 ;
  len = length ( search ) ;
  if ( len == 0 ) 
  {
    result = 65545L ;
    goto lab40 ;
  } 
  else {
      
    s = search - 1 ;
    while ( s > 65535L ) {
	
      if ( length ( s ) == len ) {
	  
	if ( streqstr ( s , search ) ) 
	{
	  result = s ;
	  goto lab40 ;
	} 
      } 
      decr ( s ) ;
    } 
  } 
  lab40: Result = result ;
  return Result ;
} 
strnumber 
slowmakestring ( void ) 
{
  /* 10 */ register strnumber Result; slowmakestring_regmem 
  strnumber s  ;
  strnumber t  ;
  t = makestring () ;
  s = searchstring ( t ) ;
  if ( s > 0 ) 
  {
    {
      decr ( strptr ) ;
      poolptr = strstart [( strptr ) - 65536L ];
    } 
    Result = s ;
    return Result ;
  } 
  Result = t ;
  return Result ;
} 
void 
zprinttwo ( integer n ) 
{
  printtwo_regmem 
  n = abs ( n ) % 100 ;
  printchar ( 48 + ( n / 10 ) ) ;
  printchar ( 48 + ( n % 10 ) ) ;
} 
void 
zprinthex ( integer n ) 
{
  printhex_regmem 
  unsigned char k  ;
  k = 0 ;
  printchar ( 34 ) ;
  do {
      dig [k ]= n % 16 ;
    n = n / 16 ;
    incr ( k ) ;
  } while ( ! ( n == 0 ) ) ;
  printthedigs ( k ) ;
} 
void 
zprintromanint ( integer n ) 
{
  /* 10 */ printromanint_regmem 
  poolpointer j, k  ;
  nonnegativeinteger u, v  ;
  j = strstart [( 65542L ) - 65536L ];
  v = 1000 ;
  while ( true ) {
      
    while ( n >= v ) {
	
      printchar ( strpool [j ]) ;
      n = n - v ;
    } 
    if ( n <= 0 ) 
    return ;
    k = j + 2 ;
    u = v / ( strpool [k - 1 ]- 48 ) ;
    if ( strpool [k - 1 ]== 50 ) 
    {
      k = k + 2 ;
      u = u / ( strpool [k - 1 ]- 48 ) ;
    } 
    if ( n + u >= v ) 
    {
      printchar ( strpool [k ]) ;
      n = n + u ;
    } 
    else {
	
      j = j + 2 ;
      v = v / ( strpool [j - 1 ]- 48 ) ;
    } 
  } 
} 
void 
printcurrentstring ( void ) 
{
  printcurrentstring_regmem 
  poolpointer j  ;
  j = strstart [( strptr ) - 65536L ];
  while ( j < poolptr ) {
      
    printchar ( strpool [j ]) ;
    incr ( j ) ;
  } 
} 
void 
terminput ( void ) 
{
  terminput_regmem 
  integer k  ;
  fflush ( stdout ) ;
  if ( ! inputln ( termin , true ) ) 
  {
    curinput .limitfield = 0 ;
    fatalerror ( 65543L ) ;
  } 
  termoffset = 0 ;
  decr ( selector ) ;
  if ( last != first ) 
  {register integer for_end; k = first ;for_end = last - 1 ; if ( k <= 
  for_end) do 
    print ( buffer [k ]) ;
  while ( k++ < for_end ) ;} 
  println () ;
  incr ( selector ) ;
} 
void 
zinterror ( integer n ) 
{
  interror_regmem 
  print ( 65568L ) ;
  printint ( n ) ;
  printchar ( 41 ) ;
  error () ;
} 
void 
normalizeselector ( void ) 
{
  normalizeselector_regmem 
  if ( logopened ) 
  selector = 19 ;
  else selector = 17 ;
  if ( jobname == 0 ) 
  openlogfile () ;
  if ( interaction == 0 ) 
  decr ( selector ) ;
} 
void 
pauseforinstructions ( void ) 
{
  pauseforinstructions_regmem 
  if ( OKtointerrupt ) 
  {
    interaction = 3 ;
    if ( ( selector == 18 ) || ( selector == 16 ) ) 
    incr ( selector ) ;
    {
      if ( interaction == 3 ) 
      ;
      if ( filelineerrorstylep ) 
      printfileline () ;
      else printnl ( 65544L ) ;
      print ( 65578L ) ;
    } 
    {
      helpptr = 3 ;
      helpline [2 ]= 65579L ;
      helpline [1 ]= 65580L ;
      helpline [0 ]= 65581L ;
    } 
    deletionsallowed = false ;
    error () ;
    deletionsallowed = true ;
    interrupt = 0 ;
  } 
} 
integer 
zhalf ( integer x ) 
{
  register integer Result; half_regmem 
  if ( odd ( x ) ) 
  Result = ( x + 1 ) / 2 ;
  else Result = x / 2 ;
  return Result ;
} 
scaled 
zrounddecimals ( smallnumber k ) 
{
  register scaled Result; rounddecimals_regmem 
  integer a  ;
  a = 0 ;
  while ( k > 0 ) {
      
    decr ( k ) ;
    a = ( a + dig [k ]* 131072L ) / 10 ;
  } 
  Result = ( a + 1 ) / 2 ;
  return Result ;
} 
void 
zprintscaled ( scaled s ) 
{
  printscaled_regmem 
  scaled delta  ;
  if ( s < 0 ) 
  {
    printchar ( 45 ) ;
    s = - (integer) s ;
  } 
  printint ( s / 65536L ) ;
  printchar ( 46 ) ;
  s = 10 * ( s % 65536L ) + 5 ;
  delta = 10 ;
  do {
      if ( delta > 65536L ) 
    s = s - 17232 ;
    printchar ( 48 + ( s / 65536L ) ) ;
    s = 10 * ( s % 65536L ) ;
    delta = delta * 10 ;
  } while ( ! ( s <= delta ) ) ;
} 
scaled 
zmultandadd ( integer n , scaled x , scaled y , scaled maxanswer ) 
{
  register scaled Result; multandadd_regmem 
  if ( n < 0 ) 
  {
    x = - (integer) x ;
    n = - (integer) n ;
  } 
  if ( n == 0 ) 
  Result = y ;
  else if ( ( ( x <= ( maxanswer - y ) / n ) && ( - (integer) x <= ( maxanswer 
  + y ) / n ) ) ) 
  Result = n * x + y ;
  else {
      
    aritherror = true ;
    Result = 0 ;
  } 
  return Result ;
} 
scaled 
zxovern ( scaled x , integer n ) 
{
  register scaled Result; xovern_regmem 
  boolean negative  ;
  negative = false ;
  if ( n == 0 ) 
  {
    aritherror = true ;
    Result = 0 ;
    texremainder = x ;
  } 
  else {
      
    if ( n < 0 ) 
    {
      x = - (integer) x ;
      n = - (integer) n ;
      negative = true ;
    } 
    if ( x >= 0 ) 
    {
      Result = x / n ;
      texremainder = x % n ;
    } 
    else {
	
      Result = - (integer) ( ( - (integer) x ) / n ) ;
      texremainder = - (integer) ( ( - (integer) x ) % n ) ;
    } 
  } 
  if ( negative ) 
  texremainder = - (integer) texremainder ;
  return Result ;
} 
scaled 
zxnoverd ( scaled x , integer n , integer d ) 
{
  register scaled Result; xnoverd_regmem 
  boolean positive  ;
  nonnegativeinteger t, u, v  ;
  if ( x >= 0 ) 
  positive = true ;
  else {
      
    x = - (integer) x ;
    positive = false ;
  } 
  t = ( x % 32768L ) * n ;
  u = ( x / 32768L ) * n + ( t / 32768L ) ;
  v = ( u % d ) * 32768L + ( t % 32768L ) ;
  if ( u / d >= 32768L ) 
  aritherror = true ;
  else u = 32768L * ( u / d ) + ( v / d ) ;
  if ( positive ) 
  {
    Result = u ;
    texremainder = v % d ;
  } 
  else {
      
    Result = - (integer) u ;
    texremainder = - (integer) ( v % d ) ;
  } 
  return Result ;
} 
halfword 
zbadness ( scaled t , scaled s ) 
{
  register halfword Result; badness_regmem 
  integer r  ;
  if ( t == 0 ) 
  Result = 0 ;
  else if ( s <= 0 ) 
  Result = 10000 ;
  else {
      
    if ( t <= 7230584L ) 
    r = ( t * 297 ) / s ;
    else if ( s >= 1663497L ) 
    r = t / ( s / 297 ) ;
    else r = t ;
    if ( r > 1290 ) 
    Result = 10000 ;
    else Result = ( r * r * r + 131072L ) / 262144L ;
  } 
  return Result ;
} 
integer 
zmakefrac ( integer p , integer q ) 
{
  register integer Result; makefrac_regmem 
  integer f  ;
  integer n  ;
  boolean negative  ;
  integer becareful  ;
  if ( p >= 0 ) 
  negative = false ;
  else {
      
    p = - (integer) p ;
    negative = true ;
  } 
  if ( q <= 0 ) 
  {
	;
#ifdef TEXMF_DEBUG
    if ( q == 0 ) 
    confusion ( 47 ) ;
#endif /* TEXMF_DEBUG */
    q = - (integer) q ;
    negative = ! negative ;
  } 
  n = p / q ;
  p = p % q ;
  if ( n >= 8 ) 
  {
    aritherror = true ;
    if ( negative ) 
    Result = -2147483647L ;
    else Result = 2147483647L ;
  } 
  else {
      
    n = ( n - 1 ) * 268435456L ;
    f = 1 ;
    do {
	becareful = p - q ;
      p = becareful + p ;
      if ( p >= 0 ) 
      f = f + f + 1 ;
      else {
	  
	f = f + f ;
	p = p + q ;
      } 
    } while ( ! ( f >= 268435456L ) ) ;
    becareful = p - q ;
    if ( becareful + p >= 0 ) 
    incr ( f ) ;
    if ( negative ) 
    Result = - (integer) ( f + n ) ;
    else Result = f + n ;
  } 
  return Result ;
} 
integer 
ztakefrac ( integer q , integer f ) 
{
  register integer Result; takefrac_regmem 
  integer p  ;
  boolean negative  ;
  integer n  ;
  integer becareful  ;
  if ( f >= 0 ) 
  negative = false ;
  else {
      
    f = - (integer) f ;
    negative = true ;
  } 
  if ( q < 0 ) 
  {
    q = - (integer) q ;
    negative = ! negative ;
  } 
  if ( f < 268435456L ) 
  n = 0 ;
  else {
      
    n = f / 268435456L ;
    f = f % 268435456L ;
    if ( q <= 2147483647L / n ) 
    n = n * q ;
    else {
	
      aritherror = true ;
      n = 2147483647L ;
    } 
  } 
  f = f + 268435456L ;
  p = 134217728L ;
  if ( q < 1073741824L ) 
  do {
      if ( odd ( f ) ) 
    p = ( p + q ) / 2 ;
    else p = ( p ) / 2 ;
    f = ( f ) / 2 ;
  } while ( ! ( f == 1 ) ) ;
  else do {
      if ( odd ( f ) ) 
    p = p + ( q - p ) / 2 ;
    else p = ( p ) / 2 ;
    f = ( f ) / 2 ;
  } while ( ! ( f == 1 ) ) ;
  becareful = n - 2147483647L ;
  if ( becareful + p > 0 ) 
  {
    aritherror = true ;
    n = 2147483647L - p ;
  } 
  if ( negative ) 
  Result = - (integer) ( n + p ) ;
  else Result = n + p ;
  return Result ;
} 
integer 
zmlog ( integer x ) 
{
  register integer Result; mlog_regmem 
  integer y, z  ;
  integer k  ;
  if ( x <= 0 ) 
  {
    {
      if ( interaction == 3 ) 
      ;
      if ( filelineerrorstylep ) 
      printfileline () ;
      else printnl ( 65544L ) ;
      print ( 65582L ) ;
    } 
    printscaled ( x ) ;
    print ( 65583L ) ;
    {
      helpptr = 2 ;
      helpline [1 ]= 65584L ;
      helpline [0 ]= 65585L ;
    } 
    error () ;
    Result = 0 ;
  } 
  else {
      
    y = 1302456860L ;
    z = 6581195L ;
    while ( x < 1073741824L ) {
	
      x = x + x ;
      y = y - 93032639L ;
      z = z - 48782L ;
    } 
    y = y + ( z / 65536L ) ;
    k = 2 ;
    while ( x > 1073741828L ) {
	
      z = ( ( x - 1 ) / twotothe [k ]) + 1 ;
      while ( x < 1073741824L + z ) {
	  
	z = ( z + 1 ) / 2 ;
	k = k + 1 ;
      } 
      y = y + speclog [k ];
      x = x - z ;
    } 
    Result = y / 8 ;
  } 
  return Result ;
} 
integer 
zabvscd ( integer a , integer b , integer c , integer d ) 
{
  /* 10 */ register integer Result; abvscd_regmem 
  integer q, r  ;
  if ( a < 0 ) 
  {
    a = - (integer) a ;
    b = - (integer) b ;
  } 
  if ( c < 0 ) 
  {
    c = - (integer) c ;
    d = - (integer) d ;
  } 
  if ( d <= 0 ) 
  {
    if ( b >= 0 ) {
	
      if ( ( ( a == 0 ) || ( b == 0 ) ) && ( ( c == 0 ) || ( d == 0 ) ) ) 
      {
	Result = 0 ;
	return Result ;
      } 
      else {
	  
	Result = 1 ;
	return Result ;
      } 
    } 
    if ( d == 0 ) {
	
      if ( a == 0 ) 
      {
	Result = 0 ;
	return Result ;
      } 
      else {
	  
	Result = -1 ;
	return Result ;
      } 
    } 
    q = a ;
    a = c ;
    c = q ;
    q = - (integer) b ;
    b = - (integer) d ;
    d = q ;
  } 
  else if ( b <= 0 ) 
  {
    if ( b < 0 ) {
	
      if ( a > 0 ) 
      {
	Result = -1 ;
	return Result ;
      } 
    } 
    if ( c == 0 ) 
    {
      Result = 0 ;
      return Result ;
    } 
    else {
	
      Result = -1 ;
      return Result ;
    } 
  } 
  while ( true ) {
      
    q = a / d ;
    r = c / b ;
    if ( q != r ) {
	
      if ( q > r ) 
      {
	Result = 1 ;
	return Result ;
      } 
      else {
	  
	Result = -1 ;
	return Result ;
      } 
    } 
    q = a % d ;
    r = c % b ;
    if ( r == 0 ) {
	
      if ( q == 0 ) 
      {
	Result = 0 ;
	return Result ;
      } 
      else {
	  
	Result = 1 ;
	return Result ;
      } 
    } 
    if ( q == 0 ) 
    {
      Result = -1 ;
      return Result ;
    } 
    a = b ;
    b = q ;
    c = d ;
    d = r ;
  } 
  return Result ;
} 
void 
newrandoms ( void ) 
{
  newrandoms_regmem 
  unsigned char k  ;
  integer x  ;
  {register integer for_end; k = 0 ;for_end = 23 ; if ( k <= for_end) do 
    {
      x = randoms [k ]- randoms [k + 31 ];
      if ( x < 0 ) 
      x = x + 268435456L ;
      randoms [k ]= x ;
    } 
  while ( k++ < for_end ) ;} 
  {register integer for_end; k = 24 ;for_end = 54 ; if ( k <= for_end) do 
    {
      x = randoms [k ]- randoms [k - 24 ];
      if ( x < 0 ) 
      x = x + 268435456L ;
      randoms [k ]= x ;
    } 
  while ( k++ < for_end ) ;} 
  jrandom = 54 ;
} 
void 
zinitrandoms ( integer seed ) 
{
  initrandoms_regmem 
  integer j, jj, k  ;
  unsigned char i  ;
  j = abs ( seed ) ;
  while ( j >= 268435456L ) j = ( j ) / 2 ;
  k = 1 ;
  {register integer for_end; i = 0 ;for_end = 54 ; if ( i <= for_end) do 
    {
      jj = k ;
      k = j - k ;
      j = jj ;
      if ( k < 0 ) 
      k = k + 268435456L ;
      randoms [( i * 21 ) % 55 ]= j ;
    } 
  while ( i++ < for_end ) ;} 
  newrandoms () ;
  newrandoms () ;
  newrandoms () ;
} 
integer 
zunifrand ( integer x ) 
{
  register integer Result; unifrand_regmem 
  integer y  ;
  if ( jrandom == 0 ) 
  newrandoms () ;
  else decr ( jrandom ) ;
  y = takefrac ( abs ( x ) , randoms [jrandom ]) ;
  if ( y == abs ( x ) ) 
  Result = 0 ;
  else if ( x > 0 ) 
  Result = y ;
  else Result = - (integer) y ;
  return Result ;
} 
integer 
normrand ( void ) 
{
  register integer Result; normrand_regmem 
  integer x, u, l  ;
  do {
      do { if ( jrandom == 0 ) 
      newrandoms () ;
      else decr ( jrandom ) ;
      x = takefrac ( 112429L , randoms [jrandom ]- 134217728L ) ;
      if ( jrandom == 0 ) 
      newrandoms () ;
      else decr ( jrandom ) ;
      u = randoms [jrandom ];
    } while ( ! ( abs ( x ) < u ) ) ;
    x = makefrac ( x , u ) ;
    l = 139548960L - mlog ( u ) ;
  } while ( ! ( abvscd ( 1024 , l , x , x ) >= 0 ) ) ;
  Result = x ;
  return Result ;
} 
#ifdef TEXMF_DEBUG
void 
zprintword ( memoryword w ) 
{
  printword_regmem 
  printint ( w .cint ) ;
  printchar ( 32 ) ;
  printscaled ( w .cint ) ;
  printchar ( 32 ) ;
  printscaled ( round ( 65536L * w .gr ) ) ;
  println () ;
  printint ( w .hh .v.LH ) ;
  printchar ( 61 ) ;
  printint ( w .hh.b0 ) ;
  printchar ( 58 ) ;
  printint ( w .hh.b1 ) ;
  printchar ( 59 ) ;
  printint ( w .hh .v.RH ) ;
  printchar ( 32 ) ;
  printint ( w .qqqq .b0 ) ;
  printchar ( 58 ) ;
  printint ( w .qqqq .b1 ) ;
  printchar ( 58 ) ;
  printint ( w .qqqq .b2 ) ;
  printchar ( 58 ) ;
  printint ( w .qqqq .b3 ) ;
} 
#endif /* TEXMF_DEBUG */
void 
zshowtokenlist ( integer p , integer q , integer l ) 
{
  /* 10 */ showtokenlist_regmem 
  integer m, c  ;
  integer matchchr  ;
  UTF16code n  ;
  matchchr = 35 ;
  n = 48 ;
  tally = 0 ;
  while ( ( p != -268435455L ) && ( tally < l ) ) {
      
    if ( p == q ) 
    {
      firstcount = tally ;
      trickcount = tally + 1 + errorline - halferrorline ;
      if ( trickcount < errorline ) 
      trickcount = errorline ;
    } 
    if ( ( p < himemmin ) || ( p > memend ) ) 
    {
      printesc ( 65597L ) ;
      return ;
    } 
    if ( mem [p ].hh .v.LH >= 33554431L ) 
    printcs ( mem [p ].hh .v.LH - 33554431L ) ;
    else {
	
      m = mem [p ].hh .v.LH / 2097152L ;
      c = mem [p ].hh .v.LH % 2097152L ;
      if ( mem [p ].hh .v.LH < 0 ) 
      printesc ( 65883L ) ;
      else switch ( m ) 
      {case 1 : 
      case 2 : 
      case 3 : 
      case 4 : 
      case 7 : 
      case 8 : 
      case 10 : 
      case 11 : 
      case 12 : 
	printchar ( c ) ;
	break ;
      case 6 : 
	{
	  printchar ( c ) ;
	  printchar ( c ) ;
	} 
	break ;
      case 5 : 
	{
	  printchar ( matchchr ) ;
	  if ( c <= 9 ) 
	  printchar ( c + 48 ) ;
	  else {
	      
	    printchar ( 33 ) ;
	    return ;
	  } 
	} 
	break ;
      case 13 : 
	{
	  matchchr = c ;
	  printchar ( c ) ;
	  incr ( n ) ;
	  printchar ( n ) ;
	  if ( n > 57 ) 
	  return ;
	} 
	break ;
      case 14 : 
	if ( c == 0 ) 
	print ( 65884L ) ;
	break ;
	default: 
	printesc ( 65883L ) ;
	break ;
      } 
    } 
    p = mem [p ].hh .v.RH ;
  } 
  if ( p != -268435455L ) 
  printesc ( 65709L ) ;
} 
void 
runaway ( void ) 
{
  runaway_regmem 
  halfword p  ;
  if ( scannerstatus > 1 ) 
  {
    switch ( scannerstatus ) 
    {case 2 : 
      {
	printnl ( 65897L ) ;
	p = defref ;
      } 
      break ;
    case 3 : 
      {
	printnl ( 65898L ) ;
	p = memtop - 3 ;
      } 
      break ;
    case 4 : 
      {
	printnl ( 65899L ) ;
	p = memtop - 4 ;
      } 
      break ;
    case 5 : 
      {
	printnl ( 65900L ) ;
	p = defref ;
      } 
      break ;
    } 
    printchar ( 63 ) ;
    println () ;
    showtokenlist ( mem [p ].hh .v.RH , -268435455L , errorline - 10 ) ;
  } 
} 
halfword 
getavail ( void ) 
{
  register halfword Result; getavail_regmem 
  halfword p  ;
  p = avail ;
  if ( p != -268435455L ) 
  avail = mem [avail ].hh .v.RH ;
  else if ( memend < memmax ) 
  {
    incr ( memend ) ;
    p = memend ;
  } 
  else {
      
    decr ( himemmin ) ;
    p = himemmin ;
    if ( himemmin <= lomemmax ) 
    {
      runaway () ;
      overflow ( 65586L , memmax + 1 - memmin ) ;
    } 
  } 
  mem [p ].hh .v.RH = -268435455L ;
	;
#ifdef STAT
  incr ( dynused ) ;
#endif /* STAT */
  Result = p ;
  return Result ;
} 
void 
zflushlist ( halfword p ) 
{
  flushlist_regmem 
  halfword q, r  ;
  if ( p != -268435455L ) 
  {
    r = p ;
    do {
	q = r ;
      r = mem [r ].hh .v.RH ;
	;
#ifdef STAT
      decr ( dynused ) ;
#endif /* STAT */
    } while ( ! ( r == -268435455L ) ) ;
    mem [q ].hh .v.RH = avail ;
    avail = p ;
  } 
} 
halfword 
zgetnode ( integer s ) 
{
  /* 40 10 20 */ register halfword Result; getnode_regmem 
  halfword p  ;
  halfword q  ;
  integer r  ;
  integer t  ;
  lab20: p = rover ;
  do {
      q = p + mem [p ].hh .v.LH ;
    while ( ( mem [q ].hh .v.RH == 1073741823L ) ) {
	
      t = mem [q + 1 ].hh .v.RH ;
      if ( q == rover ) 
      rover = t ;
      mem [t + 1 ].hh .v.LH = mem [q + 1 ].hh .v.LH ;
      mem [mem [q + 1 ].hh .v.LH + 1 ].hh .v.RH = t ;
      q = q + mem [q ].hh .v.LH ;
    } 
    r = q - s ;
    if ( r > p + 1 ) 
    {
      mem [p ].hh .v.LH = r - p ;
      rover = p ;
      goto lab40 ;
    } 
    if ( r == p ) {
	
      if ( mem [p + 1 ].hh .v.RH != p ) 
      {
	rover = mem [p + 1 ].hh .v.RH ;
	t = mem [p + 1 ].hh .v.LH ;
	mem [rover + 1 ].hh .v.LH = t ;
	mem [t + 1 ].hh .v.RH = rover ;
	goto lab40 ;
      } 
    } 
    mem [p ].hh .v.LH = q - p ;
    p = mem [p + 1 ].hh .v.RH ;
  } while ( ! ( p == rover ) ) ;
  if ( s == 1073741824L ) 
  {
    Result = 1073741823L ;
    return Result ;
  } 
  if ( lomemmax + 2 < himemmin ) {
      
    if ( lomemmax + 2 <= membot + 1073741823L ) 
    {
      if ( himemmin - lomemmax >= 1998 ) 
      t = lomemmax + 1000 ;
      else t = lomemmax + 1 + ( himemmin - lomemmax ) / 2 ;
      p = mem [rover + 1 ].hh .v.LH ;
      q = lomemmax ;
      mem [p + 1 ].hh .v.RH = q ;
      mem [rover + 1 ].hh .v.LH = q ;
      if ( t > membot + 1073741823L ) 
      t = membot + 1073741823L ;
      mem [q + 1 ].hh .v.RH = rover ;
      mem [q + 1 ].hh .v.LH = p ;
      mem [q ].hh .v.RH = 1073741823L ;
      mem [q ].hh .v.LH = t - lomemmax ;
      lomemmax = t ;
      mem [lomemmax ].hh .v.RH = -268435455L ;
      mem [lomemmax ].hh .v.LH = -268435455L ;
      rover = q ;
      goto lab20 ;
    } 
  } 
  overflow ( 65586L , memmax + 1 - memmin ) ;
  lab40: mem [r ].hh .v.RH = -268435455L ;
	;
#ifdef STAT
  varused = varused + s ;
#endif /* STAT */
  if ( s >= 3 ) 
  {
    mem [r + s - 1 ].hh .v.LH = curinput .synctextagfield ;
    mem [r + s - 1 ].hh .v.RH = line ;
  } 
  Result = r ;
  return Result ;
} 
void 
zfreenode ( halfword p , halfword s ) 
{
  freenode_regmem 
  halfword q  ;
  mem [p ].hh .v.LH = s ;
  mem [p ].hh .v.RH = 1073741823L ;
  q = mem [rover + 1 ].hh .v.LH ;
  mem [p + 1 ].hh .v.LH = q ;
  mem [p + 1 ].hh .v.RH = rover ;
  mem [rover + 1 ].hh .v.LH = p ;
  mem [q + 1 ].hh .v.RH = p ;
	;
#ifdef STAT
  varused = varused - s ;
#endif /* STAT */
} 
halfword 
newnullbox ( void ) 
{
  register halfword Result; newnullbox_regmem 
  halfword p  ;
  p = getnode ( 8 ) ;
  mem [p ].hh.b0 = 0 ;
  mem [p ].hh.b1 = 0 ;
  mem [p + 1 ].cint = 0 ;
  mem [p + 2 ].cint = 0 ;
  mem [p + 3 ].cint = 0 ;
  mem [p + 4 ].cint = 0 ;
  mem [p + 5 ].hh .v.RH = -268435455L ;
  mem [p + 5 ].hh.b0 = 0 ;
  mem [p + 5 ].hh.b1 = 0 ;
  mem [p + 6 ].gr = 0.0 ;
  Result = p ;
  return Result ;
} 
halfword 
newrule ( void ) 
{
  register halfword Result; newrule_regmem 
  halfword p  ;
  p = getnode ( 5 ) ;
  mem [p ].hh.b0 = 2 ;
  mem [p ].hh.b1 = 0 ;
  mem [p + 1 ].cint = -1073741824L ;
  mem [p + 2 ].cint = -1073741824L ;
  mem [p + 3 ].cint = -1073741824L ;
  Result = p ;
  return Result ;
} 
halfword 
znewligature ( internalfontnumber f , quarterword c , halfword q ) 
{
  register halfword Result; newligature_regmem 
  halfword p  ;
  p = getnode ( 2 ) ;
  mem [p ].hh.b0 = 6 ;
  mem [p + 1 ].hh.b0 = f ;
  mem [p + 1 ].hh.b1 = c ;
  mem [p + 1 ].hh .v.RH = q ;
  mem [p ].hh.b1 = 0 ;
  Result = p ;
  return Result ;
} 
halfword 
znewligitem ( quarterword c ) 
{
  register halfword Result; newligitem_regmem 
  halfword p  ;
  p = getnode ( 2 ) ;
  mem [p ].hh.b1 = c ;
  mem [p + 1 ].hh .v.RH = -268435455L ;
  Result = p ;
  return Result ;
} 
halfword 
newdisc ( void ) 
{
  register halfword Result; newdisc_regmem 
  halfword p  ;
  p = getnode ( 2 ) ;
  mem [p ].hh.b0 = 7 ;
  mem [p ].hh.b1 = 0 ;
  mem [p + 1 ].hh .v.LH = -268435455L ;
  mem [p + 1 ].hh .v.RH = -268435455L ;
  Result = p ;
  return Result ;
} 
void 
zcopynativeglyphinfo ( halfword src , halfword dest ) 
{
  copynativeglyphinfo_regmem 
  integer glyphcount  ;
  if ( mem [src + 5 ].ptr != nullptr ) 
  {
    glyphcount = mem [src + 4 ].qqqq .b3 ;
    mem [dest + 5 ].ptr = xmallocarray ( char , glyphcount * 10 ) ;
    memcpy ( mem [dest + 5 ].ptr , mem [src + 5 ].ptr , glyphcount * 10 ) 
    ;
    mem [dest + 4 ].qqqq .b3 = glyphcount ;
  } 
} 
halfword 
znewmath ( scaled w , smallnumber s ) 
{
  register halfword Result; newmath_regmem 
  halfword p  ;
  p = getnode ( 3 ) ;
  mem [p ].hh.b0 = 9 ;
  mem [p ].hh.b1 = s ;
  mem [p + 1 ].cint = w ;
  Result = p ;
  return Result ;
} 
halfword 
znewspec ( halfword p ) 
{
  register halfword Result; newspec_regmem 
  halfword q  ;
  q = getnode ( 4 ) ;
  mem [q ]= mem [p ];
  mem [q ].hh .v.RH = -268435455L ;
  mem [q + 1 ].cint = mem [p + 1 ].cint ;
  mem [q + 2 ].cint = mem [p + 2 ].cint ;
  mem [q + 3 ].cint = mem [p + 3 ].cint ;
  Result = q ;
  return Result ;
} 
halfword 
znewparamglue ( smallnumber n ) 
{
  register halfword Result; newparamglue_regmem 
  halfword p  ;
  halfword q  ;
  p = getnode ( 3 ) ;
  mem [p ].hh.b0 = 10 ;
  mem [p ].hh.b1 = n + 1 ;
  mem [p + 1 ].hh .v.RH = -268435455L ;
  q = eqtb [1205764L + n ].hh .v.RH ;
  mem [p + 1 ].hh .v.LH = q ;
  incr ( mem [q ].hh .v.RH ) ;
  Result = p ;
  return Result ;
} 
halfword 
znewglue ( halfword q ) 
{
  register halfword Result; newglue_regmem 
  halfword p  ;
  p = getnode ( 3 ) ;
  mem [p ].hh.b0 = 10 ;
  mem [p ].hh.b1 = 0 ;
  mem [p + 1 ].hh .v.RH = -268435455L ;
  mem [p + 1 ].hh .v.LH = q ;
  incr ( mem [q ].hh .v.RH ) ;
  Result = p ;
  return Result ;
} 
halfword 
znewskipparam ( smallnumber n ) 
{
  register halfword Result; newskipparam_regmem 
  halfword p  ;
  tempptr = newspec ( eqtb [1205764L + n ].hh .v.RH ) ;
  p = newglue ( tempptr ) ;
  mem [tempptr ].hh .v.RH = -268435455L ;
  mem [p ].hh.b1 = n + 1 ;
  Result = p ;
  return Result ;
} 
halfword 
znewkern ( scaled w ) 
{
  register halfword Result; newkern_regmem 
  halfword p  ;
  p = getnode ( 3 ) ;
  mem [p ].hh.b0 = 11 ;
  mem [p ].hh.b1 = 0 ;
  mem [p + 1 ].cint = w ;
  Result = p ;
  return Result ;
} 
halfword 
znewpenalty ( integer m ) 
{
  register halfword Result; newpenalty_regmem 
  halfword p  ;
  p = getnode ( 3 ) ;
  mem [p ].hh.b0 = 12 ;
  mem [p ].hh.b1 = 0 ;
  mem [p + 1 ].cint = m ;
  Result = p ;
  return Result ;
} 
#ifdef TEXMF_DEBUG
void 
zcheckmem ( boolean printlocs ) 
{
  /* 31 32 */ checkmem_regmem 
  halfword p, q  ;
  boolean clobbered  ;
  {register integer for_end; p = memmin ;for_end = lomemmax ; if ( p <= 
  for_end) do 
    freearr [p ]= false ;
  while ( p++ < for_end ) ;} 
  {register integer for_end; p = himemmin ;for_end = memend ; if ( p <= 
  for_end) do 
    freearr [p ]= false ;
  while ( p++ < for_end ) ;} 
  p = avail ;
  q = -268435455L ;
  clobbered = false ;
  while ( p != -268435455L ) {
      
    if ( ( p > memend ) || ( p < himemmin ) ) 
    clobbered = true ;
    else if ( freearr [p ]) 
    clobbered = true ;
    if ( clobbered ) 
    {
      printnl ( 65587L ) ;
      printint ( q ) ;
      goto lab31 ;
    } 
    freearr [p ]= true ;
    q = p ;
    p = mem [q ].hh .v.RH ;
  } 
  lab31: ;
  p = rover ;
  q = -268435455L ;
  clobbered = false ;
  do {
      if ( ( p >= lomemmax ) || ( p < memmin ) ) 
    clobbered = true ;
    else if ( ( mem [p + 1 ].hh .v.RH >= lomemmax ) || ( mem [p + 1 ].hh 
    .v.RH < memmin ) ) 
    clobbered = true ;
    else if ( ! ( ( mem [p ].hh .v.RH == 1073741823L ) ) || ( mem [p ].hh 
    .v.LH < 2 ) || ( p + mem [p ].hh .v.LH > lomemmax ) || ( mem [mem [p + 
    1 ].hh .v.RH + 1 ].hh .v.LH != p ) ) 
    clobbered = true ;
    if ( clobbered ) 
    {
      printnl ( 65588L ) ;
      printint ( q ) ;
      goto lab32 ;
    } 
    {register integer for_end; q = p ;for_end = p + mem [p ].hh .v.LH - 1 
    ; if ( q <= for_end) do 
      {
	if ( freearr [q ]) 
	{
	  printnl ( 65589L ) ;
	  printint ( q ) ;
	  goto lab32 ;
	} 
	freearr [q ]= true ;
      } 
    while ( q++ < for_end ) ;} 
    q = p ;
    p = mem [p + 1 ].hh .v.RH ;
  } while ( ! ( p == rover ) ) ;
  lab32: ;
  p = memmin ;
  while ( p <= lomemmax ) {
      
    if ( ( mem [p ].hh .v.RH == 1073741823L ) ) 
    {
      printnl ( 65590L ) ;
      printint ( p ) ;
    } 
    while ( ( p <= lomemmax ) && ! freearr [p ]) incr ( p ) ;
    while ( ( p <= lomemmax ) && freearr [p ]) incr ( p ) ;
  } 
  if ( printlocs ) 
  {
    printnl ( 65591L ) ;
    {register integer for_end; p = memmin ;for_end = lomemmax ; if ( p <= 
    for_end) do 
      if ( ! freearr [p ]&& ( ( p > waslomax ) || wasfree [p ]) ) 
      {
	printchar ( 32 ) ;
	printint ( p ) ;
      } 
    while ( p++ < for_end ) ;} 
    {register integer for_end; p = himemmin ;for_end = memend ; if ( p <= 
    for_end) do 
      if ( ! freearr [p ]&& ( ( p < washimin ) || ( p > wasmemend ) || 
      wasfree [p ]) ) 
      {
	printchar ( 32 ) ;
	printint ( p ) ;
      } 
    while ( p++ < for_end ) ;} 
  } 
  {register integer for_end; p = memmin ;for_end = lomemmax ; if ( p <= 
  for_end) do 
    wasfree [p ]= freearr [p ];
  while ( p++ < for_end ) ;} 
  {register integer for_end; p = himemmin ;for_end = memend ; if ( p <= 
  for_end) do 
    wasfree [p ]= freearr [p ];
  while ( p++ < for_end ) ;} 
  wasmemend = memend ;
  waslomax = lomemmax ;
  washimin = himemmin ;
} 
#endif /* TEXMF_DEBUG */
#ifdef TEXMF_DEBUG
void 
zsearchmem ( halfword p ) 
{
  searchmem_regmem 
  integer q  ;
  {register integer for_end; q = memmin ;for_end = lomemmax ; if ( q <= 
  for_end) do 
    {
      if ( mem [q ].hh .v.RH == p ) 
      {
	printnl ( 65592L ) ;
	printint ( q ) ;
	printchar ( 41 ) ;
      } 
      if ( mem [q ].hh .v.LH == p ) 
      {
	printnl ( 65593L ) ;
	printint ( q ) ;
	printchar ( 41 ) ;
      } 
    } 
  while ( q++ < for_end ) ;} 
  {register integer for_end; q = himemmin ;for_end = memend ; if ( q <= 
  for_end) do 
    {
      if ( mem [q ].hh .v.RH == p ) 
      {
	printnl ( 65592L ) ;
	printint ( q ) ;
	printchar ( 41 ) ;
      } 
      if ( mem [q ].hh .v.LH == p ) 
      {
	printnl ( 65593L ) ;
	printint ( q ) ;
	printchar ( 41 ) ;
      } 
    } 
  while ( q++ < for_end ) ;} 
  {register integer for_end; q = 1 ;for_end = 1206822L ; if ( q <= for_end) 
  do 
    {
      if ( eqtb [q ].hh .v.RH == p ) 
      {
	printnl ( 65813L ) ;
	printint ( q ) ;
	printchar ( 41 ) ;
      } 
    } 
  while ( q++ < for_end ) ;} 
  if ( saveptr > 0 ) 
  {register integer for_end; q = 0 ;for_end = saveptr - 1 ; if ( q <= 
  for_end) do 
    {
      if ( savestack [q ].hh .v.RH == p ) 
      {
	printnl ( 65875L ) ;
	printint ( q ) ;
	printchar ( 41 ) ;
      } 
    } 
  while ( q++ < for_end ) ;} 
  {register integer for_end; q = 0 ;for_end = hyphsize ; if ( q <= for_end) 
  do 
    {
      if ( hyphlist [q ]== p ) 
      {
	printnl ( 66377L ) ;
	printint ( q ) ;
	printchar ( 41 ) ;
      } 
    } 
  while ( q++ < for_end ) ;} 
} 
#endif /* TEXMF_DEBUG */
void 
zpdferror ( strnumber t , strnumber p ) 
{
  pdferror_regmem 
  normalizeselector () ;
  {
    if ( interaction == 3 ) 
    ;
    if ( filelineerrorstylep ) 
    printfileline () ;
    else printnl ( 65544L ) ;
    print ( 65594L ) ;
  } 
  if ( t != 0 ) 
  {
    print ( 65568L ) ;
    print ( t ) ;
    print ( 41 ) ;
  } 
  print ( 65595L ) ;
  print ( p ) ;
  {
    if ( interaction == 3 ) 
    interaction = 2 ;
    if ( logopened ) 
    error () ;
	;
#ifdef TEXMF_DEBUG
    if ( interaction > 0 ) 
    debughelp () ;
#endif /* TEXMF_DEBUG */
    history = 3 ;
    jumpout () ;
  } 
} 
halfword 
zprevrightmost ( halfword s , halfword e ) 
{
  register halfword Result; prevrightmost_regmem 
  halfword p  ;
  Result = -268435455L ;
  p = s ;
  if ( p == -268435455L ) 
  return Result ;
  while ( mem [p ].hh .v.RH != e ) {
      
    p = mem [p ].hh .v.RH ;
    if ( p == -268435455L ) 
    return Result ;
  } 
  Result = p ;
  return Result ;
} 
scaled 
zroundxnoverd ( scaled x , integer n , integer d ) 
{
  register scaled Result; roundxnoverd_regmem 
  boolean positive  ;
  nonnegativeinteger t, u, v  ;
  if ( x >= 0 ) 
  positive = true ;
  else {
      
    x = - (integer) x ;
    positive = false ;
  } 
  t = ( x % 32768L ) * n ;
  u = ( x / 32768L ) * n + ( t / 32768L ) ;
  v = ( u % d ) * 32768L + ( t % 32768L ) ;
  if ( u / d >= 32768L ) 
  aritherror = true ;
  else u = 32768L * ( u / d ) + ( v / d ) ;
  v = v % d ;
  if ( 2 * v >= d ) 
  incr ( u ) ;
  if ( positive ) 
  Result = u ;
  else Result = - (integer) u ;
  return Result ;
} 
boolean 
zisbitset ( integer n , smallnumber s ) 
{
  register boolean Result; isbitset_regmem 
  integer m, i  ;
  m = 1 ;
  {register integer for_end; i = 1 ;for_end = s - 1 ; if ( i <= for_end) do 
    m = m * 2 ;
  while ( i++ < for_end ) ;} 
  Result = ( n / m ) % 2 ;
  return Result ;
} 
integer 
getmicrointerval ( void ) 
{
  register integer Result; getmicrointerval_regmem 
  integer s, m  ;
  secondsandmicros ( s , m ) ;
  if ( ( s - epochseconds ) > 32767 ) 
  Result = 2147483647L ;
  else if ( ( microseconds > m ) ) 
  Result = ( ( s - 1 - epochseconds ) * 65536L ) + ( ( ( m + 1000000L - 
  microseconds ) / ((double) 100 ) ) * 65536L ) / ((double) 10000 ) ;
  else Result = ( ( s - epochseconds ) * 65536L ) + ( ( ( m - microseconds ) 
  / ((double) 100 ) ) * 65536L ) / ((double) 10000 ) ;
  return Result ;
} 
void 
zshortdisplay ( integer p ) 
{
  shortdisplay_regmem 
  integer n  ;
  while ( p > memmin ) {
      
    if ( ( p >= himemmin ) ) 
    {
      if ( p <= memend ) 
      {
	if ( mem [p ].hh.b0 != fontinshortdisplay ) 
	{
	  if ( ( mem [p ].hh.b0 > fontmax ) ) 
	  printchar ( 42 ) ;
	  else printesc ( hash [1196762L + mem [p ].hh.b0 ].v.RH ) ;
	  printchar ( 32 ) ;
	  fontinshortdisplay = mem [p ].hh.b0 ;
	} 
	print ( mem [p ].hh.b1 ) ;
      } 
    } 
    else switch ( mem [p ].hh.b0 ) 
    {case 0 : 
    case 1 : 
    case 3 : 
    case 4 : 
    case 5 : 
    case 13 : 
      print ( 65596L ) ;
      break ;
    case 8 : 
      switch ( mem [p ].hh.b1 ) 
      {case 40 : 
      case 41 : 
	{
	  if ( mem [p + 4 ].qqqq .b1 != fontinshortdisplay ) 
	  {
	    printesc ( hash [1196762L + mem [p + 4 ].qqqq .b1 ].v.RH ) ;
	    printchar ( 32 ) ;
	    fontinshortdisplay = mem [p + 4 ].qqqq .b1 ;
	  } 
	  printnativeword ( p ) ;
	} 
	break ;
	default: 
	print ( 65596L ) ;
	break ;
      } 
      break ;
    case 2 : 
      printchar ( 124 ) ;
      break ;
    case 10 : 
      if ( mem [p + 1 ].hh .v.LH != membot ) 
      printchar ( 32 ) ;
      break ;
    case 9 : 
      if ( mem [p ].hh.b1 >= 4 ) 
      print ( 65596L ) ;
      else printchar ( 36 ) ;
      break ;
    case 6 : 
      shortdisplay ( mem [p + 1 ].hh .v.RH ) ;
      break ;
    case 7 : 
      {
	shortdisplay ( mem [p + 1 ].hh .v.LH ) ;
	shortdisplay ( mem [p + 1 ].hh .v.RH ) ;
	n = mem [p ].hh.b1 ;
	while ( n > 0 ) {
	    
	  if ( mem [p ].hh .v.RH != -268435455L ) 
	  p = mem [p ].hh .v.RH ;
	  decr ( n ) ;
	} 
      } 
      break ;
      default: 
      ;
      break ;
    } 
    p = mem [p ].hh .v.RH ;
  } 
} 
void 
zprintfontandchar ( integer p ) 
{
  printfontandchar_regmem 
  if ( p > memend ) 
  printesc ( 65597L ) ;
  else {
      
    if ( ( mem [p ].hh.b0 > fontmax ) ) 
    printchar ( 42 ) ;
    else printesc ( hash [1196762L + mem [p ].hh.b0 ].v.RH ) ;
    printchar ( 32 ) ;
    print ( mem [p ].hh.b1 ) ;
  } 
} 
void 
zprintmark ( integer p ) 
{
  printmark_regmem 
  printchar ( 123 ) ;
  if ( ( p < himemmin ) || ( p > memend ) ) 
  printesc ( 65597L ) ;
  else showtokenlist ( mem [p ].hh .v.RH , -268435455L , maxprintline - 10 ) 
  ;
  printchar ( 125 ) ;
} 
void 
zprintruledimen ( scaled d ) 
{
  printruledimen_regmem 
  if ( ( d == -1073741824L ) ) 
  printchar ( 42 ) ;
  else printscaled ( d ) ;
} 
void 
zprintglue ( scaled d , integer order , strnumber s ) 
{
  printglue_regmem 
  printscaled ( d ) ;
  if ( ( order < 0 ) || ( order > 3 ) ) 
  print ( 65598L ) ;
  else if ( order > 0 ) 
  {
    print ( 65599L ) ;
    while ( order > 1 ) {
	
      printchar ( 108 ) ;
      decr ( order ) ;
    } 
  } 
  else if ( s != 0 ) 
  print ( s ) ;
} 
void 
zprintspec ( integer p , strnumber s ) 
{
  printspec_regmem 
  if ( ( p < memmin ) || ( p >= lomemmax ) ) 
  printchar ( 42 ) ;
  else {
      
    printscaled ( mem [p + 1 ].cint ) ;
    if ( s != 0 ) 
    print ( s ) ;
    if ( mem [p + 2 ].cint != 0 ) 
    {
      print ( 65600L ) ;
      printglue ( mem [p + 2 ].cint , mem [p ].hh.b0 , s ) ;
    } 
    if ( mem [p + 3 ].cint != 0 ) 
    {
      print ( 65601L ) ;
      printglue ( mem [p + 3 ].cint , mem [p ].hh.b1 , s ) ;
    } 
  } 
} 
void 
zprintfamandchar ( halfword p ) 
{
  printfamandchar_regmem 
  integer c  ;
  printesc ( 65765L ) ;
  printint ( ( mem [p ].hh.b0 % 256 ) % 256 ) ;
  printchar ( 32 ) ;
  c = ( casttoushort ( mem [p ].hh.b1 ) + ( ( mem [p ].hh.b0 / 256 ) * 
  65536L ) ) ;
  if ( c < 65536L ) 
  print ( c ) ;
  else printchar ( c ) ;
} 
void 
zprintdelimiter ( halfword p ) 
{
  printdelimiter_regmem 
  integer a  ;
  a = ( mem [p ].qqqq .b0 % 256 ) * 256 + ( mem [p ].qqqq .b1 + ( mem [p 
  ].qqqq .b0 / 256 ) * 65536L ) ;
  a = a * 4096 + ( mem [p ].qqqq .b2 % 256 ) * 256 + ( mem [p ].qqqq .b3 + 
  ( mem [p ].qqqq .b2 / 256 ) * 65536L ) ;
  if ( a < 0 ) 
  printint ( a ) ;
  else printhex ( a ) ;
} 
void 
zprintsubsidiarydata ( halfword p , UTF16code c ) 
{
  printsubsidiarydata_regmem 
  if ( ( poolptr - strstart [( strptr ) - 65536L ]) >= depththreshold ) 
  {
    if ( mem [p ].hh .v.RH != 0 ) 
    print ( 65602L ) ;
  } 
  else {
      
    {
      if ( ( c > 65535L ) ) 
      {
	strpool [poolptr ]= ( c - 65536L ) / 1024 + 55296L ;
	incr ( poolptr ) ;
	strpool [poolptr ]= ( c ) % 1024 + 56320L ;
	incr ( poolptr ) ;
      } 
      else {
	  
	strpool [poolptr ]= c ;
	incr ( poolptr ) ;
      } 
    } 
    tempptr = p ;
    switch ( mem [p ].hh .v.RH ) 
    {case 1 : 
      {
	println () ;
	printcurrentstring () ;
	printfamandchar ( p ) ;
      } 
      break ;
    case 2 : 
      showinfo () ;
      break ;
    case 3 : 
      if ( mem [p ].hh .v.LH == -268435455L ) 
      {
	println () ;
	printcurrentstring () ;
	print ( 66271L ) ;
      } 
      else showinfo () ;
      break ;
      default: 
      ;
      break ;
    } 
    decr ( poolptr ) ;
  } 
} 
void 
zprintstyle ( integer c ) 
{
  printstyle_regmem 
  switch ( c / 2 ) 
  {case 0 : 
    printesc ( 66272L ) ;
    break ;
  case 1 : 
    printesc ( 66273L ) ;
    break ;
  case 2 : 
    printesc ( 66274L ) ;
    break ;
  case 3 : 
    printesc ( 66275L ) ;
    break ;
    default: 
    print ( 66276L ) ;
    break ;
  } 
} 
void 
zprintskipparam ( integer n ) 
{
  printskipparam_regmem 
  switch ( n ) 
  {case 0 : 
    printesc ( 65676L ) ;
    break ;
  case 1 : 
    printesc ( 65677L ) ;
    break ;
  case 2 : 
    printesc ( 65678L ) ;
    break ;
  case 3 : 
    printesc ( 65679L ) ;
    break ;
  case 4 : 
    printesc ( 65680L ) ;
    break ;
  case 5 : 
    printesc ( 65681L ) ;
    break ;
  case 6 : 
    printesc ( 65682L ) ;
    break ;
  case 7 : 
    printesc ( 65683L ) ;
    break ;
  case 8 : 
    printesc ( 65684L ) ;
    break ;
  case 9 : 
    printesc ( 65685L ) ;
    break ;
  case 10 : 
    printesc ( 65686L ) ;
    break ;
  case 11 : 
    printesc ( 65687L ) ;
    break ;
  case 12 : 
    printesc ( 65688L ) ;
    break ;
  case 13 : 
    printesc ( 65689L ) ;
    break ;
  case 14 : 
    printesc ( 65690L ) ;
    break ;
  case 15 : 
    printesc ( 65691L ) ;
    break ;
  case 16 : 
    printesc ( 65692L ) ;
    break ;
  case 17 : 
    printesc ( 65693L ) ;
    break ;
  case 18 : 
    printesc ( 65694L ) ;
    break ;
    default: 
    print ( 65695L ) ;
    break ;
  } 
} 
void 
zshownodelist ( integer p ) 
{
  /* 10 */ shownodelist_regmem 
  integer n  ;
  integer i  ;
  real g  ;
  if ( ( poolptr - strstart [( strptr ) - 65536L ]) > depththreshold ) 
  {
    if ( p > -268435455L ) 
    print ( 65602L ) ;
    return ;
  } 
  n = 0 ;
  while ( p > memmin ) {
      
    println () ;
    printcurrentstring () ;
    if ( p > memend ) 
    {
      print ( 65603L ) ;
      return ;
    } 
    incr ( n ) ;
    if ( n > breadthmax ) 
    {
      print ( 65604L ) ;
      return ;
    } 
    if ( ( p >= himemmin ) ) 
    printfontandchar ( p ) ;
    else switch ( mem [p ].hh.b0 ) 
    {case 0 : 
    case 1 : 
    case 13 : 
      {
	if ( mem [p ].hh.b0 == 0 ) 
	printesc ( 104 ) ;
	else if ( mem [p ].hh.b0 == 1 ) 
	printesc ( 118 ) ;
	else printesc ( 65609L ) ;
	print ( 65610L ) ;
	printscaled ( mem [p + 3 ].cint ) ;
	printchar ( 43 ) ;
	printscaled ( mem [p + 2 ].cint ) ;
	print ( 65611L ) ;
	printscaled ( mem [p + 1 ].cint ) ;
	if ( mem [p ].hh.b0 == 13 ) 
	{
	  if ( mem [p ].hh.b1 != 0 ) 
	  {
	    print ( 65568L ) ;
	    printint ( mem [p ].hh.b1 + 1 ) ;
	    print ( 65613L ) ;
	  } 
	  if ( mem [p + 6 ].cint != 0 ) 
	  {
	    print ( 65614L ) ;
	    printglue ( mem [p + 6 ].cint , mem [p + 5 ].hh.b1 , 0 ) ;
	  } 
	  if ( mem [p + 4 ].cint != 0 ) 
	  {
	    print ( 65615L ) ;
	    printglue ( mem [p + 4 ].cint , mem [p + 5 ].hh.b0 , 0 ) ;
	  } 
	} 
	else {
	    
	  g = mem [p + 6 ].gr ;
	  if ( ( g != 0.0 ) && ( mem [p + 5 ].hh.b0 != 0 ) ) 
	  {
	    print ( 65616L ) ;
	    if ( mem [p + 5 ].hh.b0 == 2 ) 
	    print ( 65617L ) ;
	    if ( fabs ( g ) > 20000.0 ) 
	    {
	      if ( g > 0.0 ) 
	      printchar ( 62 ) ;
	      else print ( 65618L ) ;
	      printglue ( 20000 * 65536L , mem [p + 5 ].hh.b1 , 0 ) ;
	    } 
	    else printglue ( round ( 65536L * g ) , mem [p + 5 ].hh.b1 , 0 ) 
	    ;
	  } 
	  if ( mem [p + 4 ].cint != 0 ) 
	  {
	    print ( 65612L ) ;
	    printscaled ( mem [p + 4 ].cint ) ;
	  } 
	  if ( ( eTeXmode == 1 ) ) {
	      
	    if ( ( mem [p ].hh.b0 == 0 ) && ( ( mem [p ].hh.b1 ) == 2 ) ) 
	    print ( 66926L ) ;
	  } 
	} 
	{
	  {
	    if ( ( 46 > 65535L ) ) 
	    {
	      strpool [poolptr ]= ( -65490L ) / 1024 + 55296L ;
	      incr ( poolptr ) ;
	      strpool [poolptr ]= ( 46 ) % 1024 + 56320L ;
	      incr ( poolptr ) ;
	    } 
	    else {
		
	      strpool [poolptr ]= 46 ;
	      incr ( poolptr ) ;
	    } 
	  } 
	  shownodelist ( mem [p + 5 ].hh .v.RH ) ;
	  decr ( poolptr ) ;
	} 
      } 
      break ;
    case 2 : 
      {
	printesc ( 65619L ) ;
	printruledimen ( mem [p + 3 ].cint ) ;
	printchar ( 43 ) ;
	printruledimen ( mem [p + 2 ].cint ) ;
	print ( 65611L ) ;
	printruledimen ( mem [p + 1 ].cint ) ;
      } 
      break ;
    case 3 : 
      {
	printesc ( 65620L ) ;
	printint ( mem [p ].hh.b1 ) ;
	print ( 65621L ) ;
	printscaled ( mem [p + 3 ].cint ) ;
	print ( 65622L ) ;
	printspec ( mem [p + 4 ].hh .v.RH , 0 ) ;
	printchar ( 44 ) ;
	printscaled ( mem [p + 2 ].cint ) ;
	print ( 65623L ) ;
	printint ( mem [p + 1 ].cint ) ;
	{
	  {
	    if ( ( 46 > 65535L ) ) 
	    {
	      strpool [poolptr ]= ( -65490L ) / 1024 + 55296L ;
	      incr ( poolptr ) ;
	      strpool [poolptr ]= ( 46 ) % 1024 + 56320L ;
	      incr ( poolptr ) ;
	    } 
	    else {
		
	      strpool [poolptr ]= 46 ;
	      incr ( poolptr ) ;
	    } 
	  } 
	  shownodelist ( mem [p + 4 ].hh .v.LH ) ;
	  decr ( poolptr ) ;
	} 
      } 
      break ;
    case 8 : 
      switch ( mem [p ].hh.b1 ) 
      {case 0 : 
	{
	  printwritewhatsit ( 66749L , p ) ;
	  printchar ( 61 ) ;
	  printfilename ( mem [p + 1 ].hh .v.RH , mem [p + 2 ].hh .v.LH , 
	  mem [p + 2 ].hh .v.RH ) ;
	} 
	break ;
      case 1 : 
	{
	  printwritewhatsit ( 65923L , p ) ;
	  printmark ( mem [p + 1 ].hh .v.RH ) ;
	} 
	break ;
      case 2 : 
	printwritewhatsit ( 66750L , p ) ;
	break ;
      case 3 : 
	{
	  printesc ( 66751L ) ;
	  printmark ( mem [p + 1 ].hh .v.RH ) ;
	} 
	break ;
      case 4 : 
	{
	  printesc ( 66751L ) ;
	  print ( 66766L ) ;
	  printmark ( mem [p + 1 ].hh .v.RH ) ;
	} 
	break ;
      case 5 : 
	{
	  printesc ( 66753L ) ;
	  printint ( mem [p + 1 ].hh .v.RH ) ;
	  print ( 66767L ) ;
	  printint ( mem [p + 1 ].hh.b0 ) ;
	  printchar ( 44 ) ;
	  printint ( mem [p + 1 ].hh.b1 ) ;
	  printchar ( 41 ) ;
	} 
	break ;
      case 23 : 
	printesc ( 66761L ) ;
	break ;
      case 40 : 
      case 41 : 
	{
	  printesc ( hash [1196762L + mem [p + 4 ].qqqq .b1 ].v.RH ) ;
	  printchar ( 32 ) ;
	  printnativeword ( p ) ;
	} 
	break ;
      case 42 : 
	{
	  printesc ( hash [1196762L + mem [p + 4 ].qqqq .b1 ].v.RH ) ;
	  print ( 66768L ) ;
	  printint ( mem [p + 4 ].qqqq .b2 ) ;
	} 
	break ;
      case 43 : 
      case 44 : 
	{
	  if ( mem [p ].hh.b1 == 43 ) 
	  printesc ( 66756L ) ;
	  else printesc ( 66757L ) ;
	  print ( 66769L ) ;
	  {register integer for_end; i = 0 ;for_end = mem [p + 4 ].hh.b0 - 
	  1 ; if ( i <= for_end) do 
	    printrawchar ( picpathbyte ( p , i ) , true ) ;
	  while ( i++ < for_end ) ;} 
	  print ( 34 ) ;
	} 
	break ;
	default: 
	print ( 66770L ) ;
	break ;
      } 
      break ;
    case 10 : 
      if ( mem [p ].hh.b1 >= 100 ) 
      {
	printesc ( 65545L ) ;
	if ( mem [p ].hh.b1 == 101 ) 
	printchar ( 99 ) ;
	else if ( mem [p ].hh.b1 == 102 ) 
	printchar ( 120 ) ;
	print ( 65628L ) ;
	printspec ( mem [p + 1 ].hh .v.LH , 0 ) ;
	{
	  {
	    if ( ( 46 > 65535L ) ) 
	    {
	      strpool [poolptr ]= ( -65490L ) / 1024 + 55296L ;
	      incr ( poolptr ) ;
	      strpool [poolptr ]= ( 46 ) % 1024 + 56320L ;
	      incr ( poolptr ) ;
	    } 
	    else {
		
	      strpool [poolptr ]= 46 ;
	      incr ( poolptr ) ;
	    } 
	  } 
	  shownodelist ( mem [p + 1 ].hh .v.RH ) ;
	  decr ( poolptr ) ;
	} 
      } 
      else {
	  
	printesc ( 65624L ) ;
	if ( mem [p ].hh.b1 != 0 ) 
	{
	  printchar ( 40 ) ;
	  if ( mem [p ].hh.b1 < 98 ) 
	  printskipparam ( mem [p ].hh.b1 - 1 ) ;
	  else if ( mem [p ].hh.b1 == 98 ) 
	  printesc ( 65625L ) ;
	  else printesc ( 65626L ) ;
	  printchar ( 41 ) ;
	} 
	if ( mem [p ].hh.b1 != 98 ) 
	{
	  printchar ( 32 ) ;
	  if ( mem [p ].hh.b1 < 98 ) 
	  printspec ( mem [p + 1 ].hh .v.LH , 0 ) ;
	  else printspec ( mem [p + 1 ].hh .v.LH , 65627L ) ;
	} 
      } 
      break ;
    case 11 : 
      if ( mem [p ].hh.b1 != 99 ) 
      {
	printesc ( 65605L ) ;
	if ( mem [p ].hh.b1 != 0 ) 
	printchar ( 32 ) ;
	printscaled ( mem [p + 1 ].cint ) ;
	if ( mem [p ].hh.b1 == 2 ) 
	print ( 65629L ) ;
	else if ( mem [p ].hh.b1 == 3 ) 
	print ( 65630L ) ;
      } 
      else {
	  
	printesc ( 65631L ) ;
	printscaled ( mem [p + 1 ].cint ) ;
	print ( 65627L ) ;
      } 
      break ;
    case 40 : 
      {
	printesc ( 65605L ) ;
	printscaled ( mem [p + 1 ].cint ) ;
	if ( mem [p ].hh.b1 == 0 ) 
	print ( 65606L ) ;
	else print ( 65607L ) ;
      } 
      break ;
    case 9 : 
      if ( mem [p ].hh.b1 > 1 ) 
      {
	if ( odd ( mem [p ].hh.b1 ) ) 
	printesc ( 65632L ) ;
	else printesc ( 65633L ) ;
	if ( mem [p ].hh.b1 > 8 ) 
	printchar ( 82 ) ;
	else if ( mem [p ].hh.b1 > 4 ) 
	printchar ( 76 ) ;
	else printchar ( 77 ) ;
      } 
      else {
	  
	printesc ( 65634L ) ;
	if ( mem [p ].hh.b1 == 0 ) 
	print ( 65635L ) ;
	else print ( 65636L ) ;
	if ( mem [p + 1 ].cint != 0 ) 
	{
	  print ( 65637L ) ;
	  printscaled ( mem [p + 1 ].cint ) ;
	} 
      } 
      break ;
    case 6 : 
      {
	printfontandchar ( p + 1 ) ;
	print ( 65638L ) ;
	if ( mem [p ].hh.b1 > 1 ) 
	printchar ( 124 ) ;
	fontinshortdisplay = mem [p + 1 ].hh.b0 ;
	shortdisplay ( mem [p + 1 ].hh .v.RH ) ;
	if ( odd ( mem [p ].hh.b1 ) ) 
	printchar ( 124 ) ;
	printchar ( 41 ) ;
      } 
      break ;
    case 12 : 
      {
	printesc ( 65639L ) ;
	printint ( mem [p + 1 ].cint ) ;
      } 
      break ;
    case 7 : 
      {
	printesc ( 65640L ) ;
	if ( mem [p ].hh.b1 > 0 ) 
	{
	  print ( 65641L ) ;
	  printint ( mem [p ].hh.b1 ) ;
	} 
	{
	  {
	    if ( ( 46 > 65535L ) ) 
	    {
	      strpool [poolptr ]= ( -65490L ) / 1024 + 55296L ;
	      incr ( poolptr ) ;
	      strpool [poolptr ]= ( 46 ) % 1024 + 56320L ;
	      incr ( poolptr ) ;
	    } 
	    else {
		
	      strpool [poolptr ]= 46 ;
	      incr ( poolptr ) ;
	    } 
	  } 
	  shownodelist ( mem [p + 1 ].hh .v.LH ) ;
	  decr ( poolptr ) ;
	} 
	{
	  if ( ( 124 > 65535L ) ) 
	  {
	    strpool [poolptr ]= ( -65412L ) / 1024 + 55296L ;
	    incr ( poolptr ) ;
	    strpool [poolptr ]= ( 124 ) % 1024 + 56320L ;
	    incr ( poolptr ) ;
	  } 
	  else {
	      
	    strpool [poolptr ]= 124 ;
	    incr ( poolptr ) ;
	  } 
	} 
	shownodelist ( mem [p + 1 ].hh .v.RH ) ;
	decr ( poolptr ) ;
      } 
      break ;
    case 4 : 
      {
	printesc ( 65642L ) ;
	if ( mem [p + 1 ].hh .v.LH != 0 ) 
	{
	  printchar ( 115 ) ;
	  printint ( mem [p + 1 ].hh .v.LH ) ;
	} 
	printmark ( mem [p + 1 ].hh .v.RH ) ;
      } 
      break ;
    case 5 : 
      {
	printesc ( 65643L ) ;
	if ( mem [p ].hh.b1 != 0 ) 
	print ( 65644L ) ;
	{
	  {
	    if ( ( 46 > 65535L ) ) 
	    {
	      strpool [poolptr ]= ( -65490L ) / 1024 + 55296L ;
	      incr ( poolptr ) ;
	      strpool [poolptr ]= ( 46 ) % 1024 + 56320L ;
	      incr ( poolptr ) ;
	    } 
	    else {
		
	      strpool [poolptr ]= 46 ;
	      incr ( poolptr ) ;
	    } 
	  } 
	  shownodelist ( mem [p + 1 ].cint ) ;
	  decr ( poolptr ) ;
	} 
      } 
      break ;
    case 14 : 
      printstyle ( mem [p ].hh.b1 ) ;
      break ;
    case 15 : 
      {
	printesc ( 65847L ) ;
	{
	  if ( ( 68 > 65535L ) ) 
	  {
	    strpool [poolptr ]= ( -65468L ) / 1024 + 55296L ;
	    incr ( poolptr ) ;
	    strpool [poolptr ]= ( 68 ) % 1024 + 56320L ;
	    incr ( poolptr ) ;
	  } 
	  else {
	      
	    strpool [poolptr ]= 68 ;
	    incr ( poolptr ) ;
	  } 
	} 
	shownodelist ( mem [p + 1 ].hh .v.LH ) ;
	decr ( poolptr ) ;
	{
	  if ( ( 84 > 65535L ) ) 
	  {
	    strpool [poolptr ]= ( -65452L ) / 1024 + 55296L ;
	    incr ( poolptr ) ;
	    strpool [poolptr ]= ( 84 ) % 1024 + 56320L ;
	    incr ( poolptr ) ;
	  } 
	  else {
	      
	    strpool [poolptr ]= 84 ;
	    incr ( poolptr ) ;
	  } 
	} 
	shownodelist ( mem [p + 1 ].hh .v.RH ) ;
	decr ( poolptr ) ;
	{
	  if ( ( 83 > 65535L ) ) 
	  {
	    strpool [poolptr ]= ( -65453L ) / 1024 + 55296L ;
	    incr ( poolptr ) ;
	    strpool [poolptr ]= ( 83 ) % 1024 + 56320L ;
	    incr ( poolptr ) ;
	  } 
	  else {
	      
	    strpool [poolptr ]= 83 ;
	    incr ( poolptr ) ;
	  } 
	} 
	shownodelist ( mem [p + 2 ].hh .v.LH ) ;
	decr ( poolptr ) ;
	{
	  if ( ( 115 > 65535L ) ) 
	  {
	    strpool [poolptr ]= ( -65421L ) / 1024 + 55296L ;
	    incr ( poolptr ) ;
	    strpool [poolptr ]= ( 115 ) % 1024 + 56320L ;
	    incr ( poolptr ) ;
	  } 
	  else {
	      
	    strpool [poolptr ]= 115 ;
	    incr ( poolptr ) ;
	  } 
	} 
	shownodelist ( mem [p + 2 ].hh .v.RH ) ;
	decr ( poolptr ) ;
      } 
      break ;
    case 16 : 
    case 17 : 
    case 18 : 
    case 19 : 
    case 20 : 
    case 21 : 
    case 22 : 
    case 23 : 
    case 24 : 
    case 27 : 
    case 26 : 
    case 29 : 
    case 28 : 
    case 30 : 
    case 31 : 
      {
	switch ( mem [p ].hh.b0 ) 
	{case 16 : 
	  printesc ( 66277L ) ;
	  break ;
	case 17 : 
	  printesc ( 66278L ) ;
	  break ;
	case 18 : 
	  printesc ( 66279L ) ;
	  break ;
	case 19 : 
	  printesc ( 66280L ) ;
	  break ;
	case 20 : 
	  printesc ( 66281L ) ;
	  break ;
	case 21 : 
	  printesc ( 66282L ) ;
	  break ;
	case 22 : 
	  printesc ( 66283L ) ;
	  break ;
	case 23 : 
	  printesc ( 66284L ) ;
	  break ;
	case 27 : 
	  printesc ( 66285L ) ;
	  break ;
	case 26 : 
	  printesc ( 66286L ) ;
	  break ;
	case 29 : 
	  printesc ( 65864L ) ;
	  break ;
	case 24 : 
	  {
	    printesc ( 65856L ) ;
	    printdelimiter ( p + 4 ) ;
	  } 
	  break ;
	case 28 : 
	  {
	    printesc ( 65822L ) ;
	    printfamandchar ( p + 4 ) ;
	  } 
	  break ;
	case 30 : 
	  {
	    printesc ( 66287L ) ;
	    printdelimiter ( p + 1 ) ;
	  } 
	  break ;
	case 31 : 
	  {
	    if ( mem [p ].hh.b1 == 0 ) 
	    printesc ( 66288L ) ;
	    else printesc ( 66289L ) ;
	    printdelimiter ( p + 1 ) ;
	  } 
	  break ;
	} 
	if ( mem [p ].hh.b0 < 30 ) 
	{
	  if ( mem [p ].hh.b1 != 0 ) {
	      
	    if ( mem [p ].hh.b1 == 1 ) 
	    printesc ( 66290L ) ;
	    else printesc ( 66291L ) ;
	  } 
	  printsubsidiarydata ( p + 1 , 46 ) ;
	} 
	printsubsidiarydata ( p + 2 , 94 ) ;
	printsubsidiarydata ( p + 3 , 95 ) ;
      } 
      break ;
    case 25 : 
      {
	printesc ( 66292L ) ;
	if ( mem [p + 1 ].cint == 1073741824L ) 
	print ( 66293L ) ;
	else printscaled ( mem [p + 1 ].cint ) ;
	if ( ( ( mem [p + 4 ].qqqq .b0 % 256 ) != 0 ) || ( ( mem [p + 4 ]
	.qqqq .b1 + ( mem [p + 4 ].qqqq .b0 / 256 ) * 65536L ) != 0 ) || ( ( 
	mem [p + 4 ].qqqq .b2 % 256 ) != 0 ) || ( ( mem [p + 4 ].qqqq .b3 
	+ ( mem [p + 4 ].qqqq .b2 / 256 ) * 65536L ) != 0 ) ) 
	{
	  print ( 66294L ) ;
	  printdelimiter ( p + 4 ) ;
	} 
	if ( ( ( mem [p + 5 ].qqqq .b0 % 256 ) != 0 ) || ( ( mem [p + 5 ]
	.qqqq .b1 + ( mem [p + 5 ].qqqq .b0 / 256 ) * 65536L ) != 0 ) || ( ( 
	mem [p + 5 ].qqqq .b2 % 256 ) != 0 ) || ( ( mem [p + 5 ].qqqq .b3 
	+ ( mem [p + 5 ].qqqq .b2 / 256 ) * 65536L ) != 0 ) ) 
	{
	  print ( 66295L ) ;
	  printdelimiter ( p + 5 ) ;
	} 
	printsubsidiarydata ( p + 2 , 92 ) ;
	printsubsidiarydata ( p + 3 , 47 ) ;
      } 
      break ;
      default: 
      print ( 65608L ) ;
      break ;
    } 
    p = mem [p ].hh .v.RH ;
  } 
} 
void 
zshowbox ( halfword p ) 
{
  showbox_regmem 
  depththreshold = eqtb [7892289L ].cint ;
  breadthmax = eqtb [7892288L ].cint ;
  if ( breadthmax <= 0 ) 
  breadthmax = 5 ;
  if ( poolptr + depththreshold >= poolsize ) 
  depththreshold = poolsize - poolptr - 1 ;
  shownodelist ( p ) ;
  println () ;
} 
void 
zshortdisplayn ( integer p , integer m ) 
{
  shortdisplayn_regmem 
  breadthmax = m ;
  depththreshold = poolsize - poolptr - 1 ;
  shownodelist ( p ) ;
} 
void 
zdeletetokenref ( halfword p ) 
{
  deletetokenref_regmem 
  if ( mem [p ].hh .v.LH == -268435455L ) 
  flushlist ( p ) ;
  else decr ( mem [p ].hh .v.LH ) ;
} 
void 
zdeleteglueref ( halfword p ) 
{
  deleteglueref_regmem 
  if ( mem [p ].hh .v.RH == -268435455L ) 
  freenode ( p , 4 ) ;
  else decr ( mem [p ].hh .v.RH ) ;
} 
void 
zflushnodelist ( halfword p ) 
{
  /* 30 */ flushnodelist_regmem 
  halfword q  ;
  while ( p != -268435455L ) {
      
    q = mem [p ].hh .v.RH ;
    if ( ( p >= himemmin ) ) 
    {
      mem [p ].hh .v.RH = avail ;
      avail = p ;
	;
#ifdef STAT
      decr ( dynused ) ;
#endif /* STAT */
    } 
    else {
	
      switch ( mem [p ].hh.b0 ) 
      {case 0 : 
      case 1 : 
      case 13 : 
	{
	  flushnodelist ( mem [p + 5 ].hh .v.RH ) ;
	  freenode ( p , 8 ) ;
	  goto lab30 ;
	} 
	break ;
      case 2 : 
	{
	  freenode ( p , 5 ) ;
	  goto lab30 ;
	} 
	break ;
      case 3 : 
	{
	  flushnodelist ( mem [p + 4 ].hh .v.LH ) ;
	  deleteglueref ( mem [p + 4 ].hh .v.RH ) ;
	  freenode ( p , 5 ) ;
	  goto lab30 ;
	} 
	break ;
      case 8 : 
	{
	  switch ( mem [p ].hh.b1 ) 
	  {case 0 : 
	    freenode ( p , 3 ) ;
	    break ;
	  case 1 : 
	  case 3 : 
	  case 4 : 
	    {
	      deletetokenref ( mem [p + 1 ].hh .v.RH ) ;
	      freenode ( p , 2 ) ;
	      goto lab30 ;
	    } 
	    break ;
	  case 2 : 
	  case 5 : 
	    freenode ( p , 2 ) ;
	    break ;
	  case 40 : 
	  case 41 : 
	    {
	      {
		if ( mem [p + 5 ].ptr != nullptr ) 
		{
		  libcfree ( mem [p + 5 ].ptr ) ;
		  mem [p + 5 ].ptr = nullptr ;
		  mem [p + 4 ].qqqq .b3 = 0 ;
		} 
	      } 
	      freenode ( p , mem [p + 4 ].qqqq .b0 ) ;
	    } 
	    break ;
	  case 42 : 
	    freenode ( p , 5 ) ;
	    break ;
	  case 43 : 
	  case 44 : 
	    freenode ( p , ( 9 + ( mem [p + 4 ].hh.b0 + sizeof ( memoryword 
	    ) - 1 ) / sizeof ( memoryword ) ) ) ;
	    break ;
	  case 23 : 
	    freenode ( p , 2 ) ;
	    break ;
	    default: 
	    confusion ( 66772L ) ;
	    break ;
	  } 
	  goto lab30 ;
	} 
	break ;
      case 10 : 
	{
	  {
	    if ( mem [mem [p + 1 ].hh .v.LH ].hh .v.RH == -268435455L ) 
	    freenode ( mem [p + 1 ].hh .v.LH , 4 ) ;
	    else decr ( mem [mem [p + 1 ].hh .v.LH ].hh .v.RH ) ;
	  } 
	  if ( mem [p + 1 ].hh .v.RH != -268435455L ) 
	  flushnodelist ( mem [p + 1 ].hh .v.RH ) ;
	  freenode ( p , 3 ) ;
	  goto lab30 ;
	} 
	break ;
      case 11 : 
      case 9 : 
      case 12 : 
	{
	  freenode ( p , 3 ) ;
	  goto lab30 ;
	} 
	break ;
      case 40 : 
	{
	  freenode ( p , 3 ) ;
	  goto lab30 ;
	} 
	break ;
      case 6 : 
	flushnodelist ( mem [p + 1 ].hh .v.RH ) ;
	break ;
      case 4 : 
	deletetokenref ( mem [p + 1 ].hh .v.RH ) ;
	break ;
      case 7 : 
	{
	  flushnodelist ( mem [p + 1 ].hh .v.LH ) ;
	  flushnodelist ( mem [p + 1 ].hh .v.RH ) ;
	} 
	break ;
      case 5 : 
	flushnodelist ( mem [p + 1 ].cint ) ;
	break ;
      case 14 : 
	{
	  freenode ( p , 3 ) ;
	  goto lab30 ;
	} 
	break ;
      case 15 : 
	{
	  flushnodelist ( mem [p + 1 ].hh .v.LH ) ;
	  flushnodelist ( mem [p + 1 ].hh .v.RH ) ;
	  flushnodelist ( mem [p + 2 ].hh .v.LH ) ;
	  flushnodelist ( mem [p + 2 ].hh .v.RH ) ;
	  freenode ( p , 3 ) ;
	  goto lab30 ;
	} 
	break ;
      case 16 : 
      case 17 : 
      case 18 : 
      case 19 : 
      case 20 : 
      case 21 : 
      case 22 : 
      case 23 : 
      case 24 : 
      case 27 : 
      case 26 : 
      case 29 : 
      case 28 : 
	{
	  if ( mem [p + 1 ].hh .v.RH >= 2 ) 
	  flushnodelist ( mem [p + 1 ].hh .v.LH ) ;
	  if ( mem [p + 2 ].hh .v.RH >= 2 ) 
	  flushnodelist ( mem [p + 2 ].hh .v.LH ) ;
	  if ( mem [p + 3 ].hh .v.RH >= 2 ) 
	  flushnodelist ( mem [p + 3 ].hh .v.LH ) ;
	  if ( mem [p ].hh.b0 == 24 ) 
	  freenode ( p , 5 ) ;
	  else if ( mem [p ].hh.b0 == 28 ) 
	  freenode ( p , 5 ) ;
	  else freenode ( p , 4 ) ;
	  goto lab30 ;
	} 
	break ;
      case 30 : 
      case 31 : 
	{
	  freenode ( p , 4 ) ;
	  goto lab30 ;
	} 
	break ;
      case 25 : 
	{
	  flushnodelist ( mem [p + 2 ].hh .v.LH ) ;
	  flushnodelist ( mem [p + 3 ].hh .v.LH ) ;
	  freenode ( p , 6 ) ;
	  goto lab30 ;
	} 
	break ;
	default: 
	confusion ( 65645L ) ;
	break ;
      } 
      freenode ( p , 2 ) ;
      lab30: ;
    } 
    p = q ;
  } 
} 
halfword 
zcopynodelist ( halfword p ) 
{
  register halfword Result; copynodelist_regmem 
  halfword h  ;
  halfword q  ;
  halfword r  ;
  unsigned char words  ;
  h = getavail () ;
  q = h ;
  while ( p != -268435455L ) {
      
    words = 1 ;
    if ( ( p >= himemmin ) ) 
    r = getavail () ;
    else switch ( mem [p ].hh.b0 ) 
    {case 0 : 
    case 1 : 
    case 13 : 
      {
	r = getnode ( 8 ) ;
	mem [r + 7 ].hh .v.LH = mem [p + 7 ].hh .v.LH ;
	mem [r + 7 ].hh .v.RH = mem [p + 7 ].hh .v.RH ;
	mem [r + 6 ]= mem [p + 6 ];
	mem [r + 5 ]= mem [p + 5 ];
	mem [r + 5 ].hh .v.RH = copynodelist ( mem [p + 5 ].hh .v.RH ) ;
	words = 5 ;
      } 
      break ;
    case 2 : 
      {
	r = getnode ( 5 ) ;
	words = 4 ;
      } 
      break ;
    case 3 : 
      {
	r = getnode ( 5 ) ;
	mem [r + 4 ]= mem [p + 4 ];
	incr ( mem [mem [p + 4 ].hh .v.RH ].hh .v.RH ) ;
	mem [r + 4 ].hh .v.LH = copynodelist ( mem [p + 4 ].hh .v.LH ) ;
	words = 4 ;
      } 
      break ;
    case 8 : 
      switch ( mem [p ].hh.b1 ) 
      {case 0 : 
	{
	  r = getnode ( 3 ) ;
	  words = 3 ;
	} 
	break ;
      case 1 : 
      case 3 : 
      case 4 : 
	{
	  r = getnode ( 2 ) ;
	  incr ( mem [mem [p + 1 ].hh .v.RH ].hh .v.LH ) ;
	  words = 2 ;
	} 
	break ;
      case 2 : 
      case 5 : 
	{
	  r = getnode ( 2 ) ;
	  words = 2 ;
	} 
	break ;
      case 40 : 
      case 41 : 
	{
	  words = mem [p + 4 ].qqqq .b0 ;
	  r = getnode ( words ) ;
	  while ( words > 0 ) {
	      
	    decr ( words ) ;
	    mem [r + words ]= mem [p + words ];
	  } 
	  mem [r + 5 ].ptr = nullptr ;
	  mem [r + 4 ].qqqq .b3 = 0 ;
	  copynativeglyphinfo ( p , r ) ;
	} 
	break ;
      case 42 : 
	{
	  r = getnode ( 5 ) ;
	  words = 5 ;
	} 
	break ;
      case 43 : 
      case 44 : 
	{
	  words = ( 9 + ( mem [p + 4 ].hh.b0 + sizeof ( memoryword ) - 1 ) / 
	  sizeof ( memoryword ) ) ;
	  r = getnode ( words ) ;
	} 
	break ;
      case 23 : 
	r = getnode ( 2 ) ;
	break ;
	default: 
	confusion ( 66771L ) ;
	break ;
      } 
      break ;
    case 10 : 
      {
	r = getnode ( 3 ) ;
	incr ( mem [mem [p + 1 ].hh .v.LH ].hh .v.RH ) ;
	mem [r + 2 ].hh .v.LH = mem [p + 2 ].hh .v.LH ;
	mem [r + 2 ].hh .v.RH = mem [p + 2 ].hh .v.RH ;
	mem [r + 1 ].hh .v.LH = mem [p + 1 ].hh .v.LH ;
	mem [r + 1 ].hh .v.RH = copynodelist ( mem [p + 1 ].hh .v.RH ) ;
      } 
      break ;
    case 11 : 
    case 9 : 
    case 12 : 
      {
	r = getnode ( 3 ) ;
	words = 3 ;
      } 
      break ;
    case 40 : 
      {
	r = getnode ( 3 ) ;
	words = 3 ;
      } 
      break ;
    case 6 : 
      {
	r = getnode ( 2 ) ;
	mem [r + 1 ]= mem [p + 1 ];
	mem [r + 1 ].hh .v.RH = copynodelist ( mem [p + 1 ].hh .v.RH ) ;
      } 
      break ;
    case 7 : 
      {
	r = getnode ( 2 ) ;
	mem [r + 1 ].hh .v.LH = copynodelist ( mem [p + 1 ].hh .v.LH ) ;
	mem [r + 1 ].hh .v.RH = copynodelist ( mem [p + 1 ].hh .v.RH ) ;
      } 
      break ;
    case 4 : 
      {
	r = getnode ( 2 ) ;
	incr ( mem [mem [p + 1 ].hh .v.RH ].hh .v.LH ) ;
	words = 2 ;
      } 
      break ;
    case 5 : 
      {
	r = getnode ( 2 ) ;
	mem [r + 1 ].cint = copynodelist ( mem [p + 1 ].cint ) ;
      } 
      break ;
      default: 
      confusion ( 65646L ) ;
      break ;
    } 
    while ( words > 0 ) {
	
      decr ( words ) ;
      mem [r + words ]= mem [p + words ];
    } 
    mem [q ].hh .v.RH = r ;
    q = r ;
    p = mem [p ].hh .v.RH ;
  } 
  mem [q ].hh .v.RH = -268435455L ;
  q = mem [h ].hh .v.RH ;
  {
    mem [h ].hh .v.RH = avail ;
    avail = h ;
	;
#ifdef STAT
    decr ( dynused ) ;
#endif /* STAT */
  } 
  Result = q ;
  return Result ;
} 
void 
zprintmode ( integer m ) 
{
  printmode_regmem 
  if ( m > 0 ) 
  switch ( m / ( 104 ) ) 
  {case 0 : 
    print ( 65647L ) ;
    break ;
  case 1 : 
    print ( 65648L ) ;
    break ;
  case 2 : 
    print ( 65649L ) ;
    break ;
  } 
  else if ( m == 0 ) 
  print ( 65650L ) ;
  else switch ( ( - (integer) m ) / ( 104 ) ) 
  {case 0 : 
    print ( 65651L ) ;
    break ;
  case 1 : 
    print ( 65652L ) ;
    break ;
  case 2 : 
    print ( 65653L ) ;
    break ;
  } 
} 
void 
zprintinmode ( integer m ) 
{
  printinmode_regmem 
  if ( m > 0 ) 
  switch ( m / ( 104 ) ) 
  {case 0 : 
    print ( 65654L ) ;
    break ;
  case 1 : 
    print ( 65655L ) ;
    break ;
  case 2 : 
    print ( 65656L ) ;
    break ;
  } 
  else if ( m == 0 ) 
  print ( 65657L ) ;
  else switch ( ( - (integer) m ) / ( 104 ) ) 
  {case 0 : 
    print ( 65658L ) ;
    break ;
  case 1 : 
    print ( 65659L ) ;
    break ;
  case 2 : 
    print ( 65660L ) ;
    break ;
  } 
} 
void 
pushnest ( void ) 
{
  pushnest_regmem 
  if ( nestptr > maxneststack ) 
  {
    maxneststack = nestptr ;
    if ( nestptr == nestsize ) 
    overflow ( 65661L , nestsize ) ;
  } 
  nest [nestptr ]= curlist ;
  incr ( nestptr ) ;
  curlist .headfield = getavail () ;
  curlist .tailfield = curlist .headfield ;
  curlist .pgfield = 0 ;
  curlist .mlfield = line ;
  curlist .eTeXauxfield = -268435455L ;
} 
void 
popnest ( void ) 
{
  popnest_regmem 
  {
    mem [curlist .headfield ].hh .v.RH = avail ;
    avail = curlist .headfield ;
	;
#ifdef STAT
    decr ( dynused ) ;
#endif /* STAT */
  } 
  decr ( nestptr ) ;
  curlist = nest [nestptr ];
} 
void 
showactivities ( void ) 
{
  showactivities_regmem 
  integer p  ;
  short m  ;
  memoryword a  ;
  halfword q, r  ;
  integer t  ;
  nest [nestptr ]= curlist ;
  printnl ( 65545L ) ;
  println () ;
  {register integer for_end; p = nestptr ;for_end = 0 ; if ( p >= for_end) 
  do 
    {
      m = nest [p ].modefield ;
      a = nest [p ].auxfield ;
      printnl ( 65662L ) ;
      printmode ( m ) ;
      print ( 65663L ) ;
      printint ( abs ( nest [p ].mlfield ) ) ;
      if ( m == 105 ) {
	  
	if ( nest [p ].pgfield != 8585216L ) 
	{
	  print ( 65664L ) ;
	  printint ( nest [p ].pgfield % 65536L ) ;
	  print ( 65665L ) ;
	  printint ( nest [p ].pgfield / 4194304L ) ;
	  printchar ( 44 ) ;
	  printint ( ( nest [p ].pgfield / 65536L ) % 64 ) ;
	  printchar ( 41 ) ;
	} 
      } 
      if ( nest [p ].mlfield < 0 ) 
      print ( 65666L ) ;
      if ( p == 0 ) 
      {
	if ( memtop - 2 != pagetail ) 
	{
	  printnl ( 66417L ) ;
	  if ( outputactive ) 
	  print ( 66418L ) ;
	  showbox ( mem [memtop - 2 ].hh .v.RH ) ;
	  if ( pagecontents > 0 ) 
	  {
	    printnl ( 66419L ) ;
	    printtotals () ;
	    printnl ( 66420L ) ;
	    printscaled ( pagesofar [0 ]) ;
	    r = mem [memtop ].hh .v.RH ;
	    while ( r != memtop ) {
		
	      println () ;
	      printesc ( 65620L ) ;
	      t = mem [r ].hh.b1 ;
	      printint ( t ) ;
	      print ( 66421L ) ;
	      if ( eqtb [7892352L + t ].cint == 1000 ) 
	      t = mem [r + 3 ].cint ;
	      else t = xovern ( mem [r + 3 ].cint , 1000 ) * eqtb [7892352L 
	      + t ].cint ;
	      printscaled ( t ) ;
	      if ( mem [r ].hh.b0 == 1 ) 
	      {
		q = memtop - 2 ;
		t = 0 ;
		do {
		    q = mem [q ].hh .v.RH ;
		  if ( ( mem [q ].hh.b0 == 3 ) && ( mem [q ].hh.b1 == mem 
		  [r ].hh.b1 ) ) 
		  incr ( t ) ;
		} while ( ! ( q == mem [r + 1 ].hh .v.LH ) ) ;
		print ( 66422L ) ;
		printint ( t ) ;
		print ( 66423L ) ;
	      } 
	      r = mem [r ].hh .v.RH ;
	    } 
	  } 
	} 
	if ( mem [memtop - 1 ].hh .v.RH != -268435455L ) 
	printnl ( 65667L ) ;
      } 
      showbox ( mem [nest [p ].headfield ].hh .v.RH ) ;
      switch ( abs ( m ) / ( 104 ) ) 
      {case 0 : 
	{
	  printnl ( 65668L ) ;
	  if ( a .cint <= -65536000L ) 
	  print ( 65669L ) ;
	  else printscaled ( a .cint ) ;
	  if ( nest [p ].pgfield != 0 ) 
	  {
	    print ( 65670L ) ;
	    printint ( nest [p ].pgfield ) ;
	    if ( nest [p ].pgfield != 1 ) 
	    print ( 65671L ) ;
	    else print ( 65672L ) ;
	  } 
	} 
	break ;
      case 1 : 
	{
	  printnl ( 65673L ) ;
	  printint ( a .hh .v.LH ) ;
	  if ( m > 0 ) {
	      
	    if ( a .hh .v.RH > 0 ) 
	    {
	      print ( 65674L ) ;
	      printint ( a .hh .v.RH ) ;
	    } 
	  } 
	} 
	break ;
      case 2 : 
	if ( a .cint != -268435455L ) 
	{
	  print ( 65675L ) ;
	  showbox ( a .cint ) ;
	} 
	break ;
      } 
    } 
  while ( p-- > for_end ) ;} 
} 
void 
zprintparam ( integer n ) 
{
  printparam_regmem 
  switch ( n ) 
  {case 0 : 
    printesc ( 65721L ) ;
    break ;
  case 1 : 
    printesc ( 65722L ) ;
    break ;
  case 2 : 
    printesc ( 65723L ) ;
    break ;
  case 3 : 
    printesc ( 65724L ) ;
    break ;
  case 4 : 
    printesc ( 65725L ) ;
    break ;
  case 5 : 
    printesc ( 65726L ) ;
    break ;
  case 6 : 
    printesc ( 65727L ) ;
    break ;
  case 7 : 
    printesc ( 65728L ) ;
    break ;
  case 8 : 
    printesc ( 65729L ) ;
    break ;
  case 9 : 
    printesc ( 65730L ) ;
    break ;
  case 10 : 
    printesc ( 65731L ) ;
    break ;
  case 11 : 
    printesc ( 65732L ) ;
    break ;
  case 12 : 
    printesc ( 65733L ) ;
    break ;
  case 13 : 
    printesc ( 65734L ) ;
    break ;
  case 14 : 
    printesc ( 65735L ) ;
    break ;
  case 15 : 
    printesc ( 65736L ) ;
    break ;
  case 16 : 
    printesc ( 65737L ) ;
    break ;
  case 17 : 
    printesc ( 65738L ) ;
    break ;
  case 18 : 
    printesc ( 65739L ) ;
    break ;
  case 19 : 
    printesc ( 65740L ) ;
    break ;
  case 20 : 
    printesc ( 65741L ) ;
    break ;
  case 21 : 
    printesc ( 65742L ) ;
    break ;
  case 22 : 
    printesc ( 65743L ) ;
    break ;
  case 23 : 
    printesc ( 65744L ) ;
    break ;
  case 24 : 
    printesc ( 65745L ) ;
    break ;
  case 25 : 
    printesc ( 65746L ) ;
    break ;
  case 26 : 
    printesc ( 65747L ) ;
    break ;
  case 27 : 
    printesc ( 65748L ) ;
    break ;
  case 28 : 
    printesc ( 65749L ) ;
    break ;
  case 29 : 
    printesc ( 65750L ) ;
    break ;
  case 30 : 
    printesc ( 65751L ) ;
    break ;
  case 31 : 
    printesc ( 65752L ) ;
    break ;
  case 32 : 
    printesc ( 65753L ) ;
    break ;
  case 33 : 
    printesc ( 65754L ) ;
    break ;
  case 34 : 
    printesc ( 65755L ) ;
    break ;
  case 35 : 
    printesc ( 65756L ) ;
    break ;
  case 36 : 
    printesc ( 65757L ) ;
    break ;
  case 37 : 
    printesc ( 65758L ) ;
    break ;
  case 38 : 
    printesc ( 65759L ) ;
    break ;
  case 39 : 
    printesc ( 65760L ) ;
    break ;
  case 40 : 
    printesc ( 65761L ) ;
    break ;
  case 41 : 
    printesc ( 65762L ) ;
    break ;
  case 42 : 
    printesc ( 65763L ) ;
    break ;
  case 43 : 
    printesc ( 65764L ) ;
    break ;
  case 44 : 
    printesc ( 65765L ) ;
    break ;
  case 45 : 
    printesc ( 65766L ) ;
    break ;
  case 46 : 
    printesc ( 65767L ) ;
    break ;
  case 47 : 
    printesc ( 65768L ) ;
    break ;
  case 48 : 
    printesc ( 65769L ) ;
    break ;
  case 49 : 
    printesc ( 65770L ) ;
    break ;
  case 50 : 
    printesc ( 65771L ) ;
    break ;
  case 51 : 
    printesc ( 65772L ) ;
    break ;
  case 52 : 
    printesc ( 65773L ) ;
    break ;
  case 53 : 
    printesc ( 65774L ) ;
    break ;
  case 54 : 
    printesc ( 65775L ) ;
    break ;
  case 55 : 
    printesc ( 65776L ) ;
    break ;
  case 56 : 
    printesc ( 65777L ) ;
    break ;
  case 57 : 
    printesc ( 65778L ) ;
    break ;
  case 58 : 
    printesc ( 65779L ) ;
    break ;
  case 59 : 
    printesc ( 65780L ) ;
    break ;
  case 60 : 
    printesc ( 65781L ) ;
    break ;
  case 73 : 
    printesc ( 65782L ) ;
    break ;
  case 74 : 
    printesc ( 65783L ) ;
    break ;
  case 87 : 
    printesc ( 66978L ) ;
    break ;
  case 61 : 
    printesc ( 66863L ) ;
    break ;
  case 62 : 
    printesc ( 66864L ) ;
    break ;
  case 63 : 
    printesc ( 66865L ) ;
    break ;
  case 64 : 
    printesc ( 66866L ) ;
    break ;
  case 65 : 
    printesc ( 66867L ) ;
    break ;
  case 66 : 
    printesc ( 66868L ) ;
    break ;
  case 67 : 
    printesc ( 66869L ) ;
    break ;
  case 68 : 
    printesc ( 66870L ) ;
    break ;
  case 69 : 
    printesc ( 66871L ) ;
    break ;
  case 71 : 
    printesc ( 66872L ) ;
    break ;
  case 70 : 
    printesc ( 66911L ) ;
    break ;
  case 75 : 
    printesc ( 66912L ) ;
    break ;
  case 77 : 
    printesc ( 66913L ) ;
    break ;
  case 78 : 
    printesc ( 66914L ) ;
    break ;
  case 79 : 
    printesc ( 66915L ) ;
    break ;
  case 76 : 
    printesc ( 66916L ) ;
    break ;
  case 80 : 
    printesc ( 66917L ) ;
    break ;
  case 83 : 
    printesc ( 66918L ) ;
    break ;
  case 84 : 
    printesc ( 66919L ) ;
    break ;
  case 85 : 
    printesc ( 66920L ) ;
    break ;
  case 86 : 
    printesc ( 66921L ) ;
    break ;
    default: 
    print ( 65784L ) ;
    break ;
  } 
} 
void 
fixdateandtime ( void ) 
{
  fixdateandtime_regmem 
  dateandtime ( systime , sysday , sysmonth , sysyear ) ;
  eqtb [7892284L ].cint = systime ;
  eqtb [7892285L ].cint = sysday ;
  eqtb [7892286L ].cint = sysmonth ;
  eqtb [7892287L ].cint = sysyear ;
} 
void 
begindiagnostic ( void ) 
{
  begindiagnostic_regmem 
  oldsetting = selector ;
  if ( ( eqtb [7892293L ].cint <= 0 ) && ( selector == 19 ) ) 
  {
    decr ( selector ) ;
    if ( history == 0 ) 
    history = 1 ;
  } 
} 
void 
zenddiagnostic ( boolean blankline ) 
{
  enddiagnostic_regmem 
  printnl ( 65545L ) ;
  if ( blankline ) 
  println () ;
  selector = oldsetting ;
} 
void 
zprintlengthparam ( integer n ) 
{
  printlengthparam_regmem 
  switch ( n ) 
  {case 0 : 
    printesc ( 65788L ) ;
    break ;
  case 1 : 
    printesc ( 65789L ) ;
    break ;
  case 2 : 
    printesc ( 65790L ) ;
    break ;
  case 3 : 
    printesc ( 65791L ) ;
    break ;
  case 4 : 
    printesc ( 65792L ) ;
    break ;
  case 5 : 
    printesc ( 65793L ) ;
    break ;
  case 6 : 
    printesc ( 65794L ) ;
    break ;
  case 7 : 
    printesc ( 65795L ) ;
    break ;
  case 8 : 
    printesc ( 65796L ) ;
    break ;
  case 9 : 
    printesc ( 65797L ) ;
    break ;
  case 10 : 
    printesc ( 65798L ) ;
    break ;
  case 11 : 
    printesc ( 65799L ) ;
    break ;
  case 12 : 
    printesc ( 65800L ) ;
    break ;
  case 13 : 
    printesc ( 65801L ) ;
    break ;
  case 14 : 
    printesc ( 65802L ) ;
    break ;
  case 15 : 
    printesc ( 65803L ) ;
    break ;
  case 16 : 
    printesc ( 65804L ) ;
    break ;
  case 17 : 
    printesc ( 65805L ) ;
    break ;
  case 18 : 
    printesc ( 65806L ) ;
    break ;
  case 19 : 
    printesc ( 65807L ) ;
    break ;
  case 20 : 
    printesc ( 65808L ) ;
    break ;
  case 21 : 
    printesc ( 65809L ) ;
    break ;
  case 22 : 
    printesc ( 65810L ) ;
    break ;
    default: 
    print ( 65811L ) ;
    break ;
  } 
} 
void 
zprintcmdchr ( quarterword cmd , halfword chrcode ) 
{
  printcmdchr_regmem 
  integer n  ;
  strnumber fontnamestr  ;
  UTF16code quotechar  ;
  switch ( cmd ) 
  {case 1 : 
    {
      print ( 65885L ) ;
      if ( chrcode < 65536L ) 
      print ( chrcode ) ;
      else printchar ( chrcode ) ;
    } 
    break ;
  case 2 : 
    {
      print ( 65886L ) ;
      if ( chrcode < 65536L ) 
      print ( chrcode ) ;
      else printchar ( chrcode ) ;
    } 
    break ;
  case 3 : 
    {
      print ( 65887L ) ;
      if ( chrcode < 65536L ) 
      print ( chrcode ) ;
      else printchar ( chrcode ) ;
    } 
    break ;
  case 6 : 
    {
      print ( 65888L ) ;
      if ( chrcode < 65536L ) 
      print ( chrcode ) ;
      else printchar ( chrcode ) ;
    } 
    break ;
  case 7 : 
    {
      print ( 65889L ) ;
      if ( chrcode < 65536L ) 
      print ( chrcode ) ;
      else printchar ( chrcode ) ;
    } 
    break ;
  case 8 : 
    {
      print ( 65890L ) ;
      if ( chrcode < 65536L ) 
      print ( chrcode ) ;
      else printchar ( chrcode ) ;
    } 
    break ;
  case 9 : 
    print ( 65891L ) ;
    break ;
  case 10 : 
    {
      print ( 65892L ) ;
      if ( chrcode < 65536L ) 
      print ( chrcode ) ;
      else printchar ( chrcode ) ;
    } 
    break ;
  case 11 : 
    {
      print ( 65893L ) ;
      if ( chrcode < 65536L ) 
      print ( chrcode ) ;
      else printchar ( chrcode ) ;
    } 
    break ;
  case 12 : 
    {
      print ( 65894L ) ;
      if ( chrcode < 65536L ) 
      print ( chrcode ) ;
      else printchar ( chrcode ) ;
    } 
    break ;
  case 76 : 
  case 77 : 
    if ( chrcode < 1205783L ) 
    printskipparam ( chrcode - 1205764L ) ;
    else if ( chrcode < 1206039L ) 
    {
      printesc ( 65696L ) ;
      printint ( chrcode - 1205783L ) ;
    } 
    else {
	
      printesc ( 65697L ) ;
      printint ( chrcode - 1206039L ) ;
    } 
    break ;
  case 73 : 
    if ( chrcode >= 1206307L ) 
    {
      printesc ( 65708L ) ;
      printint ( chrcode - 1206307L ) ;
    } 
    else switch ( chrcode ) 
    {case 1206296 : 
      printesc ( 65699L ) ;
      break ;
    case 1206297 : 
      printesc ( 65700L ) ;
      break ;
    case 1206298 : 
      printesc ( 65701L ) ;
      break ;
    case 1206299 : 
      printesc ( 65702L ) ;
      break ;
    case 1206300 : 
      printesc ( 65703L ) ;
      break ;
    case 1206301 : 
      printesc ( 65704L ) ;
      break ;
    case 1206302 : 
      printesc ( 65705L ) ;
      break ;
    case 1206303 : 
      printesc ( 65706L ) ;
      break ;
    case 1206305 : 
      printesc ( 66862L ) ;
      break ;
    case 1206306 : 
      printesc ( 66760L ) ;
      break ;
      default: 
      printesc ( 65707L ) ;
      break ;
    } 
    break ;
  case 74 : 
    if ( chrcode < 7892352L ) 
    printparam ( chrcode - 7892264L ) ;
    else {
	
      printesc ( 65786L ) ;
      printint ( chrcode - 7892352L ) ;
    } 
    break ;
  case 75 : 
    if ( chrcode < 9006743L ) 
    printlengthparam ( chrcode - 9006720L ) ;
    else {
	
      printesc ( 65812L ) ;
      printint ( chrcode - 9006743L ) ;
    } 
    break ;
  case 45 : 
    printesc ( 65822L ) ;
    break ;
  case 92 : 
    printesc ( 65823L ) ;
    break ;
  case 40 : 
    printesc ( 65824L ) ;
    break ;
  case 41 : 
    printesc ( 65825L ) ;
    break ;
  case 78 : 
    printesc ( 65835L ) ;
    break ;
  case 61 : 
    printesc ( 65826L ) ;
    break ;
  case 42 : 
    printesc ( 65854L ) ;
    break ;
  case 16 : 
    printesc ( 65827L ) ;
    break ;
  case 110 : 
    printesc ( 65818L ) ;
    break ;
  case 90 : 
    printesc ( 65834L ) ;
    break ;
  case 15 : 
    if ( chrcode == 1 ) 
    printesc ( 65830L ) ;
    else printesc ( 65828L ) ;
    break ;
  case 94 : 
    printesc ( 65831L ) ;
    break ;
  case 67 : 
    printesc ( 65819L ) ;
    break ;
  case 62 : 
    printesc ( 65832L ) ;
    break ;
  case 64 : 
    printesc ( 32 ) ;
    break ;
  case 105 : 
    if ( chrcode == 0 ) 
    printesc ( 65833L ) ;
    else printesc ( 66165L ) ;
    break ;
  case 32 : 
    printesc ( 65836L ) ;
    break ;
  case 36 : 
    printesc ( 65837L ) ;
    break ;
  case 39 : 
    if ( chrcode == 0 ) 
    printesc ( 65838L ) ;
    else printesc ( 65815L ) ;
    break ;
  case 37 : 
    printesc ( 65620L ) ;
    break ;
  case 44 : 
    printesc ( 47 ) ;
    break ;
  case 18 : 
    {
      printesc ( 65642L ) ;
      if ( chrcode > 0 ) 
      printchar ( 115 ) ;
    } 
    break ;
  case 46 : 
    if ( chrcode == 1 ) 
    printesc ( 65841L ) ;
    else printesc ( 65839L ) ;
    break ;
  case 17 : 
    if ( chrcode == 2 ) 
    printesc ( 65846L ) ;
    else if ( chrcode == 1 ) 
    printesc ( 65844L ) ;
    else printesc ( 65842L ) ;
    break ;
  case 54 : 
    printesc ( 65847L ) ;
    break ;
  case 93 : 
    printesc ( 65848L ) ;
    break ;
  case 34 : 
    printesc ( 65849L ) ;
    break ;
  case 65 : 
    printesc ( 65850L ) ;
    break ;
  case 106 : 
    if ( chrcode == 0 ) 
    printesc ( 65851L ) ;
    else printesc ( 65815L ) ;
    break ;
  case 55 : 
    printesc ( 65625L ) ;
    break ;
  case 63 : 
    printesc ( 65852L ) ;
    break ;
  case 66 : 
    if ( chrcode == 1 ) 
    printesc ( 65858L ) ;
    else printesc ( 65856L ) ;
    break ;
  case 98 : 
    if ( chrcode == 0 ) 
    printesc ( 65859L ) ;
    else printesc ( 66936L ) ;
    break ;
  case 0 : 
    printesc ( 65860L ) ;
    break ;
  case 100 : 
    printesc ( 65861L ) ;
    break ;
  case 81 : 
    printesc ( 65855L ) ;
    break ;
  case 85 : 
    switch ( chrcode ) 
    {case 1206295 : 
      printesc ( 65853L ) ;
      break ;
    case 1206563 : 
      printesc ( 66971L ) ;
      break ;
    case 1206564 : 
      printesc ( 66972L ) ;
      break ;
    case 1206565 : 
      printesc ( 66973L ) ;
      break ;
    case 1206566 : 
      printesc ( 66974L ) ;
      break ;
    } 
    break ;
  case 112 : 
    if ( chrcode == 0 ) 
    printesc ( 65862L ) ;
    else if ( chrcode == 1 ) 
    printesc ( 66901L ) ;
    else printesc ( 66902L ) ;
    break ;
  case 72 : 
    {
      printesc ( 65708L ) ;
      if ( chrcode != membot ) 
      printsanum ( chrcode ) ;
    } 
    break ;
  case 38 : 
    printesc ( 65643L ) ;
    break ;
  case 33 : 
    if ( chrcode == 0 ) 
    printesc ( 65863L ) ;
    else switch ( chrcode ) 
    {case 6 : 
      printesc ( 66922L ) ;
      break ;
    case 7 : 
      printesc ( 66923L ) ;
      break ;
    case 10 : 
      printesc ( 66924L ) ;
      break ;
      default: 
      printesc ( 66925L ) ;
      break ;
    } 
    break ;
  case 56 : 
    printesc ( 65864L ) ;
    break ;
  case 35 : 
    printesc ( 65865L ) ;
    break ;
  case 103 : 
    printesc ( 65785L ) ;
    break ;
  case 13 : 
    printesc ( 65927L ) ;
    break ;
  case 107 : 
    if ( chrcode == 0 ) 
    printesc ( 65963L ) ;
    else if ( chrcode == 2 ) 
    printesc ( 66934L ) ;
    else printesc ( 65964L ) ;
    break ;
  case 113 : 
    {
      switch ( ( chrcode % 5 ) ) 
      {case 1 : 
	printesc ( 65966L ) ;
	break ;
      case 2 : 
	printesc ( 65967L ) ;
	break ;
      case 3 : 
	printesc ( 65968L ) ;
	break ;
      case 4 : 
	printesc ( 65969L ) ;
	break ;
	default: 
	printesc ( 65965L ) ;
	break ;
      } 
      if ( chrcode >= 5 ) 
      printchar ( 115 ) ;
    } 
    break ;
  case 91 : 
    {
      if ( ( chrcode < membot ) || ( chrcode > membot + 19 ) ) 
      cmd = ( mem [chrcode ].hh.b0 / 64 ) ;
      else {
	  
	cmd = chrcode - membot ;
	chrcode = -268435455L ;
      } 
      if ( cmd == 0 ) 
      printesc ( 65786L ) ;
      else if ( cmd == 1 ) 
      printesc ( 65812L ) ;
      else if ( cmd == 2 ) 
      printesc ( 65696L ) ;
      else printesc ( 65697L ) ;
      if ( chrcode != -268435455L ) 
      printsanum ( chrcode ) ;
    } 
    break ;
  case 80 : 
    if ( chrcode == 1 ) 
    printesc ( 66014L ) ;
    else printesc ( 66013L ) ;
    break ;
  case 83 : 
    if ( chrcode == 0 ) 
    printesc ( 66015L ) ;
    else if ( chrcode == 2 ) 
    printesc ( 66907L ) ;
    else printesc ( 66016L ) ;
    break ;
  case 84 : 
    if ( chrcode == 1 ) 
    printesc ( 66017L ) ;
    else if ( chrcode == 3 ) 
    printesc ( 66018L ) ;
    else printesc ( 66019L ) ;
    break ;
  case 71 : 
    switch ( chrcode ) 
    {case 0 : 
      printesc ( 66020L ) ;
      break ;
    case 1 : 
      printesc ( 66021L ) ;
      break ;
    case 2 : 
      printesc ( 66022L ) ;
      break ;
    case 4 : 
      printesc ( 66023L ) ;
      break ;
    case 3 : 
      printesc ( 66817L ) ;
      break ;
    case 19 : 
      printesc ( 66818L ) ;
      break ;
    case 27 : 
      printesc ( 66819L ) ;
      break ;
    case 28 : 
      printesc ( 66821L ) ;
      break ;
    case 29 : 
      printesc ( 66822L ) ;
      break ;
    case 30 : 
      printesc ( 66823L ) ;
      break ;
    case 31 : 
      printesc ( 66824L ) ;
      break ;
    case 32 : 
      printesc ( 66825L ) ;
      break ;
    case 33 : 
      printesc ( 66826L ) ;
      break ;
    case 34 : 
      printesc ( 66827L ) ;
      break ;
    case 35 : 
      printesc ( 66828L ) ;
      break ;
    case 36 : 
      printesc ( 66829L ) ;
      break ;
    case 37 : 
      printesc ( 66830L ) ;
      break ;
    case 38 : 
      printesc ( 66831L ) ;
      break ;
    case 39 : 
      printesc ( 66832L ) ;
      break ;
    case 40 : 
      printesc ( 66833L ) ;
      break ;
    case 41 : 
      printesc ( 66834L ) ;
      break ;
    case 42 : 
      printesc ( 66835L ) ;
      break ;
    case 43 : 
      printesc ( 66839L ) ;
      break ;
    case 44 : 
      printesc ( 66840L ) ;
      break ;
    case 45 : 
      printesc ( 66841L ) ;
      break ;
    case 46 : 
      printesc ( 66842L ) ;
      break ;
    case 47 : 
      printesc ( 66843L ) ;
      break ;
    case 48 : 
      printesc ( 66844L ) ;
      break ;
    case 49 : 
      printesc ( 66845L ) ;
      break ;
    case 50 : 
      printesc ( 66846L ) ;
      break ;
    case 55 : 
      printesc ( 66847L ) ;
      break ;
    case 51 : 
      printesc ( 66849L ) ;
      break ;
    case 52 : 
      printesc ( 66850L ) ;
      break ;
    case 53 : 
      printesc ( 66851L ) ;
      break ;
    case 54 : 
      printesc ( 66852L ) ;
      break ;
    case 20 : 
      printesc ( 66886L ) ;
      break ;
    case 21 : 
      printesc ( 66887L ) ;
      break ;
    case 22 : 
      printesc ( 66888L ) ;
      break ;
    case 23 : 
      printesc ( 66889L ) ;
      break ;
    case 24 : 
      printesc ( 66890L ) ;
      break ;
    case 56 : 
      printesc ( 66891L ) ;
      break ;
    case 57 : 
      printesc ( 66892L ) ;
      break ;
    case 58 : 
      printesc ( 66893L ) ;
      break ;
    case 59 : 
      printesc ( 66894L ) ;
      break ;
    case 60 : 
      printesc ( 66895L ) ;
      break ;
    case 61 : 
      printesc ( 66896L ) ;
      break ;
    case 62 : 
      printesc ( 66897L ) ;
      break ;
    case 67 : 
      printesc ( 66946L ) ;
      break ;
    case 68 : 
      printesc ( 66947L ) ;
      break ;
    case 69 : 
      printesc ( 66948L ) ;
      break ;
    case 70 : 
      printesc ( 66949L ) ;
      break ;
    case 25 : 
      printesc ( 66953L ) ;
      break ;
    case 26 : 
      printesc ( 66954L ) ;
      break ;
    case 63 : 
      printesc ( 66955L ) ;
      break ;
    case 64 : 
      printesc ( 66956L ) ;
      break ;
    case 65 : 
      printesc ( 66957L ) ;
      break ;
    case 66 : 
      printesc ( 66958L ) ;
      break ;
    case 12 : 
      printesc ( 66025L ) ;
      break ;
    case 13 : 
      printesc ( 66026L ) ;
      break ;
    case 16 : 
      printesc ( 66027L ) ;
      break ;
    case 17 : 
      printesc ( 66028L ) ;
      break ;
    case 18 : 
      printesc ( 66029L ) ;
      break ;
      default: 
      printesc ( 66024L ) ;
      break ;
    } 
    break ;
  case 111 : 
    switch ( chrcode ) 
    {case 0 : 
      printesc ( 66097L ) ;
      break ;
    case 1 : 
      printesc ( 66098L ) ;
      break ;
    case 2 : 
      printesc ( 66099L ) ;
      break ;
    case 3 : 
      printesc ( 66100L ) ;
      break ;
    case 4 : 
      printesc ( 66101L ) ;
      break ;
    case 5 : 
      printesc ( 66116L ) ;
      break ;
    case 6 : 
      printesc ( 66102L ) ;
      break ;
    case 16 : 
      printesc ( 66103L ) ;
      break ;
    case 17 : 
      printesc ( 66104L ) ;
      break ;
    case 22 : 
      printesc ( 66105L ) ;
      break ;
    case 23 : 
      printesc ( 66106L ) ;
      break ;
    case 24 : 
      printesc ( 66107L ) ;
      break ;
    case 25 : 
      printesc ( 66108L ) ;
      break ;
    case 26 : 
      printesc ( 66109L ) ;
      break ;
    case 18 : 
      printesc ( 66110L ) ;
      break ;
    case 29 : 
      printesc ( 66111L ) ;
      break ;
    case 30 : 
      printesc ( 66112L ) ;
      break ;
    case 33 : 
      printesc ( 66820L ) ;
      break ;
    case 34 : 
      printesc ( 66836L ) ;
      break ;
    case 35 : 
      printesc ( 66837L ) ;
      break ;
    case 36 : 
      printesc ( 66838L ) ;
      break ;
    case 37 : 
      printesc ( 66848L ) ;
      break ;
    case 38 : 
      printesc ( 66114L ) ;
      break ;
    case 39 : 
      printesc ( 66115L ) ;
      break ;
      default: 
      printesc ( 66113L ) ;
      break ;
    } 
    break ;
  case 108 : 
    {
      if ( chrcode >= 32 ) 
      printesc ( 66165L ) ;
      switch ( chrcode % 32 ) 
      {case 1 : 
	printesc ( 66148L ) ;
	break ;
      case 2 : 
	printesc ( 66149L ) ;
	break ;
      case 3 : 
	printesc ( 66150L ) ;
	break ;
      case 4 : 
	printesc ( 66151L ) ;
	break ;
      case 5 : 
	printesc ( 66152L ) ;
	break ;
      case 6 : 
	printesc ( 66153L ) ;
	break ;
      case 7 : 
	printesc ( 66154L ) ;
	break ;
      case 8 : 
	printesc ( 66155L ) ;
	break ;
      case 9 : 
	printesc ( 66156L ) ;
	break ;
      case 10 : 
	printesc ( 66157L ) ;
	break ;
      case 11 : 
	printesc ( 66158L ) ;
	break ;
      case 12 : 
	printesc ( 66159L ) ;
	break ;
      case 13 : 
	printesc ( 66160L ) ;
	break ;
      case 14 : 
	printesc ( 66161L ) ;
	break ;
      case 15 : 
	printesc ( 66162L ) ;
	break ;
      case 16 : 
	printesc ( 66163L ) ;
	break ;
      case 21 : 
	printesc ( 66164L ) ;
	break ;
      case 17 : 
	printesc ( 66937L ) ;
	break ;
      case 18 : 
	printesc ( 66938L ) ;
	break ;
      case 19 : 
	printesc ( 66939L ) ;
	break ;
      case 20 : 
	printesc ( 66940L ) ;
	break ;
	default: 
	printesc ( 66147L ) ;
	break ;
      } 
    } 
    break ;
  case 109 : 
    if ( chrcode == 2 ) 
    printesc ( 66166L ) ;
    else if ( chrcode == 4 ) 
    printesc ( 66167L ) ;
    else printesc ( 66168L ) ;
    break ;
  case 4 : 
    if ( chrcode == 1114113L ) 
    printesc ( 66327L ) ;
    else {
	
      print ( 66331L ) ;
      if ( chrcode < 65536L ) 
      print ( chrcode ) ;
      else printchar ( chrcode ) ;
    } 
    break ;
  case 5 : 
    if ( chrcode == 1114114L ) 
    printesc ( 66328L ) ;
    else printesc ( 66329L ) ;
    break ;
  case 82 : 
    switch ( chrcode ) 
    {case 0 : 
      printesc ( 66407L ) ;
      break ;
    case 1 : 
      printesc ( 66408L ) ;
      break ;
    case 2 : 
      printesc ( 66409L ) ;
      break ;
    case 3 : 
      printesc ( 66410L ) ;
      break ;
    case 4 : 
      printesc ( 66411L ) ;
      break ;
    case 5 : 
      printesc ( 66412L ) ;
      break ;
    case 6 : 
      printesc ( 66413L ) ;
      break ;
      default: 
      printesc ( 66414L ) ;
      break ;
    } 
    break ;
  case 14 : 
    if ( chrcode == 1 ) 
    printesc ( 66460L ) ;
    else printesc ( 65632L ) ;
    break ;
  case 26 : 
    switch ( chrcode ) 
    {case 4 : 
      printesc ( 66461L ) ;
      break ;
    case 0 : 
      printesc ( 66462L ) ;
      break ;
    case 1 : 
      printesc ( 66463L ) ;
      break ;
    case 2 : 
      printesc ( 66464L ) ;
      break ;
      default: 
      printesc ( 66465L ) ;
      break ;
    } 
    break ;
  case 27 : 
    switch ( chrcode ) 
    {case 4 : 
      printesc ( 66466L ) ;
      break ;
    case 0 : 
      printesc ( 66467L ) ;
      break ;
    case 1 : 
      printesc ( 66468L ) ;
      break ;
    case 2 : 
      printesc ( 66469L ) ;
      break ;
      default: 
      printesc ( 66470L ) ;
      break ;
    } 
    break ;
  case 28 : 
    printesc ( 65626L ) ;
    break ;
  case 29 : 
    printesc ( 65605L ) ;
    break ;
  case 30 : 
    printesc ( 65631L ) ;
    break ;
  case 21 : 
    if ( chrcode == 1 ) 
    printesc ( 66488L ) ;
    else printesc ( 66489L ) ;
    break ;
  case 22 : 
    if ( chrcode == 1 ) 
    printesc ( 66490L ) ;
    else printesc ( 66491L ) ;
    break ;
  case 20 : 
    switch ( chrcode ) 
    {case 0 : 
      printesc ( 65710L ) ;
      break ;
    case 1 : 
      printesc ( 66492L ) ;
      break ;
    case 2 : 
      printesc ( 66493L ) ;
      break ;
    case 3 : 
      printesc ( 66402L ) ;
      break ;
    case 4 : 
      printesc ( 66494L ) ;
      break ;
    case 5 : 
      printesc ( 66404L ) ;
      break ;
      default: 
      printesc ( 66495L ) ;
      break ;
    } 
    break ;
  case 31 : 
    if ( chrcode == 100 ) 
    printesc ( 66497L ) ;
    else if ( chrcode == 101 ) 
    printesc ( 66498L ) ;
    else if ( chrcode == 102 ) 
    printesc ( 66499L ) ;
    else printesc ( 66496L ) ;
    break ;
  case 43 : 
    if ( chrcode == 0 ) 
    printesc ( 66516L ) ;
    else printesc ( 66515L ) ;
    break ;
  case 25 : 
    if ( chrcode == 10 ) 
    printesc ( 66528L ) ;
    else if ( chrcode == 11 ) 
    printesc ( 66527L ) ;
    else printesc ( 66526L ) ;
    break ;
  case 23 : 
    if ( chrcode == 1 ) 
    printesc ( 66530L ) ;
    else printesc ( 66529L ) ;
    break ;
  case 24 : 
    if ( chrcode == 1 ) 
    printesc ( 66532L ) ;
    else if ( chrcode == 2 ) 
    printesc ( 66969L ) ;
    else if ( chrcode == 3 ) 
    printesc ( 66970L ) ;
    else printesc ( 66531L ) ;
    break ;
  case 47 : 
    if ( chrcode == 1 ) 
    printesc ( 45 ) ;
    else printesc ( 65640L ) ;
    break ;
  case 48 : 
    if ( chrcode == 1 ) 
    printesc ( 66564L ) ;
    else printesc ( 66563L ) ;
    break ;
  case 50 : 
    switch ( chrcode ) 
    {case 16 : 
      printesc ( 66277L ) ;
      break ;
    case 17 : 
      printesc ( 66278L ) ;
      break ;
    case 18 : 
      printesc ( 66279L ) ;
      break ;
    case 19 : 
      printesc ( 66280L ) ;
      break ;
    case 20 : 
      printesc ( 66281L ) ;
      break ;
    case 21 : 
      printesc ( 66282L ) ;
      break ;
    case 22 : 
      printesc ( 66283L ) ;
      break ;
    case 23 : 
      printesc ( 66284L ) ;
      break ;
    case 26 : 
      printesc ( 66286L ) ;
      break ;
      default: 
      printesc ( 66285L ) ;
      break ;
    } 
    break ;
  case 51 : 
    if ( chrcode == 1 ) 
    printesc ( 66290L ) ;
    else if ( chrcode == 2 ) 
    printesc ( 66291L ) ;
    else printesc ( 66565L ) ;
    break ;
  case 53 : 
    printstyle ( chrcode ) ;
    break ;
  case 52 : 
    switch ( chrcode ) 
    {case 1 : 
      printesc ( 66586L ) ;
      break ;
    case 2 : 
      printesc ( 66587L ) ;
      break ;
    case 3 : 
      printesc ( 66588L ) ;
      break ;
    case 4 : 
      printesc ( 66589L ) ;
      break ;
    case 5 : 
      printesc ( 66590L ) ;
      break ;
      default: 
      printesc ( 66585L ) ;
      break ;
    } 
    break ;
  case 49 : 
    if ( chrcode == 30 ) 
    printesc ( 66287L ) ;
    else if ( chrcode == 1 ) 
    printesc ( 66289L ) ;
    else printesc ( 66288L ) ;
    break ;
  case 95 : 
    if ( chrcode == 1 ) 
    printesc ( 66610L ) ;
    else if ( chrcode == 2 ) 
    printesc ( 66611L ) ;
    else if ( chrcode == 8 ) 
    printesc ( 66624L ) ;
    else printesc ( 66612L ) ;
    break ;
  case 99 : 
    if ( chrcode == 0 ) 
    printesc ( 66613L ) ;
    else if ( chrcode == 1 ) 
    printesc ( 66614L ) ;
    else if ( chrcode == 2 ) 
    printesc ( 66615L ) ;
    else printesc ( 66616L ) ;
    break ;
  case 96 : 
    if ( chrcode != 0 ) 
    printesc ( 66634L ) ;
    else printesc ( 66633L ) ;
    break ;
  case 97 : 
    switch ( chrcode ) 
    {case 0 : 
      printesc ( 66635L ) ;
      break ;
    case 1 : 
      printesc ( 66636L ) ;
      break ;
    case 9 : 
      printesc ( 66640L ) ;
      break ;
    case 8 : 
      printesc ( 66638L ) ;
      break ;
    case 2 : 
      printesc ( 66641L ) ;
      break ;
    case 3 : 
      printesc ( 66642L ) ;
      break ;
    case 4 : 
      printesc ( 66643L ) ;
      break ;
    case 5 : 
      printesc ( 66644L ) ;
      break ;
    case 7 : 
      printesc ( 66646L ) ;
      break ;
      default: 
      printesc ( 66645L ) ;
      break ;
    } 
    break ;
  case 68 : 
    {
      printesc ( 65827L ) ;
      printhex ( chrcode ) ;
    } 
    break ;
  case 69 : 
    {
      printesc ( 65842L ) ;
      printhex ( chrcode ) ;
    } 
    break ;
  case 70 : 
    {
      printesc ( 65846L ) ;
      printhex ( mathclassfield ( chrcode ) ) ;
      printhex ( mathfamfield ( chrcode ) ) ;
      printhex ( mathcharfield ( chrcode ) ) ;
    } 
    break ;
  case 86 : 
    if ( chrcode == 1207592L ) 
    printesc ( 65716L ) ;
    else if ( chrcode == 5664040L ) 
    printesc ( 65720L ) ;
    else if ( chrcode == 2321704L ) 
    printesc ( 65717L ) ;
    else if ( chrcode == 3435816L ) 
    printesc ( 65718L ) ;
    else if ( chrcode == 4549928L ) 
    printesc ( 65719L ) ;
    else printesc ( 65787L ) ;
    break ;
  case 87 : 
    if ( chrcode == 4549928L ) 
    printesc ( 66655L ) ;
    else if ( chrcode == 5664040L ) 
    printesc ( 66652L ) ;
    else if ( chrcode == 5664041L ) 
    printesc ( 66654L ) ;
    else if ( chrcode == 7892608L ) 
    printesc ( 66657L ) ;
    else printesc ( 66659L ) ;
    break ;
  case 88 : 
    printsize ( chrcode - 1206824L ) ;
    break ;
  case 101 : 
    if ( chrcode == 1 ) 
    printesc ( 66390L ) ;
    else printesc ( 66378L ) ;
    break ;
  case 79 : 
    switch ( chrcode ) 
    {case 0 : 
      printesc ( 66674L ) ;
      break ;
    case 1 : 
      printesc ( 66675L ) ;
      break ;
    case 2 : 
      printesc ( 66676L ) ;
      break ;
    case 3 : 
      printesc ( 66677L ) ;
      break ;
    } 
    break ;
  case 89 : 
    {
      print ( 66685L ) ;
      fontnamestr = fontname [chrcode ];
      if ( ( ( fontarea [chrcode ]== 65535L ) || ( fontarea [chrcode ]== 
      65534L ) ) ) 
      {
	quotechar = 34 ;
	{register integer for_end; n = 0 ;for_end = length ( fontnamestr ) - 
	1 ; if ( n <= for_end) do 
	  if ( strpool [strstart [( fontnamestr ) - 65536L ]+ n ]== 34 ) 
	  quotechar = 39 ;
	while ( n++ < for_end ) ;} 
	printchar ( quotechar ) ;
	print ( fontnamestr ) ;
	printchar ( quotechar ) ;
      } 
      else print ( fontnamestr ) ;
      if ( fontsize [chrcode ]!= fontdsize [chrcode ]) 
      {
	print ( 66131L ) ;
	printscaled ( fontsize [chrcode ]) ;
	print ( 65698L ) ;
      } 
    } 
    break ;
  case 102 : 
    switch ( chrcode ) 
    {case 0 : 
      printesc ( 65556L ) ;
      break ;
    case 1 : 
      printesc ( 65557L ) ;
      break ;
    case 2 : 
      printesc ( 65558L ) ;
      break ;
      default: 
      printesc ( 66686L ) ;
      break ;
    } 
    break ;
  case 60 : 
    if ( chrcode == 0 ) 
    printesc ( 66688L ) ;
    else printesc ( 66687L ) ;
    break ;
  case 58 : 
    if ( chrcode == 0 ) 
    printesc ( 66689L ) ;
    else printesc ( 66690L ) ;
    break ;
  case 57 : 
    if ( chrcode == 2321704L ) 
    printesc ( 66696L ) ;
    else printesc ( 66697L ) ;
    break ;
  case 19 : 
    switch ( chrcode ) 
    {case 1 : 
      printesc ( 66699L ) ;
      break ;
    case 2 : 
      printesc ( 66700L ) ;
      break ;
    case 3 : 
      printesc ( 66701L ) ;
      break ;
    case 4 : 
      printesc ( 66898L ) ;
      break ;
    case 5 : 
      printesc ( 66900L ) ;
      break ;
    case 6 : 
      printesc ( 66903L ) ;
      break ;
      default: 
      printesc ( 66698L ) ;
      break ;
    } 
    break ;
  case 104 : 
    print ( 66708L ) ;
    break ;
  case 114 : 
  case 115 : 
  case 116 : 
  case 117 : 
    {
      n = cmd - 114 ;
      if ( mem [mem [chrcode ].hh .v.RH ].hh .v.LH == 29360129L ) 
      n = n + 4 ;
      if ( odd ( n / 4 ) ) 
      printesc ( 66624L ) ;
      if ( odd ( n ) ) 
      printesc ( 66610L ) ;
      if ( odd ( n / 2 ) ) 
      printesc ( 66611L ) ;
      if ( n > 0 ) 
      printchar ( 32 ) ;
      print ( 66709L ) ;
    } 
    break ;
  case 118 : 
    printesc ( 66710L ) ;
    break ;
  case 59 : 
    switch ( chrcode ) 
    {case 0 : 
      printesc ( 66749L ) ;
      break ;
    case 1 : 
      printesc ( 65923L ) ;
      break ;
    case 2 : 
      printesc ( 66750L ) ;
      break ;
    case 3 : 
      printesc ( 66751L ) ;
      break ;
    case 5 : 
      printesc ( 66752L ) ;
      break ;
    case 6 : 
      printesc ( 66753L ) ;
      break ;
    case 23 : 
      printesc ( 66761L ) ;
      break ;
    case 33 : 
      printesc ( 66754L ) ;
      break ;
    case 35 : 
      printesc ( 66755L ) ;
      break ;
    case 41 : 
      printesc ( 66756L ) ;
      break ;
    case 42 : 
      printesc ( 66757L ) ;
      break ;
    case 43 : 
      printesc ( 66758L ) ;
      break ;
    case 46 : 
      printesc ( 66759L ) ;
      break ;
    case 44 : 
      printesc ( 66762L ) ;
      break ;
    case 45 : 
      printesc ( 66763L ) ;
      break ;
      default: 
      print ( 66764L ) ;
      break ;
    } 
    break ;
    default: 
    print ( 65895L ) ;
    break ;
  } 
} 
void 
znotaatfonterror ( integer cmd , integer c , integer f ) 
{
  notaatfonterror_regmem 
  {
    if ( interaction == 3 ) 
    ;
    if ( filelineerrorstylep ) 
    printfileline () ;
    else printnl ( 65544L ) ;
    print ( 66853L ) ;
  } 
  printcmdchr ( cmd , c ) ;
  print ( 66854L ) ;
  print ( fontname [f ]) ;
  print ( 66855L ) ;
  error () ;
} 
void 
znotaatgrfonterror ( integer cmd , integer c , integer f ) 
{
  notaatgrfonterror_regmem 
  {
    if ( interaction == 3 ) 
    ;
    if ( filelineerrorstylep ) 
    printfileline () ;
    else printnl ( 65544L ) ;
    print ( 66853L ) ;
  } 
  printcmdchr ( cmd , c ) ;
  print ( 66854L ) ;
  print ( fontname [f ]) ;
  print ( 66856L ) ;
  error () ;
} 
void 
znototfonterror ( integer cmd , integer c , integer f ) 
{
  nototfonterror_regmem 
  {
    if ( interaction == 3 ) 
    ;
    if ( filelineerrorstylep ) 
    printfileline () ;
    else printnl ( 65544L ) ;
    print ( 66853L ) ;
  } 
  printcmdchr ( cmd , c ) ;
  print ( 66854L ) ;
  print ( fontname [f ]) ;
  print ( 66857L ) ;
  error () ;
} 
void 
znotnativefonterror ( integer cmd , integer c , integer f ) 
{
  notnativefonterror_regmem 
  {
    if ( interaction == 3 ) 
    ;
    if ( filelineerrorstylep ) 
    printfileline () ;
    else printnl ( 65544L ) ;
    print ( 66853L ) ;
  } 
  printcmdchr ( cmd , c ) ;
  print ( 66854L ) ;
  print ( fontname [f ]) ;
  print ( 66858L ) ;
  error () ;
} 
#ifdef STAT
void 
zshoweqtb ( halfword n ) 
{
  showeqtb_regmem 
  if ( n < 1 ) 
  printchar ( 63 ) ;
  else if ( ( n < 1205764L ) || ( ( n > 9006998L ) && ( n <= eqtbtop ) ) ) 
  {
    sprintcs ( n ) ;
    printchar ( 61 ) ;
    printcmdchr ( eqtb [n ].hh.b0 , eqtb [n ].hh .v.RH ) ;
    if ( eqtb [n ].hh.b0 >= 114 ) 
    {
      printchar ( 58 ) ;
      showtokenlist ( mem [eqtb [n ].hh .v.RH ].hh .v.RH , -268435455L , 
      32 ) ;
    } 
  } 
  else if ( n < 1206295L ) {
      
    if ( n < 1205783L ) 
    {
      printskipparam ( n - 1205764L ) ;
      printchar ( 61 ) ;
      if ( n < 1205780L ) 
      printspec ( eqtb [n ].hh .v.RH , 65698L ) ;
      else printspec ( eqtb [n ].hh .v.RH , 65627L ) ;
    } 
    else if ( n < 1206039L ) 
    {
      printesc ( 65696L ) ;
      printint ( n - 1205783L ) ;
      printchar ( 61 ) ;
      printspec ( eqtb [n ].hh .v.RH , 65698L ) ;
    } 
    else {
	
      printesc ( 65697L ) ;
      printint ( n - 1206039L ) ;
      printchar ( 61 ) ;
      printspec ( eqtb [n ].hh .v.RH , 65627L ) ;
    } 
  } 
  else if ( n < 7892264L ) {
      
    if ( ( n == 1206295L ) || ( ( n >= 1206563L ) && ( n < 1206567L ) ) ) 
    {
      printcmdchr ( 85 , n ) ;
      printchar ( 61 ) ;
      if ( eqtb [n ].hh .v.RH == -268435455L ) 
      printchar ( 48 ) ;
      else if ( n > 1206295L ) 
      {
	printint ( mem [eqtb [n ].hh .v.RH + 1 ].cint ) ;
	printchar ( 32 ) ;
	printint ( mem [eqtb [n ].hh .v.RH + 2 ].cint ) ;
	if ( mem [eqtb [n ].hh .v.RH + 1 ].cint > 1 ) 
	printesc ( 65709L ) ;
      } 
      else printint ( mem [eqtb [1206295L ].hh .v.RH ].hh .v.LH ) ;
    } 
    else if ( n < 1206307L ) 
    {
      printcmdchr ( 73 , n ) ;
      printchar ( 61 ) ;
      if ( eqtb [n ].hh .v.RH != -268435455L ) 
      showtokenlist ( mem [eqtb [n ].hh .v.RH ].hh .v.RH , -268435455L , 
      32 ) ;
    } 
    else if ( n < 1206567L ) 
    {
      printesc ( 65708L ) ;
      printint ( n - 1206307L ) ;
      printchar ( 61 ) ;
      if ( eqtb [n ].hh .v.RH != -268435455L ) 
      showtokenlist ( mem [eqtb [n ].hh .v.RH ].hh .v.RH , -268435455L , 
      32 ) ;
    } 
    else if ( n < 1206823L ) 
    {
      printesc ( 65710L ) ;
      printint ( n - 1206567L ) ;
      printchar ( 61 ) ;
      if ( eqtb [n ].hh .v.RH == -268435455L ) 
      print ( 65711L ) ;
      else {
	  
	depththreshold = 0 ;
	breadthmax = 1 ;
	shownodelist ( eqtb [n ].hh .v.RH ) ;
      } 
    } 
    else if ( n < 1207592L ) 
    {
      if ( n == 1206823L ) 
      print ( 65712L ) ;
      else if ( n < 1207080L ) 
      {
	printesc ( 65713L ) ;
	printint ( n - 1206824L ) ;
      } 
      else if ( n < 1207336L ) 
      {
	printesc ( 65714L ) ;
	printint ( n - 1207080L ) ;
      } 
      else {
	  
	printesc ( 65715L ) ;
	printint ( n - 1207336L ) ;
      } 
      printchar ( 61 ) ;
      printesc ( hash [1196762L + eqtb [n ].hh .v.RH ].v.RH ) ;
    } 
    else if ( n < 5664040L ) 
    {
      if ( n < 2321704L ) 
      {
	printesc ( 65716L ) ;
	printint ( n - 1207592L ) ;
      } 
      else if ( n < 3435816L ) 
      {
	printesc ( 65717L ) ;
	printint ( n - 2321704L ) ;
      } 
      else if ( n < 4549928L ) 
      {
	printesc ( 65718L ) ;
	printint ( n - 3435816L ) ;
      } 
      else {
	  
	printesc ( 65719L ) ;
	printint ( n - 4549928L ) ;
      } 
      printchar ( 61 ) ;
      printint ( eqtb [n ].hh .v.RH ) ;
    } 
    else {
	
      printesc ( 65720L ) ;
      printint ( n - 5664040L ) ;
      printchar ( 61 ) ;
      printint ( eqtb [n ].hh .v.RH ) ;
    } 
  } 
  else if ( n < 9006720L ) 
  {
    if ( n < 7892352L ) 
    printparam ( n - 7892264L ) ;
    else if ( n < 7892608L ) 
    {
      printesc ( 65786L ) ;
      printint ( n - 7892352L ) ;
    } 
    else {
	
      printesc ( 65787L ) ;
      printint ( n - 7892608L ) ;
    } 
    printchar ( 61 ) ;
    printint ( eqtb [n ].cint ) ;
  } 
  else if ( n <= 9006998L ) 
  {
    if ( n < 9006743L ) 
    printlengthparam ( n - 9006720L ) ;
    else {
	
      printesc ( 65812L ) ;
      printint ( n - 9006743L ) ;
    } 
    printchar ( 61 ) ;
    printscaled ( eqtb [n ].cint ) ;
    print ( 65698L ) ;
  } 
  else printchar ( 63 ) ;
} 
#endif /* STAT */
halfword 
zidlookup ( integer j , integer l ) 
{
  /* 40 */ register halfword Result; idlookup_regmem 
  integer h  ;
  integer d  ;
  halfword p  ;
  halfword k  ;
  integer ll  ;
  h = 0 ;
  {register integer for_end; k = j ;for_end = j + l - 1 ; if ( k <= for_end) 
  do 
    {
      h = h + h + buffer [k ];
      while ( h >= 8501 ) h = h - 8501 ;
    } 
  while ( k++ < for_end ) ;} 
  p = h + 1179650L ;
  ll = l ;
  {register integer for_end; d = 0 ;for_end = l - 1 ; if ( d <= for_end) do 
    if ( buffer [j + d ]>= 65536L ) 
    incr ( ll ) ;
  while ( d++ < for_end ) ;} 
  while ( true ) {
      
    if ( hash [p ].v.RH > 0 ) {
	
      if ( length ( hash [p ].v.RH ) == ll ) {
	  
	if ( streqbuf ( hash [p ].v.RH , j ) ) 
	goto lab40 ;
      } 
    } 
    if ( hash [p ].v.LH == 0 ) 
    {
      if ( nonewcontrolsequence ) 
      p = 1205763L ;
      else {
	  
	if ( hash [p ].v.RH > 0 ) 
	{
	  if ( hashhigh < hashextra ) 
	  {
	    incr ( hashhigh ) ;
	    hash [p ].v.LH = hashhigh + 9006998L ;
	    p = hashhigh + 9006998L ;
	  } 
	  else {
	      
	    do {
		if ( ( hashused == 1179650L ) ) 
	      overflow ( 65816L , 15000 + hashextra ) ;
	      decr ( hashused ) ;
	    } while ( ! ( hash [hashused ].v.RH == 0 ) ) ;
	    hash [p ].v.LH = hashused ;
	    p = hashused ;
	  } 
	} 
	{
	  if ( poolptr + ll > poolsize ) 
	  overflow ( 65539L , poolsize - initpoolptr ) ;
	} 
	d = ( poolptr - strstart [( strptr ) - 65536L ]) ;
	while ( poolptr > strstart [( strptr ) - 65536L ]) {
	    
	  decr ( poolptr ) ;
	  strpool [poolptr + l ]= strpool [poolptr ];
	} 
	{register integer for_end; k = j ;for_end = j + l - 1 ; if ( k <= 
	for_end) do 
	  {
	    if ( buffer [k ]< 65536L ) 
	    {
	      if ( ( buffer [k ]> 65535L ) ) 
	      {
		strpool [poolptr ]= ( buffer [k ]- 65536L ) / 1024 + 
		55296L ;
		incr ( poolptr ) ;
		strpool [poolptr ]= ( buffer [k ]) % 1024 + 56320L ;
		incr ( poolptr ) ;
	      } 
	      else {
		  
		strpool [poolptr ]= buffer [k ];
		incr ( poolptr ) ;
	      } 
	    } 
	    else {
		
	      {
		if ( ( 55296L + ( buffer [k ]- 65536L ) / 1024 > 65535L ) ) 
		{
		  strpool [poolptr ]= ( 55296L + ( buffer [k ]- 65536L ) / 
		  1024 - 65536L ) / 1024 + 55296L ;
		  incr ( poolptr ) ;
		  strpool [poolptr ]= ( 55296L + ( buffer [k ]- 65536L ) / 
		  1024 ) % 1024 + 56320L ;
		  incr ( poolptr ) ;
		} 
		else {
		    
		  strpool [poolptr ]= 55296L + ( buffer [k ]- 65536L ) / 
		  1024 ;
		  incr ( poolptr ) ;
		} 
	      } 
	      {
		if ( ( 56320L + ( buffer [k ]- 65536L ) % 1024 > 65535L ) ) 
		{
		  strpool [poolptr ]= ( 56320L + ( buffer [k ]- 65536L ) % 
		  1024 - 65536L ) / 1024 + 55296L ;
		  incr ( poolptr ) ;
		  strpool [poolptr ]= ( 56320L + ( buffer [k ]- 65536L ) % 
		  1024 ) % 1024 + 56320L ;
		  incr ( poolptr ) ;
		} 
		else {
		    
		  strpool [poolptr ]= 56320L + ( buffer [k ]- 65536L ) % 
		  1024 ;
		  incr ( poolptr ) ;
		} 
	      } 
	    } 
	  } 
	while ( k++ < for_end ) ;} 
	hash [p ].v.RH = makestring () ;
	poolptr = poolptr + d ;
	;
#ifdef STAT
	incr ( cscount ) ;
#endif /* STAT */
      } 
      goto lab40 ;
    } 
    p = hash [p ].v.LH ;
  } 
  lab40: Result = p ;
  return Result ;
} 
halfword 
zprimlookup ( strnumber s ) 
{
  /* 40 */ register halfword Result; primlookup_regmem 
  integer h  ;
  halfword p  ;
  halfword k  ;
  integer j, l  ;
  if ( s <= 65535L ) 
  {
    if ( s < 0 ) 
    {
      p = 0 ;
      goto lab40 ;
    } 
    else p = ( s % 1777 ) + 1 ;
  } 
  else {
      
    j = strstart [( s ) - 65536L ];
    if ( s == strptr ) 
    l = ( poolptr - strstart [( strptr ) - 65536L ]) ;
    else l = length ( s ) ;
    h = strpool [j ];
    {register integer for_end; k = j + 1 ;for_end = j + l - 1 ; if ( k <= 
    for_end) do 
      {
	h = h + h + strpool [k ];
	while ( h >= 1777 ) h = h - 1777 ;
      } 
    while ( k++ < for_end ) ;} 
    p = h + 1 ;
  } 
  while ( true ) {
      
    if ( prim [p ].v.RH > 65536L ) 
    {
      if ( length ( prim [p ].v.RH - 1 ) == l ) {
	  
	if ( streqstr ( prim [p ].v.RH - 1 , s ) ) 
	goto lab40 ;
      } 
    } 
    else if ( prim [p ].v.RH == 1 + s ) 
    goto lab40 ;
    if ( prim [p ].v.LH == 0 ) 
    {
      if ( nonewcontrolsequence ) 
      p = 0 ;
      else {
	  
	if ( prim [p ].v.RH > 0 ) 
	{
	  do {
	      if ( ( primused == 1 ) ) 
	    overflow ( 65817L , 2100 ) ;
	    decr ( primused ) ;
	  } while ( ! ( prim [primused ].v.RH == 0 ) ) ;
	  prim [p ].v.LH = primused ;
	  p = primused ;
	} 
	prim [p ].v.RH = s + 1 ;
      } 
      goto lab40 ;
    } 
    p = prim [p ].v.LH ;
  } 
  lab40: Result = p ;
  return Result ;
} 
#ifdef STAT
void 
zrestoretrace ( halfword p , strnumber s ) 
{
  restoretrace_regmem 
  begindiagnostic () ;
  printchar ( 123 ) ;
  print ( s ) ;
  printchar ( 32 ) ;
  showeqtb ( p ) ;
  printchar ( 125 ) ;
  enddiagnostic ( false ) ;
} 
#endif /* STAT */
void 
zprintgroup ( boolean e ) 
{
  /* 10 */ printgroup_regmem 
  switch ( curgroup ) 
  {case 0 : 
    {
      print ( 66873L ) ;
      return ;
    } 
    break ;
  case 1 : 
  case 14 : 
    {
      if ( curgroup == 14 ) 
      print ( 66874L ) ;
      print ( 66875L ) ;
    } 
    break ;
  case 2 : 
  case 3 : 
    {
      if ( curgroup == 3 ) 
      print ( 66876L ) ;
      print ( 66495L ) ;
    } 
    break ;
  case 4 : 
    print ( 66404L ) ;
    break ;
  case 5 : 
    print ( 66494L ) ;
    break ;
  case 6 : 
  case 7 : 
    {
      if ( curgroup == 7 ) 
      print ( 66877L ) ;
      print ( 66878L ) ;
    } 
    break ;
  case 8 : 
    print ( 65699L ) ;
    break ;
  case 10 : 
    print ( 66879L ) ;
    break ;
  case 11 : 
    print ( 65620L ) ;
    break ;
  case 12 : 
    print ( 65864L ) ;
    break ;
  case 9 : 
  case 13 : 
  case 15 : 
  case 16 : 
    {
      print ( 65634L ) ;
      if ( curgroup == 13 ) 
      print ( 66880L ) ;
      else if ( curgroup == 15 ) 
      print ( 66881L ) ;
      else if ( curgroup == 16 ) 
      print ( 66882L ) ;
    } 
    break ;
  } 
  print ( 66883L ) ;
  printint ( curlevel ) ;
  printchar ( 41 ) ;
  if ( savestack [saveptr - 1 ].cint != 0 ) 
  {
    if ( e ) 
    print ( 65663L ) ;
    else print ( 66311L ) ;
    printint ( savestack [saveptr - 1 ].cint ) ;
  } 
} 
#ifdef STAT
void 
zgrouptrace ( boolean e ) 
{
  grouptrace_regmem 
  begindiagnostic () ;
  printchar ( 123 ) ;
  if ( e ) 
  print ( 66884L ) ;
  else print ( 66885L ) ;
  printgroup ( e ) ;
  printchar ( 125 ) ;
  enddiagnostic ( false ) ;
} 
#endif /* STAT */
boolean 
pseudoinput ( void ) 
{
  register boolean Result; pseudoinput_regmem 
  halfword p  ;
  integer sz  ;
  fourquarters w  ;
  halfword r  ;
  last = first ;
  p = mem [pseudofiles ].hh .v.LH ;
  if ( p == -268435455L ) 
  Result = false ;
  else {
      
    mem [pseudofiles ].hh .v.LH = mem [p ].hh .v.RH ;
    sz = mem [p ].hh .v.LH ;
    if ( 4 * sz - 3 >= bufsize - last ) 
    {
      curinput .locfield = first ;
      curinput .limitfield = last - 1 ;
      overflow ( 65538L , bufsize ) ;
    } 
    last = first ;
    {register integer for_end; r = p + 1 ;for_end = p + sz - 1 ; if ( r <= 
    for_end) do 
      {
	w = mem [r ].qqqq ;
	buffer [last ]= w .b0 ;
	buffer [last + 1 ]= w .b1 ;
	buffer [last + 2 ]= w .b2 ;
	buffer [last + 3 ]= w .b3 ;
	last = last + 4 ;
      } 
    while ( r++ < for_end ) ;} 
    if ( last >= maxbufstack ) 
    maxbufstack = last + 1 ;
    while ( ( last > first ) && ( buffer [last - 1 ]== 32 ) ) decr ( last ) 
    ;
    freenode ( p , sz ) ;
    Result = true ;
  } 
  return Result ;
} 
void 
pseudoclose ( void ) 
{
  pseudoclose_regmem 
  halfword p, q  ;
  p = mem [pseudofiles ].hh .v.RH ;
  q = mem [pseudofiles ].hh .v.LH ;
  {
    mem [pseudofiles ].hh .v.RH = avail ;
    avail = pseudofiles ;
	;
#ifdef STAT
    decr ( dynused ) ;
#endif /* STAT */
  } 
  pseudofiles = p ;
  while ( q != -268435455L ) {
      
    p = q ;
    q = mem [p ].hh .v.RH ;
    freenode ( p , mem [p ].hh .v.LH ) ;
  } 
} 
void 
groupwarning ( void ) 
{
  groupwarning_regmem 
  integer i  ;
  boolean w  ;
  baseptr = inputptr ;
  inputstack [baseptr ]= curinput ;
  i = inopen ;
  w = false ;
  while ( ( grpstack [i ]== curboundary ) && ( i > 0 ) ) {
      
    if ( eqtb [7892329L ].cint > 0 ) 
    {
      while ( ( inputstack [baseptr ].statefield == 0 ) || ( inputstack [
      baseptr ].indexfield > i ) ) decr ( baseptr ) ;
      if ( inputstack [baseptr ].namefield > 17 ) 
      w = true ;
    } 
    grpstack [i ]= savestack [saveptr ].hh .v.RH ;
    decr ( i ) ;
  } 
  if ( w ) 
  {
    printnl ( 66942L ) ;
    printgroup ( true ) ;
    print ( 66943L ) ;
    println () ;
    if ( eqtb [7892329L ].cint > 1 ) 
    showcontext () ;
    if ( history == 0 ) 
    history = 1 ;
  } 
} 
void 
ifwarning ( void ) 
{
  ifwarning_regmem 
  integer i  ;
  boolean w  ;
  baseptr = inputptr ;
  inputstack [baseptr ]= curinput ;
  i = inopen ;
  w = false ;
  while ( ifstack [i ]== condptr ) {
      
    if ( eqtb [7892329L ].cint > 0 ) 
    {
      while ( ( inputstack [baseptr ].statefield == 0 ) || ( inputstack [
      baseptr ].indexfield > i ) ) decr ( baseptr ) ;
      if ( inputstack [baseptr ].namefield > 17 ) 
      w = true ;
    } 
    ifstack [i ]= mem [condptr ].hh .v.RH ;
    decr ( i ) ;
  } 
  if ( w ) 
  {
    printnl ( 66942L ) ;
    printcmdchr ( 108 , curif ) ;
    if ( ifline != 0 ) 
    {
      print ( 66904L ) ;
      printint ( ifline ) ;
    } 
    print ( 66943L ) ;
    println () ;
    if ( eqtb [7892329L ].cint > 1 ) 
    showcontext () ;
    if ( history == 0 ) 
    history = 1 ;
  } 
} 
void 
filewarning ( void ) 
{
  filewarning_regmem 
  halfword p  ;
  quarterword l  ;
  quarterword c  ;
  integer i  ;
  p = saveptr ;
  l = curlevel ;
  c = curgroup ;
  saveptr = curboundary ;
  while ( grpstack [inopen ]!= saveptr ) {
      
    decr ( curlevel ) ;
    printnl ( 66944L ) ;
    printgroup ( true ) ;
    print ( 66945L ) ;
    curgroup = savestack [saveptr ].hh.b1 ;
    saveptr = savestack [saveptr ].hh .v.RH ;
  } 
  saveptr = p ;
  curlevel = l ;
  curgroup = c ;
  p = condptr ;
  l = iflimit ;
  c = curif ;
  i = ifline ;
  while ( ifstack [inopen ]!= condptr ) {
      
    printnl ( 66944L ) ;
    printcmdchr ( 108 , curif ) ;
    if ( iflimit == 2 ) 
    printesc ( 66168L ) ;
    if ( ifline != 0 ) 
    {
      print ( 66904L ) ;
      printint ( ifline ) ;
    } 
    print ( 66945L ) ;
    ifline = mem [condptr + 1 ].cint ;
    curif = mem [condptr ].hh.b1 ;
    iflimit = mem [condptr ].hh.b0 ;
    condptr = mem [condptr ].hh .v.RH ;
  } 
  condptr = p ;
  iflimit = l ;
  curif = c ;
  ifline = i ;
  println () ;
  if ( eqtb [7892329L ].cint > 1 ) 
  showcontext () ;
  if ( history == 0 ) 
  history = 1 ;
} 
void 
zdeletesaref ( halfword q ) 
{
  /* 10 */ deletesaref_regmem 
  halfword p  ;
  smallnumber i  ;
  smallnumber s  ;
  decr ( mem [q + 1 ].hh .v.LH ) ;
  if ( mem [q + 1 ].hh .v.LH != -268435455L ) 
  return ;
  if ( mem [q ].hh.b0 < 128 ) {
      
    if ( mem [q + 2 ].cint == 0 ) 
    s = 3 ;
    else return ;
  } 
  else {
      
    if ( mem [q ].hh.b0 < 256 ) {
	
      if ( mem [q + 1 ].hh .v.RH == membot ) 
      deleteglueref ( membot ) ;
      else return ;
    } 
    else if ( mem [q + 1 ].hh .v.RH != -268435455L ) 
    return ;
    s = 2 ;
  } 
  do {
      i = mem [q ].hh.b0 % 64 ;
    p = q ;
    q = mem [p ].hh .v.RH ;
    freenode ( p , s ) ;
    if ( q == -268435455L ) 
    {
      saroot [i ]= -268435455L ;
      return ;
    } 
    {
      if ( odd ( i ) ) 
      mem [q + ( i / 2 ) + 1 ].hh .v.RH = -268435455L ;
      else mem [q + ( i / 2 ) + 1 ].hh .v.LH = -268435455L ;
      decr ( mem [q ].hh.b1 ) ;
    } 
    s = 33 ;
  } while ( ! ( mem [q ].hh.b1 > 0 ) ) ;
} 
#ifdef STAT
void 
zshowsa ( halfword p , strnumber s ) 
{
  showsa_regmem 
  smallnumber t  ;
  begindiagnostic () ;
  printchar ( 123 ) ;
  print ( s ) ;
  printchar ( 32 ) ;
  if ( p == -268435455L ) 
  printchar ( 63 ) ;
  else {
      
    t = ( mem [p ].hh.b0 / 64 ) ;
    if ( t < 4 ) 
    printcmdchr ( 91 , p ) ;
    else if ( t == 4 ) 
    {
      printesc ( 65710L ) ;
      printsanum ( p ) ;
    } 
    else if ( t == 5 ) 
    printcmdchr ( 72 , p ) ;
    else printchar ( 63 ) ;
    printchar ( 61 ) ;
    if ( t == 0 ) 
    printint ( mem [p + 2 ].cint ) ;
    else if ( t == 1 ) 
    {
      printscaled ( mem [p + 2 ].cint ) ;
      print ( 65698L ) ;
    } 
    else {
	
      p = mem [p + 1 ].hh .v.RH ;
      if ( t == 2 ) 
      printspec ( p , 65698L ) ;
      else if ( t == 3 ) 
      printspec ( p , 65627L ) ;
      else if ( t == 4 ) {
	  
	if ( p == -268435455L ) 
	print ( 65711L ) ;
	else {
	    
	  depththreshold = 0 ;
	  breadthmax = 1 ;
	  shownodelist ( p ) ;
	} 
      } 
      else if ( t == 5 ) 
      {
	if ( p != -268435455L ) 
	showtokenlist ( mem [p ].hh .v.RH , -268435455L , 32 ) ;
      } 
      else printchar ( 63 ) ;
    } 
  } 
  printchar ( 125 ) ;
  enddiagnostic ( false ) ;
} 
#endif /* STAT */
void 
zsasave ( halfword p ) 
{
  sasave_regmem 
  halfword q  ;
  quarterword i  ;
  if ( curlevel != salevel ) 
  {
    if ( saveptr > maxsavestack ) 
    {
      maxsavestack = saveptr ;
      if ( maxsavestack > savesize - 7 ) 
      overflow ( 65866L , savesize ) ;
    } 
    savestack [saveptr ].hh.b0 = 4 ;
    savestack [saveptr ].hh.b1 = salevel ;
    savestack [saveptr ].hh .v.RH = sachain ;
    incr ( saveptr ) ;
    sachain = -268435455L ;
    salevel = curlevel ;
  } 
  i = mem [p ].hh.b0 ;
  if ( i < 128 ) 
  {
    if ( mem [p + 2 ].cint == 0 ) 
    {
      q = getnode ( 2 ) ;
      i = 384 ;
    } 
    else {
	
      q = getnode ( 3 ) ;
      mem [q + 2 ].cint = mem [p + 2 ].cint ;
    } 
    mem [q + 1 ].hh .v.RH = -268435455L ;
  } 
  else {
      
    q = getnode ( 2 ) ;
    mem [q + 1 ].hh .v.RH = mem [p + 1 ].hh .v.RH ;
  } 
  mem [q + 1 ].hh .v.LH = p ;
  mem [q ].hh.b0 = i ;
  mem [q ].hh.b1 = mem [p ].hh.b1 ;
  mem [q ].hh .v.RH = sachain ;
  sachain = q ;
  incr ( mem [p + 1 ].hh .v.LH ) ;
} 
void 
zsadestroy ( halfword p ) 
{
  sadestroy_regmem 
  if ( mem [p ].hh.b0 < 256 ) 
  deleteglueref ( mem [p + 1 ].hh .v.RH ) ;
  else if ( mem [p + 1 ].hh .v.RH != -268435455L ) {
      
    if ( mem [p ].hh.b0 < 320 ) 
    flushnodelist ( mem [p + 1 ].hh .v.RH ) ;
    else deletetokenref ( mem [p + 1 ].hh .v.RH ) ;
  } 
} 
void 
zsadef ( halfword p , halfword e ) 
{
  sadef_regmem 
  incr ( mem [p + 1 ].hh .v.LH ) ;
  if ( mem [p + 1 ].hh .v.RH == e ) 
  {
	;
#ifdef STAT
    if ( eqtb [7892325L ].cint > 0 ) 
    showsa ( p , 65868L ) ;
#endif /* STAT */
    sadestroy ( p ) ;
  } 
  else {
      
	;
#ifdef STAT
    if ( eqtb [7892325L ].cint > 0 ) 
    showsa ( p , 65869L ) ;
#endif /* STAT */
    if ( mem [p ].hh.b1 == curlevel ) 
    sadestroy ( p ) ;
    else sasave ( p ) ;
    mem [p ].hh.b1 = curlevel ;
    mem [p + 1 ].hh .v.RH = e ;
	;
#ifdef STAT
    if ( eqtb [7892325L ].cint > 0 ) 
    showsa ( p , 65870L ) ;
#endif /* STAT */
  } 
  deletesaref ( p ) ;
} 
void 
zsawdef ( halfword p , integer w ) 
{
  sawdef_regmem 
  incr ( mem [p + 1 ].hh .v.LH ) ;
  if ( mem [p + 2 ].cint == w ) 
  {
	;
#ifdef STAT
    if ( eqtb [7892325L ].cint > 0 ) 
    showsa ( p , 65868L ) ;
#endif /* STAT */
  } 
  else {
      
	;
#ifdef STAT
    if ( eqtb [7892325L ].cint > 0 ) 
    showsa ( p , 65869L ) ;
#endif /* STAT */
    if ( mem [p ].hh.b1 != curlevel ) 
    sasave ( p ) ;
    mem [p ].hh.b1 = curlevel ;
    mem [p + 2 ].cint = w ;
	;
#ifdef STAT
    if ( eqtb [7892325L ].cint > 0 ) 
    showsa ( p , 65870L ) ;
#endif /* STAT */
  } 
  deletesaref ( p ) ;
} 
void 
zgsadef ( halfword p , halfword e ) 
{
  gsadef_regmem 
  incr ( mem [p + 1 ].hh .v.LH ) ;
	;
#ifdef STAT
  if ( eqtb [7892325L ].cint > 0 ) 
  showsa ( p , 65871L ) ;
#endif /* STAT */
  sadestroy ( p ) ;
  mem [p ].hh.b1 = 1 ;
  mem [p + 1 ].hh .v.RH = e ;
	;
#ifdef STAT
  if ( eqtb [7892325L ].cint > 0 ) 
  showsa ( p , 65870L ) ;
#endif /* STAT */
  deletesaref ( p ) ;
} 
void 
zgsawdef ( halfword p , integer w ) 
{
  gsawdef_regmem 
  incr ( mem [p + 1 ].hh .v.LH ) ;
	;
#ifdef STAT
  if ( eqtb [7892325L ].cint > 0 ) 
  showsa ( p , 65871L ) ;
#endif /* STAT */
  mem [p ].hh.b1 = 1 ;
  mem [p + 2 ].cint = w ;
	;
#ifdef STAT
  if ( eqtb [7892325L ].cint > 0 ) 
  showsa ( p , 65870L ) ;
#endif /* STAT */
  deletesaref ( p ) ;
} 
void 
sarestore ( void ) 
{
  sarestore_regmem 
  halfword p  ;
  do {
      p = mem [sachain + 1 ].hh .v.LH ;
    if ( mem [p ].hh.b1 == 1 ) 
    {
      if ( mem [p ].hh.b0 >= 128 ) 
      sadestroy ( sachain ) ;
	;
#ifdef STAT
      if ( eqtb [7892301L ].cint > 0 ) 
      showsa ( p , 65873L ) ;
#endif /* STAT */
    } 
    else {
	
      if ( mem [p ].hh.b0 < 128 ) {
	  
	if ( mem [sachain ].hh.b0 < 128 ) 
	mem [p + 2 ].cint = mem [sachain + 2 ].cint ;
	else mem [p + 2 ].cint = 0 ;
      } 
      else {
	  
	sadestroy ( p ) ;
	mem [p + 1 ].hh .v.RH = mem [sachain + 1 ].hh .v.RH ;
      } 
      mem [p ].hh.b1 = mem [sachain ].hh.b1 ;
	;
#ifdef STAT
      if ( eqtb [7892301L ].cint > 0 ) 
      showsa ( p , 65874L ) ;
#endif /* STAT */
    } 
    deletesaref ( p ) ;
    p = sachain ;
    sachain = mem [p ].hh .v.RH ;
    if ( mem [p ].hh.b0 < 128 ) 
    freenode ( p , 3 ) ;
    else freenode ( p , 2 ) ;
  } while ( ! ( sachain == -268435455L ) ) ;
} 
void 
znewsavelevel ( groupcode c ) 
{
  newsavelevel_regmem 
  if ( saveptr > maxsavestack ) 
  {
    maxsavestack = saveptr ;
    if ( maxsavestack > savesize - 7 ) 
    overflow ( 65866L , savesize ) ;
  } 
  if ( ( eTeXmode == 1 ) ) 
  {
    savestack [saveptr + 0 ].cint = line ;
    incr ( saveptr ) ;
  } 
  savestack [saveptr ].hh.b0 = 3 ;
  savestack [saveptr ].hh.b1 = curgroup ;
  savestack [saveptr ].hh .v.RH = curboundary ;
  if ( curlevel == 65535L ) 
  overflow ( 65867L , 65535L ) ;
  curboundary = saveptr ;
  curgroup = c ;
	;
#ifdef STAT
  if ( eqtb [7892326L ].cint > 0 ) 
  grouptrace ( false ) ;
#endif /* STAT */
  incr ( curlevel ) ;
  incr ( saveptr ) ;
} 
void 
zeqdestroy ( memoryword w ) 
{
  eqdestroy_regmem 
  halfword q  ;
  switch ( w .hh.b0 ) 
  {case 114 : 
  case 115 : 
  case 116 : 
  case 117 : 
    deletetokenref ( w .hh .v.RH ) ;
    break ;
  case 120 : 
    deleteglueref ( w .hh .v.RH ) ;
    break ;
  case 121 : 
    {
      q = w .hh .v.RH ;
      if ( q != -268435455L ) 
      freenode ( q , mem [q ].hh .v.LH + mem [q ].hh .v.LH + 1 ) ;
    } 
    break ;
  case 122 : 
    flushnodelist ( w .hh .v.RH ) ;
    break ;
  case 72 : 
  case 91 : 
    if ( ( w .hh .v.RH < membot ) || ( w .hh .v.RH > membot + 19 ) ) 
    deletesaref ( w .hh .v.RH ) ;
    break ;
    default: 
    ;
    break ;
  } 
} 
void 
zeqsave ( halfword p , quarterword l ) 
{
  eqsave_regmem 
  if ( saveptr > maxsavestack ) 
  {
    maxsavestack = saveptr ;
    if ( maxsavestack > savesize - 7 ) 
    overflow ( 65866L , savesize ) ;
  } 
  if ( l == 0 ) 
  savestack [saveptr ].hh.b0 = 1 ;
  else {
      
    savestack [saveptr ]= eqtb [p ];
    incr ( saveptr ) ;
    savestack [saveptr ].hh.b0 = 0 ;
  } 
  savestack [saveptr ].hh.b1 = l ;
  savestack [saveptr ].hh .v.RH = p ;
  incr ( saveptr ) ;
} 
void 
zeqdefine ( halfword p , quarterword t , halfword e ) 
{
  /* 10 */ eqdefine_regmem 
  if ( ( eTeXmode == 1 ) && ( eqtb [p ].hh.b0 == t ) && ( eqtb [p ].hh 
  .v.RH == e ) ) 
  {
	;
#ifdef STAT
    if ( eqtb [7892325L ].cint > 0 ) 
    restoretrace ( p , 65868L ) ;
#endif /* STAT */
    eqdestroy ( eqtb [p ]) ;
    return ;
  } 
	;
#ifdef STAT
  if ( eqtb [7892325L ].cint > 0 ) 
  restoretrace ( p , 65869L ) ;
#endif /* STAT */
  if ( eqtb [p ].hh.b1 == curlevel ) 
  eqdestroy ( eqtb [p ]) ;
  else if ( curlevel > 1 ) 
  eqsave ( p , eqtb [p ].hh.b1 ) ;
  eqtb [p ].hh.b1 = curlevel ;
  eqtb [p ].hh.b0 = t ;
  eqtb [p ].hh .v.RH = e ;
	;
#ifdef STAT
  if ( eqtb [7892325L ].cint > 0 ) 
  restoretrace ( p , 65870L ) ;
#endif /* STAT */
} 
void 
zeqworddefine ( halfword p , integer w ) 
{
  /* 10 */ eqworddefine_regmem 
  if ( ( eTeXmode == 1 ) && ( eqtb [p ].cint == w ) ) 
  {
	;
#ifdef STAT
    if ( eqtb [7892325L ].cint > 0 ) 
    restoretrace ( p , 65868L ) ;
#endif /* STAT */
    return ;
  } 
	;
#ifdef STAT
  if ( eqtb [7892325L ].cint > 0 ) 
  restoretrace ( p , 65869L ) ;
#endif /* STAT */
  if ( xeqlevel [p ]!= curlevel ) 
  {
    eqsave ( p , xeqlevel [p ]) ;
    xeqlevel [p ]= curlevel ;
  } 
  eqtb [p ].cint = w ;
	;
#ifdef STAT
  if ( eqtb [7892325L ].cint > 0 ) 
  restoretrace ( p , 65870L ) ;
#endif /* STAT */
} 
void 
zgeqdefine ( halfword p , quarterword t , halfword e ) 
{
  geqdefine_regmem 
	;
#ifdef STAT
  if ( eqtb [7892325L ].cint > 0 ) 
  restoretrace ( p , 65871L ) ;
#endif /* STAT */
  {
    eqdestroy ( eqtb [p ]) ;
    eqtb [p ].hh.b1 = 1 ;
    eqtb [p ].hh.b0 = t ;
    eqtb [p ].hh .v.RH = e ;
  } 
	;
#ifdef STAT
  if ( eqtb [7892325L ].cint > 0 ) 
  restoretrace ( p , 65870L ) ;
#endif /* STAT */
} 
void 
zgeqworddefine ( halfword p , integer w ) 
{
  geqworddefine_regmem 
	;
#ifdef STAT
  if ( eqtb [7892325L ].cint > 0 ) 
  restoretrace ( p , 65871L ) ;
#endif /* STAT */
  {
    eqtb [p ].cint = w ;
    xeqlevel [p ]= 1 ;
  } 
	;
#ifdef STAT
  if ( eqtb [7892325L ].cint > 0 ) 
  restoretrace ( p , 65870L ) ;
#endif /* STAT */
} 
void 
zsaveforafter ( halfword t ) 
{
  saveforafter_regmem 
  if ( curlevel > 1 ) 
  {
    if ( saveptr > maxsavestack ) 
    {
      maxsavestack = saveptr ;
      if ( maxsavestack > savesize - 7 ) 
      overflow ( 65866L , savesize ) ;
    } 
    savestack [saveptr ].hh.b0 = 2 ;
    savestack [saveptr ].hh.b1 = 0 ;
    savestack [saveptr ].hh .v.RH = t ;
    incr ( saveptr ) ;
  } 
} 
void 
unsave ( void ) 
{
  /* 30 */ unsave_regmem 
  halfword p  ;
  quarterword l  ;
  halfword t  ;
  boolean a  ;
  a = false ;
  if ( curlevel > 1 ) 
  {
    decr ( curlevel ) ;
    while ( true ) {
	
      decr ( saveptr ) ;
      if ( savestack [saveptr ].hh.b0 == 3 ) 
      goto lab30 ;
      p = savestack [saveptr ].hh .v.RH ;
      if ( savestack [saveptr ].hh.b0 == 2 ) 
      {
	t = curtok ;
	curtok = p ;
	if ( a ) 
	{
	  p = getavail () ;
	  mem [p ].hh .v.LH = curtok ;
	  mem [p ].hh .v.RH = curinput .locfield ;
	  curinput .locfield = p ;
	  curinput .startfield = p ;
	  if ( curtok < 6291456L ) {
	      
	    if ( curtok < 4194304L ) 
	    decr ( alignstate ) ;
	    else incr ( alignstate ) ;
	  } 
	} 
	else {
	    
	  backinput () ;
	  a = ( eTeXmode == 1 ) ;
	} 
	curtok = t ;
      } 
      else if ( savestack [saveptr ].hh.b0 == 4 ) 
      {
	sarestore () ;
	sachain = p ;
	salevel = savestack [saveptr ].hh.b1 ;
      } 
      else {
	  
	if ( savestack [saveptr ].hh.b0 == 0 ) 
	{
	  l = savestack [saveptr ].hh.b1 ;
	  decr ( saveptr ) ;
	} 
	else savestack [saveptr ]= eqtb [1205763L ];
	if ( ( p < 7892264L ) || ( p > 9006998L ) ) {
	    
	  if ( eqtb [p ].hh.b1 == 1 ) 
	  {
	    eqdestroy ( savestack [saveptr ]) ;
	;
#ifdef STAT
	    if ( eqtb [7892301L ].cint > 0 ) 
	    restoretrace ( p , 65873L ) ;
#endif /* STAT */
	  } 
	  else {
	      
	    eqdestroy ( eqtb [p ]) ;
	    eqtb [p ]= savestack [saveptr ];
	;
#ifdef STAT
	    if ( eqtb [7892301L ].cint > 0 ) 
	    restoretrace ( p , 65874L ) ;
#endif /* STAT */
	  } 
	} 
	else if ( xeqlevel [p ]!= 1 ) 
	{
	  eqtb [p ]= savestack [saveptr ];
	  xeqlevel [p ]= l ;
	;
#ifdef STAT
	  if ( eqtb [7892301L ].cint > 0 ) 
	  restoretrace ( p , 65874L ) ;
#endif /* STAT */
	} 
	else {
	    
	;
#ifdef STAT
	  if ( eqtb [7892301L ].cint > 0 ) 
	  restoretrace ( p , 65873L ) ;
#endif /* STAT */
	} 
      } 
    } 
    lab30: 
	;
#ifdef STAT
    if ( eqtb [7892326L ].cint > 0 ) 
    grouptrace ( true ) ;
#endif /* STAT */
    if ( grpstack [inopen ]== curboundary ) 
    groupwarning () ;
    curgroup = savestack [saveptr ].hh.b1 ;
    curboundary = savestack [saveptr ].hh .v.RH ;
    if ( ( eTeXmode == 1 ) ) 
    decr ( saveptr ) ;
  } 
  else confusion ( 65872L ) ;
} 
void 
preparemag ( void ) 
{
  preparemag_regmem 
  if ( ( magset > 0 ) && ( eqtb [7892281L ].cint != magset ) ) 
  {
    {
      if ( interaction == 3 ) 
      ;
      if ( filelineerrorstylep ) 
      printfileline () ;
      else printnl ( 65544L ) ;
      print ( 65876L ) ;
    } 
    printint ( eqtb [7892281L ].cint ) ;
    print ( 65877L ) ;
    printnl ( 65878L ) ;
    {
      helpptr = 2 ;
      helpline [1 ]= 65879L ;
      helpline [0 ]= 65880L ;
    } 
    interror ( magset ) ;
    geqworddefine ( 7892281L , magset ) ;
  } 
  if ( ( eqtb [7892281L ].cint <= 0 ) || ( eqtb [7892281L ].cint > 32768L 
  ) ) 
  {
    {
      if ( interaction == 3 ) 
      ;
      if ( filelineerrorstylep ) 
      printfileline () ;
      else printnl ( 65544L ) ;
      print ( 65881L ) ;
    } 
    {
      helpptr = 1 ;
      helpline [0 ]= 65882L ;
    } 
    interror ( eqtb [7892281L ].cint ) ;
    geqworddefine ( 7892281L , 1000 ) ;
  } 
  magset = eqtb [7892281L ].cint ;
} 
void 
ztokenshow ( halfword p ) 
{
  tokenshow_regmem 
  if ( p != -268435455L ) 
  showtokenlist ( mem [p ].hh .v.RH , -268435455L , 10000000L ) ;
} 
void 
printmeaning ( void ) 
{
  printmeaning_regmem 
  printcmdchr ( curcmd , curchr ) ;
  if ( curcmd >= 114 ) 
  {
    printchar ( 58 ) ;
    println () ;
    tokenshow ( curchr ) ;
  } 
  else if ( ( curcmd == 113 ) && ( curchr < 5 ) ) 
  {
    printchar ( 58 ) ;
    println () ;
    tokenshow ( curmark [curchr ]) ;
  } 
} 
void 
showcurcmdchr ( void ) 
{
  showcurcmdchr_regmem 
  integer n  ;
  integer l  ;
  halfword p  ;
  begindiagnostic () ;
  printnl ( 123 ) ;
  if ( curlist .modefield != shownmode ) 
  {
    printmode ( curlist .modefield ) ;
    print ( 65595L ) ;
    shownmode = curlist .modefield ;
  } 
  printcmdchr ( curcmd , curchr ) ;
  if ( eqtb [7892327L ].cint > 0 ) {
      
    if ( curcmd >= 108 ) {
	
      if ( curcmd <= 109 ) 
      {
	print ( 65595L ) ;
	if ( curcmd == 109 ) 
	{
	  printcmdchr ( 108 , curif ) ;
	  printchar ( 32 ) ;
	  n = 0 ;
	  l = ifline ;
	} 
	else {
	    
	  n = 1 ;
	  l = line ;
	} 
	p = condptr ;
	while ( p != -268435455L ) {
	    
	  incr ( n ) ;
	  p = mem [p ].hh .v.RH ;
	} 
	print ( 65896L ) ;
	printint ( n ) ;
	printchar ( 41 ) ;
	if ( l != 0 ) 
	{
	  print ( 66904L ) ;
	  printint ( l ) ;
	} 
      } 
    } 
  } 
  printchar ( 125 ) ;
  enddiagnostic ( false ) ;
} 
void 
showcontext ( void ) 
{
  /* 30 */ showcontext_regmem 
  unsigned char oldsetting  ;
  integer nn  ;
  boolean bottomline  ;
  integer i  ;
  integer j  ;
  integer l  ;
  integer m  ;
  integer n  ;
  integer p  ;
  integer q  ;
  baseptr = inputptr ;
  inputstack [baseptr ]= curinput ;
  nn = -1 ;
  bottomline = false ;
  while ( true ) {
      
    curinput = inputstack [baseptr ];
    if ( ( curinput .statefield != 0 ) ) {
	
      if ( ( curinput .namefield > 19 ) || ( baseptr == 0 ) ) 
      bottomline = true ;
    } 
    if ( ( baseptr == inputptr ) || bottomline || ( nn < eqtb [7892318L ]
    .cint ) ) 
    {
      if ( ( baseptr == inputptr ) || ( curinput .statefield != 0 ) || ( 
      curinput .indexfield != 3 ) || ( curinput .locfield != -268435455L ) ) 
      {
	tally = 0 ;
	oldsetting = selector ;
	if ( curinput .statefield != 0 ) 
	{
	  if ( curinput .namefield <= 17 ) {
	      
	    if ( ( curinput .namefield == 0 ) ) {
		
	      if ( baseptr == 0 ) 
	      printnl ( 65901L ) ;
	      else printnl ( 65902L ) ;
	    } 
	    else {
		
	      printnl ( 65903L ) ;
	      if ( curinput .namefield == 17 ) 
	      printchar ( 42 ) ;
	      else printint ( curinput .namefield - 1 ) ;
	      printchar ( 62 ) ;
	    } 
	  } 
	  else {
	      
	    printnl ( 65904L ) ;
	    if ( curinput .indexfield == inopen ) 
	    printint ( line ) ;
	    else printint ( linestack [curinput .indexfield + 1 ]) ;
	  } 
	  printchar ( 32 ) ;
	  {
	    l = tally ;
	    tally = 0 ;
	    selector = 20 ;
	    trickcount = 1000000L ;
	  } 
	  if ( buffer [curinput .limitfield ]== eqtb [7892312L ].cint ) 
	  j = curinput .limitfield ;
	  else j = curinput .limitfield + 1 ;
	  if ( j > 0 ) 
	  {register integer for_end; i = curinput .startfield ;for_end = j - 
	  1 ; if ( i <= for_end) do 
	    {
	      if ( i == curinput .locfield ) 
	      {
		firstcount = tally ;
		trickcount = tally + 1 + errorline - halferrorline ;
		if ( trickcount < errorline ) 
		trickcount = errorline ;
	      } 
	      printchar ( buffer [i ]) ;
	    } 
	  while ( i++ < for_end ) ;} 
	} 
	else {
	    
	  switch ( curinput .indexfield ) 
	  {case 0 : 
	    printnl ( 65905L ) ;
	    break ;
	  case 1 : 
	  case 2 : 
	    printnl ( 65906L ) ;
	    break ;
	  case 3 : 
	  case 4 : 
	    if ( curinput .locfield == -268435455L ) 
	    printnl ( 65907L ) ;
	    else printnl ( 65908L ) ;
	    break ;
	  case 5 : 
	    printnl ( 65909L ) ;
	    break ;
	  case 6 : 
	    {
	      println () ;
	      printcs ( curinput .namefield ) ;
	    } 
	    break ;
	  case 7 : 
	    printnl ( 65910L ) ;
	    break ;
	  case 8 : 
	    printnl ( 65911L ) ;
	    break ;
	  case 9 : 
	    printnl ( 65912L ) ;
	    break ;
	  case 10 : 
	    printnl ( 65913L ) ;
	    break ;
	  case 11 : 
	    printnl ( 65914L ) ;
	    break ;
	  case 12 : 
	    printnl ( 65915L ) ;
	    break ;
	  case 13 : 
	    printnl ( 65916L ) ;
	    break ;
	  case 14 : 
	    printnl ( 65917L ) ;
	    break ;
	  case 15 : 
	    printnl ( 65918L ) ;
	    break ;
	  case 16 : 
	    printnl ( 65919L ) ;
	    break ;
	  case 17 : 
	    printnl ( 65920L ) ;
	    break ;
	  case 18 : 
	    printnl ( 65921L ) ;
	    break ;
	    default: 
	    printnl ( 63 ) ;
	    break ;
	  } 
	  {
	    l = tally ;
	    tally = 0 ;
	    selector = 20 ;
	    trickcount = 1000000L ;
	  } 
	  if ( curinput .indexfield < 6 ) 
	  showtokenlist ( curinput .startfield , curinput .locfield , 100000L 
	  ) ;
	  else showtokenlist ( mem [curinput .startfield ].hh .v.RH , 
	  curinput .locfield , 100000L ) ;
	} 
	selector = oldsetting ;
	if ( trickcount == 1000000L ) 
	{
	  firstcount = tally ;
	  trickcount = tally + 1 + errorline - halferrorline ;
	  if ( trickcount < errorline ) 
	  trickcount = errorline ;
	} 
	if ( tally < trickcount ) 
	m = tally - firstcount ;
	else m = trickcount - firstcount ;
	if ( l + firstcount <= halferrorline ) 
	{
	  p = 0 ;
	  n = l + firstcount ;
	} 
	else {
	    
	  print ( 65559L ) ;
	  p = l + firstcount - halferrorline + 3 ;
	  n = halferrorline ;
	} 
	{register integer for_end; q = p ;for_end = firstcount - 1 ; if ( q 
	<= for_end) do 
	  printchar ( trickbuf [q % errorline ]) ;
	while ( q++ < for_end ) ;} 
	println () ;
	{register integer for_end; q = 1 ;for_end = n ; if ( q <= for_end) 
	do 
	  printrawchar ( 32 , true ) ;
	while ( q++ < for_end ) ;} 
	if ( m + n <= errorline ) 
	p = firstcount + m ;
	else p = firstcount + ( errorline - n - 3 ) ;
	{register integer for_end; q = firstcount ;for_end = p - 1 ; if ( q 
	<= for_end) do 
	  printchar ( trickbuf [q % errorline ]) ;
	while ( q++ < for_end ) ;} 
	if ( m + n > errorline ) 
	print ( 65559L ) ;
	incr ( nn ) ;
      } 
    } 
    else if ( nn == eqtb [7892318L ].cint ) 
    {
      printnl ( 65559L ) ;
      incr ( nn ) ;
    } 
    if ( bottomline ) 
    goto lab30 ;
    decr ( baseptr ) ;
  } 
  lab30: curinput = inputstack [inputptr ];
} 
void 
zbegintokenlist ( halfword p , quarterword t ) 
{
  begintokenlist_regmem 
  {
    if ( inputptr > maxinstack ) 
    {
      maxinstack = inputptr ;
      if ( inputptr == stacksize ) 
      overflow ( 65922L , stacksize ) ;
    } 
    inputstack [inputptr ]= curinput ;
    incr ( inputptr ) ;
  } 
  curinput .statefield = 0 ;
  curinput .startfield = p ;
  curinput .indexfield = t ;
  if ( t >= 6 ) 
  {
    incr ( mem [p ].hh .v.LH ) ;
    if ( t == 6 ) 
    curinput .limitfield = paramptr ;
    else {
	
      curinput .locfield = mem [p ].hh .v.RH ;
      if ( eqtb [7892294L ].cint > 1 ) 
      {
	begindiagnostic () ;
	printnl ( 65545L ) ;
	switch ( t ) 
	{case 15 : 
	  printesc ( 65642L ) ;
	  break ;
	case 18 : 
	  printesc ( 65923L ) ;
	  break ;
	  default: 
	  printcmdchr ( 73 , t + 1206289L ) ;
	  break ;
	} 
	print ( 65884L ) ;
	tokenshow ( p ) ;
	enddiagnostic ( false ) ;
      } 
    } 
  } 
  else curinput .locfield = p ;
} 
void 
endtokenlist ( void ) 
{
  endtokenlist_regmem 
  if ( curinput .indexfield >= 3 ) 
  {
    if ( curinput .indexfield <= 5 ) 
    flushlist ( curinput .startfield ) ;
    else {
	
      deletetokenref ( curinput .startfield ) ;
      if ( curinput .indexfield == 6 ) 
      while ( paramptr > curinput .limitfield ) {
	  
	decr ( paramptr ) ;
	flushlist ( paramstack [paramptr ]) ;
      } 
      else if ( ( curinput .indexfield == 7 ) && ( ! outputcanend ) ) 
      fatalerror ( 65924L ) ;
    } 
  } 
  else if ( curinput .indexfield == 1 ) {
      
    if ( alignstate > 500000L ) 
    alignstate = 0 ;
    else fatalerror ( 65925L ) ;
  } 
  {
    decr ( inputptr ) ;
    curinput = inputstack [inputptr ];
  } 
  {
    if ( interrupt != 0 ) 
    pauseforinstructions () ;
  } 
} 
void 
backinput ( void ) 
{
  backinput_regmem 
  halfword p  ;
  while ( ( curinput .locfield == -268435455L ) && ( curinput .indexfield != 2 
  ) && ( curinput .indexfield != 7 ) ) endtokenlist () ;
  p = getavail () ;
  mem [p ].hh .v.LH = curtok ;
  if ( curtok < 6291456L ) {
      
    if ( curtok < 4194304L ) 
    decr ( alignstate ) ;
    else incr ( alignstate ) ;
  } 
  {
    if ( inputptr > maxinstack ) 
    {
      maxinstack = inputptr ;
      if ( inputptr == stacksize ) 
      overflow ( 65922L , stacksize ) ;
    } 
    inputstack [inputptr ]= curinput ;
    incr ( inputptr ) ;
  } 
  curinput .statefield = 0 ;
  curinput .startfield = p ;
  curinput .indexfield = 3 ;
  curinput .locfield = p ;
} 
void 
backerror ( void ) 
{
  backerror_regmem 
  OKtointerrupt = false ;
  backinput () ;
  OKtointerrupt = true ;
  error () ;
} 
void 
inserror ( void ) 
{
  inserror_regmem 
  OKtointerrupt = false ;
  backinput () ;
  curinput .indexfield = 5 ;
  OKtointerrupt = true ;
  error () ;
} 
void 
beginfilereading ( void ) 
{
  beginfilereading_regmem 
  if ( inopen == maxinopen ) 
  overflow ( 65926L , maxinopen ) ;
  if ( first == bufsize ) 
  overflow ( 65538L , bufsize ) ;
  incr ( inopen ) ;
  {
    if ( inputptr > maxinstack ) 
    {
      maxinstack = inputptr ;
      if ( inputptr == stacksize ) 
      overflow ( 65922L , stacksize ) ;
    } 
    inputstack [inputptr ]= curinput ;
    incr ( inputptr ) ;
  } 
  curinput .indexfield = inopen ;
  sourcefilenamestack [curinput .indexfield ]= 0 ;
  fullsourcefilenamestack [curinput .indexfield ]= 0 ;
  eofseen [curinput .indexfield ]= false ;
  grpstack [curinput .indexfield ]= curboundary ;
  ifstack [curinput .indexfield ]= condptr ;
  linestack [curinput .indexfield ]= line ;
  curinput .startfield = first ;
  curinput .statefield = 1 ;
  curinput .namefield = 0 ;
  curinput .synctextagfield = 0 ;
} 
void 
endfilereading ( void ) 
{
  endfilereading_regmem 
  first = curinput .startfield ;
  line = linestack [curinput .indexfield ];
  if ( ( curinput .namefield == 18 ) || ( curinput .namefield == 19 ) ) 
  pseudoclose () ;
  else if ( curinput .namefield > 17 ) 
  uclose ( inputfile [curinput .indexfield ]) ;
  {
    decr ( inputptr ) ;
    curinput = inputstack [inputptr ];
  } 
  decr ( inopen ) ;
} 
void 
clearforerrorprompt ( void ) 
{
  clearforerrorprompt_regmem 
  while ( ( curinput .statefield != 0 ) && ( curinput .namefield == 0 ) && ( 
  inputptr > 0 ) && ( curinput .locfield > curinput .limitfield ) ) 
  endfilereading () ;
  println () ;
} 
void 
checkoutervalidity ( void ) 
{
  checkoutervalidity_regmem 
  halfword p  ;
  halfword q  ;
  if ( scannerstatus != 0 ) 
  {
    deletionsallowed = false ;
    if ( curcs != 0 ) 
    {
      if ( ( curinput .statefield == 0 ) || ( curinput .namefield < 1 ) || ( 
      curinput .namefield > 17 ) ) 
      {
	p = getavail () ;
	mem [p ].hh .v.LH = 33554431L + curcs ;
	begintokenlist ( p , 3 ) ;
      } 
      curcmd = 10 ;
      curchr = 32 ;
    } 
    if ( scannerstatus > 1 ) 
    {
      runaway () ;
      if ( curcs == 0 ) 
      {
	if ( interaction == 3 ) 
	;
	if ( filelineerrorstylep ) 
	printfileline () ;
	else printnl ( 65544L ) ;
	print ( 65934L ) ;
      } 
      else {
	  
	curcs = 0 ;
	{
	  if ( interaction == 3 ) 
	  ;
	  if ( filelineerrorstylep ) 
	  printfileline () ;
	  else printnl ( 65544L ) ;
	  print ( 65935L ) ;
	} 
      } 
      p = getavail () ;
      switch ( scannerstatus ) 
      {case 2 : 
	{
	  print ( 65941L ) ;
	  mem [p ].hh .v.LH = 4194429L ;
	} 
	break ;
      case 3 : 
	{
	  print ( 65942L ) ;
	  mem [p ].hh .v.LH = partoken ;
	  longstate = 116 ;
	} 
	break ;
      case 4 : 
	{
	  print ( 65943L ) ;
	  mem [p ].hh .v.LH = 4194429L ;
	  q = p ;
	  p = getavail () ;
	  mem [p ].hh .v.RH = q ;
	  mem [p ].hh .v.LH = 34749082L ;
	  alignstate = -1000000L ;
	} 
	break ;
      case 5 : 
	{
	  print ( 65944L ) ;
	  mem [p ].hh .v.LH = 4194429L ;
	} 
	break ;
      } 
      begintokenlist ( p , 5 ) ;
      print ( 65936L ) ;
      sprintcs ( warningindex ) ;
      {
	helpptr = 4 ;
	helpline [3 ]= 65937L ;
	helpline [2 ]= 65938L ;
	helpline [1 ]= 65939L ;
	helpline [0 ]= 65940L ;
      } 
      error () ;
    } 
    else {
	
      {
	if ( interaction == 3 ) 
	;
	if ( filelineerrorstylep ) 
	printfileline () ;
	else printnl ( 65544L ) ;
	print ( 65928L ) ;
      } 
      printcmdchr ( 108 , curif ) ;
      print ( 65929L ) ;
      printint ( skipline ) ;
      {
	helpptr = 3 ;
	helpline [2 ]= 65930L ;
	helpline [1 ]= 65931L ;
	helpline [0 ]= 65932L ;
      } 
      if ( curcs != 0 ) 
      curcs = 0 ;
      else helpline [2 ]= 65933L ;
      curtok = 34749085L ;
      inserror () ;
    } 
    deletionsallowed = true ;
  } 
} 
void 
getnext ( void ) 
{
  /* 20 25 21 26 40 27 10 */ getnext_regmem 
  integer k  ;
  halfword t  ;
  unsigned char cat  ;
  UnicodeScalar c  ;
  UTF16code lower  ;
  smallnumber d  ;
  smallnumber supcount  ;
  lab20: curcs = 0 ;
  if ( curinput .statefield != 0 ) 
  {
    lab25: if ( curinput .locfield <= curinput .limitfield ) 
    {
      curchr = buffer [curinput .locfield ];
      incr ( curinput .locfield ) ;
      if ( ( curchr >= 55296L ) && ( curchr < 56320L ) && ( curinput .locfield 
      <= curinput .limitfield ) && ( buffer [curinput .locfield ]>= 56320L ) 
      && ( buffer [curinput .locfield ]< 57344L ) ) 
      {
	lower = buffer [curinput .locfield ]- 56320L ;
	incr ( curinput .locfield ) ;
	curchr = 65536L + ( curchr - 55296L ) * 1024 + lower ;
      } 
      lab21: curcmd = eqtb [1207592L + curchr ].hh .v.RH ;
      switch ( curinput .statefield + curcmd ) 
      {case 10 : 
      case 26 : 
      case 42 : 
      case 27 : 
      case 43 : 
	goto lab25 ;
	break ;
      case 1 : 
      case 17 : 
      case 33 : 
	{
	  if ( curinput .locfield > curinput .limitfield ) 
	  curcs = 1179649L ;
	  else {
	      
	    lab26: k = curinput .locfield ;
	    curchr = buffer [k ];
	    cat = eqtb [1207592L + curchr ].hh .v.RH ;
	    incr ( k ) ;
	    if ( cat == 11 ) 
	    curinput .statefield = 17 ;
	    else if ( cat == 10 ) 
	    curinput .statefield = 17 ;
	    else curinput .statefield = 1 ;
	    if ( ( cat == 11 ) && ( k <= curinput .limitfield ) ) 
	    {
	      do {
		  curchr = buffer [k ];
		cat = eqtb [1207592L + curchr ].hh .v.RH ;
		incr ( k ) ;
	      } while ( ! ( ( cat != 11 ) || ( k > curinput .limitfield ) ) ) 
	      ;
	      {
		if ( ( cat == 7 ) && ( buffer [k ]== curchr ) && ( k < 
		curinput .limitfield ) ) 
		{
		  supcount = 2 ;
		  while ( ( supcount < 6 ) && ( k + 2 * supcount - 2 <= 
		  curinput .limitfield ) && ( buffer [k + supcount - 1 ]== 
		  curchr ) ) incr ( supcount ) ;
		  {register integer for_end; d = 1 ;for_end = supcount 
		  ; if ( d <= for_end) do 
		    if ( ! ( ( ( buffer [k + supcount - 2 + d ]>= 48 ) && ( 
		    buffer [k + supcount - 2 + d ]<= 57 ) ) || ( ( buffer [
		    k + supcount - 2 + d ]>= 97 ) && ( buffer [k + supcount 
		    - 2 + d ]<= 102 ) ) ) ) 
		    {
		      c = buffer [k + 1 ];
		      if ( c < 128 ) 
		      {
			if ( c < 64 ) 
			buffer [k - 1 ]= c + 64 ;
			else buffer [k - 1 ]= c - 64 ;
			d = 2 ;
			curinput .limitfield = curinput .limitfield - d ;
			while ( k <= curinput .limitfield ) {
			    
			  buffer [k ]= buffer [k + d ];
			  incr ( k ) ;
			} 
			goto lab26 ;
		      } 
		      else supcount = 0 ;
		    } 
		  while ( d++ < for_end ) ;} 
		  if ( supcount > 0 ) 
		  {
		    curchr = 0 ;
		    {register integer for_end; d = 1 ;for_end = supcount 
		    ; if ( d <= for_end) do 
		      {
			c = buffer [k + supcount - 2 + d ];
			if ( c <= 57 ) 
			curchr = 16 * curchr + c - 48 ;
			else curchr = 16 * curchr + c - 87 ;
		      } 
		    while ( d++ < for_end ) ;} 
		    if ( curchr > 1114111L ) 
		    curchr = buffer [k ];
		    else {
			
		      buffer [k - 1 ]= curchr ;
		      d = 2 * supcount - 1 ;
		      curinput .limitfield = curinput .limitfield - d ;
		      while ( k <= curinput .limitfield ) {
			  
			buffer [k ]= buffer [k + d ];
			incr ( k ) ;
		      } 
		      goto lab26 ;
		    } 
		  } 
		} 
	      } 
	      if ( cat != 11 ) 
	      decr ( k ) ;
	      if ( k > curinput .locfield + 1 ) 
	      {
		curcs = idlookup ( curinput .locfield , k - curinput .locfield 
		) ;
		curinput .locfield = k ;
		goto lab40 ;
	      } 
	    } 
	    else {
		
	      if ( ( cat == 7 ) && ( buffer [k ]== curchr ) && ( k < 
	      curinput .limitfield ) ) 
	      {
		supcount = 2 ;
		while ( ( supcount < 6 ) && ( k + 2 * supcount - 2 <= curinput 
		.limitfield ) && ( buffer [k + supcount - 1 ]== curchr ) ) 
		incr ( supcount ) ;
		{register integer for_end; d = 1 ;for_end = supcount ; if ( 
		d <= for_end) do 
		  if ( ! ( ( ( buffer [k + supcount - 2 + d ]>= 48 ) && ( 
		  buffer [k + supcount - 2 + d ]<= 57 ) ) || ( ( buffer [k 
		  + supcount - 2 + d ]>= 97 ) && ( buffer [k + supcount - 2 
		  + d ]<= 102 ) ) ) ) 
		  {
		    c = buffer [k + 1 ];
		    if ( c < 128 ) 
		    {
		      if ( c < 64 ) 
		      buffer [k - 1 ]= c + 64 ;
		      else buffer [k - 1 ]= c - 64 ;
		      d = 2 ;
		      curinput .limitfield = curinput .limitfield - d ;
		      while ( k <= curinput .limitfield ) {
			  
			buffer [k ]= buffer [k + d ];
			incr ( k ) ;
		      } 
		      goto lab26 ;
		    } 
		    else supcount = 0 ;
		  } 
		while ( d++ < for_end ) ;} 
		if ( supcount > 0 ) 
		{
		  curchr = 0 ;
		  {register integer for_end; d = 1 ;for_end = supcount 
		  ; if ( d <= for_end) do 
		    {
		      c = buffer [k + supcount - 2 + d ];
		      if ( c <= 57 ) 
		      curchr = 16 * curchr + c - 48 ;
		      else curchr = 16 * curchr + c - 87 ;
		    } 
		  while ( d++ < for_end ) ;} 
		  if ( curchr > 1114111L ) 
		  curchr = buffer [k ];
		  else {
		      
		    buffer [k - 1 ]= curchr ;
		    d = 2 * supcount - 1 ;
		    curinput .limitfield = curinput .limitfield - d ;
		    while ( k <= curinput .limitfield ) {
			
		      buffer [k ]= buffer [k + d ];
		      incr ( k ) ;
		    } 
		    goto lab26 ;
		  } 
		} 
	      } 
	    } 
	    if ( buffer [curinput .locfield ]> 65535L ) 
	    {
	      curcs = idlookup ( curinput .locfield , 1 ) ;
	      incr ( curinput .locfield ) ;
	      goto lab40 ;
	    } 
	    curcs = 1114113L + buffer [curinput .locfield ];
	    incr ( curinput .locfield ) ;
	  } 
	  lab40: curcmd = eqtb [curcs ].hh.b0 ;
	  curchr = eqtb [curcs ].hh .v.RH ;
	  if ( curcmd >= 116 ) 
	  checkoutervalidity () ;
	} 
	break ;
      case 14 : 
      case 30 : 
      case 46 : 
	{
	  curcs = curchr + 1 ;
	  curcmd = eqtb [curcs ].hh.b0 ;
	  curchr = eqtb [curcs ].hh .v.RH ;
	  curinput .statefield = 1 ;
	  if ( curcmd >= 116 ) 
	  checkoutervalidity () ;
	} 
	break ;
      case 8 : 
      case 24 : 
      case 40 : 
	{
	  if ( curchr == buffer [curinput .locfield ]) {
	      
	    if ( curinput .locfield < curinput .limitfield ) 
	    {
	      supcount = 2 ;
	      while ( ( supcount < 6 ) && ( curinput .locfield + 2 * supcount 
	      - 2 <= curinput .limitfield ) && ( curchr == buffer [curinput 
	      .locfield + supcount - 1 ]) ) incr ( supcount ) ;
	      {register integer for_end; d = 1 ;for_end = supcount ; if ( d 
	      <= for_end) do 
		if ( ! ( ( ( buffer [curinput .locfield + supcount - 2 + d ]
		>= 48 ) && ( buffer [curinput .locfield + supcount - 2 + d ]
		<= 57 ) ) || ( ( buffer [curinput .locfield + supcount - 2 + 
		d ]>= 97 ) && ( buffer [curinput .locfield + supcount - 2 + 
		d ]<= 102 ) ) ) ) 
		{
		  c = buffer [curinput .locfield + 1 ];
		  if ( c < 128 ) 
		  {
		    curinput .locfield = curinput .locfield + 2 ;
		    if ( c < 64 ) 
		    curchr = c + 64 ;
		    else curchr = c - 64 ;
		    goto lab21 ;
		  } 
		  goto lab27 ;
		} 
	      while ( d++ < for_end ) ;} 
	      curchr = 0 ;
	      {register integer for_end; d = 1 ;for_end = supcount ; if ( d 
	      <= for_end) do 
		{
		  c = buffer [curinput .locfield + supcount - 2 + d ];
		  if ( c <= 57 ) 
		  curchr = 16 * curchr + c - 48 ;
		  else curchr = 16 * curchr + c - 87 ;
		} 
	      while ( d++ < for_end ) ;} 
	      if ( curchr > 1114111L ) 
	      {
		curchr = buffer [curinput .locfield ];
		goto lab27 ;
	      } 
	      curinput .locfield = curinput .locfield + 2 * supcount - 1 ;
	      goto lab21 ;
	    } 
	  } 
	  lab27: curinput .statefield = 1 ;
	} 
	break ;
      case 16 : 
      case 32 : 
      case 48 : 
	{
	  {
	    if ( interaction == 3 ) 
	    ;
	    if ( filelineerrorstylep ) 
	    printfileline () ;
	    else printnl ( 65544L ) ;
	    print ( 65945L ) ;
	  } 
	  {
	    helpptr = 2 ;
	    helpline [1 ]= 65946L ;
	    helpline [0 ]= 65947L ;
	  } 
	  deletionsallowed = false ;
	  error () ;
	  deletionsallowed = true ;
	  goto lab20 ;
	} 
	break ;
      case 11 : 
	{
	  curinput .statefield = 17 ;
	  curchr = 32 ;
	} 
	break ;
      case 6 : 
	{
	  curinput .locfield = curinput .limitfield + 1 ;
	  curcmd = 10 ;
	  curchr = 32 ;
	} 
	break ;
      case 22 : 
      case 15 : 
      case 31 : 
      case 47 : 
	{
	  curinput .locfield = curinput .limitfield + 1 ;
	  goto lab25 ;
	} 
	break ;
      case 38 : 
	{
	  curinput .locfield = curinput .limitfield + 1 ;
	  curcs = parloc ;
	  curcmd = eqtb [curcs ].hh.b0 ;
	  curchr = eqtb [curcs ].hh .v.RH ;
	  if ( curcmd >= 116 ) 
	  checkoutervalidity () ;
	} 
	break ;
      case 2 : 
	incr ( alignstate ) ;
	break ;
      case 18 : 
      case 34 : 
	{
	  curinput .statefield = 1 ;
	  incr ( alignstate ) ;
	} 
	break ;
      case 3 : 
	decr ( alignstate ) ;
	break ;
      case 19 : 
      case 35 : 
	{
	  curinput .statefield = 1 ;
	  decr ( alignstate ) ;
	} 
	break ;
      case 20 : 
      case 21 : 
      case 23 : 
      case 25 : 
      case 28 : 
      case 29 : 
      case 36 : 
      case 37 : 
      case 39 : 
      case 41 : 
      case 44 : 
      case 45 : 
	curinput .statefield = 1 ;
	break ;
	default: 
	;
	break ;
      } 
    } 
    else {
	
      curinput .statefield = 33 ;
      if ( curinput .namefield > 17 ) 
      {
	incr ( line ) ;
	first = curinput .startfield ;
	if ( ! forceeof ) {
	    
	  if ( curinput .namefield <= 19 ) 
	  {
	    if ( pseudoinput () ) 
	    firmuptheline () ;
	    else if ( ( eqtb [1206305L ].hh .v.RH != -268435455L ) && ! 
	    eofseen [curinput .indexfield ]) 
	    {
	      curinput .limitfield = first - 1 ;
	      eofseen [curinput .indexfield ]= true ;
	      begintokenlist ( eqtb [1206305L ].hh .v.RH , 16 ) ;
	      goto lab20 ;
	    } 
	    else forceeof = true ;
	  } 
	  else {
	      
	    if ( inputln ( inputfile [curinput .indexfield ], true ) ) 
	    firmuptheline () ;
	    else if ( ( eqtb [1206305L ].hh .v.RH != -268435455L ) && ! 
	    eofseen [curinput .indexfield ]) 
	    {
	      curinput .limitfield = first - 1 ;
	      eofseen [curinput .indexfield ]= true ;
	      begintokenlist ( eqtb [1206305L ].hh .v.RH , 16 ) ;
	      goto lab20 ;
	    } 
	    else forceeof = true ;
	  } 
	} 
	if ( forceeof ) 
	{
	  if ( eqtb [7892329L ].cint > 0 ) {
	      
	    if ( ( grpstack [inopen ]!= curboundary ) || ( ifstack [inopen 
	    ]!= condptr ) ) 
	    filewarning () ;
	  } 
	  if ( curinput .namefield >= 19 ) 
	  {
	    printchar ( 41 ) ;
	    decr ( openparens ) ;
	    fflush ( stdout ) ;
	  } 
	  forceeof = false ;
	  endfilereading () ;
	  checkoutervalidity () ;
	  goto lab20 ;
	} 
	if ( ( eqtb [7892312L ].cint < 0 ) || ( eqtb [7892312L ].cint > 
	255 ) ) 
	decr ( curinput .limitfield ) ;
	else buffer [curinput .limitfield ]= eqtb [7892312L ].cint ;
	first = curinput .limitfield + 1 ;
	curinput .locfield = curinput .startfield ;
      } 
      else {
	  
	if ( ! ( curinput .namefield == 0 ) ) 
	{
	  curcmd = 0 ;
	  curchr = 0 ;
	  return ;
	} 
	if ( inputptr > 0 ) 
	{
	  endfilereading () ;
	  goto lab20 ;
	} 
	if ( selector < 18 ) 
	openlogfile () ;
	if ( interaction > 1 ) 
	{
	  if ( ( eqtb [7892312L ].cint < 0 ) || ( eqtb [7892312L ].cint > 
	  255 ) ) 
	  incr ( curinput .limitfield ) ;
	  if ( curinput .limitfield == curinput .startfield ) 
	  printnl ( 65949L ) ;
	  println () ;
	  first = curinput .startfield ;
	  {
	    ;
	    print ( 42 ) ;
	    terminput () ;
	  } 
	  curinput .limitfield = last ;
	  if ( ( eqtb [7892312L ].cint < 0 ) || ( eqtb [7892312L ].cint > 
	  255 ) ) 
	  decr ( curinput .limitfield ) ;
	  else buffer [curinput .limitfield ]= eqtb [7892312L ].cint ;
	  first = curinput .limitfield + 1 ;
	  curinput .locfield = curinput .startfield ;
	} 
	else fatalerror ( 65950L ) ;
      } 
      {
	if ( interrupt != 0 ) 
	pauseforinstructions () ;
      } 
      goto lab25 ;
    } 
  } 
  else if ( curinput .locfield != -268435455L ) 
  {
    t = mem [curinput .locfield ].hh .v.LH ;
    curinput .locfield = mem [curinput .locfield ].hh .v.RH ;
    if ( t >= 33554431L ) 
    {
      curcs = t - 33554431L ;
      curcmd = eqtb [curcs ].hh.b0 ;
      curchr = eqtb [curcs ].hh .v.RH ;
      if ( curcmd >= 116 ) {
	  
	if ( curcmd == 119 ) 
	{
	  curcs = mem [curinput .locfield ].hh .v.LH - 33554431L ;
	  curinput .locfield = -268435455L ;
	  curcmd = eqtb [curcs ].hh.b0 ;
	  curchr = eqtb [curcs ].hh .v.RH ;
	  if ( curcmd > 103 ) 
	  {
	    curcmd = 0 ;
	    curchr = 1114113L ;
	  } 
	} 
	else {
	    
	  if ( ( curcs == 1194658L ) && ( curlist .modefield == 0 ) ) 
	  fatalerror ( 65948L ) ;
	  checkoutervalidity () ;
	} 
      } 
    } 
    else {
	
      curcmd = t / 2097152L ;
      curchr = t % 2097152L ;
      switch ( curcmd ) 
      {case 1 : 
	incr ( alignstate ) ;
	break ;
      case 2 : 
	decr ( alignstate ) ;
	break ;
      case 5 : 
	{
	  begintokenlist ( paramstack [curinput .limitfield + curchr - 1 ], 
	  0 ) ;
	  goto lab20 ;
	} 
	break ;
	default: 
	;
	break ;
      } 
    } 
  } 
  else {
      
    endtokenlist () ;
    goto lab20 ;
  } 
  if ( curcmd <= 5 ) {
      
    if ( curcmd >= 4 ) {
	
      if ( alignstate == 0 ) 
      {
	if ( ( scannerstatus == 4 ) || ( curalign == -268435455L ) ) 
	fatalerror ( 65925L ) ;
	curcmd = mem [curalign + 5 ].hh .v.LH ;
	mem [curalign + 5 ].hh .v.LH = curchr ;
	if ( curcmd == 63 ) 
	begintokenlist ( memtop - 10 , 2 ) ;
	else begintokenlist ( mem [curalign + 2 ].cint , 2 ) ;
	alignstate = 1000000L ;
	goto lab20 ;
      } 
    } 
  } 
} 
void 
firmuptheline ( void ) 
{
  firmuptheline_regmem 
  integer k  ;
  curinput .limitfield = last ;
  if ( eqtb [7892292L ].cint > 0 ) {
      
    if ( interaction > 1 ) 
    {
      ;
      println () ;
      if ( curinput .startfield < curinput .limitfield ) 
      {register integer for_end; k = curinput .startfield ;for_end = 
      curinput .limitfield - 1 ; if ( k <= for_end) do 
	print ( buffer [k ]) ;
      while ( k++ < for_end ) ;} 
      first = curinput .limitfield ;
      {
	;
	print ( 65951L ) ;
	terminput () ;
      } 
      if ( last > first ) 
      {
	{register integer for_end; k = first ;for_end = last - 1 ; if ( k <= 
	for_end) do 
	  buffer [k + curinput .startfield - first ]= buffer [k ];
	while ( k++ < for_end ) ;} 
	curinput .limitfield = curinput .startfield + last - first ;
      } 
    } 
  } 
} 
void 
gettoken ( void ) 
{
  gettoken_regmem 
  nonewcontrolsequence = false ;
  getnext () ;
  nonewcontrolsequence = true ;
  if ( curcs == 0 ) 
  curtok = ( curcmd * 2097152L ) + curchr ;
  else curtok = 33554431L + curcs ;
} 
void 
macrocall ( void ) 
{
  /* 10 22 30 31 40 */ macrocall_regmem 
  halfword r  ;
  halfword p  ;
  halfword q  ;
  halfword s  ;
  halfword t  ;
  halfword u, v  ;
  halfword rbraceptr  ;
  smallnumber n  ;
  halfword unbalance  ;
  halfword m  ;
  halfword refcount  ;
  smallnumber savescannerstatus  ;
  halfword savewarningindex  ;
  UTF16code matchchr  ;
  savescannerstatus = scannerstatus ;
  savewarningindex = warningindex ;
  warningindex = curcs ;
  refcount = curchr ;
  r = mem [refcount ].hh .v.RH ;
  n = 0 ;
  if ( eqtb [7892294L ].cint > 0 ) 
  {
    begindiagnostic () ;
    if ( eqtb [7892322L ].cint > 0 ) {
	
      if ( inputptr < eqtb [7892322L ].cint ) 
      {
	v = inputptr ;
	println () ;
	printchar ( 126 ) ;
	while ( v > 0 ) {
	    
	  printchar ( 46 ) ;
	  decr ( v ) ;
	} 
	printcs ( warningindex ) ;
	tokenshow ( refcount ) ;
      } 
      else {
	  
	printchar ( 126 ) ;
	printchar ( 126 ) ;
	printcs ( warningindex ) ;
      } 
    } 
    else {
	
      println () ;
      printcs ( warningindex ) ;
      tokenshow ( refcount ) ;
    } 
    enddiagnostic ( false ) ;
  } 
  if ( mem [r ].hh .v.LH == 29360129L ) 
  r = mem [r ].hh .v.RH ;
  if ( mem [r ].hh .v.LH != 29360128L ) 
  {
    scannerstatus = 3 ;
    unbalance = 0 ;
    longstate = eqtb [curcs ].hh.b0 ;
    if ( longstate >= 116 ) 
    longstate = longstate - 2 ;
    do {
	mem [memtop - 3 ].hh .v.RH = -268435455L ;
      if ( ( mem [r ].hh .v.LH >= 29360128L ) || ( mem [r ].hh .v.LH < 
      27262976L ) ) 
      s = -268435455L ;
      else {
	  
	matchchr = mem [r ].hh .v.LH - 27262976L ;
	s = mem [r ].hh .v.RH ;
	r = s ;
	p = memtop - 3 ;
	m = 0 ;
      } 
      lab22: gettoken () ;
      if ( curtok == mem [r ].hh .v.LH ) 
      {
	r = mem [r ].hh .v.RH ;
	if ( ( mem [r ].hh .v.LH >= 27262976L ) && ( mem [r ].hh .v.LH <= 
	29360128L ) ) 
	{
	  if ( curtok < 4194304L ) 
	  decr ( alignstate ) ;
	  goto lab40 ;
	} 
	else goto lab22 ;
      } 
      if ( s != r ) {
	  
	if ( s == -268435455L ) 
	{
	  {
	    if ( interaction == 3 ) 
	    ;
	    if ( filelineerrorstylep ) 
	    printfileline () ;
	    else printnl ( 65544L ) ;
	    print ( 65984L ) ;
	  } 
	  sprintcs ( warningindex ) ;
	  print ( 65985L ) ;
	  {
	    helpptr = 4 ;
	    helpline [3 ]= 65986L ;
	    helpline [2 ]= 65987L ;
	    helpline [1 ]= 65988L ;
	    helpline [0 ]= 65989L ;
	  } 
	  error () ;
	  goto lab10 ;
	} 
	else {
	    
	  t = s ;
	  do {
	      { 
	      q = getavail () ;
	      mem [p ].hh .v.RH = q ;
	      mem [q ].hh .v.LH = mem [t ].hh .v.LH ;
	      p = q ;
	    } 
	    incr ( m ) ;
	    u = mem [t ].hh .v.RH ;
	    v = s ;
	    while ( true ) {
		
	      if ( u == r ) {
		  
		if ( curtok != mem [v ].hh .v.LH ) 
		goto lab30 ;
		else {
		    
		  r = mem [v ].hh .v.RH ;
		  goto lab22 ;
		} 
	      } 
	      if ( mem [u ].hh .v.LH != mem [v ].hh .v.LH ) 
	      goto lab30 ;
	      u = mem [u ].hh .v.RH ;
	      v = mem [v ].hh .v.RH ;
	    } 
	    lab30: t = mem [t ].hh .v.RH ;
	  } while ( ! ( t == r ) ) ;
	  r = s ;
	} 
      } 
      if ( curtok == partoken ) {
	  
	if ( longstate != 115 ) 
	{
	  if ( longstate == 114 ) 
	  {
	    runaway () ;
	    {
	      if ( interaction == 3 ) 
	      ;
	      if ( filelineerrorstylep ) 
	      printfileline () ;
	      else printnl ( 65544L ) ;
	      print ( 65979L ) ;
	    } 
	    sprintcs ( warningindex ) ;
	    print ( 65980L ) ;
	    {
	      helpptr = 3 ;
	      helpline [2 ]= 65981L ;
	      helpline [1 ]= 65982L ;
	      helpline [0 ]= 65983L ;
	    } 
	    backerror () ;
	  } 
	  pstack [n ]= mem [memtop - 3 ].hh .v.RH ;
	  alignstate = alignstate - unbalance ;
	  {register integer for_end; m = 0 ;for_end = n ; if ( m <= for_end) 
	  do 
	    flushlist ( pstack [m ]) ;
	  while ( m++ < for_end ) ;} 
	  goto lab10 ;
	} 
      } 
      if ( curtok < 6291456L ) {
	  
	if ( curtok < 4194304L ) 
	{
	  unbalance = 1 ;
	  while ( true ) {
	      
	    {
	      {
		q = avail ;
		if ( q == -268435455L ) 
		q = getavail () ;
		else {
		    
		  avail = mem [q ].hh .v.RH ;
		  mem [q ].hh .v.RH = -268435455L ;
	;
#ifdef STAT
		  incr ( dynused ) ;
#endif /* STAT */
		} 
	      } 
	      mem [p ].hh .v.RH = q ;
	      mem [q ].hh .v.LH = curtok ;
	      p = q ;
	    } 
	    gettoken () ;
	    if ( curtok == partoken ) {
		
	      if ( longstate != 115 ) 
	      {
		if ( longstate == 114 ) 
		{
		  runaway () ;
		  {
		    if ( interaction == 3 ) 
		    ;
		    if ( filelineerrorstylep ) 
		    printfileline () ;
		    else printnl ( 65544L ) ;
		    print ( 65979L ) ;
		  } 
		  sprintcs ( warningindex ) ;
		  print ( 65980L ) ;
		  {
		    helpptr = 3 ;
		    helpline [2 ]= 65981L ;
		    helpline [1 ]= 65982L ;
		    helpline [0 ]= 65983L ;
		  } 
		  backerror () ;
		} 
		pstack [n ]= mem [memtop - 3 ].hh .v.RH ;
		alignstate = alignstate - unbalance ;
		{register integer for_end; m = 0 ;for_end = n ; if ( m <= 
		for_end) do 
		  flushlist ( pstack [m ]) ;
		while ( m++ < for_end ) ;} 
		goto lab10 ;
	      } 
	    } 
	    if ( curtok < 6291456L ) {
		
	      if ( curtok < 4194304L ) 
	      incr ( unbalance ) ;
	      else {
		  
		decr ( unbalance ) ;
		if ( unbalance == 0 ) 
		goto lab31 ;
	      } 
	    } 
	  } 
	  lab31: rbraceptr = p ;
	  {
	    q = getavail () ;
	    mem [p ].hh .v.RH = q ;
	    mem [q ].hh .v.LH = curtok ;
	    p = q ;
	  } 
	} 
	else {
	    
	  backinput () ;
	  {
	    if ( interaction == 3 ) 
	    ;
	    if ( filelineerrorstylep ) 
	    printfileline () ;
	    else printnl ( 65544L ) ;
	    print ( 65971L ) ;
	  } 
	  sprintcs ( warningindex ) ;
	  print ( 65972L ) ;
	  {
	    helpptr = 6 ;
	    helpline [5 ]= 65973L ;
	    helpline [4 ]= 65974L ;
	    helpline [3 ]= 65975L ;
	    helpline [2 ]= 65976L ;
	    helpline [1 ]= 65977L ;
	    helpline [0 ]= 65978L ;
	  } 
	  incr ( alignstate ) ;
	  longstate = 114 ;
	  curtok = partoken ;
	  inserror () ;
	  goto lab22 ;
	} 
      } 
      else {
	  
	if ( curtok == 20971552L ) {
	    
	  if ( mem [r ].hh .v.LH <= 29360128L ) {
	      
	    if ( mem [r ].hh .v.LH >= 27262976L ) 
	    goto lab22 ;
	  } 
	} 
	{
	  q = getavail () ;
	  mem [p ].hh .v.RH = q ;
	  mem [q ].hh .v.LH = curtok ;
	  p = q ;
	} 
      } 
      incr ( m ) ;
      if ( mem [r ].hh .v.LH > 29360128L ) 
      goto lab22 ;
      if ( mem [r ].hh .v.LH < 27262976L ) 
      goto lab22 ;
      lab40: if ( s != -268435455L ) 
      {
	if ( ( m == 1 ) && ( mem [p ].hh .v.LH < 6291456L ) ) 
	{
	  mem [rbraceptr ].hh .v.RH = -268435455L ;
	  {
	    mem [p ].hh .v.RH = avail ;
	    avail = p ;
	;
#ifdef STAT
	    decr ( dynused ) ;
#endif /* STAT */
	  } 
	  p = mem [memtop - 3 ].hh .v.RH ;
	  pstack [n ]= mem [p ].hh .v.RH ;
	  {
	    mem [p ].hh .v.RH = avail ;
	    avail = p ;
	;
#ifdef STAT
	    decr ( dynused ) ;
#endif /* STAT */
	  } 
	} 
	else pstack [n ]= mem [memtop - 3 ].hh .v.RH ;
	incr ( n ) ;
	if ( eqtb [7892294L ].cint > 0 ) {
	    
	  if ( ( eqtb [7892322L ].cint == 0 ) || ( inputptr < eqtb [
	  7892322L ].cint ) ) 
	  {
	    begindiagnostic () ;
	    printnl ( matchchr ) ;
	    printint ( n ) ;
	    print ( 65990L ) ;
	    showtokenlist ( pstack [n - 1 ], -268435455L , 1000 ) ;
	    enddiagnostic ( false ) ;
	  } 
	} 
      } 
    } while ( ! ( mem [r ].hh .v.LH == 29360128L ) ) ;
  } 
  while ( ( curinput .locfield == -268435455L ) && ( curinput .indexfield != 2 
  ) && ( curinput .indexfield != 7 ) ) endtokenlist () ;
  begintokenlist ( refcount , 6 ) ;
  curinput .namefield = warningindex ;
  curinput .locfield = mem [r ].hh .v.RH ;
  if ( n > 0 ) 
  {
    if ( paramptr + n > maxparamstack ) 
    {
      maxparamstack = paramptr + n ;
      if ( maxparamstack > paramsize ) 
      overflow ( 65970L , paramsize ) ;
    } 
    {register integer for_end; m = 0 ;for_end = n - 1 ; if ( m <= for_end) 
    do 
      paramstack [paramptr + m ]= pstack [m ];
    while ( m++ < for_end ) ;} 
    paramptr = paramptr + n ;
  } 
  lab10: scannerstatus = savescannerstatus ;
  warningindex = savewarningindex ;
} 
void 
insertrelax ( void ) 
{
  insertrelax_regmem 
  curtok = 33554431L + curcs ;
  backinput () ;
  curtok = 34749088L ;
  backinput () ;
  curinput .indexfield = 5 ;
} 
void 
znewindex ( quarterword i , halfword q ) 
{
  newindex_regmem 
  smallnumber k  ;
  curptr = getnode ( 33 ) ;
  mem [curptr ].hh.b0 = i ;
  mem [curptr ].hh.b1 = 0 ;
  mem [curptr ].hh .v.RH = q ;
  {register integer for_end; k = 1 ;for_end = 32 ; if ( k <= for_end) do 
    mem [curptr + k ]= sanull ;
  while ( k++ < for_end ) ;} 
} 
void 
zfindsaelement ( smallnumber t , halfword n , boolean w ) 
{
  /* 45 46 47 48 49 10 */ findsaelement_regmem 
  halfword q  ;
  smallnumber i  ;
  curptr = saroot [t ];
  {
    if ( curptr == -268435455L ) {
	
      if ( w ) 
      goto lab45 ;
      else return ;
    } 
  } 
  q = curptr ;
  i = n / 262144L ;
  if ( odd ( i ) ) 
  curptr = mem [q + ( i / 2 ) + 1 ].hh .v.RH ;
  else curptr = mem [q + ( i / 2 ) + 1 ].hh .v.LH ;
  {
    if ( curptr == -268435455L ) {
	
      if ( w ) 
      goto lab46 ;
      else return ;
    } 
  } 
  q = curptr ;
  i = ( n / 4096 ) % 64 ;
  if ( odd ( i ) ) 
  curptr = mem [q + ( i / 2 ) + 1 ].hh .v.RH ;
  else curptr = mem [q + ( i / 2 ) + 1 ].hh .v.LH ;
  {
    if ( curptr == -268435455L ) {
	
      if ( w ) 
      goto lab47 ;
      else return ;
    } 
  } 
  q = curptr ;
  i = ( n / 64 ) % 64 ;
  if ( odd ( i ) ) 
  curptr = mem [q + ( i / 2 ) + 1 ].hh .v.RH ;
  else curptr = mem [q + ( i / 2 ) + 1 ].hh .v.LH ;
  {
    if ( curptr == -268435455L ) {
	
      if ( w ) 
      goto lab48 ;
      else return ;
    } 
  } 
  q = curptr ;
  i = n % 64 ;
  if ( odd ( i ) ) 
  curptr = mem [q + ( i / 2 ) + 1 ].hh .v.RH ;
  else curptr = mem [q + ( i / 2 ) + 1 ].hh .v.LH ;
  if ( ( curptr == -268435455L ) && w ) 
  goto lab49 ;
  return ;
  lab45: newindex ( t , -268435455L ) ;
  saroot [t ]= curptr ;
  q = curptr ;
  i = n / 262144L ;
  lab46: newindex ( i , q ) ;
  {
    if ( odd ( i ) ) 
    mem [q + ( i / 2 ) + 1 ].hh .v.RH = curptr ;
    else mem [q + ( i / 2 ) + 1 ].hh .v.LH = curptr ;
    incr ( mem [q ].hh.b1 ) ;
  } 
  q = curptr ;
  i = ( n / 4096 ) % 64 ;
  lab47: newindex ( i , q ) ;
  {
    if ( odd ( i ) ) 
    mem [q + ( i / 2 ) + 1 ].hh .v.RH = curptr ;
    else mem [q + ( i / 2 ) + 1 ].hh .v.LH = curptr ;
    incr ( mem [q ].hh.b1 ) ;
  } 
  q = curptr ;
  i = ( n / 64 ) % 64 ;
  lab48: newindex ( i , q ) ;
  {
    if ( odd ( i ) ) 
    mem [q + ( i / 2 ) + 1 ].hh .v.RH = curptr ;
    else mem [q + ( i / 2 ) + 1 ].hh .v.LH = curptr ;
    incr ( mem [q ].hh.b1 ) ;
  } 
  q = curptr ;
  i = n % 64 ;
  lab49: if ( t == 7 ) 
  {
    curptr = getnode ( 4 ) ;
    mem [curptr + 1 ]= sanull ;
    mem [curptr + 2 ]= sanull ;
    mem [curptr + 3 ]= sanull ;
  } 
  else {
      
    if ( t <= 1 ) 
    {
      curptr = getnode ( 3 ) ;
      mem [curptr + 2 ].cint = 0 ;
      mem [curptr + 1 ].hh .v.RH = n ;
    } 
    else {
	
      curptr = getnode ( 2 ) ;
      if ( t <= 3 ) 
      {
	mem [curptr + 1 ].hh .v.RH = membot ;
	incr ( mem [membot ].hh .v.RH ) ;
      } 
      else mem [curptr + 1 ].hh .v.RH = -268435455L ;
    } 
    mem [curptr + 1 ].hh .v.LH = -268435455L ;
  } 
  mem [curptr ].hh.b0 = 64 * t + i ;
  mem [curptr ].hh.b1 = 1 ;
  mem [curptr ].hh .v.RH = q ;
  {
    if ( odd ( i ) ) 
    mem [q + ( i / 2 ) + 1 ].hh .v.RH = curptr ;
    else mem [q + ( i / 2 ) + 1 ].hh .v.LH = curptr ;
    incr ( mem [q ].hh.b1 ) ;
  } 
} 
void 
expand ( void ) 
{
  /* 21 */ expand_regmem 
  halfword t  ;
  boolean b  ;
  halfword p, q, r  ;
  integer j  ;
  integer cvbackup  ;
  smallnumber cvlbackup, radixbackup, cobackup  ;
  halfword backupbackup  ;
  smallnumber savescannerstatus  ;
  incr ( expanddepthcount ) ;
  if ( expanddepthcount >= expanddepth ) 
  overflow ( 65952L , expanddepth ) ;
  cvbackup = curval ;
  cvlbackup = curvallevel ;
  radixbackup = radix ;
  cobackup = curorder ;
  backupbackup = mem [memtop - 13 ].hh .v.RH ;
  lab21: if ( curcmd < 114 ) 
  {
    if ( eqtb [7892300L ].cint > 1 ) 
    showcurcmdchr () ;
    switch ( curcmd ) 
    {case 113 : 
      {
	t = curchr % 5 ;
	if ( curchr >= 5 ) 
	scanregisternum () ;
	else curval = 0 ;
	if ( curval == 0 ) 
	curptr = curmark [t ];
	else {
	    
	  findsaelement ( 7 , curval , false ) ;
	  if ( curptr != -268435455L ) {
	      
	    if ( odd ( t ) ) 
	    curptr = mem [curptr + ( t / 2 ) + 1 ].hh .v.RH ;
	    else curptr = mem [curptr + ( t / 2 ) + 1 ].hh .v.LH ;
	  } 
	} 
	if ( curptr != -268435455L ) 
	begintokenlist ( curptr , 15 ) ;
      } 
      break ;
    case 105 : 
      if ( curchr == 0 ) 
      {
	gettoken () ;
	t = curtok ;
	gettoken () ;
	if ( curcmd > 103 ) 
	expand () ;
	else backinput () ;
	curtok = t ;
	backinput () ;
      } 
      else {
	  
	gettoken () ;
	if ( ( curcmd == 108 ) && ( curchr != 16 ) ) 
	{
	  curchr = curchr + 32 ;
	  goto lab21 ;
	} 
	{
	  if ( interaction == 3 ) 
	  ;
	  if ( filelineerrorstylep ) 
	  printfileline () ;
	  else printnl ( 65544L ) ;
	  print ( 66035L ) ;
	} 
	printesc ( 66165L ) ;
	print ( 66941L ) ;
	printcmdchr ( curcmd , curchr ) ;
	printchar ( 39 ) ;
	{
	  helpptr = 1 ;
	  helpline [0 ]= 65947L ;
	} 
	backerror () ;
      } 
      break ;
    case 106 : 
      if ( curchr == 0 ) 
      {
	savescannerstatus = scannerstatus ;
	scannerstatus = 0 ;
	gettoken () ;
	scannerstatus = savescannerstatus ;
	t = curtok ;
	backinput () ;
	if ( ( t >= 33554431L ) && ( t != 34749089L ) ) 
	{
	  p = getavail () ;
	  mem [p ].hh .v.LH = 34749090L ;
	  mem [p ].hh .v.RH = curinput .locfield ;
	  curinput .startfield = p ;
	  curinput .locfield = p ;
	} 
      } 
      else {
	  
	savescannerstatus = scannerstatus ;
	scannerstatus = 0 ;
	gettoken () ;
	scannerstatus = savescannerstatus ;
	if ( curcs < 1179650L ) 
	curcs = primlookup ( curcs - 1114113L ) ;
	else curcs = primlookup ( hash [curcs ].v.RH ) ;
	if ( curcs != 0 ) 
	{
	  t = eqtb [1194662L + curcs ].hh.b0 ;
	  if ( t > 103 ) 
	  {
	    curcmd = t ;
	    curchr = eqtb [1194662L + curcs ].hh .v.RH ;
	    curtok = ( curcmd * 2097152L ) + curchr ;
	    curcs = 0 ;
	    goto lab21 ;
	  } 
	  else {
	      
	    backinput () ;
	    p = getavail () ;
	    mem [p ].hh .v.LH = 34749092L ;
	    mem [p ].hh .v.RH = curinput .locfield ;
	    curinput .locfield = p ;
	    curinput .startfield = p ;
	  } 
	} 
      } 
      break ;
    case 110 : 
      {
	r = getavail () ;
	p = r ;
	b = isincsname ;
	isincsname = true ;
	do {
	    getxtoken () ;
	  if ( curcs == 0 ) 
	  {
	    q = getavail () ;
	    mem [p ].hh .v.RH = q ;
	    mem [q ].hh .v.LH = curtok ;
	    p = q ;
	  } 
	} while ( ! ( curcs != 0 ) ) ;
	if ( curcmd != 67 ) 
	{
	  {
	    if ( interaction == 3 ) 
	    ;
	    if ( filelineerrorstylep ) 
	    printfileline () ;
	    else printnl ( 65544L ) ;
	    print ( 65959L ) ;
	  } 
	  printesc ( 65819L ) ;
	  print ( 65960L ) ;
	  {
	    helpptr = 2 ;
	    helpline [1 ]= 65961L ;
	    helpline [0 ]= 65962L ;
	  } 
	  backerror () ;
	} 
	isincsname = b ;
	j = first ;
	p = mem [r ].hh .v.RH ;
	while ( p != -268435455L ) {
	    
	  if ( j >= maxbufstack ) 
	  {
	    maxbufstack = j + 1 ;
	    if ( maxbufstack == bufsize ) 
	    overflow ( 65538L , bufsize ) ;
	  } 
	  buffer [j ]= mem [p ].hh .v.LH % 2097152L ;
	  incr ( j ) ;
	  p = mem [p ].hh .v.RH ;
	} 
	if ( ( j > first + 1 ) || ( buffer [first ]> 65535L ) ) 
	{
	  nonewcontrolsequence = false ;
	  curcs = idlookup ( first , j - first ) ;
	  nonewcontrolsequence = true ;
	} 
	else if ( j == first ) 
	curcs = 1179649L ;
	else curcs = 1114113L + buffer [first ];
	flushlist ( r ) ;
	if ( eqtb [curcs ].hh.b0 == 104 ) 
	{
	  eqdefine ( curcs , 0 , 1114112L ) ;
	} 
	curtok = curcs + 33554431L ;
	backinput () ;
      } 
      break ;
    case 111 : 
      convtoks () ;
      break ;
    case 112 : 
      insthetoks () ;
      break ;
    case 108 : 
      conditional () ;
      break ;
    case 109 : 
      {
	if ( eqtb [7892327L ].cint > 0 ) {
	    
	  if ( eqtb [7892300L ].cint <= 1 ) 
	  showcurcmdchr () ;
	} 
	if ( curchr > iflimit ) {
	    
	  if ( iflimit == 1 ) 
	  insertrelax () ;
	  else {
	      
	    {
	      if ( interaction == 3 ) 
	      ;
	      if ( filelineerrorstylep ) 
	      printfileline () ;
	      else printnl ( 65544L ) ;
	      print ( 66169L ) ;
	    } 
	    printcmdchr ( 109 , curchr ) ;
	    {
	      helpptr = 1 ;
	      helpline [0 ]= 66170L ;
	    } 
	    error () ;
	  } 
	} 
	else {
	    
	  while ( curchr != 2 ) passtext () ;
	  {
	    if ( ifstack [inopen ]== condptr ) 
	    ifwarning () ;
	    p = condptr ;
	    ifline = mem [p + 1 ].cint ;
	    curif = mem [p ].hh.b1 ;
	    iflimit = mem [p ].hh.b0 ;
	    condptr = mem [p ].hh .v.RH ;
	    freenode ( p , 2 ) ;
	  } 
	} 
      } 
      break ;
    case 107 : 
      if ( curchr == 1 ) 
      forceeof = true ;
      else if ( curchr == 2 ) 
      pseudostart () ;
      else if ( nameinprogress ) 
      insertrelax () ;
      else startinput () ;
      break ;
      default: 
      {
	{
	  if ( interaction == 3 ) 
	  ;
	  if ( filelineerrorstylep ) 
	  printfileline () ;
	  else printnl ( 65544L ) ;
	  print ( 65953L ) ;
	} 
	{
	  helpptr = 5 ;
	  helpline [4 ]= 65954L ;
	  helpline [3 ]= 65955L ;
	  helpline [2 ]= 65956L ;
	  helpline [1 ]= 65957L ;
	  helpline [0 ]= 65958L ;
	} 
	error () ;
      } 
      break ;
    } 
  } 
  else if ( curcmd < 118 ) 
  macrocall () ;
  else {
      
    curtok = 34749087L ;
    backinput () ;
  } 
  curval = cvbackup ;
  curvallevel = cvlbackup ;
  radix = radixbackup ;
  curorder = cobackup ;
  mem [memtop - 13 ].hh .v.RH = backupbackup ;
  decr ( expanddepthcount ) ;
} 
void 
getxtoken ( void ) 
{
  /* 20 30 */ getxtoken_regmem 
  lab20: getnext () ;
  if ( curcmd <= 103 ) 
  goto lab30 ;
  if ( curcmd >= 114 ) {
      
    if ( curcmd < 118 ) 
    macrocall () ;
    else {
	
      curcs = 1194656L ;
      curcmd = 9 ;
      goto lab30 ;
    } 
  } 
  else expand () ;
  goto lab20 ;
  lab30: if ( curcs == 0 ) 
  curtok = ( curcmd * 2097152L ) + curchr ;
  else curtok = 33554431L + curcs ;
} 
void 
xtoken ( void ) 
{
  xtoken_regmem 
  while ( curcmd > 103 ) {
      
    expand () ;
    getnext () ;
  } 
  if ( curcs == 0 ) 
  curtok = ( curcmd * 2097152L ) + curchr ;
  else curtok = 33554431L + curcs ;
} 
void 
scanleftbrace ( void ) 
{
  scanleftbrace_regmem 
  do {
      getxtoken () ;
  } while ( ! ( ( curcmd != 10 ) && ( curcmd != 0 ) ) ) ;
  if ( curcmd != 1 ) 
  {
    {
      if ( interaction == 3 ) 
      ;
      if ( filelineerrorstylep ) 
      printfileline () ;
      else printnl ( 65544L ) ;
      print ( 65991L ) ;
    } 
    {
      helpptr = 4 ;
      helpline [3 ]= 65992L ;
      helpline [2 ]= 65993L ;
      helpline [1 ]= 65994L ;
      helpline [0 ]= 65995L ;
    } 
    backerror () ;
    curtok = 2097275L ;
    curcmd = 1 ;
    curchr = 123 ;
    incr ( alignstate ) ;
  } 
} 
void 
scanoptionalequals ( void ) 
{
  scanoptionalequals_regmem 
  do {
      getxtoken () ;
  } while ( ! ( curcmd != 10 ) ) ;
  if ( curtok != 25165885L ) 
  backinput () ;
} 
boolean 
zscankeyword ( strnumber s ) 
{
  /* 10 */ register boolean Result; scankeyword_regmem 
  halfword p  ;
  halfword q  ;
  poolpointer k  ;
  halfword savecurcs  ;
  p = memtop - 13 ;
  mem [p ].hh .v.RH = -268435455L ;
  if ( s < 65536L ) 
  {
    while ( true ) {
	
      getxtoken () ;
      if ( ( curcs == 0 ) && ( ( curchr == s ) || ( curchr == s - 32 ) ) ) 
      {
	{
	  q = getavail () ;
	  mem [p ].hh .v.RH = q ;
	  mem [q ].hh .v.LH = curtok ;
	  p = q ;
	} 
	flushlist ( mem [memtop - 13 ].hh .v.RH ) ;
	Result = true ;
	return Result ;
      } 
      else if ( ( curcmd != 10 ) || ( p != memtop - 13 ) ) 
      {
	backinput () ;
	if ( p != memtop - 13 ) 
	begintokenlist ( mem [memtop - 13 ].hh .v.RH , 3 ) ;
	Result = false ;
	return Result ;
      } 
    } 
  } 
  k = strstart [( s ) - 65536L ];
  savecurcs = curcs ;
  while ( k < strstart [( s + 1 ) - 65536L ]) {
      
    getxtoken () ;
    if ( ( curcs == 0 ) && ( ( curchr == strpool [k ]) || ( curchr == 
    strpool [k ]- 32 ) ) ) 
    {
      {
	q = getavail () ;
	mem [p ].hh .v.RH = q ;
	mem [q ].hh .v.LH = curtok ;
	p = q ;
      } 
      incr ( k ) ;
    } 
    else if ( ( curcmd != 10 ) || ( p != memtop - 13 ) ) 
    {
      backinput () ;
      if ( p != memtop - 13 ) 
      begintokenlist ( mem [memtop - 13 ].hh .v.RH , 3 ) ;
      curcs = savecurcs ;
      Result = false ;
      return Result ;
    } 
  } 
  flushlist ( mem [memtop - 13 ].hh .v.RH ) ;
  Result = true ;
  return Result ;
} 
void 
muerror ( void ) 
{
  muerror_regmem 
  {
    if ( interaction == 3 ) 
    ;
    if ( filelineerrorstylep ) 
    printfileline () ;
    else printnl ( 65544L ) ;
    print ( 65996L ) ;
  } 
  {
    helpptr = 1 ;
    helpline [0 ]= 65997L ;
  } 
  error () ;
} 
void 
zscanglyphnumber ( internalfontnumber f ) 
{
  scanglyphnumber_regmem 
  if ( scankeyword ( 47 ) ) 
  {
    scanandpackname () ;
    {
      curval = mapglyphtoindex ( f ) ;
      curvallevel = 0 ;
    } 
  } 
  else if ( scankeyword ( 117 ) ) 
  {
    scancharnum () ;
    {
      curval = mapchartoglyph ( f , curval ) ;
      curvallevel = 0 ;
    } 
  } 
  else scanint () ;
} 
void 
scancharclass ( void ) 
{
  scancharclass_regmem 
  scanint () ;
  if ( ( curval < 0 ) || ( curval > 4096 ) ) 
  {
    {
      if ( interaction == 3 ) 
      ;
      if ( filelineerrorstylep ) 
      printfileline () ;
      else printnl ( 65544L ) ;
      print ( 66037L ) ;
    } 
    {
      helpptr = 2 ;
      helpline [1 ]= 66038L ;
      helpline [0 ]= 66006L ;
    } 
    interror ( curval ) ;
    curval = 0 ;
  } 
} 
void 
scancharclassnotignored ( void ) 
{
  scancharclassnotignored_regmem 
  scanint () ;
  if ( ( curval < 0 ) || ( curval > 4096 ) ) 
  {
    {
      if ( interaction == 3 ) 
      ;
      if ( filelineerrorstylep ) 
      printfileline () ;
      else printnl ( 65544L ) ;
      print ( 66037L ) ;
    } 
    {
      helpptr = 2 ;
      helpline [1 ]= 66039L ;
      helpline [0 ]= 66006L ;
    } 
    interror ( curval ) ;
    curval = 0 ;
  } 
} 
void 
scaneightbitint ( void ) 
{
  scaneightbitint_regmem 
  scanint () ;
  if ( ( curval < 0 ) || ( curval > 255 ) ) 
  {
    {
      if ( interaction == 3 ) 
      ;
      if ( filelineerrorstylep ) 
      printfileline () ;
      else printnl ( 65544L ) ;
      print ( 66040L ) ;
    } 
    {
      helpptr = 2 ;
      helpline [1 ]= 66041L ;
      helpline [0 ]= 66006L ;
    } 
    interror ( curval ) ;
    curval = 0 ;
  } 
} 
void 
scanusvnum ( void ) 
{
  scanusvnum_regmem 
  scanint () ;
  if ( ( curval < 0 ) || ( curval > 1114111L ) ) 
  {
    {
      if ( interaction == 3 ) 
      ;
      if ( filelineerrorstylep ) 
      printfileline () ;
      else printnl ( 65544L ) ;
      print ( 66042L ) ;
    } 
    {
      helpptr = 2 ;
      helpline [1 ]= 66043L ;
      helpline [0 ]= 66006L ;
    } 
    interror ( curval ) ;
    curval = 0 ;
  } 
} 
void 
scancharnum ( void ) 
{
  scancharnum_regmem 
  scanint () ;
  if ( ( curval < 0 ) || ( curval > 65535L ) ) 
  {
    {
      if ( interaction == 3 ) 
      ;
      if ( filelineerrorstylep ) 
      printfileline () ;
      else printnl ( 65544L ) ;
      print ( 66042L ) ;
    } 
    {
      helpptr = 2 ;
      helpline [1 ]= 66044L ;
      helpline [0 ]= 66006L ;
    } 
    interror ( curval ) ;
    curval = 0 ;
  } 
} 
void 
scanxetexmathcharint ( void ) 
{
  scanxetexmathcharint_regmem 
  scanint () ;
  if ( mathcharfield ( curval ) == 2097151L ) 
  {
    if ( curval != 2097151L ) 
    {
      {
	if ( interaction == 3 ) 
	;
	if ( filelineerrorstylep ) 
	printfileline () ;
	else printnl ( 65544L ) ;
	print ( 66045L ) ;
      } 
      {
	helpptr = 2 ;
	helpline [1 ]= 66046L ;
	helpline [0 ]= 66047L ;
      } 
      interror ( curval ) ;
      curval = 2097151L ;
    } 
  } 
  else if ( mathcharfield ( curval ) > 1114111L ) 
  {
    {
      if ( interaction == 3 ) 
      ;
      if ( filelineerrorstylep ) 
      printfileline () ;
      else printnl ( 65544L ) ;
      print ( 66048L ) ;
    } 
    {
      helpptr = 2 ;
      helpline [1 ]= 66049L ;
      helpline [0 ]= 66006L ;
    } 
    interror ( curval ) ;
    curval = 0 ;
  } 
} 
void 
scanmathclassint ( void ) 
{
  scanmathclassint_regmem 
  scanint () ;
  if ( ( curval < 0 ) || ( curval > 7 ) ) 
  {
    {
      if ( interaction == 3 ) 
      ;
      if ( filelineerrorstylep ) 
      printfileline () ;
      else printnl ( 65544L ) ;
      print ( 66050L ) ;
    } 
    {
      helpptr = 2 ;
      helpline [1 ]= 66051L ;
      helpline [0 ]= 66006L ;
    } 
    interror ( curval ) ;
    curval = 0 ;
  } 
} 
void 
scanmathfamint ( void ) 
{
  scanmathfamint_regmem 
  scanint () ;
  if ( ( curval < 0 ) || ( curval > 255 ) ) 
  {
    {
      if ( interaction == 3 ) 
      ;
      if ( filelineerrorstylep ) 
      printfileline () ;
      else printnl ( 65544L ) ;
      print ( 66052L ) ;
    } 
    {
      helpptr = 2 ;
      helpline [1 ]= 66053L ;
      helpline [0 ]= 66006L ;
    } 
    interror ( curval ) ;
    curval = 0 ;
  } 
} 
void 
scanfourbitint ( void ) 
{
  scanfourbitint_regmem 
  scanint () ;
  if ( ( curval < 0 ) || ( curval > 15 ) ) 
  {
    {
      if ( interaction == 3 ) 
      ;
      if ( filelineerrorstylep ) 
      printfileline () ;
      else printnl ( 65544L ) ;
      print ( 66054L ) ;
    } 
    {
      helpptr = 2 ;
      helpline [1 ]= 66055L ;
      helpline [0 ]= 66006L ;
    } 
    interror ( curval ) ;
    curval = 0 ;
  } 
} 
void 
scanfifteenbitint ( void ) 
{
  scanfifteenbitint_regmem 
  scanint () ;
  if ( ( curval < 0 ) || ( curval > 32767 ) ) 
  {
    {
      if ( interaction == 3 ) 
      ;
      if ( filelineerrorstylep ) 
      printfileline () ;
      else printnl ( 65544L ) ;
      print ( 66056L ) ;
    } 
    {
      helpptr = 2 ;
      helpline [1 ]= 66057L ;
      helpline [0 ]= 66006L ;
    } 
    interror ( curval ) ;
    curval = 0 ;
  } 
} 
void 
scandelimiterint ( void ) 
{
  scandelimiterint_regmem 
  scanint () ;
  if ( ( curval < 0 ) || ( curval > 134217727L ) ) 
  {
    {
      if ( interaction == 3 ) 
      ;
      if ( filelineerrorstylep ) 
      printfileline () ;
      else printnl ( 65544L ) ;
      print ( 66058L ) ;
    } 
    {
      helpptr = 2 ;
      helpline [1 ]= 66059L ;
      helpline [0 ]= 66006L ;
    } 
    interror ( curval ) ;
    curval = 0 ;
  } 
} 
void 
scanregisternum ( void ) 
{
  scanregisternum_regmem 
  scanint () ;
  if ( ( curval < 0 ) || ( curval > maxregnum ) ) 
  {
    {
      if ( interaction == 3 ) 
      ;
      if ( filelineerrorstylep ) 
      printfileline () ;
      else printnl ( 65544L ) ;
      print ( 66040L ) ;
    } 
    {
      helpptr = 2 ;
      helpline [1 ]= maxreghelpline ;
      helpline [0 ]= 66006L ;
    } 
    interror ( curval ) ;
    curval = 0 ;
  } 
} 
void 
scanfourbitintor18 ( void ) 
{
  scanfourbitintor18_regmem 
  scanint () ;
  if ( ( curval < 0 ) || ( ( curval > 15 ) && ( curval != 18 ) ) ) 
  {
    {
      if ( interaction == 3 ) 
      ;
      if ( filelineerrorstylep ) 
      printfileline () ;
      else printnl ( 65544L ) ;
      print ( 66054L ) ;
    } 
    {
      helpptr = 2 ;
      helpline [1 ]= 66055L ;
      helpline [0 ]= 66006L ;
    } 
    interror ( curval ) ;
    curval = 0 ;
  } 
} 
void 
getxorprotected ( void ) 
{
  /* 10 */ getxorprotected_regmem 
  while ( true ) {
      
    gettoken () ;
    if ( curcmd <= 103 ) 
    return ;
    if ( ( curcmd >= 114 ) && ( curcmd < 118 ) ) {
	
      if ( mem [mem [curchr ].hh .v.RH ].hh .v.LH == 29360129L ) 
      return ;
    } 
    expand () ;
  } 
} 
integer 
zeffectivechar ( boolean errp , internalfontnumber f , quarterword c ) 
{
  /* 40 */ register integer Result; effectivechar_regmem 
  integer basec  ;
  integer result  ;
  if ( ( ! xtxligaturepresent ) && ( fontmapping [f ]!= nil ) ) 
  c = applytfmfontmapping ( fontmapping [f ], c ) ;
  xtxligaturepresent = false ;
  result = c ;
  if ( ! mltexenabledp ) 
  goto lab40 ;
  if ( fontec [f ]>= c ) {
      
    if ( fontbc [f ]<= c ) {
	
      if ( ( fontinfo [charbase [f ]+ c ].qqqq .b0 > 0 ) ) 
      goto lab40 ;
    } 
  } 
  if ( c >= eqtb [7892319L ].cint ) {
      
    if ( c <= eqtb [7892320L ].cint ) {
	
      if ( ( eqtb [6778152L + c ].hh .v.RH > 0 ) ) 
      {
	basec = ( eqtb [6778152L + c ].hh .v.RH % 256 ) ;
	result = basec ;
	if ( ! errp ) 
	goto lab40 ;
	if ( fontec [f ]>= basec ) {
	    
	  if ( fontbc [f ]<= basec ) {
	      
	    if ( ( fontinfo [charbase [f ]+ basec ].qqqq .b0 > 0 ) ) 
	    goto lab40 ;
	  } 
	} 
      } 
    } 
  } 
  if ( errp ) 
  {
    begindiagnostic () ;
    printnl ( 66225L ) ;
    print ( 66975L ) ;
    print ( c ) ;
    print ( 66226L ) ;
    print ( fontname [f ]) ;
    printchar ( 33 ) ;
    enddiagnostic ( false ) ;
    result = fontbc [f ];
  } 
  lab40: Result = result ;
  return Result ;
} 
void 
scanfontident ( void ) 
{
  scanfontident_regmem 
  internalfontnumber f  ;
  halfword m  ;
  do {
      getxtoken () ;
  } while ( ! ( curcmd != 10 ) ) ;
  if ( curcmd == 90 ) 
  f = eqtb [1206823L ].hh .v.RH ;
  else if ( curcmd == 89 ) 
  f = curchr ;
  else if ( curcmd == 88 ) 
  {
    m = curchr ;
    scanmathfamint () ;
    f = eqtb [m + curval ].hh .v.RH ;
  } 
  else {
      
    {
      if ( interaction == 3 ) 
      ;
      if ( filelineerrorstylep ) 
      printfileline () ;
      else printnl ( 65544L ) ;
      print ( 66216L ) ;
    } 
    {
      helpptr = 2 ;
      helpline [1 ]= 66217L ;
      helpline [0 ]= 66218L ;
    } 
    backerror () ;
    f = 0 ;
  } 
  curval = f ;
} 
void 
zfindfontdimen ( boolean writing ) 
{
  findfontdimen_regmem 
  internalfontnumber f  ;
  integer n  ;
  scanint () ;
  n = curval ;
  scanfontident () ;
  f = curval ;
  if ( n <= 0 ) 
  curval = fmemptr ;
  else {
      
    if ( writing && ( n <= 4 ) && ( n >= 2 ) && ( fontglue [f ]!= 
    -268435455L ) ) 
    {
      deleteglueref ( fontglue [f ]) ;
      fontglue [f ]= -268435455L ;
    } 
    if ( n > fontparams [f ]) {
	
      if ( f < fontptr ) 
      curval = fmemptr ;
      else {
	  
	do {
	    if ( fmemptr == fontmemsize ) 
	  overflow ( 66223L , fontmemsize ) ;
	  fontinfo [fmemptr ].cint = 0 ;
	  incr ( fmemptr ) ;
	  incr ( fontparams [f ]) ;
	} while ( ! ( n == fontparams [f ]) ) ;
	curval = fmemptr - 1 ;
      } 
    } 
    else curval = n + parambase [f ];
  } 
  if ( curval == fmemptr ) 
  {
    {
      if ( interaction == 3 ) 
      ;
      if ( filelineerrorstylep ) 
      printfileline () ;
      else printnl ( 65544L ) ;
      print ( 66200L ) ;
    } 
    printesc ( hash [1196762L + f ].v.RH ) ;
    print ( 66219L ) ;
    printint ( fontparams [f ]) ;
    print ( 66220L ) ;
    {
      helpptr = 2 ;
      helpline [1 ]= 66221L ;
      helpline [0 ]= 66222L ;
    } 
    error () ;
  } 
} 
void 
zscansomethinginternal ( smallnumber level , boolean negative ) 
{
  /* 10 20 */ scansomethinginternal_regmem 
  halfword m  ;
  integer n, k, kk  ;
  halfword q, r  ;
  halfword tx  ;
  fourquarters i  ;
  integer p  ;
  lab20: m = curchr ;
  switch ( curcmd ) 
  {case 86 : 
    {
      scanusvnum () ;
      if ( m == 5664040L ) 
      {
	curval1 = eqtb [5664040L + curval ].hh .v.RH ;
	if ( mathcharfield ( curval1 ) == 2097151L ) 
	curval1 = 32768L ;
	else if ( ( mathclassfield ( curval1 ) > 7 ) || ( mathfamfield ( 
	curval1 ) > 15 ) || ( mathcharfield ( curval1 ) > 255 ) ) 
	{
	  {
	    if ( interaction == 3 ) 
	    ;
	    if ( filelineerrorstylep ) 
	    printfileline () ;
	    else printnl ( 65544L ) ;
	    print ( 66004L ) ;
	  } 
	  {
	    helpptr = 2 ;
	    helpline [1 ]= 66005L ;
	    helpline [0 ]= 66006L ;
	  } 
	  interror ( curval1 ) ;
	  curval1 = 0 ;
	} 
	curval1 = ( mathclassfield ( curval1 ) * 4096 ) + ( mathfamfield ( 
	curval1 ) * 256 ) + mathcharfield ( curval1 ) ;
	{
	  curval = curval1 ;
	  curvallevel = 0 ;
	} 
      } 
      else if ( m == 7892608L ) 
      {
	curval1 = eqtb [7892608L + curval ].cint ;
	if ( curval1 >= 1073741824L ) 
	{
	  {
	    if ( interaction == 3 ) 
	    ;
	    if ( filelineerrorstylep ) 
	    printfileline () ;
	    else printnl ( 65544L ) ;
	    print ( 66007L ) ;
	  } 
	  {
	    helpptr = 2 ;
	    helpline [1 ]= 66008L ;
	    helpline [0 ]= 66006L ;
	  } 
	  error () ;
	  {
	    curval = 0 ;
	    curvallevel = 0 ;
	  } 
	} 
	else {
	    
	  {
	    curval = curval1 ;
	    curvallevel = 0 ;
	  } 
	} 
      } 
      else if ( m < 4549928L ) 
      {
	curval = eqtb [m + curval ].hh .v.RH ;
	curvallevel = 0 ;
      } 
      else if ( m < 5664040L ) 
      {
	curval = eqtb [m + curval ].hh .v.RH % 65536L ;
	curvallevel = 0 ;
      } 
      else {
	  
	curval = eqtb [m + curval ].cint ;
	curvallevel = 0 ;
      } 
    } 
    break ;
  case 87 : 
    {
      scanusvnum () ;
      if ( m == 4549928L ) 
      {
	{
	  curval = eqtb [4549928L + curval ].hh .v.RH / 65536L ;
	  curvallevel = 0 ;
	} 
      } 
      else if ( m == 5664040L ) 
      {
	{
	  curval = eqtb [5664040L + curval ].hh .v.RH ;
	  curvallevel = 0 ;
	} 
      } 
      else if ( m == 5664041L ) 
      {
	{
	  if ( interaction == 3 ) 
	  ;
	  if ( filelineerrorstylep ) 
	  printfileline () ;
	  else printnl ( 65544L ) ;
	  print ( 65998L ) ;
	} 
	{
	  helpptr = 2 ;
	  helpline [1 ]= 65999L ;
	  helpline [0 ]= 66000L ;
	} 
	error () ;
	{
	  curval = 0 ;
	  curvallevel = 0 ;
	} 
      } 
      else if ( m == 7892608L ) 
      {
	{
	  curval = eqtb [7892608L + curval ].cint ;
	  curvallevel = 0 ;
	} 
      } 
      else {
	  
	{
	  if ( interaction == 3 ) 
	  ;
	  if ( filelineerrorstylep ) 
	  printfileline () ;
	  else printnl ( 65544L ) ;
	  print ( 66001L ) ;
	} 
	{
	  helpptr = 2 ;
	  helpline [1 ]= 66002L ;
	  helpline [0 ]= 66003L ;
	} 
	error () ;
	{
	  curval = 0 ;
	  curvallevel = 0 ;
	} 
      } 
    } 
    break ;
  case 72 : 
  case 73 : 
  case 88 : 
  case 89 : 
  case 90 : 
    if ( level != 5 ) 
    {
      {
	if ( interaction == 3 ) 
	;
	if ( filelineerrorstylep ) 
	printfileline () ;
	else printnl ( 65544L ) ;
	print ( 66009L ) ;
      } 
      {
	helpptr = 3 ;
	helpline [2 ]= 66010L ;
	helpline [1 ]= 66011L ;
	helpline [0 ]= 66012L ;
      } 
      backerror () ;
      {
	curval = 0 ;
	curvallevel = 1 ;
      } 
    } 
    else if ( curcmd <= 73 ) 
    {
      if ( curcmd < 73 ) {
	  
	if ( m == membot ) 
	{
	  scanregisternum () ;
	  if ( curval < 256 ) 
	  curval = eqtb [1206307L + curval ].hh .v.RH ;
	  else {
	      
	    findsaelement ( 5 , curval , false ) ;
	    if ( curptr == -268435455L ) 
	    curval = -268435455L ;
	    else curval = mem [curptr + 1 ].hh .v.RH ;
	  } 
	} 
	else curval = mem [m + 1 ].hh .v.RH ;
      } 
      else if ( curchr == 1206306L ) 
      {
	scancharclassnotignored () ;
	curptr = curval ;
	scancharclassnotignored () ;
	findsaelement ( 6 , curptr * 4096 + curval , false ) ;
	if ( curptr == -268435455L ) 
	curval = -268435455L ;
	else curval = mem [curptr + 1 ].hh .v.RH ;
      } 
      else curval = eqtb [m ].hh .v.RH ;
      curvallevel = 5 ;
    } 
    else {
	
      backinput () ;
      scanfontident () ;
      {
	curval = 1196762L + curval ;
	curvallevel = 4 ;
      } 
    } 
    break ;
  case 74 : 
    {
      curval = eqtb [m ].cint ;
      curvallevel = 0 ;
    } 
    break ;
  case 75 : 
    {
      curval = eqtb [m ].cint ;
      curvallevel = 1 ;
    } 
    break ;
  case 76 : 
    {
      curval = eqtb [m ].hh .v.RH ;
      curvallevel = 2 ;
    } 
    break ;
  case 77 : 
    {
      curval = eqtb [m ].hh .v.RH ;
      curvallevel = 3 ;
    } 
    break ;
  case 80 : 
    if ( abs ( curlist .modefield ) != m ) 
    {
      {
	if ( interaction == 3 ) 
	;
	if ( filelineerrorstylep ) 
	printfileline () ;
	else printnl ( 65544L ) ;
	print ( 66030L ) ;
      } 
      printcmdchr ( 80 , m ) ;
      {
	helpptr = 4 ;
	helpline [3 ]= 66031L ;
	helpline [2 ]= 66032L ;
	helpline [1 ]= 66033L ;
	helpline [0 ]= 66034L ;
      } 
      error () ;
      if ( level != 5 ) 
      {
	curval = 0 ;
	curvallevel = 1 ;
      } 
      else {
	  
	curval = 0 ;
	curvallevel = 0 ;
      } 
    } 
    else if ( m == 1 ) 
    {
      curval = curlist .auxfield .cint ;
      curvallevel = 1 ;
    } 
    else {
	
      curval = curlist .auxfield .hh .v.LH ;
      curvallevel = 0 ;
    } 
    break ;
  case 81 : 
    if ( curlist .modefield == 0 ) 
    {
      curval = 0 ;
      curvallevel = 0 ;
    } 
    else {
	
      nest [nestptr ]= curlist ;
      p = nestptr ;
      while ( abs ( nest [p ].modefield ) != 1 ) decr ( p ) ;
      {
	curval = nest [p ].pgfield ;
	curvallevel = 0 ;
      } 
    } 
    break ;
  case 83 : 
    {
      if ( m == 0 ) 
      curval = deadcycles ;
      else if ( m == 2 ) 
      curval = interaction ;
      else curval = insertpenalties ;
      curvallevel = 0 ;
    } 
    break ;
  case 82 : 
    {
      if ( ( pagecontents == 0 ) && ( ! outputactive ) ) {
	  
	if ( m == 0 ) 
	curval = 1073741823L ;
	else curval = 0 ;
      } 
      else curval = pagesofar [m ];
      curvallevel = 1 ;
    } 
    break ;
  case 85 : 
    {
      if ( m > 1206295L ) 
      {
	scanint () ;
	if ( ( eqtb [m ].hh .v.RH == -268435455L ) || ( curval < 0 ) ) 
	curval = 0 ;
	else {
	    
	  if ( curval > mem [eqtb [m ].hh .v.RH + 1 ].cint ) 
	  curval = mem [eqtb [m ].hh .v.RH + 1 ].cint ;
	  curval = mem [eqtb [m ].hh .v.RH + curval + 1 ].cint ;
	} 
      } 
      else if ( eqtb [1206295L ].hh .v.RH == -268435455L ) 
      curval = 0 ;
      else curval = mem [eqtb [1206295L ].hh .v.RH ].hh .v.LH ;
      curvallevel = 0 ;
    } 
    break ;
  case 84 : 
    {
      scanregisternum () ;
      if ( curval < 256 ) 
      q = eqtb [1206567L + curval ].hh .v.RH ;
      else {
	  
	findsaelement ( 4 , curval , false ) ;
	if ( curptr == -268435455L ) 
	q = -268435455L ;
	else q = mem [curptr + 1 ].hh .v.RH ;
      } 
      if ( q == -268435455L ) 
      curval = 0 ;
      else curval = mem [q + m ].cint ;
      curvallevel = 1 ;
    } 
    break ;
  case 68 : 
  case 69 : 
  case 70 : 
    {
      curval = curchr ;
      curvallevel = 0 ;
    } 
    break ;
  case 78 : 
    {
      findfontdimen ( false ) ;
      fontinfo [fmemptr ].cint = 0 ;
      {
	curval = fontinfo [curval ].cint ;
	curvallevel = 1 ;
      } 
    } 
    break ;
  case 79 : 
    {
      scanfontident () ;
      if ( m == 0 ) 
      {
	curval = hyphenchar [curval ];
	curvallevel = 0 ;
      } 
      else if ( m == 1 ) 
      {
	curval = skewchar [curval ];
	curvallevel = 0 ;
      } 
      else {
	  
	n = curval ;
	if ( ( ( fontarea [n ]== 65535L ) || ( fontarea [n ]== 65534L ) ) 
	) 
	scanglyphnumber ( n ) ;
	else scancharnum () ;
	k = curval ;
	switch ( m ) 
	{case 2 : 
	  {
	    curval = getcpcode ( n , k , 0 ) ;
	    curvallevel = 0 ;
	  } 
	  break ;
	case 3 : 
	  {
	    curval = getcpcode ( n , k , 1 ) ;
	    curvallevel = 0 ;
	  } 
	  break ;
	} 
      } 
    } 
    break ;
  case 91 : 
    {
      if ( ( m < membot ) || ( m > membot + 19 ) ) 
      {
	curvallevel = ( mem [m ].hh.b0 / 64 ) ;
	if ( curvallevel < 2 ) 
	curval = mem [m + 2 ].cint ;
	else curval = mem [m + 1 ].hh .v.RH ;
      } 
      else {
	  
	scanregisternum () ;
	curvallevel = m - membot ;
	if ( curval > 255 ) 
	{
	  findsaelement ( curvallevel , curval , false ) ;
	  if ( curptr == -268435455L ) {
	      
	    if ( curvallevel < 2 ) 
	    curval = 0 ;
	    else curval = membot ;
	  } 
	  else if ( curvallevel < 2 ) 
	  curval = mem [curptr + 2 ].cint ;
	  else curval = mem [curptr + 1 ].hh .v.RH ;
	} 
	else switch ( curvallevel ) 
	{case 0 : 
	  curval = eqtb [7892352L + curval ].cint ;
	  break ;
	case 1 : 
	  curval = eqtb [9006743L + curval ].cint ;
	  break ;
	case 2 : 
	  curval = eqtb [1205783L + curval ].hh .v.RH ;
	  break ;
	case 3 : 
	  curval = eqtb [1206039L + curval ].hh .v.RH ;
	  break ;
	} 
      } 
    } 
    break ;
  case 71 : 
    if ( m >= 4 ) {
	
      if ( m >= 65 ) 
      {
	if ( m < 66 ) 
	{
	  switch ( m ) 
	  {case 65 : 
	    scanmuglue () ;
	    break ;
	  } 
	  curvallevel = 2 ;
	} 
	else if ( m < 67 ) 
	{
	  switch ( m ) 
	  {case 66 : 
	    scannormalglue () ;
	    break ;
	  } 
	  curvallevel = 3 ;
	} 
	else {
	    
	  curvallevel = m - 67 ;
	  scanexpr () ;
	} 
	while ( curvallevel > level ) {
	    
	  if ( curvallevel == 2 ) 
	  {
	    m = curval ;
	    curval = mem [m + 1 ].cint ;
	    deleteglueref ( m ) ;
	  } 
	  else if ( curvallevel == 3 ) 
	  muerror () ;
	  decr ( curvallevel ) ;
	} 
	if ( negative ) {
	    
	  if ( curvallevel >= 2 ) 
	  {
	    m = curval ;
	    curval = newspec ( m ) ;
	    deleteglueref ( m ) ;
	    {
	      mem [curval + 1 ].cint = - (integer) mem [curval + 1 ].cint 
	      ;
	      mem [curval + 2 ].cint = - (integer) mem [curval + 2 ].cint 
	      ;
	      mem [curval + 3 ].cint = - (integer) mem [curval + 3 ].cint 
	      ;
	    } 
	  } 
	  else curval = - (integer) curval ;
	} 
	return ;
      } 
      else if ( m >= 55 ) 
      {
	switch ( m ) 
	{case 55 : 
	  {
	    if ( ( ( fontarea [eqtb [1206823L ].hh .v.RH ]== 65535L ) || ( 
	    fontarea [eqtb [1206823L ].hh .v.RH ]== 65534L ) ) ) 
	    {
	      scanint () ;
	      n = curval ;
	      if ( ( n < 1 ) || ( n > 4 ) ) 
	      {
		{
		  if ( interaction == 3 ) 
		  ;
		  if ( filelineerrorstylep ) 
		  printfileline () ;
		  else printnl ( 65544L ) ;
		  print ( 66859L ) ;
		} 
		printnl ( 66860L ) ;
		printint ( n ) ;
		error () ;
		curval = 0 ;
	      } 
	      else {
		  
		scanint () ;
		curval = getglyphbounds ( eqtb [1206823L ].hh .v.RH , n , 
		curval ) ;
	      } 
	    } 
	    else {
		
	      notnativefonterror ( 71 , m , eqtb [1206823L ].hh .v.RH ) ;
	      curval = 0 ;
	    } 
	  } 
	  break ;
	case 56 : 
	case 57 : 
	case 58 : 
	case 59 : 
	  {
	    scanfontident () ;
	    q = curval ;
	    scanusvnum () ;
	    if ( ( ( fontarea [q ]== 65535L ) || ( fontarea [q ]== 65534L 
	    ) ) ) 
	    {
	      switch ( m ) 
	      {case 56 : 
		curval = getnativecharwd ( q , curval ) ;
		break ;
	      case 57 : 
		curval = getnativecharht ( q , curval ) ;
		break ;
	      case 58 : 
		curval = getnativechardp ( q , curval ) ;
		break ;
	      case 59 : 
		curval = getnativecharic ( q , curval ) ;
		break ;
	      } 
	    } 
	    else {
		
	      if ( ( fontbc [q ]<= curval ) && ( fontec [q ]>= curval ) ) 
	      {
		i = fontinfo [charbase [q ]+ effectivechar ( true , q , 
		curval ) ].qqqq ;
		switch ( m ) 
		{case 56 : 
		  curval = fontinfo [widthbase [q ]+ i .b0 ].cint ;
		  break ;
		case 57 : 
		  curval = fontinfo [heightbase [q ]+ ( i .b1 ) / 16 ]
		  .cint ;
		  break ;
		case 58 : 
		  curval = fontinfo [depthbase [q ]+ ( i .b1 ) % 16 ].cint 
		  ;
		  break ;
		case 59 : 
		  curval = fontinfo [italicbase [q ]+ ( i .b2 ) / 4 ].cint 
		  ;
		  break ;
		} 
	      } 
	      else curval = 0 ;
	    } 
	  } 
	  break ;
	case 60 : 
	case 61 : 
	case 62 : 
	  {
	    q = curchr - 60 ;
	    scanint () ;
	    if ( ( eqtb [1206295L ].hh .v.RH == -268435455L ) || ( curval <= 
	    0 ) ) 
	    curval = 0 ;
	    else {
		
	      if ( q == 2 ) 
	      {
		q = curval % 2 ;
		curval = ( curval + q ) / 2 ;
	      } 
	      if ( curval > mem [eqtb [1206295L ].hh .v.RH ].hh .v.LH ) 
	      curval = mem [eqtb [1206295L ].hh .v.RH ].hh .v.LH ;
	      curval = mem [eqtb [1206295L ].hh .v.RH + 2 * curval - q ]
	      .cint ;
	    } 
	    curvallevel = 1 ;
	  } 
	  break ;
	case 63 : 
	case 64 : 
	  {
	    scannormalglue () ;
	    q = curval ;
	    if ( m == 63 ) 
	    curval = mem [q + 2 ].cint ;
	    else curval = mem [q + 3 ].cint ;
	    deleteglueref ( q ) ;
	  } 
	  break ;
	} 
	curvallevel = 1 ;
      } 
      else {
	  
	switch ( m ) 
	{case 4 : 
	  curval = line ;
	  break ;
	case 5 : 
	  curval = lastbadness ;
	  break ;
	case 16 : 
	  curval = getmicrointerval () ;
	  break ;
	case 18 : 
	  curval = randomseed ;
	  break ;
	case 17 : 
	  {
	    if ( shellenabledp ) 
	    {
	      if ( restrictedshell ) 
	      curval = 2 ;
	      else curval = 1 ;
	    } 
	    else curval = 0 ;
	  } 
	  break ;
	case 19 : 
	  curval = 2 ;
	  break ;
	case 27 : 
	  curval = 0 ;
	  break ;
	case 28 : 
	  {
	    scanfontident () ;
	    n = curval ;
	    if ( ( fontarea [n ]== 65535L ) ) 
	    curval = aatfontget ( m - 27 , fontlayoutengine [n ]) ;
	    else if ( ( fontarea [n ]== 65534L ) ) 
	    curval = otfontget ( m - 27 , fontlayoutengine [n ]) ;
	    else curval = 0 ;
	  } 
	  break ;
	case 35 : 
	  {
	    scanfontident () ;
	    n = curval ;
	    if ( ( fontarea [n ]== 65535L ) ) 
	    curval = aatfontget ( m - 27 , fontlayoutengine [n ]) ;
	    else if ( ( ( fontarea [n ]== 65534L ) && ( usingGraphite ( 
	    fontlayoutengine [n ]) ) ) ) 
	    curval = otfontget ( m - 27 , fontlayoutengine [n ]) ;
	    else curval = 0 ;
	  } 
	  break ;
	case 30 : 
	case 32 : 
	case 33 : 
	case 34 : 
	case 29 : 
	  {
	    scanfontident () ;
	    n = curval ;
	    curval = 0 ;
	  } 
	  break ;
	case 36 : 
	case 38 : 
	case 39 : 
	  {
	    scanfontident () ;
	    n = curval ;
	    if ( ( fontarea [n ]== 65535L ) ) 
	    {
	      scanint () ;
	      k = curval ;
	      curval = aatfontget1 ( m - 27 , fontlayoutengine [n ], k ) ;
	    } 
	    else if ( ( ( fontarea [n ]== 65534L ) && ( usingGraphite ( 
	    fontlayoutengine [n ]) ) ) ) 
	    {
	      scanint () ;
	      k = curval ;
	      curval = otfontget1 ( m - 27 , fontlayoutengine [n ], k ) ;
	    } 
	    else {
		
	      notaatgrfonterror ( 71 , m , n ) ;
	      curval = -1 ;
	    } 
	  } 
	  break ;
	case 40 : 
	case 42 : 
	  {
	    scanfontident () ;
	    n = curval ;
	    if ( ( fontarea [n ]== 65535L ) ) 
	    {
	      scanint () ;
	      k = curval ;
	      scanint () ;
	      curval = aatfontget2 ( m - 27 , fontlayoutengine [n ], k , 
	      curval ) ;
	    } 
	    else if ( ( ( fontarea [n ]== 65534L ) && ( usingGraphite ( 
	    fontlayoutengine [n ]) ) ) ) 
	    {
	      scanint () ;
	      k = curval ;
	      scanint () ;
	      curval = otfontget2 ( m - 27 , fontlayoutengine [n ], k , 
	      curval ) ;
	    } 
	    else {
		
	      notaatgrfonterror ( 71 , m , n ) ;
	      curval = -1 ;
	    } 
	  } 
	  break ;
	case 31 : 
	  {
	    scanfontident () ;
	    n = curval ;
	    if ( ( fontarea [n ]== 65535L ) ) 
	    {
	      scanandpackname () ;
	      curval = aatfontgetnamed ( m - 27 , fontlayoutengine [n ]) ;
	    } 
	    else {
		
	      notaatfonterror ( 71 , m , n ) ;
	      curval = -1 ;
	    } 
	  } 
	  break ;
	case 37 : 
	  {
	    scanfontident () ;
	    n = curval ;
	    if ( ( fontarea [n ]== 65535L ) ) 
	    {
	      scanandpackname () ;
	      curval = aatfontgetnamed ( m - 27 , fontlayoutengine [n ]) ;
	    } 
	    else if ( ( ( fontarea [n ]== 65534L ) && ( usingGraphite ( 
	    fontlayoutengine [n ]) ) ) ) 
	    {
	      scanandpackname () ;
	      curval = grfontgetnamed ( m - 27 , fontlayoutengine [n ]) ;
	    } 
	    else {
		
	      notaatgrfonterror ( 71 , m , n ) ;
	      curval = -1 ;
	    } 
	  } 
	  break ;
	case 41 : 
	  {
	    scanfontident () ;
	    n = curval ;
	    if ( ( fontarea [n ]== 65535L ) ) 
	    {
	      scanint () ;
	      k = curval ;
	      scanandpackname () ;
	      curval = aatfontgetnamed1 ( m - 27 , fontlayoutengine [n ], k 
	      ) ;
	    } 
	    else if ( ( ( fontarea [n ]== 65534L ) && ( usingGraphite ( 
	    fontlayoutengine [n ]) ) ) ) 
	    {
	      scanint () ;
	      k = curval ;
	      scanandpackname () ;
	      curval = grfontgetnamed1 ( m - 27 , fontlayoutengine [n ], k ) 
	      ;
	    } 
	    else {
		
	      notaatgrfonterror ( 71 , m , n ) ;
	      curval = -1 ;
	    } 
	  } 
	  break ;
	case 43 : 
	  {
	    scanfontident () ;
	    n = curval ;
	    if ( ( ( fontarea [n ]== 65534L ) && ( usingOpenType ( 
	    fontlayoutengine [n ]) ) ) ) 
	    curval = otfontget ( m - 27 , fontlayoutengine [n ]) ;
	    else {
		
	      curval = 0 ;
	    } 
	  } 
	  break ;
	case 44 : 
	case 46 : 
	  {
	    scanfontident () ;
	    n = curval ;
	    if ( ( ( fontarea [n ]== 65534L ) && ( usingOpenType ( 
	    fontlayoutengine [n ]) ) ) ) 
	    {
	      scanint () ;
	      curval = otfontget1 ( m - 27 , fontlayoutengine [n ], curval ) 
	      ;
	    } 
	    else {
		
	      nototfonterror ( 71 , m , n ) ;
	      curval = -1 ;
	    } 
	  } 
	  break ;
	case 45 : 
	case 47 : 
	  {
	    scanfontident () ;
	    n = curval ;
	    if ( ( ( fontarea [n ]== 65534L ) && ( usingOpenType ( 
	    fontlayoutengine [n ]) ) ) ) 
	    {
	      scanint () ;
	      k = curval ;
	      scanint () ;
	      curval = otfontget2 ( m - 27 , fontlayoutengine [n ], k , 
	      curval ) ;
	    } 
	    else {
		
	      nototfonterror ( 71 , m , n ) ;
	      curval = -1 ;
	    } 
	  } 
	  break ;
	case 48 : 
	  {
	    scanfontident () ;
	    n = curval ;
	    if ( ( ( fontarea [n ]== 65534L ) && ( usingOpenType ( 
	    fontlayoutengine [n ]) ) ) ) 
	    {
	      scanint () ;
	      k = curval ;
	      scanint () ;
	      kk = curval ;
	      scanint () ;
	      curval = otfontget3 ( m - 27 , fontlayoutengine [n ], k , kk , 
	      curval ) ;
	    } 
	    else {
		
	      nototfonterror ( 71 , m , n ) ;
	      curval = -1 ;
	    } 
	  } 
	  break ;
	case 49 : 
	  {
	    if ( ( ( fontarea [eqtb [1206823L ].hh .v.RH ]== 65535L ) || ( 
	    fontarea [eqtb [1206823L ].hh .v.RH ]== 65534L ) ) ) 
	    {
	      scanint () ;
	      n = curval ;
	      curval = mapchartoglyph ( eqtb [1206823L ].hh .v.RH , n ) ;
	    } 
	    else {
		
	      notnativefonterror ( 71 , m , eqtb [1206823L ].hh .v.RH ) ;
	      curval = 0 ;
	    } 
	  } 
	  break ;
	case 50 : 
	  {
	    if ( ( ( fontarea [eqtb [1206823L ].hh .v.RH ]== 65535L ) || ( 
	    fontarea [eqtb [1206823L ].hh .v.RH ]== 65534L ) ) ) 
	    {
	      scanandpackname () ;
	      curval = mapglyphtoindex ( eqtb [1206823L ].hh .v.RH ) ;
	    } 
	    else {
		
	      notnativefonterror ( 71 , m , eqtb [1206823L ].hh .v.RH ) ;
	      curval = 0 ;
	    } 
	  } 
	  break ;
	case 51 : 
	  {
	    scanfontident () ;
	    n = curval ;
	    if ( ( fontarea [n ]== 65535L ) ) 
	    curval = 1 ;
	    else if ( ( ( fontarea [n ]== 65534L ) && ( usingOpenType ( 
	    fontlayoutengine [n ]) ) ) ) 
	    curval = 2 ;
	    else if ( ( ( fontarea [n ]== 65534L ) && ( usingGraphite ( 
	    fontlayoutengine [n ]) ) ) ) 
	    curval = 3 ;
	    else curval = 0 ;
	  } 
	  break ;
	case 52 : 
	case 53 : 
	  {
	    scanfontident () ;
	    n = curval ;
	    if ( ( ( fontarea [n ]== 65535L ) || ( fontarea [n ]== 65534L 
	    ) ) ) 
	    curval = getfontcharrange ( n , m == 52 ) ;
	    else {
		
	      if ( m == 52 ) 
	      curval = fontbc [n ];
	      else curval = fontec [n ];
	    } 
	  } 
	  break ;
	case 12 : 
	  curval = pdflastxpos ;
	  break ;
	case 13 : 
	  curval = pdflastypos ;
	  break ;
	case 54 : 
	  {
	    scanandpackname () ;
	    curval = countpdffilepages () ;
	  } 
	  break ;
	case 20 : 
	  curval = curlevel - 1 ;
	  break ;
	case 21 : 
	  curval = curgroup ;
	  break ;
	case 22 : 
	  {
	    q = condptr ;
	    curval = 0 ;
	    while ( q != -268435455L ) {
		
	      incr ( curval ) ;
	      q = mem [q ].hh .v.RH ;
	    } 
	  } 
	  break ;
	case 23 : 
	  if ( condptr == -268435455L ) 
	  curval = 0 ;
	  else if ( curif < 32 ) 
	  curval = curif + 1 ;
	  else curval = - (integer) ( curif - 31 ) ;
	  break ;
	case 24 : 
	  if ( ( iflimit == 4 ) || ( iflimit == 3 ) ) 
	  curval = 1 ;
	  else if ( iflimit == 2 ) 
	  curval = -1 ;
	  else curval = 0 ;
	  break ;
	case 25 : 
	case 26 : 
	  {
	    scannormalglue () ;
	    q = curval ;
	    if ( m == 25 ) 
	    curval = mem [q ].hh.b0 ;
	    else curval = mem [q ].hh.b1 ;
	    deleteglueref ( q ) ;
	  } 
	  break ;
	} 
	curvallevel = 0 ;
      } 
    } 
    else {
	
      if ( curchr == 2 ) 
      curval = membot ;
      else curval = 0 ;
      tx = curlist .tailfield ;
      if ( ! ( tx >= himemmin ) ) {
	  
	if ( ( mem [tx ].hh.b0 == 9 ) && ( mem [tx ].hh.b1 == 3 ) ) 
	{
	  r = curlist .headfield ;
	  do {
	      q = r ;
	    r = mem [q ].hh .v.RH ;
	  } while ( ! ( r == tx ) ) ;
	  tx = q ;
	} 
      } 
      if ( curchr == 3 ) 
      {
	curvallevel = 0 ;
	if ( ( tx == curlist .headfield ) || ( curlist .modefield == 0 ) ) 
	curval = -1 ;
      } 
      else curvallevel = curchr ;
      if ( ! ( tx >= himemmin ) && ( curlist .modefield != 0 ) ) 
      switch ( curchr ) 
      {case 0 : 
	if ( mem [tx ].hh.b0 == 12 ) 
	curval = mem [tx + 1 ].cint ;
	break ;
      case 1 : 
	if ( mem [tx ].hh.b0 == 11 ) 
	curval = mem [tx + 1 ].cint ;
	break ;
      case 2 : 
	if ( mem [tx ].hh.b0 == 10 ) 
	{
	  curval = mem [tx + 1 ].hh .v.LH ;
	  if ( mem [tx ].hh.b1 == 99 ) 
	  curvallevel = 3 ;
	} 
	break ;
      case 3 : 
	if ( mem [tx ].hh.b0 <= 13 ) 
	curval = mem [tx ].hh.b0 + 1 ;
	else curval = 15 ;
	break ;
      } 
      else if ( ( curlist .modefield == 1 ) && ( tx == curlist .headfield ) ) 
      switch ( curchr ) 
      {case 0 : 
	curval = lastpenalty ;
	break ;
      case 1 : 
	curval = lastkern ;
	break ;
      case 2 : 
	if ( lastglue != 1073741823L ) 
	curval = lastglue ;
	break ;
      case 3 : 
	curval = lastnodetype ;
	break ;
      } 
    } 
    break ;
  case 39 : 
    if ( curchr == 1 ) 
    {
      gettoken () ;
      if ( curcs < 1179650L ) 
      curcs = primlookup ( curcs - 1114113L ) ;
      else curcs = primlookup ( hash [curcs ].v.RH ) ;
      if ( curcs != 0 ) 
      {
	curcmd = eqtb [1194662L + curcs ].hh.b0 ;
	curchr = eqtb [1194662L + curcs ].hh .v.RH ;
	curcs = 1194662L + curcs ;
	curtok = 33554431L + curcs ;
      } 
      else {
	  
	curcmd = 0 ;
	curchr = 0 ;
	curtok = 34749088L ;
	curcs = 1194657L ;
      } 
      goto lab20 ;
    } 
    break ;
    default: 
    {
      {
	if ( interaction == 3 ) 
	;
	if ( filelineerrorstylep ) 
	printfileline () ;
	else printnl ( 65544L ) ;
	print ( 66035L ) ;
      } 
      printcmdchr ( curcmd , curchr ) ;
      print ( 66036L ) ;
      printesc ( 65862L ) ;
      {
	helpptr = 1 ;
	helpline [0 ]= 66034L ;
      } 
      error () ;
      if ( level != 5 ) 
      {
	curval = 0 ;
	curvallevel = 1 ;
      } 
      else {
	  
	curval = 0 ;
	curvallevel = 0 ;
      } 
    } 
    break ;
  } 
  while ( curvallevel > level ) {
      
    if ( curvallevel == 2 ) 
    curval = mem [curval + 1 ].cint ;
    else if ( curvallevel == 3 ) 
    muerror () ;
    decr ( curvallevel ) ;
  } 
  if ( negative ) {
      
    if ( curvallevel >= 2 ) 
    {
      curval = newspec ( curval ) ;
      {
	mem [curval + 1 ].cint = - (integer) mem [curval + 1 ].cint ;
	mem [curval + 2 ].cint = - (integer) mem [curval + 2 ].cint ;
	mem [curval + 3 ].cint = - (integer) mem [curval + 3 ].cint ;
      } 
    } 
    else curval = - (integer) curval ;
  } 
  else if ( ( curvallevel >= 2 ) && ( curvallevel <= 3 ) ) 
  incr ( mem [curval ].hh .v.RH ) ;
} 
void 
scanint ( void ) 
{
  /* 30 20 */ scanint_regmem 
  boolean negative  ;
  integer m  ;
  smallnumber d  ;
  boolean vacuous  ;
  boolean OKsofar  ;
  radix = 0 ;
  OKsofar = true ;
  negative = false ;
  do {
      do { getxtoken () ;
    } while ( ! ( curcmd != 10 ) ) ;
    if ( curtok == 25165869L ) 
    {
      negative = ! negative ;
      curtok = 25165867L ;
    } 
  } while ( ! ( curtok != 25165867L ) ) ;
  lab20: if ( curtok == 25165920L ) 
  {
    gettoken () ;
    if ( curtok < 33554431L ) 
    {
      curval = curchr ;
      if ( curcmd <= 2 ) {
	  
	if ( curcmd == 2 ) 
	incr ( alignstate ) ;
	else decr ( alignstate ) ;
      } 
    } 
    else if ( curtok < 34668544L ) 
    curval = curtok - 33554432L ;
    else if ( curtok < 34734080L ) 
    curval = curtok - 34668544L ;
    else {
	
      m = hash [curtok - 33554431L ].v.RH ;
      if ( strstart [( m + 1 ) - 65536L ]== 2 + strstart [( m ) - 65536L ]
      ) 
      {
	m = strstart [( m ) - 65536L ];
	if ( ( strpool [m ]>= 55296L ) && ( strpool [m ]<= 56319L ) && ( 
	strpool [m + 1 ]>= 56320L ) && ( strpool [m + 1 ]<= 57343L ) ) 
	curval = 65536L + ( strpool [m ]- 55296L ) * 1024 + strpool [m + 1 
	]- 56320L ;
	else curval = 1114112L ;
      } 
      else curval = 1114112L ;
    } 
    if ( curval > 1114111L ) 
    {
      {
	if ( interaction == 3 ) 
	;
	if ( filelineerrorstylep ) 
	printfileline () ;
	else printnl ( 65544L ) ;
	print ( 66060L ) ;
      } 
      {
	helpptr = 2 ;
	helpline [1 ]= 66061L ;
	helpline [0 ]= 66062L ;
      } 
      curval = 48 ;
      backerror () ;
    } 
    else {
	
      getxtoken () ;
      if ( curcmd != 10 ) 
      backinput () ;
    } 
  } 
  else if ( curtok == 34749092L ) 
  {
    gettoken () ;
    if ( curcs < 1179650L ) 
    curcs = primlookup ( curcs - 1114113L ) ;
    else curcs = primlookup ( hash [curcs ].v.RH ) ;
    if ( curcs != 0 ) 
    {
      curcmd = eqtb [1194662L + curcs ].hh.b0 ;
      curchr = eqtb [1194662L + curcs ].hh .v.RH ;
      curcs = 1194662L + curcs ;
      curtok = 33554431L + curcs ;
    } 
    else {
	
      curcmd = 0 ;
      curchr = 0 ;
      curtok = 34749088L ;
      curcs = 1194657L ;
    } 
    goto lab20 ;
  } 
  else if ( ( curcmd >= 68 ) && ( curcmd <= 91 ) ) 
  scansomethinginternal ( 0 , false ) ;
  else {
      
    radix = 10 ;
    m = 214748364L ;
    if ( curtok == 25165863L ) 
    {
      radix = 8 ;
      m = 268435456L ;
      getxtoken () ;
    } 
    else if ( curtok == 25165858L ) 
    {
      radix = 16 ;
      m = 134217728L ;
      getxtoken () ;
    } 
    vacuous = true ;
    curval = 0 ;
    while ( true ) {
	
      if ( ( curtok < 25165872L + radix ) && ( curtok >= 25165872L ) && ( 
      curtok <= 25165881L ) ) 
      d = curtok - 25165872L ;
      else if ( radix == 16 ) {
	  
	if ( ( curtok <= 23068742L ) && ( curtok >= 23068737L ) ) 
	d = curtok - 23068727L ;
	else if ( ( curtok <= 25165894L ) && ( curtok >= 25165889L ) ) 
	d = curtok - 25165879L ;
	else goto lab30 ;
      } 
      else goto lab30 ;
      vacuous = false ;
      if ( ( curval >= m ) && ( ( curval > m ) || ( d > 7 ) || ( radix != 10 ) 
      ) ) 
      {
	if ( OKsofar ) 
	{
	  {
	    if ( interaction == 3 ) 
	    ;
	    if ( filelineerrorstylep ) 
	    printfileline () ;
	    else printnl ( 65544L ) ;
	    print ( 66063L ) ;
	  } 
	  {
	    helpptr = 2 ;
	    helpline [1 ]= 66064L ;
	    helpline [0 ]= 66065L ;
	  } 
	  error () ;
	  curval = 2147483647L ;
	  OKsofar = false ;
	} 
      } 
      else curval = curval * radix + d ;
      getxtoken () ;
    } 
    lab30: ;
    if ( vacuous ) 
    {
      {
	if ( interaction == 3 ) 
	;
	if ( filelineerrorstylep ) 
	printfileline () ;
	else printnl ( 65544L ) ;
	print ( 66009L ) ;
      } 
      {
	helpptr = 3 ;
	helpline [2 ]= 66010L ;
	helpline [1 ]= 66011L ;
	helpline [0 ]= 66012L ;
      } 
      backerror () ;
    } 
    else if ( curcmd != 10 ) 
    backinput () ;
  } 
  if ( negative ) 
  curval = - (integer) curval ;
} 
void 
zxetexscandimen ( boolean mu , boolean inf , boolean shortcut , boolean 
requiresunits ) 
{
  /* 30 31 32 40 45 88 89 */ xetexscandimen_regmem 
  boolean negative  ;
  integer f  ;
  integer num, denom  ;
  smallnumber k, kk  ;
  halfword p, q  ;
  scaled v  ;
  integer savecurval  ;
  f = 0 ;
  aritherror = false ;
  curorder = 0 ;
  negative = false ;
  if ( ! shortcut ) 
  {
    negative = false ;
    do {
	do { getxtoken () ;
      } while ( ! ( curcmd != 10 ) ) ;
      if ( curtok == 25165869L ) 
      {
	negative = ! negative ;
	curtok = 25165867L ;
      } 
    } while ( ! ( curtok != 25165867L ) ) ;
    if ( ( curcmd >= 68 ) && ( curcmd <= 91 ) ) {
	
      if ( mu ) 
      {
	scansomethinginternal ( 3 , false ) ;
	if ( curvallevel != 0 ) 
	{
	  if ( curvallevel >= 2 ) 
	  {
	    v = mem [curval + 1 ].cint ;
	    deleteglueref ( curval ) ;
	    curval = v ;
	  } 
	  if ( curvallevel != 3 ) 
	  muerror () ;
	  goto lab89 ;
	} 
      } 
      else {
	  
	scansomethinginternal ( 1 , false ) ;
	if ( curvallevel == 1 ) 
	goto lab89 ;
      } 
    } 
    else {
	
      backinput () ;
      if ( curtok == 25165868L ) 
      curtok = 25165870L ;
      if ( curtok != 25165870L ) 
      scanint () ;
      else {
	  
	radix = 10 ;
	curval = 0 ;
      } 
      if ( curtok == 25165868L ) 
      curtok = 25165870L ;
      if ( ( radix == 10 ) && ( curtok == 25165870L ) ) 
      {
	k = 0 ;
	p = -268435455L ;
	gettoken () ;
	while ( true ) {
	    
	  getxtoken () ;
	  if ( ( curtok > 25165881L ) || ( curtok < 25165872L ) ) 
	  goto lab31 ;
	  if ( k < 17 ) 
	  {
	    q = getavail () ;
	    mem [q ].hh .v.RH = p ;
	    mem [q ].hh .v.LH = curtok - 25165872L ;
	    p = q ;
	    incr ( k ) ;
	  } 
	} 
	lab31: {
	    register integer for_end; kk = k ;for_end = 1 ; if ( kk >= 
	for_end) do 
	  {
	    dig [kk - 1 ]= mem [p ].hh .v.LH ;
	    q = p ;
	    p = mem [p ].hh .v.RH ;
	    {
	      mem [q ].hh .v.RH = avail ;
	      avail = q ;
	;
#ifdef STAT
	      decr ( dynused ) ;
#endif /* STAT */
	    } 
	  } 
	while ( kk-- > for_end ) ;} 
	f = rounddecimals ( k ) ;
	if ( curcmd != 10 ) 
	backinput () ;
      } 
    } 
  } 
  if ( curval < 0 ) 
  {
    negative = ! negative ;
    curval = - (integer) curval ;
  } 
  if ( requiresunits ) 
  {
    if ( inf ) {
	
      if ( scankeyword ( 65599L ) ) 
      {
	curorder = 1 ;
	while ( scankeyword ( 108 ) ) {
	    
	  if ( curorder == 3 ) 
	  {
	    {
	      if ( interaction == 3 ) 
	      ;
	      if ( filelineerrorstylep ) 
	      printfileline () ;
	      else printnl ( 65544L ) ;
	      print ( 66067L ) ;
	    } 
	    print ( 66068L ) ;
	    {
	      helpptr = 1 ;
	      helpline [0 ]= 66069L ;
	    } 
	    error () ;
	  } 
	  else incr ( curorder ) ;
	} 
	goto lab88 ;
      } 
    } 
    savecurval = curval ;
    do {
	getxtoken () ;
    } while ( ! ( curcmd != 10 ) ) ;
    if ( ( curcmd < 68 ) || ( curcmd > 91 ) ) 
    backinput () ;
    else {
	
      if ( mu ) 
      {
	scansomethinginternal ( 3 , false ) ;
	if ( curvallevel >= 2 ) 
	{
	  v = mem [curval + 1 ].cint ;
	  deleteglueref ( curval ) ;
	  curval = v ;
	} 
	if ( curvallevel != 3 ) 
	muerror () ;
      } 
      else scansomethinginternal ( 1 , false ) ;
      v = curval ;
      goto lab40 ;
    } 
    if ( mu ) 
    goto lab45 ;
    if ( scankeyword ( 66070L ) ) 
    v = ( fontinfo [6 + parambase [eqtb [1206823L ].hh .v.RH ]].cint ) ;
    else if ( scankeyword ( 66071L ) ) 
    v = ( fontinfo [5 + parambase [eqtb [1206823L ].hh .v.RH ]].cint ) ;
    else goto lab45 ;
    {
      getxtoken () ;
      if ( curcmd != 10 ) 
      backinput () ;
    } 
    lab40: curval = multandadd ( savecurval , v , xnoverd ( v , f , 65536L ) , 
    1073741823L ) ;
    goto lab89 ;
    lab45: ;
    if ( mu ) {
	
      if ( scankeyword ( 65627L ) ) 
      goto lab88 ;
      else {
	  
	{
	  if ( interaction == 3 ) 
	  ;
	  if ( filelineerrorstylep ) 
	  printfileline () ;
	  else printnl ( 65544L ) ;
	  print ( 66067L ) ;
	} 
	print ( 66072L ) ;
	{
	  helpptr = 4 ;
	  helpline [3 ]= 66073L ;
	  helpline [2 ]= 66074L ;
	  helpline [1 ]= 66075L ;
	  helpline [0 ]= 66076L ;
	} 
	error () ;
	goto lab88 ;
      } 
    } 
    if ( scankeyword ( 66066L ) ) 
    {
      preparemag () ;
      if ( eqtb [7892281L ].cint != 1000 ) 
      {
	curval = xnoverd ( curval , 1000 , eqtb [7892281L ].cint ) ;
	f = ( 1000 * f + 65536L * texremainder ) / eqtb [7892281L ].cint ;
	curval = curval + ( f / 65536L ) ;
	f = f % 65536L ;
      } 
    } 
    if ( scankeyword ( 65698L ) ) 
    goto lab88 ;
    if ( scankeyword ( 66077L ) ) 
    {
      num = 7227 ;
      denom = 100 ;
    } 
    else if ( scankeyword ( 66078L ) ) 
    {
      num = 12 ;
      denom = 1 ;
    } 
    else if ( scankeyword ( 66079L ) ) 
    {
      num = 7227 ;
      denom = 254 ;
    } 
    else if ( scankeyword ( 66080L ) ) 
    {
      num = 7227 ;
      denom = 2540 ;
    } 
    else if ( scankeyword ( 66081L ) ) 
    {
      num = 7227 ;
      denom = 7200 ;
    } 
    else if ( scankeyword ( 66082L ) ) 
    {
      num = 1238 ;
      denom = 1157 ;
    } 
    else if ( scankeyword ( 66083L ) ) 
    {
      num = 14856 ;
      denom = 1157 ;
    } 
    else if ( scankeyword ( 66084L ) ) 
    goto lab30 ;
    else {
	
      {
	if ( interaction == 3 ) 
	;
	if ( filelineerrorstylep ) 
	printfileline () ;
	else printnl ( 65544L ) ;
	print ( 66067L ) ;
      } 
      print ( 66085L ) ;
      {
	helpptr = 6 ;
	helpline [5 ]= 66086L ;
	helpline [4 ]= 66087L ;
	helpline [3 ]= 66088L ;
	helpline [2 ]= 66074L ;
	helpline [1 ]= 66075L ;
	helpline [0 ]= 66076L ;
      } 
      error () ;
      goto lab32 ;
    } 
    curval = xnoverd ( curval , num , denom ) ;
    f = ( num * f + 65536L * texremainder ) / denom ;
    curval = curval + ( f / 65536L ) ;
    f = f % 65536L ;
    lab32: ;
    lab88: if ( curval >= 16384 ) 
    aritherror = true ;
    else curval = curval * 65536L + f ;
    lab30: ;
    {
      getxtoken () ;
      if ( curcmd != 10 ) 
      backinput () ;
    } 
  } 
  else {
      
    if ( curval >= 16384 ) 
    aritherror = true ;
    else curval = curval * 65536L + f ;
  } 
  lab89: if ( aritherror || ( abs ( curval ) >= 1073741824L ) ) 
  {
    {
      if ( interaction == 3 ) 
      ;
      if ( filelineerrorstylep ) 
      printfileline () ;
      else printnl ( 65544L ) ;
      print ( 66089L ) ;
    } 
    {
      helpptr = 2 ;
      helpline [1 ]= 66090L ;
      helpline [0 ]= 66091L ;
    } 
    error () ;
    curval = 1073741823L ;
    aritherror = false ;
  } 
  if ( negative ) 
  curval = - (integer) curval ;
} 
void 
zscandimen ( boolean mu , boolean inf , boolean shortcut ) 
{
  scandimen_regmem 
  xetexscandimen ( mu , inf , shortcut , true ) ;
} 
void 
scandecimal ( void ) 
{
  scandecimal_regmem 
  xetexscandimen ( false , false , false , false ) ;
} 
void 
zscanglue ( smallnumber level ) 
{
  /* 10 */ scanglue_regmem 
  boolean negative  ;
  halfword q  ;
  boolean mu  ;
  mu = ( level == 3 ) ;
  negative = false ;
  do {
      do { getxtoken () ;
    } while ( ! ( curcmd != 10 ) ) ;
    if ( curtok == 25165869L ) 
    {
      negative = ! negative ;
      curtok = 25165867L ;
    } 
  } while ( ! ( curtok != 25165867L ) ) ;
  if ( ( curcmd >= 68 ) && ( curcmd <= 91 ) ) 
  {
    scansomethinginternal ( level , negative ) ;
    if ( curvallevel >= 2 ) 
    {
      if ( curvallevel != level ) 
      muerror () ;
      return ;
    } 
    if ( curvallevel == 0 ) 
    scandimen ( mu , false , true ) ;
    else if ( level == 3 ) 
    muerror () ;
  } 
  else {
      
    backinput () ;
    scandimen ( mu , false , false ) ;
    if ( negative ) 
    curval = - (integer) curval ;
  } 
  q = newspec ( membot ) ;
  mem [q + 1 ].cint = curval ;
  if ( scankeyword ( 66092L ) ) 
  {
    scandimen ( mu , true , false ) ;
    mem [q + 2 ].cint = curval ;
    mem [q ].hh.b0 = curorder ;
  } 
  if ( scankeyword ( 66093L ) ) 
  {
    scandimen ( mu , true , false ) ;
    mem [q + 3 ].cint = curval ;
    mem [q ].hh.b1 = curorder ;
  } 
  curval = q ;
} 
integer 
zaddorsub ( integer x , integer y , integer maxanswer , boolean negative ) 
{
  register integer Result; addorsub_regmem 
  integer a  ;
  if ( negative ) 
  y = - (integer) y ;
  if ( x >= 0 ) {
      
    if ( y <= maxanswer - x ) 
    a = x + y ;
    else {
	
      aritherror = true ;
      a = 0 ;
    } 
  } 
  else if ( y >= - (integer) maxanswer - x ) 
  a = x + y ;
  else {
      
    aritherror = true ;
    a = 0 ;
  } 
  Result = a ;
  return Result ;
} 
integer 
zquotient ( integer n , integer d ) 
{
  register integer Result; quotient_regmem 
  boolean negative  ;
  integer a  ;
  if ( d == 0 ) 
  {
    aritherror = true ;
    a = 0 ;
  } 
  else {
      
    if ( d > 0 ) 
    negative = false ;
    else {
	
      d = - (integer) d ;
      negative = true ;
    } 
    if ( n < 0 ) 
    {
      n = - (integer) n ;
      negative = ! negative ;
    } 
    a = n / d ;
    n = n - a * d ;
    d = n - d ;
    if ( d + n >= 0 ) 
    incr ( a ) ;
    if ( negative ) 
    a = - (integer) a ;
  } 
  Result = a ;
  return Result ;
} 
integer 
zfract ( integer x , integer n , integer d , integer maxanswer ) 
{
  /* 40 41 88 30 */ register integer Result; fract_regmem 
  boolean negative  ;
  integer a  ;
  integer f  ;
  integer h  ;
  integer r  ;
  integer t  ;
  if ( d == 0 ) 
  goto lab88 ;
  a = 0 ;
  if ( d > 0 ) 
  negative = false ;
  else {
      
    d = - (integer) d ;
    negative = true ;
  } 
  if ( x < 0 ) 
  {
    x = - (integer) x ;
    negative = ! negative ;
  } 
  else if ( x == 0 ) 
  goto lab30 ;
  if ( n < 0 ) 
  {
    n = - (integer) n ;
    negative = ! negative ;
  } 
  t = n / d ;
  if ( t > maxanswer / x ) 
  goto lab88 ;
  a = t * x ;
  n = n - t * d ;
  if ( n == 0 ) 
  goto lab40 ;
  t = x / d ;
  if ( t > ( maxanswer - a ) / n ) 
  goto lab88 ;
  a = a + t * n ;
  x = x - t * d ;
  if ( x == 0 ) 
  goto lab40 ;
  if ( x < n ) 
  {
    t = x ;
    x = n ;
    n = t ;
  } 
  f = 0 ;
  r = ( d / 2 ) - d ;
  h = - (integer) r ;
  while ( true ) {
      
    if ( odd ( n ) ) 
    {
      r = r + x ;
      if ( r >= 0 ) 
      {
	r = r - d ;
	incr ( f ) ;
      } 
    } 
    n = n / 2 ;
    if ( n == 0 ) 
    goto lab41 ;
    if ( x < h ) 
    x = x + x ;
    else {
	
      t = x - d ;
      x = t + x ;
      f = f + n ;
      if ( x < n ) 
      {
	if ( x == 0 ) 
	goto lab41 ;
	t = x ;
	x = n ;
	n = t ;
      } 
    } 
  } 
  lab41: if ( f > ( maxanswer - a ) ) 
  goto lab88 ;
  a = a + f ;
  lab40: if ( negative ) 
  a = - (integer) a ;
  goto lab30 ;
  lab88: {
      
    aritherror = true ;
    a = 0 ;
  } 
  lab30: Result = a ;
  return Result ;
} 
void 
scanexpr ( void ) 
{
  /* 20 22 40 */ scanexpr_regmem 
  boolean a, b  ;
  smallnumber l  ;
  smallnumber r  ;
  smallnumber s  ;
  smallnumber o  ;
  integer e  ;
  integer t  ;
  integer f  ;
  integer n  ;
  halfword p  ;
  halfword q  ;
  l = curvallevel ;
  a = aritherror ;
  b = false ;
  p = -268435455L ;
  incr ( expanddepthcount ) ;
  if ( expanddepthcount >= expanddepth ) 
  overflow ( 65952L , expanddepth ) ;
  lab20: r = 0 ;
  e = 0 ;
  s = 0 ;
  t = 0 ;
  n = 0 ;
  lab22: if ( s == 0 ) 
  o = l ;
  else o = 0 ;
  do {
      getxtoken () ;
  } while ( ! ( curcmd != 10 ) ) ;
  if ( curtok == 25165864L ) 
  {
    q = getnode ( 4 ) ;
    mem [q ].hh .v.RH = p ;
    mem [q ].hh.b0 = l ;
    mem [q ].hh.b1 = 4 * s + r ;
    mem [q + 1 ].cint = e ;
    mem [q + 2 ].cint = t ;
    mem [q + 3 ].cint = n ;
    p = q ;
    l = o ;
    goto lab20 ;
  } 
  backinput () ;
  if ( o == 0 ) 
  scanint () ;
  else if ( o == 1 ) 
  scandimen ( false , false , false ) ;
  else if ( o == 2 ) 
  scannormalglue () ;
  else scanmuglue () ;
  f = curval ;
  lab40: do {
      getxtoken () ;
  } while ( ! ( curcmd != 10 ) ) ;
  if ( curtok == 25165867L ) 
  o = 1 ;
  else if ( curtok == 25165869L ) 
  o = 2 ;
  else if ( curtok == 25165866L ) 
  o = 3 ;
  else if ( curtok == 25165871L ) 
  o = 4 ;
  else {
      
    o = 0 ;
    if ( p == -268435455L ) 
    {
      if ( curcmd != 0 ) 
      backinput () ;
    } 
    else if ( curtok != 25165865L ) 
    {
      {
	if ( interaction == 3 ) 
	;
	if ( filelineerrorstylep ) 
	printfileline () ;
	else printnl ( 65544L ) ;
	print ( 66951L ) ;
      } 
      {
	helpptr = 1 ;
	helpline [0 ]= 66952L ;
      } 
      backerror () ;
    } 
  } 
  aritherror = b ;
  if ( ( l == 0 ) || ( s > 2 ) ) 
  {
    if ( ( f > 2147483647L ) || ( f < -2147483647L ) ) 
    {
      aritherror = true ;
      f = 0 ;
    } 
  } 
  else if ( l == 1 ) 
  {
    if ( abs ( f ) > 1073741823L ) 
    {
      aritherror = true ;
      f = 0 ;
    } 
  } 
  else {
      
    if ( ( abs ( mem [f + 1 ].cint ) > 1073741823L ) || ( abs ( mem [f + 2 
    ].cint ) > 1073741823L ) || ( abs ( mem [f + 3 ].cint ) > 1073741823L ) 
    ) 
    {
      aritherror = true ;
      deleteglueref ( f ) ;
      f = newspec ( membot ) ;
    } 
  } 
  switch ( s ) 
  {case 0 : 
    if ( ( l >= 2 ) && ( o != 0 ) ) 
    {
      t = newspec ( f ) ;
      deleteglueref ( f ) ;
      if ( mem [t + 2 ].cint == 0 ) 
      mem [t ].hh.b0 = 0 ;
      if ( mem [t + 3 ].cint == 0 ) 
      mem [t ].hh.b1 = 0 ;
    } 
    else t = f ;
    break ;
  case 3 : 
    if ( o == 4 ) 
    {
      n = f ;
      o = 5 ;
    } 
    else if ( l == 0 ) 
    t = multandadd ( t , f , 0 , 2147483647L ) ;
    else if ( l == 1 ) 
    t = multandadd ( t , f , 0 , 1073741823L ) ;
    else {
	
      mem [t + 1 ].cint = multandadd ( mem [t + 1 ].cint , f , 0 , 
      1073741823L ) ;
      mem [t + 2 ].cint = multandadd ( mem [t + 2 ].cint , f , 0 , 
      1073741823L ) ;
      mem [t + 3 ].cint = multandadd ( mem [t + 3 ].cint , f , 0 , 
      1073741823L ) ;
    } 
    break ;
  case 4 : 
    if ( l < 2 ) 
    t = quotient ( t , f ) ;
    else {
	
      mem [t + 1 ].cint = quotient ( mem [t + 1 ].cint , f ) ;
      mem [t + 2 ].cint = quotient ( mem [t + 2 ].cint , f ) ;
      mem [t + 3 ].cint = quotient ( mem [t + 3 ].cint , f ) ;
    } 
    break ;
  case 5 : 
    if ( l == 0 ) 
    t = fract ( t , n , f , 2147483647L ) ;
    else if ( l == 1 ) 
    t = fract ( t , n , f , 1073741823L ) ;
    else {
	
      mem [t + 1 ].cint = fract ( mem [t + 1 ].cint , n , f , 1073741823L 
      ) ;
      mem [t + 2 ].cint = fract ( mem [t + 2 ].cint , n , f , 1073741823L 
      ) ;
      mem [t + 3 ].cint = fract ( mem [t + 3 ].cint , n , f , 1073741823L 
      ) ;
    } 
    break ;
  } 
  if ( o > 2 ) 
  s = o ;
  else {
      
    s = 0 ;
    if ( r == 0 ) 
    e = t ;
    else if ( l == 0 ) 
    e = addorsub ( e , t , 2147483647L , r == 2 ) ;
    else if ( l == 1 ) 
    e = addorsub ( e , t , 1073741823L , r == 2 ) ;
    else {
	
      mem [e + 1 ].cint = addorsub ( mem [e + 1 ].cint , mem [t + 1 ]
      .cint , 1073741823L , r == 2 ) ;
      if ( mem [e ].hh.b0 == mem [t ].hh.b0 ) 
      mem [e + 2 ].cint = addorsub ( mem [e + 2 ].cint , mem [t + 2 ]
      .cint , 1073741823L , r == 2 ) ;
      else if ( ( mem [e ].hh.b0 < mem [t ].hh.b0 ) && ( mem [t + 2 ]
      .cint != 0 ) ) 
      {
	mem [e + 2 ].cint = mem [t + 2 ].cint ;
	mem [e ].hh.b0 = mem [t ].hh.b0 ;
      } 
      if ( mem [e ].hh.b1 == mem [t ].hh.b1 ) 
      mem [e + 3 ].cint = addorsub ( mem [e + 3 ].cint , mem [t + 3 ]
      .cint , 1073741823L , r == 2 ) ;
      else if ( ( mem [e ].hh.b1 < mem [t ].hh.b1 ) && ( mem [t + 3 ]
      .cint != 0 ) ) 
      {
	mem [e + 3 ].cint = mem [t + 3 ].cint ;
	mem [e ].hh.b1 = mem [t ].hh.b1 ;
      } 
      deleteglueref ( t ) ;
      if ( mem [e + 2 ].cint == 0 ) 
      mem [e ].hh.b0 = 0 ;
      if ( mem [e + 3 ].cint == 0 ) 
      mem [e ].hh.b1 = 0 ;
    } 
    r = o ;
  } 
  b = aritherror ;
  if ( o != 0 ) 
  goto lab22 ;
  if ( p != -268435455L ) 
  {
    f = e ;
    q = p ;
    e = mem [q + 1 ].cint ;
    t = mem [q + 2 ].cint ;
    n = mem [q + 3 ].cint ;
    s = mem [q ].hh.b1 / 4 ;
    r = mem [q ].hh.b1 % 4 ;
    l = mem [q ].hh.b0 ;
    p = mem [q ].hh .v.RH ;
    freenode ( q , 4 ) ;
    goto lab40 ;
  } 
  decr ( expanddepthcount ) ;
  if ( b ) 
  {
    {
      if ( interaction == 3 ) 
      ;
      if ( filelineerrorstylep ) 
      printfileline () ;
      else printnl ( 65544L ) ;
      print ( 66664L ) ;
    } 
    {
      helpptr = 2 ;
      helpline [1 ]= 66950L ;
      helpline [0 ]= 66666L ;
    } 
    error () ;
    if ( l >= 2 ) 
    {
      deleteglueref ( e ) ;
      e = membot ;
      incr ( mem [e ].hh .v.RH ) ;
    } 
    else e = 0 ;
  } 
  aritherror = a ;
  curval = e ;
  curvallevel = l ;
} 
void 
scannormalglue ( void ) 
{
  scannormalglue_regmem 
  scanglue ( 2 ) ;
} 
void 
scanmuglue ( void ) 
{
  scanmuglue_regmem 
  scanglue ( 3 ) ;
} 
halfword 
scanrulespec ( void ) 
{
  /* 21 */ register halfword Result; scanrulespec_regmem 
  halfword q  ;
  q = newrule () ;
  if ( curcmd == 35 ) 
  mem [q + 1 ].cint = 26214 ;
  else {
      
    mem [q + 3 ].cint = 26214 ;
    mem [q + 2 ].cint = 0 ;
  } 
  lab21: if ( scankeyword ( 66094L ) ) 
  {
    scandimen ( false , false , false ) ;
    mem [q + 1 ].cint = curval ;
    goto lab21 ;
  } 
  if ( scankeyword ( 66095L ) ) 
  {
    scandimen ( false , false , false ) ;
    mem [q + 3 ].cint = curval ;
    goto lab21 ;
  } 
  if ( scankeyword ( 66096L ) ) 
  {
    scandimen ( false , false , false ) ;
    mem [q + 2 ].cint = curval ;
    goto lab21 ;
  } 
  Result = q ;
  return Result ;
} 
void 
scangeneraltext ( void ) 
{
  /* 40 */ scangeneraltext_regmem 
  unsigned char s  ;
  halfword w  ;
  halfword d  ;
  halfword p  ;
  halfword q  ;
  halfword unbalance  ;
  s = scannerstatus ;
  w = warningindex ;
  d = defref ;
  scannerstatus = 5 ;
  warningindex = curcs ;
  defref = getavail () ;
  mem [defref ].hh .v.LH = -268435455L ;
  p = defref ;
  scanleftbrace () ;
  unbalance = 1 ;
  while ( true ) {
      
    gettoken () ;
    if ( curtok < 6291456L ) {
	
      if ( curcmd < 2 ) 
      incr ( unbalance ) ;
      else {
	  
	decr ( unbalance ) ;
	if ( unbalance == 0 ) 
	goto lab40 ;
      } 
    } 
    {
      q = getavail () ;
      mem [p ].hh .v.RH = q ;
      mem [q ].hh .v.LH = curtok ;
      p = q ;
    } 
  } 
  lab40: q = mem [defref ].hh .v.RH ;
  {
    mem [defref ].hh .v.RH = avail ;
    avail = defref ;
	;
#ifdef STAT
    decr ( dynused ) ;
#endif /* STAT */
  } 
  if ( q == -268435455L ) 
  curval = memtop - 3 ;
  else curval = p ;
  mem [memtop - 3 ].hh .v.RH = q ;
  scannerstatus = s ;
  warningindex = w ;
  defref = d ;
} 
void 
pseudostart ( void ) 
{
  pseudostart_regmem 
  unsigned char oldsetting  ;
  strnumber s  ;
  poolpointer l, m  ;
  halfword p, q, r  ;
  fourquarters w  ;
  integer nl, sz  ;
  scangeneraltext () ;
  oldsetting = selector ;
  selector = 21 ;
  tokenshow ( memtop - 3 ) ;
  selector = oldsetting ;
  flushlist ( mem [memtop - 3 ].hh .v.RH ) ;
  {
    if ( poolptr + 1 > poolsize ) 
    overflow ( 65539L , poolsize - initpoolptr ) ;
  } 
  s = makestring () ;
  strpool [poolptr ]= 32 ;
  l = strstart [( s ) - 65536L ];
  nl = eqtb [7892313L ].cint ;
  p = getavail () ;
  q = p ;
  while ( l < poolptr ) {
      
    m = l ;
    while ( ( l < poolptr ) && ( strpool [l ]!= nl ) ) incr ( l ) ;
    sz = ( l - m + 7 ) / 4 ;
    if ( sz == 1 ) 
    sz = 2 ;
    r = getnode ( sz ) ;
    mem [q ].hh .v.RH = r ;
    q = r ;
    mem [q ].hh .v.LH = sz ;
    while ( sz > 2 ) {
	
      decr ( sz ) ;
      incr ( r ) ;
      w .b0 = strpool [m ];
      w .b1 = strpool [m + 1 ];
      w .b2 = strpool [m + 2 ];
      w .b3 = strpool [m + 3 ];
      mem [r ].qqqq = w ;
      m = m + 4 ;
    } 
    w .b0 = 32 ;
    w .b1 = 32 ;
    w .b2 = 32 ;
    w .b3 = 32 ;
    if ( l > m ) 
    {
      w .b0 = strpool [m ];
      if ( l > m + 1 ) 
      {
	w .b1 = strpool [m + 1 ];
	if ( l > m + 2 ) 
	{
	  w .b2 = strpool [m + 2 ];
	  if ( l > m + 3 ) 
	  w .b3 = strpool [m + 3 ];
	} 
      } 
    } 
    mem [r + 1 ].qqqq = w ;
    if ( strpool [l ]== nl ) 
    incr ( l ) ;
  } 
  mem [p ].hh .v.LH = mem [p ].hh .v.RH ;
  mem [p ].hh .v.RH = pseudofiles ;
  pseudofiles = p ;
  {
    decr ( strptr ) ;
    poolptr = strstart [( strptr ) - 65536L ];
  } 
  beginfilereading () ;
  line = 0 ;
  curinput .limitfield = curinput .startfield ;
  curinput .locfield = curinput .limitfield + 1 ;
  if ( eqtb [7892328L ].cint > 0 ) 
  {
    if ( termoffset > maxprintline - 3 ) 
    println () ;
    else if ( ( termoffset > 0 ) || ( fileoffset > 0 ) ) 
    printchar ( 32 ) ;
    curinput .namefield = 19 ;
    print ( 66935L ) ;
    incr ( openparens ) ;
    fflush ( stdout ) ;
  } 
  else {
      
    curinput .namefield = 18 ;
    curinput .synctextagfield = 0 ;
  } 
} 
halfword 
zstrtokscat ( poolpointer b , smallnumber cat ) 
{
  register halfword Result; strtokscat_regmem 
  halfword p  ;
  halfword q  ;
  halfword t  ;
  poolpointer k  ;
  {
    if ( poolptr + 1 > poolsize ) 
    overflow ( 65539L , poolsize - initpoolptr ) ;
  } 
  p = memtop - 3 ;
  mem [p ].hh .v.RH = -268435455L ;
  k = b ;
  while ( k < poolptr ) {
      
    t = strpool [k ];
    if ( ( t == 32 ) && ( cat == 0 ) ) 
    t = 20971552L ;
    else {
	
      if ( ( t >= 55296L ) && ( t <= 56319L ) && ( k + 1 < poolptr ) && ( 
      strpool [k + 1 ]>= 56320L ) && ( strpool [k + 1 ]<= 57343L ) ) 
      {
	incr ( k ) ;
	t = 65536L + ( t - 55296L ) * 1024 + ( strpool [k ]- 56320L ) ;
      } 
      if ( cat == 0 ) 
      t = 25165824L + t ;
      else if ( cat == 13 ) 
      t = 33554432L + t ;
      else t = 2097152L * cat + t ;
    } 
    {
      {
	q = avail ;
	if ( q == -268435455L ) 
	q = getavail () ;
	else {
	    
	  avail = mem [q ].hh .v.RH ;
	  mem [q ].hh .v.RH = -268435455L ;
	;
#ifdef STAT
	  incr ( dynused ) ;
#endif /* STAT */
	} 
      } 
      mem [p ].hh .v.RH = q ;
      mem [q ].hh .v.LH = t ;
      p = q ;
    } 
    incr ( k ) ;
  } 
  poolptr = b ;
  Result = p ;
  return Result ;
} 
halfword 
zstrtoks ( poolpointer b ) 
{
  register halfword Result; strtoks_regmem 
  Result = strtokscat ( b , 0 ) ;
  return Result ;
} 
halfword 
thetoks ( void ) 
{
  /* 10 */ register halfword Result; thetoks_regmem 
  unsigned char oldsetting  ;
  halfword p, q, r  ;
  poolpointer b  ;
  smallnumber c  ;
  if ( odd ( curchr ) ) 
  {
    c = curchr ;
    scangeneraltext () ;
    if ( c == 1 ) 
    Result = curval ;
    else {
	
      oldsetting = selector ;
      selector = 21 ;
      b = poolptr ;
      p = getavail () ;
      mem [p ].hh .v.RH = mem [memtop - 3 ].hh .v.RH ;
      tokenshow ( p ) ;
      flushlist ( p ) ;
      selector = oldsetting ;
      Result = strtoks ( b ) ;
    } 
    return Result ;
  } 
  getxtoken () ;
  scansomethinginternal ( 5 , false ) ;
  if ( curvallevel >= 4 ) 
  {
    p = memtop - 3 ;
    mem [p ].hh .v.RH = -268435455L ;
    if ( curvallevel == 4 ) 
    {
      q = getavail () ;
      mem [p ].hh .v.RH = q ;
      mem [q ].hh .v.LH = 33554431L + curval ;
      p = q ;
    } 
    else if ( curval != -268435455L ) 
    {
      r = mem [curval ].hh .v.RH ;
      while ( r != -268435455L ) {
	  
	{
	  {
	    q = avail ;
	    if ( q == -268435455L ) 
	    q = getavail () ;
	    else {
		
	      avail = mem [q ].hh .v.RH ;
	      mem [q ].hh .v.RH = -268435455L ;
	;
#ifdef STAT
	      incr ( dynused ) ;
#endif /* STAT */
	    } 
	  } 
	  mem [p ].hh .v.RH = q ;
	  mem [q ].hh .v.LH = mem [r ].hh .v.LH ;
	  p = q ;
	} 
	r = mem [r ].hh .v.RH ;
      } 
    } 
    Result = p ;
  } 
  else {
      
    oldsetting = selector ;
    selector = 21 ;
    b = poolptr ;
    switch ( curvallevel ) 
    {case 0 : 
      printint ( curval ) ;
      break ;
    case 1 : 
      {
	printscaled ( curval ) ;
	print ( 65698L ) ;
      } 
      break ;
    case 2 : 
      {
	printspec ( curval , 65698L ) ;
	deleteglueref ( curval ) ;
      } 
      break ;
    case 3 : 
      {
	printspec ( curval , 65627L ) ;
	deleteglueref ( curval ) ;
      } 
      break ;
    } 
    selector = oldsetting ;
    Result = strtoks ( b ) ;
  } 
  return Result ;
} 
void 
insthetoks ( void ) 
{
  insthetoks_regmem 
  mem [memtop - 12 ].hh .v.RH = thetoks () ;
  begintokenlist ( mem [memtop - 3 ].hh .v.RH , 5 ) ;
} 
void 
convtoks ( void ) 
{
  convtoks_regmem 
  unsigned char oldsetting  ;
  halfword savewarningindex, savedefref  ;
  boolean boolvar  ;
  strnumber s  ;
  strnumber u  ;
  integer j  ;
  smallnumber c  ;
  smallnumber savescannerstatus  ;
  poolpointer b  ;
  integer fnt, arg1, arg2  ;
  strnumber fontnamestr  ;
  smallnumber i  ;
  UTF16code quotechar  ;
  smallnumber cat  ;
  UnicodeScalar savedchr  ;
  halfword p, q  ;
  cat = 0 ;
  c = curchr ;
  switch ( c ) 
  {case 0 : 
  case 1 : 
    scanint () ;
    break ;
  case 2 : 
  case 3 : 
    {
      savescannerstatus = scannerstatus ;
      scannerstatus = 0 ;
      gettoken () ;
      scannerstatus = savescannerstatus ;
    } 
    break ;
  case 4 : 
    scanfontident () ;
    break ;
  case 5 : 
    ;
    break ;
  case 6 : 
    {
      savescannerstatus = scannerstatus ;
      savewarningindex = warningindex ;
      savedefref = defref ;
      if ( strstart [( strptr ) - 65536L ]< poolptr ) 
      u = makestring () ;
      else u = 0 ;
      scanpdfexttoks () ;
      warningindex = savewarningindex ;
      scannerstatus = savescannerstatus ;
      begintokenlist ( mem [defref ].hh .v.RH , 5 ) ;
      {
	mem [defref ].hh .v.RH = avail ;
	avail = defref ;
	;
#ifdef STAT
	decr ( dynused ) ;
#endif /* STAT */
      } 
      defref = savedefref ;
      if ( u != 0 ) 
      decr ( strptr ) ;
      return ;
    } 
    break ;
  case 16 : 
  case 17 : 
    {
      scanregisternum () ;
      if ( curval < 256 ) 
      p = eqtb [1206567L + curval ].hh .v.RH ;
      else {
	  
	findsaelement ( 4 , curval , false ) ;
	if ( curptr == -268435455L ) 
	p = -268435455L ;
	else p = mem [curptr + 1 ].hh .v.RH ;
      } 
      if ( ( p == -268435455L ) || ( mem [p ].hh.b0 != 0 ) ) 
      pdferror ( 66117L , 66118L ) ;
    } 
    break ;
  case 22 : 
    {
      b = poolptr ;
      getcreationdate () ;
      mem [memtop - 12 ].hh .v.RH = strtoks ( b ) ;
      begintokenlist ( mem [memtop - 3 ].hh .v.RH , 5 ) ;
      return ;
    } 
    break ;
  case 23 : 
    {
      savescannerstatus = scannerstatus ;
      savewarningindex = warningindex ;
      savedefref = defref ;
      if ( strstart [( strptr ) - 65536L ]< poolptr ) 
      u = makestring () ;
      else u = 0 ;
      scanpdfexttoks () ;
      if ( selector == 21 ) 
      pdferror ( 66119L , 66120L ) ;
      oldsetting = selector ;
      selector = 21 ;
      showtokenlist ( mem [defref ].hh .v.RH , -268435455L , poolsize - 
      poolptr ) ;
      selector = oldsetting ;
      s = makestring () ;
      deletetokenref ( defref ) ;
      defref = savedefref ;
      warningindex = savewarningindex ;
      scannerstatus = savescannerstatus ;
      b = poolptr ;
      getfilemoddate ( s ) ;
      mem [memtop - 12 ].hh .v.RH = strtoks ( b ) ;
      if ( ( s == strptr - 1 ) ) 
      {
	decr ( strptr ) ;
	poolptr = strstart [( strptr ) - 65536L ];
      } 
      begintokenlist ( mem [memtop - 3 ].hh .v.RH , 5 ) ;
      if ( u != 0 ) 
      decr ( strptr ) ;
      return ;
    } 
    break ;
  case 24 : 
    {
      savescannerstatus = scannerstatus ;
      savewarningindex = warningindex ;
      savedefref = defref ;
      if ( strstart [( strptr ) - 65536L ]< poolptr ) 
      u = makestring () ;
      else u = 0 ;
      scanpdfexttoks () ;
      if ( selector == 21 ) 
      pdferror ( 66119L , 66120L ) ;
      oldsetting = selector ;
      selector = 21 ;
      showtokenlist ( mem [defref ].hh .v.RH , -268435455L , poolsize - 
      poolptr ) ;
      selector = oldsetting ;
      s = makestring () ;
      deletetokenref ( defref ) ;
      defref = savedefref ;
      warningindex = savewarningindex ;
      scannerstatus = savescannerstatus ;
      b = poolptr ;
      getfilesize ( s ) ;
      mem [memtop - 12 ].hh .v.RH = strtoks ( b ) ;
      if ( ( s == strptr - 1 ) ) 
      {
	decr ( strptr ) ;
	poolptr = strstart [( strptr ) - 65536L ];
      } 
      begintokenlist ( mem [memtop - 3 ].hh .v.RH , 5 ) ;
      if ( u != 0 ) 
      decr ( strptr ) ;
      return ;
    } 
    break ;
  case 25 : 
    {
      savescannerstatus = scannerstatus ;
      savewarningindex = warningindex ;
      savedefref = defref ;
      if ( strstart [( strptr ) - 65536L ]< poolptr ) 
      u = makestring () ;
      else u = 0 ;
      boolvar = scankeyword ( 66121L ) ;
      scanpdfexttoks () ;
      if ( selector == 21 ) 
      pdferror ( 66119L , 66120L ) ;
      oldsetting = selector ;
      selector = 21 ;
      showtokenlist ( mem [defref ].hh .v.RH , -268435455L , poolsize - 
      poolptr ) ;
      selector = oldsetting ;
      s = makestring () ;
      deletetokenref ( defref ) ;
      defref = savedefref ;
      warningindex = savewarningindex ;
      scannerstatus = savescannerstatus ;
      b = poolptr ;
      getmd5sum ( s , boolvar ) ;
      mem [memtop - 12 ].hh .v.RH = strtoks ( b ) ;
      if ( ( s == strptr - 1 ) ) 
      {
	decr ( strptr ) ;
	poolptr = strstart [( strptr ) - 65536L ];
      } 
      begintokenlist ( mem [memtop - 3 ].hh .v.RH , 5 ) ;
      if ( u != 0 ) 
      decr ( strptr ) ;
      return ;
    } 
    break ;
  case 26 : 
    {
      savescannerstatus = scannerstatus ;
      savewarningindex = warningindex ;
      savedefref = defref ;
      if ( strstart [( strptr ) - 65536L ]< poolptr ) 
      u = makestring () ;
      else u = 0 ;
      curval = 0 ;
      if ( ( scankeyword ( 66122L ) ) ) 
      {
	scanint () ;
	if ( ( curval < 0 ) ) 
	{
	  {
	    if ( interaction == 3 ) 
	    ;
	    if ( filelineerrorstylep ) 
	    printfileline () ;
	    else printnl ( 65544L ) ;
	    print ( 66123L ) ;
	  } 
	  {
	    helpptr = 2 ;
	    helpline [1 ]= 66124L ;
	    helpline [0 ]= 66006L ;
	  } 
	  interror ( curval ) ;
	  curval = 0 ;
	} 
      } 
      i = curval ;
      curval = 0 ;
      if ( ( scankeyword ( 66125L ) ) ) 
      {
	scanint () ;
	if ( ( curval < 0 ) ) 
	{
	  {
	    if ( interaction == 3 ) 
	    ;
	    if ( filelineerrorstylep ) 
	    printfileline () ;
	    else printnl ( 65544L ) ;
	    print ( 66126L ) ;
	  } 
	  {
	    helpptr = 2 ;
	    helpline [1 ]= 66127L ;
	    helpline [0 ]= 66006L ;
	  } 
	  interror ( curval ) ;
	  curval = 0 ;
	} 
      } 
      j = curval ;
      scanpdfexttoks () ;
      if ( selector == 21 ) 
      pdferror ( 66119L , 66120L ) ;
      oldsetting = selector ;
      selector = 21 ;
      showtokenlist ( mem [defref ].hh .v.RH , -268435455L , poolsize - 
      poolptr ) ;
      selector = oldsetting ;
      s = makestring () ;
      deletetokenref ( defref ) ;
      defref = savedefref ;
      warningindex = savewarningindex ;
      scannerstatus = savescannerstatus ;
      b = poolptr ;
      getfiledump ( s , i , j ) ;
      mem [memtop - 12 ].hh .v.RH = strtoks ( b ) ;
      if ( ( s == strptr - 1 ) ) 
      {
	decr ( strptr ) ;
	poolptr = strstart [( strptr ) - 65536L ];
      } 
      begintokenlist ( mem [memtop - 3 ].hh .v.RH , 5 ) ;
      if ( u != 0 ) 
      decr ( strptr ) ;
      return ;
    } 
    break ;
  case 18 : 
    {
      savescannerstatus = scannerstatus ;
      savewarningindex = warningindex ;
      savedefref = defref ;
      if ( strstart [( strptr ) - 65536L ]< poolptr ) 
      u = makestring () ;
      else u = 0 ;
      comparestrings () ;
      defref = savedefref ;
      warningindex = savewarningindex ;
      scannerstatus = savescannerstatus ;
      if ( u != 0 ) 
      decr ( strptr ) ;
    } 
    break ;
  case 38 : 
    scanusvnum () ;
    break ;
  case 39 : 
    {
      scanusvnum () ;
      savedchr = curval ;
      scanint () ;
      if ( ( curval < 1 ) || ( curval > 13 ) || ( curval == 5 ) || ( curval == 
      9 ) ) 
      {
	{
	  if ( interaction == 3 ) 
	  ;
	  if ( filelineerrorstylep ) 
	  printfileline () ;
	  else printnl ( 65544L ) ;
	  print ( 66128L ) ;
	} 
	printint ( curval ) ;
	print ( 66129L ) ;
	{
	  helpptr = 1 ;
	  helpline [0 ]= 66130L ;
	} 
	error () ;
	cat = 12 ;
      } 
      else cat = curval ;
      curval = savedchr ;
    } 
    break ;
  case 33 : 
    ;
    break ;
  case 34 : 
    {
      scanfontident () ;
      fnt = curval ;
      if ( ( fontarea [fnt ]== 65535L ) ) 
      {
	scanint () ;
	arg1 = curval ;
	arg2 = 0 ;
      } 
      else notaatfonterror ( 111 , c , fnt ) ;
    } 
    break ;
  case 35 : 
    {
      scanfontident () ;
      fnt = curval ;
      if ( ( fontarea [fnt ]== 65535L ) || ( ( fontarea [fnt ]== 65534L ) 
      && ( usingGraphite ( fontlayoutengine [fnt ]) ) ) ) 
      {
	scanint () ;
	arg1 = curval ;
	arg2 = 0 ;
      } 
      else notaatgrfonterror ( 111 , c , fnt ) ;
    } 
    break ;
  case 36 : 
    {
      scanfontident () ;
      fnt = curval ;
      if ( ( fontarea [fnt ]== 65535L ) || ( ( fontarea [fnt ]== 65534L ) 
      && ( usingGraphite ( fontlayoutengine [fnt ]) ) ) ) 
      {
	scanint () ;
	arg1 = curval ;
	scanint () ;
	arg2 = curval ;
      } 
      else notaatgrfonterror ( 111 , c , fnt ) ;
    } 
    break ;
  case 37 : 
    {
      scanfontident () ;
      fnt = curval ;
      if ( ( ( fontarea [fnt ]== 65535L ) || ( fontarea [fnt ]== 65534L ) 
      ) ) 
      {
	scanint () ;
	arg1 = curval ;
      } 
      else notnativefonterror ( 111 , c , fnt ) ;
    } 
    break ;
  case 40 : 
    if ( jobname == 0 ) 
    openlogfile () ;
    break ;
  case 29 : 
    scanint () ;
    break ;
  case 30 : 
    ;
    break ;
  } 
  oldsetting = selector ;
  selector = 21 ;
  b = poolptr ;
  switch ( c ) 
  {case 0 : 
    printint ( curval ) ;
    break ;
  case 1 : 
    printromanint ( curval ) ;
    break ;
  case 2 : 
    if ( curcs != 0 ) 
    sprintcs ( curcs ) ;
    else printchar ( curchr ) ;
    break ;
  case 3 : 
    printmeaning () ;
    break ;
  case 4 : 
    {
      fontnamestr = fontname [curval ];
      if ( ( ( fontarea [curval ]== 65535L ) || ( fontarea [curval ]== 
      65534L ) ) ) 
      {
	quotechar = 34 ;
	{register integer for_end; i = 0 ;for_end = length ( fontnamestr ) - 
	1 ; if ( i <= for_end) do 
	  if ( strpool [strstart [( fontnamestr ) - 65536L ]+ i ]== 34 ) 
	  quotechar = 39 ;
	while ( i++ < for_end ) ;} 
	printchar ( quotechar ) ;
	print ( fontnamestr ) ;
	printchar ( quotechar ) ;
      } 
      else print ( fontnamestr ) ;
      if ( fontsize [curval ]!= fontdsize [curval ]) 
      {
	print ( 66131L ) ;
	printscaled ( fontsize [curval ]) ;
	print ( 65698L ) ;
      } 
    } 
    break ;
  case 5 : 
    print ( 65536L ) ;
    break ;
  case 16 : 
    {
      p = mem [p + 5 ].hh .v.RH ;
      while ( ( p != -268435455L ) && ( ( ! ( p >= himemmin ) && ( ( mem [p ]
      .hh.b0 == 3 ) || ( mem [p ].hh.b0 == 4 ) || ( mem [p ].hh.b0 == 5 ) 
      || ( mem [p ].hh.b0 == 12 ) || ( ( mem [p ].hh.b0 == 7 ) && ( mem [
      p + 1 ].hh .v.LH == -268435455L ) && ( mem [p + 1 ].hh .v.RH == 
      -268435455L ) && ( mem [p ].hh.b1 == 0 ) ) || ( ( mem [p ].hh.b0 == 
      9 ) && ( mem [p + 1 ].cint == 0 ) ) || ( ( mem [p ].hh.b0 == 11 ) && 
      ( ( mem [p + 1 ].cint == 0 ) || ( mem [p ].hh.b1 == 0 ) ) ) || ( ( 
      mem [p ].hh.b0 == 10 ) && ( mem [p + 1 ].hh .v.LH == membot ) ) || ( 
      ( mem [p ].hh.b0 == 0 ) && ( mem [p + 1 ].cint == 0 ) && ( mem [p + 
      3 ].cint == 0 ) && ( mem [p + 2 ].cint == 0 ) && ( mem [p + 5 ].hh 
      .v.RH == -268435455L ) ) ) ) || ( ( ! ( p >= himemmin ) ) && ( mem [p ]
      .hh.b0 == 10 ) && ( mem [p ].hh.b1 == 8 ) ) ) ) p = mem [p ].hh 
      .v.RH ;
      if ( ( p != -268435455L ) && ( ! ( p >= himemmin ) ) && ( mem [p ]
      .hh.b0 == 40 ) && ( mem [p ].hh.b1 == 0 ) ) 
      printscaled ( mem [p + 1 ].cint ) ;
      else print ( 48 ) ;
      print ( 65698L ) ;
    } 
    break ;
  case 17 : 
    {
      q = mem [p + 5 ].hh .v.RH ;
      p = prevrightmost ( q , -268435455L ) ;
      while ( ( p != -268435455L ) && ( ( ! ( p >= himemmin ) && ( ( mem [p ]
      .hh.b0 == 3 ) || ( mem [p ].hh.b0 == 4 ) || ( mem [p ].hh.b0 == 5 ) 
      || ( mem [p ].hh.b0 == 12 ) || ( ( mem [p ].hh.b0 == 7 ) && ( mem [
      p + 1 ].hh .v.LH == -268435455L ) && ( mem [p + 1 ].hh .v.RH == 
      -268435455L ) && ( mem [p ].hh.b1 == 0 ) ) || ( ( mem [p ].hh.b0 == 
      9 ) && ( mem [p + 1 ].cint == 0 ) ) || ( ( mem [p ].hh.b0 == 11 ) && 
      ( ( mem [p + 1 ].cint == 0 ) || ( mem [p ].hh.b1 == 0 ) ) ) || ( ( 
      mem [p ].hh.b0 == 10 ) && ( mem [p + 1 ].hh .v.LH == membot ) ) || ( 
      ( mem [p ].hh.b0 == 0 ) && ( mem [p + 1 ].cint == 0 ) && ( mem [p + 
      3 ].cint == 0 ) && ( mem [p + 2 ].cint == 0 ) && ( mem [p + 5 ].hh 
      .v.RH == -268435455L ) ) ) ) || ( ( ! ( p >= himemmin ) ) && ( mem [p ]
      .hh.b0 == 10 ) && ( mem [p ].hh.b1 == 9 ) ) ) ) p = prevrightmost ( q 
      , p ) ;
      if ( ( p != -268435455L ) && ( ! ( p >= himemmin ) ) && ( mem [p ]
      .hh.b0 == 40 ) && ( mem [p ].hh.b1 == 1 ) ) 
      printscaled ( mem [p + 1 ].cint ) ;
      else print ( 48 ) ;
      print ( 65698L ) ;
    } 
    break ;
  case 18 : 
    printint ( curval ) ;
    break ;
  case 29 : 
    printint ( unifrand ( curval ) ) ;
    break ;
  case 30 : 
    printint ( normrand () ) ;
    break ;
  case 38 : 
  case 39 : 
    printchar ( curval ) ;
    break ;
  case 33 : 
    print ( 65537L ) ;
    break ;
  case 34 : 
    if ( ( fontarea [fnt ]== 65535L ) ) 
    aatprintfontname ( c , fontlayoutengine [fnt ], arg1 , arg2 ) ;
    break ;
  case 35 : 
  case 36 : 
    if ( ( fontarea [fnt ]== 65535L ) ) 
    aatprintfontname ( c , fontlayoutengine [fnt ], arg1 , arg2 ) ;
    else if ( ( ( fontarea [fnt ]== 65534L ) && ( usingGraphite ( 
    fontlayoutengine [fnt ]) ) ) ) 
    grprintfontname ( c , fontlayoutengine [fnt ], arg1 , arg2 ) ;
    break ;
  case 37 : 
    if ( ( ( fontarea [fnt ]== 65535L ) || ( fontarea [fnt ]== 65534L ) ) 
    ) 
    printglyphname ( fnt , arg1 ) ;
    break ;
  case 40 : 
    printfilename ( jobname , 0 , 0 ) ;
    break ;
  } 
  selector = oldsetting ;
  mem [memtop - 12 ].hh .v.RH = strtokscat ( b , cat ) ;
  begintokenlist ( mem [memtop - 3 ].hh .v.RH , 5 ) ;
} 
halfword 
zscantoks ( boolean macrodef , boolean xpand ) 
{
  /* 40 22 30 31 32 */ register halfword Result; scantoks_regmem 
  halfword t  ;
  halfword s  ;
  halfword p  ;
  halfword q  ;
  halfword unbalance  ;
  halfword hashbrace  ;
  if ( macrodef ) 
  scannerstatus = 2 ;
  else scannerstatus = 5 ;
  warningindex = curcs ;
  defref = getavail () ;
  mem [defref ].hh .v.LH = -268435455L ;
  p = defref ;
  hashbrace = 0 ;
  t = 25165872L ;
  if ( macrodef ) 
  {
    while ( true ) {
	
      lab22: gettoken () ;
      if ( curtok < 6291456L ) 
      goto lab31 ;
      if ( curcmd == 6 ) 
      {
	s = 27262976L + curchr ;
	gettoken () ;
	if ( curtok < 4194304L ) 
	{
	  hashbrace = curtok ;
	  {
	    q = getavail () ;
	    mem [p ].hh .v.RH = q ;
	    mem [q ].hh .v.LH = curtok ;
	    p = q ;
	  } 
	  {
	    q = getavail () ;
	    mem [p ].hh .v.RH = q ;
	    mem [q ].hh .v.LH = 29360128L ;
	    p = q ;
	  } 
	  goto lab30 ;
	} 
	if ( t == 25165881L ) 
	{
	  {
	    if ( interaction == 3 ) 
	    ;
	    if ( filelineerrorstylep ) 
	    printfileline () ;
	    else printnl ( 65544L ) ;
	    print ( 66134L ) ;
	  } 
	  {
	    helpptr = 2 ;
	    helpline [1 ]= 66135L ;
	    helpline [0 ]= 66136L ;
	  } 
	  error () ;
	  goto lab22 ;
	} 
	else {
	    
	  incr ( t ) ;
	  if ( curtok != t ) 
	  {
	    {
	      if ( interaction == 3 ) 
	      ;
	      if ( filelineerrorstylep ) 
	      printfileline () ;
	      else printnl ( 65544L ) ;
	      print ( 66137L ) ;
	    } 
	    {
	      helpptr = 2 ;
	      helpline [1 ]= 66138L ;
	      helpline [0 ]= 66139L ;
	    } 
	    backerror () ;
	  } 
	  curtok = s ;
	} 
      } 
      {
	q = getavail () ;
	mem [p ].hh .v.RH = q ;
	mem [q ].hh .v.LH = curtok ;
	p = q ;
      } 
    } 
    lab31: {
	
      q = getavail () ;
      mem [p ].hh .v.RH = q ;
      mem [q ].hh .v.LH = 29360128L ;
      p = q ;
    } 
    if ( curcmd == 2 ) 
    {
      {
	if ( interaction == 3 ) 
	;
	if ( filelineerrorstylep ) 
	printfileline () ;
	else printnl ( 65544L ) ;
	print ( 65991L ) ;
      } 
      incr ( alignstate ) ;
      {
	helpptr = 2 ;
	helpline [1 ]= 66132L ;
	helpline [0 ]= 66133L ;
      } 
      error () ;
      goto lab40 ;
    } 
    lab30: ;
  } 
  else scanleftbrace () ;
  unbalance = 1 ;
  while ( true ) {
      
    if ( xpand ) 
    {
      while ( true ) {
	  
	getnext () ;
	if ( curcmd >= 114 ) {
	    
	  if ( mem [mem [curchr ].hh .v.RH ].hh .v.LH == 29360129L ) 
	  {
	    curcmd = 0 ;
	    curchr = 1114113L ;
	  } 
	} 
	if ( curcmd <= 103 ) 
	goto lab32 ;
	if ( curcmd != 112 ) 
	expand () ;
	else {
	    
	  q = thetoks () ;
	  if ( mem [memtop - 3 ].hh .v.RH != -268435455L ) 
	  {
	    mem [p ].hh .v.RH = mem [memtop - 3 ].hh .v.RH ;
	    p = q ;
	  } 
	} 
      } 
      lab32: xtoken () ;
    } 
    else gettoken () ;
    if ( curtok < 6291456L ) {
	
      if ( curcmd < 2 ) 
      incr ( unbalance ) ;
      else {
	  
	decr ( unbalance ) ;
	if ( unbalance == 0 ) 
	goto lab40 ;
      } 
    } 
    else if ( curcmd == 6 ) {
	
      if ( macrodef ) 
      {
	s = curtok ;
	if ( xpand ) 
	getxtoken () ;
	else gettoken () ;
	if ( curcmd != 6 ) {
	    
	  if ( ( curtok <= 25165872L ) || ( curtok > t ) ) 
	  {
	    {
	      if ( interaction == 3 ) 
	      ;
	      if ( filelineerrorstylep ) 
	      printfileline () ;
	      else printnl ( 65544L ) ;
	      print ( 66140L ) ;
	    } 
	    sprintcs ( warningindex ) ;
	    {
	      helpptr = 3 ;
	      helpline [2 ]= 66141L ;
	      helpline [1 ]= 66142L ;
	      helpline [0 ]= 66143L ;
	    } 
	    backerror () ;
	    curtok = s ;
	  } 
	  else curtok = 10485712L + curchr ;
	} 
      } 
    } 
    {
      q = getavail () ;
      mem [p ].hh .v.RH = q ;
      mem [q ].hh .v.LH = curtok ;
      p = q ;
    } 
  } 
  lab40: scannerstatus = 0 ;
  if ( hashbrace != 0 ) 
  {
    q = getavail () ;
    mem [p ].hh .v.RH = q ;
    mem [q ].hh .v.LH = hashbrace ;
    p = q ;
  } 
  Result = p ;
  return Result ;
} 
void 
zreadtoks ( integer n , halfword r , halfword j ) 
{
  /* 30 */ readtoks_regmem 
  halfword p  ;
  halfword q  ;
  integer s  ;
  smallnumber m  ;
  scannerstatus = 2 ;
  warningindex = r ;
  defref = getavail () ;
  mem [defref ].hh .v.LH = -268435455L ;
  p = defref ;
  {
    q = getavail () ;
    mem [p ].hh .v.RH = q ;
    mem [q ].hh .v.LH = 29360128L ;
    p = q ;
  } 
  if ( ( n < 0 ) || ( n > 15 ) ) 
  m = 16 ;
  else m = n ;
  s = alignstate ;
  alignstate = 1000000L ;
  do {
      beginfilereading () ;
    curinput .namefield = m + 1 ;
    if ( readopen [m ]== 2 ) {
	
      if ( interaction > 1 ) {
	  
	if ( n < 0 ) 
	{
	  ;
	  print ( 65545L ) ;
	  terminput () ;
	} 
	else {
	    
	  ;
	  println () ;
	  sprintcs ( r ) ;
	  {
	    ;
	    print ( 61 ) ;
	    terminput () ;
	  } 
	  n = -1 ;
	} 
      } 
      else {
	  
	curinput .limitfield = 0 ;
	fatalerror ( 66144L ) ;
      } 
    } 
    else if ( readopen [m ]== 1 ) {
	
      if ( inputln ( readfile [m ], false ) ) 
      readopen [m ]= 0 ;
      else {
	  
	uclose ( readfile [m ]) ;
	readopen [m ]= 2 ;
      } 
    } 
    else {
	
      if ( ! inputln ( readfile [m ], true ) ) 
      {
	uclose ( readfile [m ]) ;
	readopen [m ]= 2 ;
	if ( alignstate != 1000000L ) 
	{
	  runaway () ;
	  {
	    if ( interaction == 3 ) 
	    ;
	    if ( filelineerrorstylep ) 
	    printfileline () ;
	    else printnl ( 65544L ) ;
	    print ( 66145L ) ;
	  } 
	  printesc ( 65859L ) ;
	  {
	    helpptr = 1 ;
	    helpline [0 ]= 66146L ;
	  } 
	  alignstate = 1000000L ;
	  curinput .limitfield = 0 ;
	  error () ;
	} 
      } 
    } 
    curinput .limitfield = last ;
    if ( ( eqtb [7892312L ].cint < 0 ) || ( eqtb [7892312L ].cint > 255 ) 
    ) 
    decr ( curinput .limitfield ) ;
    else buffer [curinput .limitfield ]= eqtb [7892312L ].cint ;
    first = curinput .limitfield + 1 ;
    curinput .locfield = curinput .startfield ;
    curinput .statefield = 33 ;
    if ( j == 1 ) 
    {
      while ( curinput .locfield <= curinput .limitfield ) {
	  
	curchr = buffer [curinput .locfield ];
	incr ( curinput .locfield ) ;
	if ( curchr == 32 ) 
	curtok = 20971552L ;
	else curtok = curchr + 25165824L ;
	{
	  q = getavail () ;
	  mem [p ].hh .v.RH = q ;
	  mem [q ].hh .v.LH = curtok ;
	  p = q ;
	} 
      } 
      goto lab30 ;
    } 
    while ( true ) {
	
      gettoken () ;
      if ( curtok == 0 ) 
      goto lab30 ;
      if ( alignstate < 1000000L ) 
      {
	do {
	    gettoken () ;
	} while ( ! ( curtok == 0 ) ) ;
	alignstate = 1000000L ;
	goto lab30 ;
      } 
      {
	q = getavail () ;
	mem [p ].hh .v.RH = q ;
	mem [q ].hh .v.LH = curtok ;
	p = q ;
      } 
    } 
    lab30: endfilereading () ;
  } while ( ! ( alignstate == 1000000L ) ) ;
  curval = defref ;
  scannerstatus = 0 ;
  alignstate = s ;
} 
void 
passtext ( void ) 
{
  /* 30 */ passtext_regmem 
  integer l  ;
  smallnumber savescannerstatus  ;
  savescannerstatus = scannerstatus ;
  scannerstatus = 1 ;
  l = 0 ;
  skipline = line ;
  while ( true ) {
      
    getnext () ;
    if ( curcmd == 109 ) 
    {
      if ( l == 0 ) 
      goto lab30 ;
      if ( curchr == 2 ) 
      decr ( l ) ;
    } 
    else if ( curcmd == 108 ) 
    incr ( l ) ;
  } 
  lab30: scannerstatus = savescannerstatus ;
  if ( eqtb [7892327L ].cint > 0 ) 
  showcurcmdchr () ;
} 
void 
zchangeiflimit ( smallnumber l , halfword p ) 
{
  /* 10 */ changeiflimit_regmem 
  halfword q  ;
  if ( p == condptr ) 
  iflimit = l ;
  else {
      
    q = condptr ;
    while ( true ) {
	
      if ( q == -268435455L ) 
      confusion ( 66147L ) ;
      if ( mem [q ].hh .v.RH == p ) 
      {
	mem [q ].hh.b0 = l ;
	return ;
      } 
      q = mem [q ].hh .v.RH ;
    } 
  } 
} 
void 
conditional ( void ) 
{
  /* 10 50 */ conditional_regmem 
  boolean b  ;
  boolean e  ;
  unsigned char r  ;
  integer m, n  ;
  halfword p, q  ;
  smallnumber savescannerstatus  ;
  halfword savecondptr  ;
  smallnumber thisif  ;
  boolean isunless  ;
  if ( eqtb [7892327L ].cint > 0 ) {
      
    if ( eqtb [7892300L ].cint <= 1 ) 
    showcurcmdchr () ;
  } 
  {
    p = getnode ( 2 ) ;
    mem [p ].hh .v.RH = condptr ;
    mem [p ].hh.b0 = iflimit ;
    mem [p ].hh.b1 = curif ;
    mem [p + 1 ].cint = ifline ;
    condptr = p ;
    curif = curchr ;
    iflimit = 1 ;
    ifline = line ;
  } 
  savecondptr = condptr ;
  isunless = ( curchr >= 32 ) ;
  thisif = curchr % 32 ;
  switch ( thisif ) 
  {case 0 : 
  case 1 : 
    {
      {
	getxtoken () ;
	if ( curcmd == 0 ) {
	    
	  if ( curchr == 1114113L ) 
	  {
	    curcmd = 13 ;
	    curchr = curtok - 33554432L ;
	  } 
	} 
      } 
      if ( ( curcmd > 13 ) || ( curchr > 1114111L ) ) 
      {
	m = 0 ;
	n = 1114112L ;
      } 
      else {
	  
	m = curcmd ;
	n = curchr ;
      } 
      {
	getxtoken () ;
	if ( curcmd == 0 ) {
	    
	  if ( curchr == 1114113L ) 
	  {
	    curcmd = 13 ;
	    curchr = curtok - 33554432L ;
	  } 
	} 
      } 
      if ( ( curcmd > 13 ) || ( curchr > 1114111L ) ) 
      {
	curcmd = 0 ;
	curchr = 1114112L ;
      } 
      if ( thisif == 0 ) 
      b = ( n == curchr ) ;
      else b = ( m == curcmd ) ;
    } 
    break ;
  case 2 : 
  case 3 : 
    {
      if ( thisif == 2 ) 
      scanint () ;
      else scandimen ( false , false , false ) ;
      n = curval ;
      do {
	  getxtoken () ;
      } while ( ! ( curcmd != 10 ) ) ;
      if ( ( curtok >= 25165884L ) && ( curtok <= 25165886L ) ) 
      r = curtok - 25165824L ;
      else {
	  
	{
	  if ( interaction == 3 ) 
	  ;
	  if ( filelineerrorstylep ) 
	  printfileline () ;
	  else printnl ( 65544L ) ;
	  print ( 66173L ) ;
	} 
	printcmdchr ( 108 , thisif ) ;
	{
	  helpptr = 1 ;
	  helpline [0 ]= 66174L ;
	} 
	backerror () ;
	r = 61 ;
      } 
      if ( thisif == 2 ) 
      scanint () ;
      else scandimen ( false , false , false ) ;
      switch ( r ) 
      {case 60 : 
	b = ( n < curval ) ;
	break ;
      case 61 : 
	b = ( n == curval ) ;
	break ;
      case 62 : 
	b = ( n > curval ) ;
	break ;
      } 
    } 
    break ;
  case 4 : 
    {
      scanint () ;
      b = odd ( curval ) ;
    } 
    break ;
  case 5 : 
    b = ( abs ( curlist .modefield ) == 1 ) ;
    break ;
  case 6 : 
    b = ( abs ( curlist .modefield ) == 105 ) ;
    break ;
  case 7 : 
    b = ( abs ( curlist .modefield ) == 209 ) ;
    break ;
  case 8 : 
    b = ( curlist .modefield < 0 ) ;
    break ;
  case 9 : 
  case 10 : 
  case 11 : 
    {
      scanregisternum () ;
      if ( curval < 256 ) 
      p = eqtb [1206567L + curval ].hh .v.RH ;
      else {
	  
	findsaelement ( 4 , curval , false ) ;
	if ( curptr == -268435455L ) 
	p = -268435455L ;
	else p = mem [curptr + 1 ].hh .v.RH ;
      } 
      if ( thisif == 9 ) 
      b = ( p == -268435455L ) ;
      else if ( p == -268435455L ) 
      b = false ;
      else if ( thisif == 10 ) 
      b = ( mem [p ].hh.b0 == 0 ) ;
      else b = ( mem [p ].hh.b0 == 1 ) ;
    } 
    break ;
  case 12 : 
    {
      savescannerstatus = scannerstatus ;
      scannerstatus = 0 ;
      getnext () ;
      n = curcs ;
      p = curcmd ;
      q = curchr ;
      getnext () ;
      if ( curcmd != p ) 
      b = false ;
      else if ( curcmd < 114 ) 
      b = ( curchr == q ) ;
      else {
	  
	p = mem [curchr ].hh .v.RH ;
	q = mem [eqtb [n ].hh .v.RH ].hh .v.RH ;
	if ( p == q ) 
	b = true ;
	else {
	    
	  while ( ( p != -268435455L ) && ( q != -268435455L ) ) if ( mem [p 
	  ].hh .v.LH != mem [q ].hh .v.LH ) 
	  p = -268435455L ;
	  else {
	      
	    p = mem [p ].hh .v.RH ;
	    q = mem [q ].hh .v.RH ;
	  } 
	  b = ( ( p == -268435455L ) && ( q == -268435455L ) ) ;
	} 
      } 
      scannerstatus = savescannerstatus ;
    } 
    break ;
  case 13 : 
    {
      scanfourbitintor18 () ;
      if ( curval == 18 ) 
      b = ! shellenabledp ;
      else b = ( readopen [curval ]== 2 ) ;
    } 
    break ;
  case 14 : 
    b = true ;
    break ;
  case 15 : 
    b = false ;
    break ;
  case 17 : 
    {
      savescannerstatus = scannerstatus ;
      scannerstatus = 0 ;
      getnext () ;
      b = ( curcmd != 104 ) ;
      scannerstatus = savescannerstatus ;
    } 
    break ;
  case 18 : 
    {
      n = getavail () ;
      p = n ;
      e = isincsname ;
      isincsname = true ;
      do {
	  getxtoken () ;
	if ( curcs == 0 ) 
	{
	  q = getavail () ;
	  mem [p ].hh .v.RH = q ;
	  mem [q ].hh .v.LH = curtok ;
	  p = q ;
	} 
      } while ( ! ( curcs != 0 ) ) ;
      if ( curcmd != 67 ) 
      {
	{
	  if ( interaction == 3 ) 
	  ;
	  if ( filelineerrorstylep ) 
	  printfileline () ;
	  else printnl ( 65544L ) ;
	  print ( 65959L ) ;
	} 
	printesc ( 65819L ) ;
	print ( 65960L ) ;
	{
	  helpptr = 2 ;
	  helpline [1 ]= 65961L ;
	  helpline [0 ]= 65962L ;
	} 
	backerror () ;
      } 
      m = first ;
      p = mem [n ].hh .v.RH ;
      while ( p != -268435455L ) {
	  
	if ( m >= maxbufstack ) 
	{
	  maxbufstack = m + 1 ;
	  if ( maxbufstack == bufsize ) 
	  overflow ( 65538L , bufsize ) ;
	} 
	buffer [m ]= mem [p ].hh .v.LH % 2097152L ;
	incr ( m ) ;
	p = mem [p ].hh .v.RH ;
      } 
      if ( m > first + 1 ) 
      curcs = idlookup ( first , m - first ) ;
      else if ( m == first ) 
      curcs = 1179649L ;
      else curcs = 1114113L + buffer [first ];
      flushlist ( n ) ;
      b = ( eqtb [curcs ].hh.b0 != 104 ) ;
      isincsname = e ;
    } 
    break ;
  case 20 : 
    b = isincsname ;
    break ;
  case 19 : 
    {
      scanfontident () ;
      n = curval ;
      scanusvnum () ;
      if ( ( ( fontarea [n ]== 65535L ) || ( fontarea [n ]== 65534L ) ) ) 
      b = ( mapchartoglyph ( n , curval ) > 0 ) ;
      else {
	  
	if ( ( fontbc [n ]<= curval ) && ( fontec [n ]>= curval ) ) 
	b = ( fontinfo [charbase [n ]+ effectivechar ( true , n , curval ) 
	].qqqq .b0 > 0 ) ;
	else b = false ;
      } 
    } 
    break ;
  case 16 : 
    {
      scanint () ;
      n = curval ;
      if ( eqtb [7892300L ].cint > 1 ) 
      {
	begindiagnostic () ;
	print ( 66175L ) ;
	printint ( n ) ;
	printchar ( 125 ) ;
	enddiagnostic ( false ) ;
      } 
      while ( n != 0 ) {
	  
	passtext () ;
	if ( condptr == savecondptr ) {
	    
	  if ( curchr == 4 ) 
	  decr ( n ) ;
	  else goto lab50 ;
	} 
	else if ( curchr == 2 ) 
	{
	  if ( ifstack [inopen ]== condptr ) 
	  ifwarning () ;
	  p = condptr ;
	  ifline = mem [p + 1 ].cint ;
	  curif = mem [p ].hh.b1 ;
	  iflimit = mem [p ].hh.b0 ;
	  condptr = mem [p ].hh .v.RH ;
	  freenode ( p , 2 ) ;
	} 
      } 
      changeiflimit ( 4 , savecondptr ) ;
      return ;
    } 
    break ;
  case 21 : 
    {
      savescannerstatus = scannerstatus ;
      scannerstatus = 0 ;
      getnext () ;
      scannerstatus = savescannerstatus ;
      if ( curcs < 1179650L ) 
      m = primlookup ( curcs - 1114113L ) ;
      else m = primlookup ( hash [curcs ].v.RH ) ;
      b = ( ( curcmd != 104 ) && ( m != 0 ) && ( curcmd == eqtb [1194662L + m 
      ].hh.b0 ) && ( curchr == eqtb [1194662L + m ].hh .v.RH ) ) ;
    } 
    break ;
  } 
  if ( isunless ) 
  b = ! b ;
  if ( eqtb [7892300L ].cint > 1 ) 
  {
    begindiagnostic () ;
    if ( b ) 
    print ( 66171L ) ;
    else print ( 66172L ) ;
    enddiagnostic ( false ) ;
  } 
  if ( b ) 
  {
    changeiflimit ( 3 , savecondptr ) ;
    return ;
  } 
  while ( true ) {
      
    passtext () ;
    if ( condptr == savecondptr ) 
    {
      if ( curchr != 4 ) 
      goto lab50 ;
      {
	if ( interaction == 3 ) 
	;
	if ( filelineerrorstylep ) 
	printfileline () ;
	else printnl ( 65544L ) ;
	print ( 66169L ) ;
      } 
      printesc ( 66167L ) ;
      {
	helpptr = 1 ;
	helpline [0 ]= 66170L ;
      } 
      error () ;
    } 
    else if ( curchr == 2 ) 
    {
      if ( ifstack [inopen ]== condptr ) 
      ifwarning () ;
      p = condptr ;
      ifline = mem [p + 1 ].cint ;
      curif = mem [p ].hh.b1 ;
      iflimit = mem [p ].hh.b0 ;
      condptr = mem [p ].hh .v.RH ;
      freenode ( p , 2 ) ;
    } 
  } 
  lab50: if ( curchr == 2 ) 
  {
    if ( ifstack [inopen ]== condptr ) 
    ifwarning () ;
    p = condptr ;
    ifline = mem [p + 1 ].cint ;
    curif = mem [p ].hh.b1 ;
    iflimit = mem [p ].hh.b0 ;
    condptr = mem [p ].hh .v.RH ;
    freenode ( p , 2 ) ;
  } 
  else iflimit = 2 ;
} 
void 
beginname ( void ) 
{
  beginname_regmem 
  areadelimiter = 0 ;
  extdelimiter = 0 ;
  quotedfilename = false ;
  filenamequotechar = 0 ;
} 
boolean 
zmorename ( UnicodeScalar c ) 
{
  register boolean Result; morename_regmem 
  if ( stopatspace && ( c == 32 ) && ( filenamequotechar == 0 ) ) 
  Result = false ;
  else if ( stopatspace && ( filenamequotechar != 0 ) && ( c == 
  filenamequotechar ) ) 
  {
    filenamequotechar = 0 ;
    Result = true ;
  } 
  else if ( stopatspace && ( filenamequotechar == 0 ) && ( ( c == 34 ) || ( c 
  == 39 ) ) ) 
  {
    filenamequotechar = c ;
    quotedfilename = true ;
    Result = true ;
  } 
  else {
      
    if ( ( c > 65535L ) ) 
    {
      if ( poolptr + 2 > poolsize ) 
      overflow ( 65539L , poolsize - initpoolptr ) ;
    } 
    else {
	
      if ( poolptr + 1 > poolsize ) 
      overflow ( 65539L , poolsize - initpoolptr ) ;
    } 
    {
      if ( ( c > 65535L ) ) 
      {
	strpool [poolptr ]= ( c - 65536L ) / 1024 + 55296L ;
	incr ( poolptr ) ;
	strpool [poolptr ]= ( c ) % 1024 + 56320L ;
	incr ( poolptr ) ;
      } 
      else {
	  
	strpool [poolptr ]= c ;
	incr ( poolptr ) ;
      } 
    } 
    if ( ISDIRSEP ( c ) ) 
    {
      areadelimiter = ( poolptr - strstart [( strptr ) - 65536L ]) ;
      extdelimiter = 0 ;
    } 
    else if ( c == 46 ) 
    extdelimiter = ( poolptr - strstart [( strptr ) - 65536L ]) ;
    Result = true ;
  } 
  return Result ;
} 
void 
endname ( void ) 
{
  endname_regmem 
  strnumber tempstr  ;
  poolpointer j  ;
  if ( strptr + 3 > maxstrings ) 
  overflow ( 65540L , maxstrings - initstrptr ) ;
  if ( areadelimiter == 0 ) 
  curarea = 65545L ;
  else {
      
    curarea = strptr ;
    strstart [( strptr + 1 ) - 65536L ]= strstart [( strptr ) - 65536L ]+ 
    areadelimiter ;
    incr ( strptr ) ;
    tempstr = searchstring ( curarea ) ;
    if ( tempstr > 0 ) 
    {
      curarea = tempstr ;
      decr ( strptr ) ;
      {register integer for_end; j = strstart [( strptr + 1 ) - 65536L ];
      for_end = poolptr - 1 ; if ( j <= for_end) do 
	{
	  strpool [j - areadelimiter ]= strpool [j ];
	} 
      while ( j++ < for_end ) ;} 
      poolptr = poolptr - areadelimiter ;
    } 
  } 
  if ( extdelimiter == 0 ) 
  {
    curext = 65545L ;
    curname = slowmakestring () ;
  } 
  else {
      
    curname = strptr ;
    strstart [( strptr + 1 ) - 65536L ]= strstart [( strptr ) - 65536L ]+ 
    extdelimiter - areadelimiter - 1 ;
    incr ( strptr ) ;
    curext = makestring () ;
    decr ( strptr ) ;
    tempstr = searchstring ( curname ) ;
    if ( tempstr > 0 ) 
    {
      curname = tempstr ;
      decr ( strptr ) ;
      {register integer for_end; j = strstart [( strptr + 1 ) - 65536L ];
      for_end = poolptr - 1 ; if ( j <= for_end) do 
	{
	  strpool [j - extdelimiter + areadelimiter + 1 ]= strpool [j ];
	} 
      while ( j++ < for_end ) ;} 
      poolptr = poolptr - extdelimiter + areadelimiter + 1 ;
    } 
    curext = slowmakestring () ;
  } 
} 
void 
zpackfilename ( strnumber n , strnumber a , strnumber e ) 
{
  packfilename_regmem 
  integer k  ;
  UnicodeScalar c  ;
  poolpointer j  ;
  k = 0 ;
  if ( nameoffile ) 
  libcfree ( nameoffile ) ;
  nameoffile = xmallocarray ( UTF8code , ( length ( a ) + length ( n ) + 
  length ( e ) ) * 3 + 1 ) ;
  {register integer for_end; j = strstart [( a ) - 65536L ];for_end = 
  strstart [( a + 1 ) - 65536L ]- 1 ; if ( j <= for_end) do 
    {
      c = strpool [j ];
      incr ( k ) ;
      if ( k <= maxint ) 
      {
	if ( ( c < 128 ) ) 
	nameoffile [k ]= c ;
	else if ( ( c < 2048 ) ) 
	{
	  nameoffile [k ]= 192 + c / 64 ;
	  incr ( k ) ;
	  nameoffile [k ]= 128 + c % 64 ;
	} 
	else if ( ( c < 55296L ) ) 
	{
	  nameoffile [k ]= 224 + c / 4096 ;
	  incr ( k ) ;
	  nameoffile [k ]= 128 + ( c % 4096 ) / 64 ;
	  incr ( k ) ;
	  nameoffile [k ]= 128 + c % 64 ;
	} 
	else if ( ( c < 56320L ) && ( k + 3 < maxint ) ) 
	{
	  nameoffile [k ]= 240 + ( c - 55232L ) / 4096 ;
	  incr ( k ) ;
	  nameoffile [k ]= 128 + ( ( c - 55232L ) % 4096 ) / 4 ;
	  incr ( k ) ;
	  nameoffile [k ]= 128 + ( c - 55232L ) % 4 * 16 ;
	  incr ( k ) ;
	  nameoffile [k ]= 128 ;
	} 
	else if ( ( c < 57344L ) && ( k > 4 ) ) 
	{
	  decr ( k ) ;
	  nameoffile [k - 1 ]= nameoffile [k - 1 ]+ ( c - 56320L ) / 64 ;
	  nameoffile [k ]= nameoffile [k ]+ ( c - 56320L ) % 64 ;
	} 
	else if ( ( c < 65536L ) ) 
	{
	  nameoffile [k ]= 224 + c / 4096 ;
	  incr ( k ) ;
	  nameoffile [k ]= 128 + ( c % 4096 ) / 64 ;
	  incr ( k ) ;
	  nameoffile [k ]= 128 + c % 64 ;
	} 
	else {
	    
	  nameoffile [k ]= 239 ;
	  incr ( k ) ;
	  nameoffile [k ]= 191 ;
	  incr ( k ) ;
	  nameoffile [k ]= 189 ;
	} 
      } 
    } 
  while ( j++ < for_end ) ;} 
  {register integer for_end; j = strstart [( n ) - 65536L ];for_end = 
  strstart [( n + 1 ) - 65536L ]- 1 ; if ( j <= for_end) do 
    {
      c = strpool [j ];
      incr ( k ) ;
      if ( k <= maxint ) 
      {
	if ( ( c < 128 ) ) 
	nameoffile [k ]= c ;
	else if ( ( c < 2048 ) ) 
	{
	  nameoffile [k ]= 192 + c / 64 ;
	  incr ( k ) ;
	  nameoffile [k ]= 128 + c % 64 ;
	} 
	else if ( ( c < 55296L ) ) 
	{
	  nameoffile [k ]= 224 + c / 4096 ;
	  incr ( k ) ;
	  nameoffile [k ]= 128 + ( c % 4096 ) / 64 ;
	  incr ( k ) ;
	  nameoffile [k ]= 128 + c % 64 ;
	} 
	else if ( ( c < 56320L ) && ( k + 3 < maxint ) ) 
	{
	  nameoffile [k ]= 240 + ( c - 55232L ) / 4096 ;
	  incr ( k ) ;
	  nameoffile [k ]= 128 + ( ( c - 55232L ) % 4096 ) / 4 ;
	  incr ( k ) ;
	  nameoffile [k ]= 128 + ( c - 55232L ) % 4 * 16 ;
	  incr ( k ) ;
	  nameoffile [k ]= 128 ;
	} 
	else if ( ( c < 57344L ) && ( k > 4 ) ) 
	{
	  decr ( k ) ;
	  nameoffile [k - 1 ]= nameoffile [k - 1 ]+ ( c - 56320L ) / 64 ;
	  nameoffile [k ]= nameoffile [k ]+ ( c - 56320L ) % 64 ;
	} 
	else if ( ( c < 65536L ) ) 
	{
	  nameoffile [k ]= 224 + c / 4096 ;
	  incr ( k ) ;
	  nameoffile [k ]= 128 + ( c % 4096 ) / 64 ;
	  incr ( k ) ;
	  nameoffile [k ]= 128 + c % 64 ;
	} 
	else {
	    
	  nameoffile [k ]= 239 ;
	  incr ( k ) ;
	  nameoffile [k ]= 191 ;
	  incr ( k ) ;
	  nameoffile [k ]= 189 ;
	} 
      } 
    } 
  while ( j++ < for_end ) ;} 
  {register integer for_end; j = strstart [( e ) - 65536L ];for_end = 
  strstart [( e + 1 ) - 65536L ]- 1 ; if ( j <= for_end) do 
    {
      c = strpool [j ];
      incr ( k ) ;
      if ( k <= maxint ) 
      {
	if ( ( c < 128 ) ) 
	nameoffile [k ]= c ;
	else if ( ( c < 2048 ) ) 
	{
	  nameoffile [k ]= 192 + c / 64 ;
	  incr ( k ) ;
	  nameoffile [k ]= 128 + c % 64 ;
	} 
	else if ( ( c < 55296L ) ) 
	{
	  nameoffile [k ]= 224 + c / 4096 ;
	  incr ( k ) ;
	  nameoffile [k ]= 128 + ( c % 4096 ) / 64 ;
	  incr ( k ) ;
	  nameoffile [k ]= 128 + c % 64 ;
	} 
	else if ( ( c < 56320L ) && ( k + 3 < maxint ) ) 
	{
	  nameoffile [k ]= 240 + ( c - 55232L ) / 4096 ;
	  incr ( k ) ;
	  nameoffile [k ]= 128 + ( ( c - 55232L ) % 4096 ) / 4 ;
	  incr ( k ) ;
	  nameoffile [k ]= 128 + ( c - 55232L ) % 4 * 16 ;
	  incr ( k ) ;
	  nameoffile [k ]= 128 ;
	} 
	else if ( ( c < 57344L ) && ( k > 4 ) ) 
	{
	  decr ( k ) ;
	  nameoffile [k - 1 ]= nameoffile [k - 1 ]+ ( c - 56320L ) / 64 ;
	  nameoffile [k ]= nameoffile [k ]+ ( c - 56320L ) % 64 ;
	} 
	else if ( ( c < 65536L ) ) 
	{
	  nameoffile [k ]= 224 + c / 4096 ;
	  incr ( k ) ;
	  nameoffile [k ]= 128 + ( c % 4096 ) / 64 ;
	  incr ( k ) ;
	  nameoffile [k ]= 128 + c % 64 ;
	} 
	else {
	    
	  nameoffile [k ]= 239 ;
	  incr ( k ) ;
	  nameoffile [k ]= 191 ;
	  incr ( k ) ;
	  nameoffile [k ]= 189 ;
	} 
      } 
    } 
  while ( j++ < for_end ) ;} 
  if ( k <= maxint ) 
  namelength = k ;
  else namelength = maxint ;
  nameoffile [namelength + 1 ]= 0 ;
} 
void 
zpackbufferedname ( smallnumber n , integer a , integer b ) 
{
  packbufferedname_regmem 
  integer k  ;
  UTF16code c  ;
  integer j  ;
  if ( n + b - a + 5 > maxint ) 
  b = a + maxint - n - 5 ;
  k = 0 ;
  if ( nameoffile ) 
  libcfree ( nameoffile ) ;
  nameoffile = xmallocarray ( UTF8code , n + ( b - a + 1 ) + 5 ) ;
  {register integer for_end; j = 1 ;for_end = n ; if ( j <= for_end) do 
    {
      c = TEXformatdefault [j ];
      incr ( k ) ;
      if ( k <= maxint ) 
      {
	if ( ( c < 128 ) ) 
	nameoffile [k ]= c ;
	else if ( ( c < 2048 ) ) 
	{
	  nameoffile [k ]= 192 + c / 64 ;
	  incr ( k ) ;
	  nameoffile [k ]= 128 + c % 64 ;
	} 
	else if ( ( c < 55296L ) ) 
	{
	  nameoffile [k ]= 224 + c / 4096 ;
	  incr ( k ) ;
	  nameoffile [k ]= 128 + ( c % 4096 ) / 64 ;
	  incr ( k ) ;
	  nameoffile [k ]= 128 + c % 64 ;
	} 
	else if ( ( c < 56320L ) && ( k + 3 < maxint ) ) 
	{
	  nameoffile [k ]= 240 + ( c - 55232L ) / 4096 ;
	  incr ( k ) ;
	  nameoffile [k ]= 128 + ( ( c - 55232L ) % 4096 ) / 4 ;
	  incr ( k ) ;
	  nameoffile [k ]= 128 + ( c - 55232L ) % 4 * 16 ;
	  incr ( k ) ;
	  nameoffile [k ]= 128 ;
	} 
	else if ( ( c < 57344L ) && ( k > 4 ) ) 
	{
	  decr ( k ) ;
	  nameoffile [k - 1 ]= nameoffile [k - 1 ]+ ( c - 56320L ) / 64 ;
	  nameoffile [k ]= nameoffile [k ]+ ( c - 56320L ) % 64 ;
	} 
	else if ( ( c < 65536L ) ) 
	{
	  nameoffile [k ]= 224 + c / 4096 ;
	  incr ( k ) ;
	  nameoffile [k ]= 128 + ( c % 4096 ) / 64 ;
	  incr ( k ) ;
	  nameoffile [k ]= 128 + c % 64 ;
	} 
	else {
	    
	  nameoffile [k ]= 239 ;
	  incr ( k ) ;
	  nameoffile [k ]= 191 ;
	  incr ( k ) ;
	  nameoffile [k ]= 189 ;
	} 
      } 
    } 
  while ( j++ < for_end ) ;} 
  {register integer for_end; j = a ;for_end = b ; if ( j <= for_end) do 
    {
      c = buffer [j ];
      incr ( k ) ;
      if ( k <= maxint ) 
      {
	if ( ( c < 128 ) ) 
	nameoffile [k ]= c ;
	else if ( ( c < 2048 ) ) 
	{
	  nameoffile [k ]= 192 + c / 64 ;
	  incr ( k ) ;
	  nameoffile [k ]= 128 + c % 64 ;
	} 
	else if ( ( c < 55296L ) ) 
	{
	  nameoffile [k ]= 224 + c / 4096 ;
	  incr ( k ) ;
	  nameoffile [k ]= 128 + ( c % 4096 ) / 64 ;
	  incr ( k ) ;
	  nameoffile [k ]= 128 + c % 64 ;
	} 
	else if ( ( c < 56320L ) && ( k + 3 < maxint ) ) 
	{
	  nameoffile [k ]= 240 + ( c - 55232L ) / 4096 ;
	  incr ( k ) ;
	  nameoffile [k ]= 128 + ( ( c - 55232L ) % 4096 ) / 4 ;
	  incr ( k ) ;
	  nameoffile [k ]= 128 + ( c - 55232L ) % 4 * 16 ;
	  incr ( k ) ;
	  nameoffile [k ]= 128 ;
	} 
	else if ( ( c < 57344L ) && ( k > 4 ) ) 
	{
	  decr ( k ) ;
	  nameoffile [k - 1 ]= nameoffile [k - 1 ]+ ( c - 56320L ) / 64 ;
	  nameoffile [k ]= nameoffile [k ]+ ( c - 56320L ) % 64 ;
	} 
	else if ( ( c < 65536L ) ) 
	{
	  nameoffile [k ]= 224 + c / 4096 ;
	  incr ( k ) ;
	  nameoffile [k ]= 128 + ( c % 4096 ) / 64 ;
	  incr ( k ) ;
	  nameoffile [k ]= 128 + c % 64 ;
	} 
	else {
	    
	  nameoffile [k ]= 239 ;
	  incr ( k ) ;
	  nameoffile [k ]= 191 ;
	  incr ( k ) ;
	  nameoffile [k ]= 189 ;
	} 
      } 
    } 
  while ( j++ < for_end ) ;} 
  {register integer for_end; j = formatdefaultlength - 3 ;for_end = 
  formatdefaultlength ; if ( j <= for_end) do 
    {
      c = TEXformatdefault [j ];
      incr ( k ) ;
      if ( k <= maxint ) 
      {
	if ( ( c < 128 ) ) 
	nameoffile [k ]= c ;
	else if ( ( c < 2048 ) ) 
	{
	  nameoffile [k ]= 192 + c / 64 ;
	  incr ( k ) ;
	  nameoffile [k ]= 128 + c % 64 ;
	} 
	else if ( ( c < 55296L ) ) 
	{
	  nameoffile [k ]= 224 + c / 4096 ;
	  incr ( k ) ;
	  nameoffile [k ]= 128 + ( c % 4096 ) / 64 ;
	  incr ( k ) ;
	  nameoffile [k ]= 128 + c % 64 ;
	} 
	else if ( ( c < 56320L ) && ( k + 3 < maxint ) ) 
	{
	  nameoffile [k ]= 240 + ( c - 55232L ) / 4096 ;
	  incr ( k ) ;
	  nameoffile [k ]= 128 + ( ( c - 55232L ) % 4096 ) / 4 ;
	  incr ( k ) ;
	  nameoffile [k ]= 128 + ( c - 55232L ) % 4 * 16 ;
	  incr ( k ) ;
	  nameoffile [k ]= 128 ;
	} 
	else if ( ( c < 57344L ) && ( k > 4 ) ) 
	{
	  decr ( k ) ;
	  nameoffile [k - 1 ]= nameoffile [k - 1 ]+ ( c - 56320L ) / 64 ;
	  nameoffile [k ]= nameoffile [k ]+ ( c - 56320L ) % 64 ;
	} 
	else if ( ( c < 65536L ) ) 
	{
	  nameoffile [k ]= 224 + c / 4096 ;
	  incr ( k ) ;
	  nameoffile [k ]= 128 + ( c % 4096 ) / 64 ;
	  incr ( k ) ;
	  nameoffile [k ]= 128 + c % 64 ;
	} 
	else {
	    
	  nameoffile [k ]= 239 ;
	  incr ( k ) ;
	  nameoffile [k ]= 191 ;
	  incr ( k ) ;
	  nameoffile [k ]= 189 ;
	} 
      } 
    } 
  while ( j++ < for_end ) ;} 
  if ( k <= maxint ) 
  namelength = k ;
  else namelength = maxint ;
  nameoffile [namelength + 1 ]= 0 ;
} 
strnumber 
makenamestring ( void ) 
{
  register strnumber Result; makenamestring_regmem 
  integer k  ;
  poolpointer saveareadelimiter, saveextdelimiter  ;
  boolean savenameinprogress, savestopatspace  ;
  if ( ( poolptr + namelength > poolsize ) || ( strptr == maxstrings ) || ( ( 
  poolptr - strstart [( strptr ) - 65536L ]) > 0 ) ) 
  Result = 63 ;
  else {
      
    makeutf16name () ;
    {register integer for_end; k = 0 ;for_end = namelength16 - 1 ; if ( k <= 
    for_end) do 
      {
	if ( ( nameoffile16 [k ]> 65535L ) ) 
	{
	  strpool [poolptr ]= ( nameoffile16 [k ]- 65536L ) / 1024 + 
	  55296L ;
	  incr ( poolptr ) ;
	  strpool [poolptr ]= ( nameoffile16 [k ]) % 1024 + 56320L ;
	  incr ( poolptr ) ;
	} 
	else {
	    
	  strpool [poolptr ]= nameoffile16 [k ];
	  incr ( poolptr ) ;
	} 
      } 
    while ( k++ < for_end ) ;} 
    Result = makestring () ;
    saveareadelimiter = areadelimiter ;
    saveextdelimiter = extdelimiter ;
    savenameinprogress = nameinprogress ;
    savestopatspace = stopatspace ;
    nameinprogress = true ;
    beginname () ;
    stopatspace = false ;
    k = 0 ;
    while ( ( k < namelength16 ) && ( morename ( nameoffile16 [k ]) ) ) incr 
    ( k ) ;
    stopatspace = savestopatspace ;
    endname () ;
    nameinprogress = savenameinprogress ;
    areadelimiter = saveareadelimiter ;
    extdelimiter = saveextdelimiter ;
  } 
  return Result ;
} 
strnumber 
zzumakenamestring ( unicodefile * f ) 
{
  register strnumber Result; umakenamestring_regmem 
  Result = makenamestring () ;
  return Result ;
} 
strnumber 
zamakenamestring ( alphafile f ) 
{
  register strnumber Result; amakenamestring_regmem 
  Result = makenamestring () ;
  return Result ;
} 
strnumber 
zbmakenamestring ( bytefile f ) 
{
  register strnumber Result; bmakenamestring_regmem 
  Result = makenamestring () ;
  return Result ;
} 
strnumber 
zzwmakenamestring ( wordfile * f ) 
{
  register strnumber Result; wmakenamestring_regmem 
  Result = makenamestring () ;
  return Result ;
} 
void 
scanfilename ( void ) 
{
  /* 30 */ scanfilename_regmem 
  halfword savewarningindex  ;
  savewarningindex = warningindex ;
  warningindex = curcs ;
  do {
      getxtoken () ;
  } while ( ! ( ( curcmd != 10 ) && ( curcmd != 0 ) ) ) ;
  backinput () ;
  if ( curcmd == 1 ) 
  scanfilenamebraced () ;
  else {
      
    nameinprogress = true ;
    beginname () ;
    do {
	getxtoken () ;
    } while ( ! ( curcmd != 10 ) ) ;
    while ( true ) {
	
      if ( ( curcmd > 12 ) || ( curchr > 1114111L ) ) 
      {
	backinput () ;
	goto lab30 ;
      } 
      if ( ! morename ( curchr ) ) 
      goto lab30 ;
      getxtoken () ;
    } 
  } 
  lab30: endname () ;
  nameinprogress = false ;
  warningindex = savewarningindex ;
} 
void 
zpackjobname ( strnumber s ) 
{
  packjobname_regmem 
  curarea = 65545L ;
  curext = s ;
  curname = jobname ;
  packfilename ( curname , curarea , curext ) ;
} 
void 
zpromptfilename ( strnumber s , strnumber e ) 
{
  /* 30 */ promptfilename_regmem 
  integer k  ;
  strnumber savedcurname  ;
  strnumber savedcurext  ;
  strnumber savedcurarea  ;
  if ( interaction == 2 ) 
  ;
  if ( s == 66177L ) 
  {
    if ( interaction == 3 ) 
    ;
    if ( filelineerrorstylep ) 
    printfileline () ;
    else printnl ( 65544L ) ;
    print ( 66178L ) ;
  } 
  else {
      
    if ( interaction == 3 ) 
    ;
    if ( filelineerrorstylep ) 
    printfileline () ;
    else printnl ( 65544L ) ;
    print ( 66179L ) ;
  } 
  printfilename ( curname , curarea , curext ) ;
  print ( 66180L ) ;
  if ( ( e == 66181L ) || ( e == 65545L ) ) 
  showcontext () ;
  println () ;
  printcstring ( promptfilenamehelpmsg ) ;
  if ( ( e != 65545L ) ) 
  {
    print ( 66182L ) ;
    print ( e ) ;
    print ( 39 ) ;
  } 
  print ( 41 ) ;
  println () ;
  printnl ( 66183L ) ;
  print ( s ) ;
  if ( interaction < 2 ) 
  fatalerror ( 66184L ) ;
  savedcurname = curname ;
  savedcurext = curext ;
  savedcurarea = curarea ;
  {
    ;
    print ( 65595L ) ;
    terminput () ;
  } 
  {
    beginname () ;
    k = first ;
    while ( ( buffer [k ]== 32 ) && ( k < last ) ) incr ( k ) ;
    while ( true ) {
	
      if ( k == last ) 
      goto lab30 ;
      if ( ! morename ( buffer [k ]) ) 
      goto lab30 ;
      incr ( k ) ;
    } 
    lab30: endname () ;
  } 
  if ( ( length ( curname ) == 0 ) && ( curext == 65545L ) && ( curarea == 
  65545L ) ) 
  {
    curname = savedcurname ;
    curext = savedcurext ;
    curarea = savedcurarea ;
  } 
  else if ( curext == 65545L ) 
  curext = e ;
  packfilename ( curname , curarea , curext ) ;
} 
void 
openlogfile ( void ) 
{
  openlogfile_regmem 
  unsigned char oldsetting  ;
  integer k  ;
  integer l  ;
  constcstring months  ;
  oldsetting = selector ;
  if ( jobname == 0 ) 
  jobname = getjobname ( 66188L ) ;
  packjobname ( 66189L ) ;
  recorderchangefilename ( stringcast ( nameoffile + 1 ) ) ;
  packjobname ( 66190L ) ;
  while ( ! aopenout ( logfile ) ) {
      
    selector = 17 ;
    promptfilename ( 66192L , 66190L ) ;
  } 
  texmflogname = amakenamestring ( logfile ) ;
  selector = 18 ;
  logopened = true ;
  {
    if ( srcspecialsp || filelineerrorstylep || parsefirstlinep ) 
    fprintf ( logfile , "%s%s%s",  "This is XeTeX, Version 3.141592653" , "-2.6" ,     "-0.999997" ) ;
    else
    fprintf ( logfile , "%s%s%s",  "This is XeTeX, Version 3.141592653" , "-2.6" ,     "-0.999997" ) ;
    Fputs ( logfile ,  versionstring ) ;
    print ( formatident ) ;
    print ( 66193L ) ;
    printint ( sysday ) ;
    printchar ( 32 ) ;
    months = " JANFEBMARAPRMAYJUNJULAUGSEPOCTNOVDEC" ;
    {register integer for_end; k = 3 * sysmonth - 2 ;for_end = 3 * sysmonth 
    ; if ( k <= for_end) do 
      putc ( months [k ],  logfile );
    while ( k++ < for_end ) ;} 
    printchar ( 32 ) ;
    printint ( sysyear ) ;
    printchar ( 32 ) ;
    printtwo ( systime / 60 ) ;
    printchar ( 58 ) ;
    printtwo ( systime % 60 ) ;
    if ( ( eTeXmode == 1 ) ) 
    {
      ;
      putc ('\n',  logfile );
      Fputs ( logfile ,  "entering extended mode" ) ;
    } 
    if ( shellenabledp ) 
    {
      putc ('\n',  logfile );
      putc ( ' ' ,  logfile );
      if ( restrictedshell ) 
      {
	Fputs ( logfile ,  "restricted " ) ;
      } 
      Fputs ( logfile ,  "\\write18 enabled." ) ;
    } 
    if ( srcspecialsp ) 
    {
      putc ('\n',  logfile );
      Fputs ( logfile ,  " Source specials enabled." ) ;
    } 
    if ( filelineerrorstylep ) 
    {
      putc ('\n',  logfile );
      Fputs ( logfile ,  " file:line:error style messages enabled." ) ;
    } 
    if ( parsefirstlinep ) 
    {
      putc ('\n',  logfile );
      Fputs ( logfile ,  " %&-line parsing enabled." ) ;
    } 
    if ( translatefilename ) 
    {
      putc ('\n',  logfile );
      Fputs ( logfile ,  " (WARNING: translate-file \"" ) ;
      fputs ( translatefilename , logfile ) ;
      Fputs ( logfile ,  "\" ignored)" ) ;
    } 
  } 
  if ( mltexenabledp ) 
  {
    putc ('\n',  logfile );
    Fputs ( logfile ,  "MLTeX v2.2 enabled" ) ;
  } 
  inputstack [inputptr ]= curinput ;
  printnl ( 66191L ) ;
  l = inputstack [0 ].limitfield ;
  if ( buffer [l ]== eqtb [7892312L ].cint ) 
  decr ( l ) ;
  {register integer for_end; k = 1 ;for_end = l ; if ( k <= for_end) do 
    print ( buffer [k ]) ;
  while ( k++ < for_end ) ;} 
  println () ;
  selector = oldsetting + 2 ;
} 
void 
startinput ( void ) 
{
  /* 30 */ startinput_regmem 
  strnumber tempstr  ;
  halfword v  ;
  integer k  ;
  scanfilename () ;
  packfilename ( curname , curarea , curext ) ;
  while ( true ) {
      
    beginfilereading () ;
    texinputtype = 1 ;
    if ( kpseinnameok ( stringcast ( nameoffile + 1 ) ) && uopenin ( inputfile 
    [curinput .indexfield ], kpsetexformat , eqtb [7892345L ].cint , eqtb 
    [7892346L ].cint ) ) 
    {
      makeutf16name () ;
      nameinprogress = true ;
      beginname () ;
      stopatspace = false ;
      k = 0 ;
      while ( ( k < namelength16 ) && ( morename ( nameoffile16 [k ]) ) ) 
      incr ( k ) ;
      stopatspace = true ;
      endname () ;
      nameinprogress = false ;
      goto lab30 ;
    } 
    endfilereading () ;
    promptfilename ( 66177L , 65545L ) ;
  } 
  lab30: curinput .namefield = amakenamestring ( inputfile [curinput 
  .indexfield ]) ;
  sourcefilenamestack [inopen ]= curinput .namefield ;
  fullsourcefilenamestack [inopen ]= makefullnamestring () ;
  if ( curinput .namefield == strptr - 1 ) 
  {
    tempstr = searchstring ( curinput .namefield ) ;
    if ( tempstr > 0 ) 
    {
      curinput .namefield = tempstr ;
      {
	decr ( strptr ) ;
	poolptr = strstart [( strptr ) - 65536L ];
      } 
    } 
  } 
  if ( jobname == 0 ) 
  {
    jobname = getjobname ( curname ) ;
    openlogfile () ;
  } 
  if ( termoffset + length ( fullsourcefilenamestack [inopen ]) > 
  maxprintline - 2 ) 
  println () ;
  else if ( ( termoffset > 0 ) || ( fileoffset > 0 ) ) 
  printchar ( 32 ) ;
  printchar ( 40 ) ;
  incr ( openparens ) ;
  print ( fullsourcefilenamestack [inopen ]) ;
  fflush ( stdout ) ;
  if ( eqtb [7892322L ].cint > 0 ) 
  {
    begindiagnostic () ;
    println () ;
    printchar ( 126 ) ;
    v = inputptr - 1 ;
    if ( v < eqtb [7892322L ].cint ) 
    while ( v > 0 ) {
	
      printchar ( 46 ) ;
      decr ( v ) ;
    } 
    else printchar ( 126 ) ;
    print ( 66194L ) ;
    print ( curname ) ;
    print ( curext ) ;
    println () ;
    enddiagnostic ( false ) ;
  } 
  curinput .statefield = 33 ;
  synctexstartinput () ;
  {
    line = 1 ;
    if ( inputln ( inputfile [curinput .indexfield ], false ) ) 
    ;
    firmuptheline () ;
    if ( ( eqtb [7892312L ].cint < 0 ) || ( eqtb [7892312L ].cint > 255 ) 
    ) 
    decr ( curinput .limitfield ) ;
    else buffer [curinput .limitfield ]= eqtb [7892312L ].cint ;
    first = curinput .limitfield + 1 ;
    curinput .locfield = curinput .startfield ;
  } 
} 
fourquarters 
zeffectivecharinfo ( internalfontnumber f , quarterword c ) 
{
  /* 10 */ register fourquarters Result; effectivecharinfo_regmem 
  fourquarters ci  ;
  integer basec  ;
  if ( ( ! xtxligaturepresent ) && ( fontmapping [f ]!= nil ) ) 
  c = applytfmfontmapping ( fontmapping [f ], c ) ;
  xtxligaturepresent = false ;
  if ( ! mltexenabledp ) 
  {
    Result = fontinfo [charbase [f ]+ c ].qqqq ;
    return Result ;
  } 
  if ( fontec [f ]>= c ) {
      
    if ( fontbc [f ]<= c ) 
    {
      ci = fontinfo [charbase [f ]+ c ].qqqq ;
      if ( ( ci .b0 > 0 ) ) 
      {
	Result = ci ;
	return Result ;
      } 
    } 
  } 
  if ( c >= eqtb [7892319L ].cint ) {
      
    if ( c <= eqtb [7892320L ].cint ) {
	
      if ( ( eqtb [6778152L + c ].hh .v.RH > 0 ) ) 
      {
	basec = ( eqtb [6778152L + c ].hh .v.RH % 256 ) ;
	if ( fontec [f ]>= basec ) {
	    
	  if ( fontbc [f ]<= basec ) 
	  {
	    ci = fontinfo [charbase [f ]+ basec ].qqqq ;
	    if ( ( ci .b0 > 0 ) ) 
	    {
	      Result = ci ;
	      return Result ;
	    } 
	  } 
	} 
      } 
    } 
  } 
  Result = nullcharacter ;
  return Result ;
} 
void 
zprintucscode ( UnicodeScalar n ) 
{
  printucscode_regmem 
  unsigned char k  ;
  k = 0 ;
  print ( 66224L ) ;
  do {
      dig [k ]= n % 16 ;
    n = n / 16 ;
    incr ( k ) ;
  } while ( ! ( n == 0 ) ) ;
  while ( k < 4 ) {
      
    dig [k ]= 0 ;
    incr ( k ) ;
  } 
  printthedigs ( k ) ;
} 
void 
zcharwarning ( internalfontnumber f , integer c ) 
{
  charwarning_regmem 
  integer oldsetting  ;
  if ( eqtb [7892299L ].cint > 0 ) 
  {
    oldsetting = eqtb [7892293L ].cint ;
    if ( ( eTeXmode == 1 ) && ( eqtb [7892299L ].cint > 1 ) ) 
    eqtb [7892293L ].cint = 1 ;
    if ( eqtb [7892299L ].cint > 2 ) 
    {
      if ( interaction == 3 ) 
      ;
      if ( filelineerrorstylep ) 
      printfileline () ;
      else printnl ( 65544L ) ;
      print ( 66225L ) ;
    } 
    else {
	
      begindiagnostic () ;
      printnl ( 66225L ) ;
    } 
    if ( c < 65536L ) 
    print ( c ) ;
    else printchar ( c ) ;
    print ( 65568L ) ;
    if ( ( ( fontarea [f ]== 65535L ) || ( fontarea [f ]== 65534L ) ) ) 
    printucscode ( c ) ;
    else printhex ( c ) ;
    print ( 41 ) ;
    print ( 66226L ) ;
    print ( fontname [f ]) ;
    if ( eqtb [7892299L ].cint < 3 ) 
    printchar ( 33 ) ;
    eqtb [7892293L ].cint = oldsetting ;
    if ( eqtb [7892299L ].cint > 2 ) 
    {
      helpptr = 0 ;
      error () ;
    } 
    else enddiagnostic ( false ) ;
  } 
} 
halfword 
znewnativewordnode ( internalfontnumber f , integer n ) 
{
  register halfword Result; newnativewordnode_regmem 
  integer l  ;
  halfword q  ;
  l = 6 + ( n * sizeof ( UTF16code ) + sizeof ( memoryword ) - 1 ) / sizeof ( 
  memoryword ) ;
  q = getnode ( l ) ;
  mem [q ].hh.b0 = 8 ;
  if ( ( eqtb [7892349L ].cint > 0 ) ) 
  mem [q ].hh.b1 = 41 ;
  else mem [q ].hh.b1 = 40 ;
  mem [q + 4 ].qqqq .b0 = l ;
  mem [q + 4 ].qqqq .b1 = f ;
  mem [q + 4 ].qqqq .b2 = n ;
  mem [q + 4 ].qqqq .b3 = 0 ;
  mem [q + 5 ].ptr = nullptr ;
  Result = q ;
  return Result ;
} 
halfword 
znewnativecharacter ( internalfontnumber f , UnicodeScalar c ) 
{
  register halfword Result; newnativecharacter_regmem 
  halfword p  ;
  integer i, len  ;
  if ( fontmapping [f ]!= 0 ) 
  {
    if ( ( c > 65535L ) ) 
    {
      if ( poolptr + 2 > poolsize ) 
      overflow ( 65539L , poolsize - initpoolptr ) ;
    } 
    else {
	
      if ( poolptr + 1 > poolsize ) 
      overflow ( 65539L , poolsize - initpoolptr ) ;
    } 
    {
      if ( ( c > 65535L ) ) 
      {
	strpool [poolptr ]= ( c - 65536L ) / 1024 + 55296L ;
	incr ( poolptr ) ;
	strpool [poolptr ]= ( c ) % 1024 + 56320L ;
	incr ( poolptr ) ;
      } 
      else {
	  
	strpool [poolptr ]= c ;
	incr ( poolptr ) ;
      } 
    } 
    len = applymapping ( fontmapping [f ], addressof ( strpool [strstart [
    ( strptr ) - 65536L ]]) , ( poolptr - strstart [( strptr ) - 65536L ]) 
    ) ;
    poolptr = strstart [( strptr ) - 65536L ];
    i = 0 ;
    while ( i < len ) {
	
      if ( ( mappedtext [i ]>= 55296L ) && ( mappedtext [i ]< 56320L ) ) 
      {
	c = ( mappedtext [i ]- 55296L ) * 1024 + mappedtext [i + 1 ]+ 9216 
	;
	if ( mapchartoglyph ( f , c ) == 0 ) 
	{
	  charwarning ( f , c ) ;
	} 
	i = i + 2 ;
      } 
      else {
	  
	if ( mapchartoglyph ( f , mappedtext [i ]) == 0 ) 
	{
	  charwarning ( f , mappedtext [i ]) ;
	} 
	i = i + 1 ;
      } 
    } 
    p = newnativewordnode ( f , len ) ;
    {register integer for_end; i = 0 ;for_end = len - 1 ; if ( i <= for_end) 
    do 
      {
	setnativechar ( p , i , mappedtext [i ]) ;
      } 
    while ( i++ < for_end ) ;} 
  } 
  else {
      
    if ( eqtb [7892299L ].cint > 0 ) {
	
      if ( mapchartoglyph ( f , c ) == 0 ) 
      {
	charwarning ( f , c ) ;
      } 
    } 
    p = getnode ( 7 ) ;
    mem [p ].hh.b0 = 8 ;
    mem [p ].hh.b1 = 40 ;
    mem [p + 4 ].qqqq .b0 = 7 ;
    mem [p + 4 ].qqqq .b3 = 0 ;
    mem [p + 5 ].ptr = nullptr ;
    mem [p + 4 ].qqqq .b1 = f ;
    if ( c > 65535L ) 
    {
      mem [p + 4 ].qqqq .b2 = 2 ;
      setnativechar ( p , 0 , ( c - 65536L ) / 1024 + 55296L ) ;
      setnativechar ( p , 1 , ( c - 65536L ) % 1024 + 56320L ) ;
    } 
    else {
	
      mem [p + 4 ].qqqq .b2 = 1 ;
      setnativechar ( p , 0 , c ) ;
    } 
  } 
  setnativemetrics ( p , ( eqtb [7892342L ].cint > 0 ) ) ;
  Result = p ;
  return Result ;
} 
void 
zfontfeaturewarning ( voidpointer featureNameP , integer featLen , voidpointer 
settingNameP , integer setLen ) 
{
  fontfeaturewarning_regmem 
  integer i  ;
  begindiagnostic () ;
  printnl ( 66296L ) ;
  if ( setLen > 0 ) 
  {
    print ( 66297L ) ;
    printutf8str ( settingNameP , setLen ) ;
    print ( 66298L ) ;
  } 
  print ( 66299L ) ;
  printutf8str ( featureNameP , featLen ) ;
  print ( 66300L ) ;
  i = 1 ;
  while ( ord ( nameoffile [i ]) != 0 ) {
      
    printrawchar ( nameoffile [i ], true ) ;
    incr ( i ) ;
  } 
  print ( 66180L ) ;
  enddiagnostic ( false ) ;
} 
void 
zfontmappingwarning ( voidpointer mappingNameP , integer mappingNameLen , 
integer warningType ) 
{
  fontmappingwarning_regmem 
  integer i  ;
  begindiagnostic () ;
  if ( warningType == 0 ) 
  printnl ( 66301L ) ;
  else printnl ( 66302L ) ;
  printutf8str ( mappingNameP , mappingNameLen ) ;
  print ( 66303L ) ;
  i = 1 ;
  while ( ord ( nameoffile [i ]) != 0 ) {
      
    printrawchar ( nameoffile [i ], true ) ;
    incr ( i ) ;
  } 
  switch ( warningType ) 
  {case 1 : 
    print ( 66304L ) ;
    break ;
  case 2 : 
    {
      print ( 66305L ) ;
      printnl ( 66306L ) ;
    } 
    break ;
    default: 
    print ( 66180L ) ;
    break ;
  } 
  enddiagnostic ( false ) ;
} 
void 
graphitewarning ( void ) 
{
  graphitewarning_regmem 
  integer i  ;
  begindiagnostic () ;
  printnl ( 66307L ) ;
  i = 1 ;
  while ( ord ( nameoffile [i ]) != 0 ) {
      
    printrawchar ( nameoffile [i ], true ) ;
    incr ( i ) ;
  } 
  print ( 66308L ) ;
  enddiagnostic ( false ) ;
} 
internalfontnumber 
zloadnativefont ( halfword u , strnumber nom , strnumber aire , scaled s ) 
{
  /* 30 */ 
#define firstmathfontdimen ( 10 ) 
  register internalfontnumber Result; loadnativefont_regmem 
  integer k, numfontdimens  ;
  voidpointer fontengine  ;
  scaled actualsize  ;
  halfword p  ;
  scaled ascent, descent, fontslant, xht, capht  ;
  internalfontnumber f  ;
  strnumber fullname  ;
  Result = 0 ;
  fontengine = findnativefont ( nameoffile + 1 , s ) ;
  if ( fontengine == 0 ) 
  goto lab30 ;
  if ( s >= 0 ) 
  actualsize = s ;
  else {
      
    if ( ( s != -1000 ) ) 
    actualsize = xnoverd ( loadedfontdesignsize , - (integer) s , 1000 ) ;
    else actualsize = loadedfontdesignsize ;
  } 
  {
    if ( poolptr + namelength > poolsize ) 
    overflow ( 65539L , poolsize - initpoolptr ) ;
  } 
  {register integer for_end; k = 1 ;for_end = namelength ; if ( k <= 
  for_end) do 
    {
      if ( ( nameoffile [k ]> 65535L ) ) 
      {
	strpool [poolptr ]= ( nameoffile [k ]- 65536L ) / 1024 + 55296L ;
	incr ( poolptr ) ;
	strpool [poolptr ]= ( nameoffile [k ]) % 1024 + 56320L ;
	incr ( poolptr ) ;
      } 
      else {
	  
	strpool [poolptr ]= nameoffile [k ];
	incr ( poolptr ) ;
      } 
    } 
  while ( k++ < for_end ) ;} 
  fullname = makestring () ;
  {register integer for_end; f = 1 ;for_end = fontptr ; if ( f <= for_end) 
  do 
    if ( ( fontarea [f ]== nativefonttypeflag ) && streqstr ( fontname [f ]
    , fullname ) && ( fontsize [f ]== actualsize ) ) 
    {
      releasefontengine ( fontengine , nativefonttypeflag ) ;
      {
	decr ( strptr ) ;
	poolptr = strstart [( strptr ) - 65536L ];
      } 
      Result = f ;
      goto lab30 ;
    } 
  while ( f++ < for_end ) ;} 
  if ( ( nativefonttypeflag == 65534L ) && isOpenTypeMathFont ( fontengine ) ) 
  numfontdimens = firstmathfontdimen + 55 ;
  else numfontdimens = 8 ;
  if ( ( fontptr == fontmax ) || ( fmemptr + numfontdimens > fontmemsize ) ) 
  {
    {
      {
	if ( interaction == 3 ) 
	;
	if ( filelineerrorstylep ) 
	printfileline () ;
	else printnl ( 65544L ) ;
	print ( 66200L ) ;
      } 
      sprintcs ( u ) ;
      printchar ( 61 ) ;
      if ( filenamequotechar != 0 ) 
      printchar ( filenamequotechar ) ;
      printfilename ( nom , aire , curext ) ;
      if ( filenamequotechar != 0 ) 
      printchar ( filenamequotechar ) ;
      if ( s >= 0 ) 
      {
	print ( 66131L ) ;
	printscaled ( s ) ;
	print ( 65698L ) ;
      } 
      else if ( s != -1000 ) 
      {
	print ( 66197L ) ;
	printint ( - (integer) s ) ;
      } 
      print ( 66209L ) ;
      {
	helpptr = 4 ;
	helpline [3 ]= 66210L ;
	helpline [2 ]= 66211L ;
	helpline [1 ]= 66212L ;
	helpline [0 ]= 66213L ;
      } 
      error () ;
      goto lab30 ;
    } 
  } 
  incr ( fontptr ) ;
  fontarea [fontptr ]= nativefonttypeflag ;
  fontname [fontptr ]= fullname ;
  fontcheck [fontptr ].b0 = 0 ;
  fontcheck [fontptr ].b1 = 0 ;
  fontcheck [fontptr ].b2 = 0 ;
  fontcheck [fontptr ].b3 = 0 ;
  fontglue [fontptr ]= -268435455L ;
  fontdsize [fontptr ]= loadedfontdesignsize ;
  fontsize [fontptr ]= actualsize ;
  if ( ( nativefonttypeflag == 65535L ) ) 
  {
    aatgetfontmetrics ( fontengine , addressof ( ascent ) , addressof ( 
    descent ) , addressof ( xht ) , addressof ( capht ) , addressof ( 
    fontslant ) ) ;
  } 
  else {
      
    otgetfontmetrics ( fontengine , addressof ( ascent ) , addressof ( descent 
    ) , addressof ( xht ) , addressof ( capht ) , addressof ( fontslant ) ) ;
  } 
  heightbase [fontptr ]= ascent ;
  depthbase [fontptr ]= - (integer) descent ;
  fontparams [fontptr ]= numfontdimens ;
  fontbc [fontptr ]= 0 ;
  fontec [fontptr ]= 65535L ;
  fontused [fontptr ]= false ;
  hyphenchar [fontptr ]= eqtb [7892310L ].cint ;
  skewchar [fontptr ]= eqtb [7892311L ].cint ;
  parambase [fontptr ]= fmemptr - 1 ;
  fontlayoutengine [fontptr ]= fontengine ;
  fontmapping [fontptr ]= 0 ;
  fontletterspace [fontptr ]= loadedfontletterspace ;
  p = newnativecharacter ( fontptr , 32 ) ;
  s = mem [p + 1 ].cint + loadedfontletterspace ;
  freenode ( p , mem [p + 4 ].qqqq .b0 ) ;
  fontinfo [fmemptr ].cint = fontslant ;
  incr ( fmemptr ) ;
  fontinfo [fmemptr ].cint = s ;
  incr ( fmemptr ) ;
  fontinfo [fmemptr ].cint = s / 2 ;
  incr ( fmemptr ) ;
  fontinfo [fmemptr ].cint = s / 3 ;
  incr ( fmemptr ) ;
  fontinfo [fmemptr ].cint = xht ;
  incr ( fmemptr ) ;
  fontinfo [fmemptr ].cint = fontsize [fontptr ];
  incr ( fmemptr ) ;
  fontinfo [fmemptr ].cint = s / 3 ;
  incr ( fmemptr ) ;
  fontinfo [fmemptr ].cint = capht ;
  incr ( fmemptr ) ;
  if ( numfontdimens == firstmathfontdimen + 55 ) 
  {
    fontinfo [fmemptr ].cint = numfontdimens ;
    incr ( fmemptr ) ;
    {register integer for_end; k = 0 ;for_end = 55 ; if ( k <= for_end) do 
      {
	fontinfo [fmemptr ].cint = getotmathconstant ( fontptr , k ) ;
	incr ( fmemptr ) ;
      } 
    while ( k++ < for_end ) ;} 
  } 
  fontmapping [fontptr ]= loadedfontmapping ;
  fontflags [fontptr ]= loadedfontflags ;
  Result = fontptr ;
  lab30: ;
  return Result ;
} 
void 
zdolocalelinebreaks ( integer s , integer len ) 
{
  dolocalelinebreaks_regmem 
  integer offs, prevOffs, i  ;
  boolean usepenalty, useskip  ;
  if ( ( eqtb [7892336L ].cint == 0 ) || ( len == 1 ) ) 
  {
    mem [curlist .tailfield ].hh .v.RH = newnativewordnode ( mainf , len ) ;
    curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
    {register integer for_end; i = 0 ;for_end = len - 1 ; if ( i <= for_end) 
    do 
      setnativechar ( curlist .tailfield , i , nativetext [s + i ]) ;
    while ( i++ < for_end ) ;} 
    setnativemetrics ( curlist .tailfield , ( eqtb [7892342L ].cint > 0 ) ) 
    ;
  } 
  else {
      
    useskip = eqtb [1205779L ].hh .v.RH != membot ;
    usepenalty = eqtb [7892337L ].cint != 0 || ! useskip ;
    linebreakstart ( mainf , eqtb [7892336L ].cint , nativetext + s , len ) 
    ;
    offs = 0 ;
    do {
	prevOffs = offs ;
      offs = linebreaknext () ;
      if ( offs > 0 ) 
      {
	if ( prevOffs != 0 ) 
	{
	  if ( usepenalty ) 
	  {
	    mem [curlist .tailfield ].hh .v.RH = newpenalty ( eqtb [
	    7892337L ].cint ) ;
	    curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
	  } 
	  if ( useskip ) 
	  {
	    mem [curlist .tailfield ].hh .v.RH = newparamglue ( 15 ) ;
	    curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
	  } 
	} 
	mem [curlist .tailfield ].hh .v.RH = newnativewordnode ( mainf , 
	offs - prevOffs ) ;
	curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
	{register integer for_end; i = prevOffs ;for_end = offs - 1 ; if ( i 
	<= for_end) do 
	  setnativechar ( curlist .tailfield , i - prevOffs , nativetext [s + 
	  i ]) ;
	while ( i++ < for_end ) ;} 
	setnativemetrics ( curlist .tailfield , ( eqtb [7892342L ].cint > 0 
	) ) ;
      } 
    } while ( ! ( offs < 0 ) ) ;
  } 
} 
void 
badutf8warning ( void ) 
{
  badutf8warning_regmem 
  begindiagnostic () ;
  printnl ( 66309L ) ;
  if ( ( curinput .namefield == 0 ) ) 
  print ( 66310L ) ;
  else {
      
    print ( 66311L ) ;
    printint ( line ) ;
  } 
  print ( 66312L ) ;
  enddiagnostic ( false ) ;
} 
integer 
getinputnormalizationstate ( void ) 
{
  register integer Result; getinputnormalizationstate_regmem 
  if ( eqtb == nil ) 
  Result = 0 ;
  else Result = eqtb [7892344L ].cint ;
  return Result ;
} 
integer 
gettracingfontsstate ( void ) 
{
  register integer Result; gettracingfontsstate_regmem 
  Result = eqtb [7892347L ].cint ;
  return Result ;
} 
internalfontnumber 
zreadfontinfo ( halfword u , strnumber nom , strnumber aire , scaled s ) 
{
  /* 30 11 45 */ register internalfontnumber Result; readfontinfo_regmem 
  fontindex k  ;
  boolean nametoolong  ;
  boolean fileopened  ;
  halfword lf, lh, bc, ec, nw, nh, nd, ni, nl, nk, ne, np  ;
  internalfontnumber f  ;
  internalfontnumber g  ;
  eightbits a, b, c, d  ;
  fourquarters qw  ;
  scaled sw  ;
  integer bchlabel  ;
  short bchar  ;
  scaled z  ;
  integer alpha  ;
  unsigned char beta  ;
  g = 0 ;
  fileopened = false ;
  packfilename ( nom , aire , curext ) ;
  if ( eqtb [7892347L ].cint > 0 ) 
  {
    begindiagnostic () ;
    printnl ( 66196L ) ;
    printcstring ( stringcast ( nameoffile + 1 ) ) ;
    print ( '"' ) ;
    if ( s < 0 ) 
    {
      print ( 66197L ) ;
      printint ( - (integer) s ) ;
    } 
    else {
	
      print ( 66131L ) ;
      printscaled ( s ) ;
      print ( 65698L ) ;
    } 
    enddiagnostic ( false ) ;
  } 
  if ( quotedfilename ) 
  {
    g = loadnativefont ( u , nom , aire , s ) ;
    if ( g != 0 ) 
    goto lab30 ;
  } 
  nametoolong = ( length ( nom ) > 255 ) || ( length ( aire ) > 255 ) ;
  if ( nametoolong ) 
  goto lab11 ;
  packfilename ( nom , aire , 65545L ) ;
  checkfortfmfontmapping () ;
  if ( bopenin ( tfmfile ) ) 
  {
    fileopened = true ;
    {
      {
	lf = tfmtemp ;
	if ( lf > 127 ) 
	goto lab11 ;
	tfmtemp = getc ( tfmfile ) ;
	lf = lf * 256 + tfmtemp ;
      } 
      tfmtemp = getc ( tfmfile ) ;
      {
	lh = tfmtemp ;
	if ( lh > 127 ) 
	goto lab11 ;
	tfmtemp = getc ( tfmfile ) ;
	lh = lh * 256 + tfmtemp ;
      } 
      tfmtemp = getc ( tfmfile ) ;
      {
	bc = tfmtemp ;
	if ( bc > 127 ) 
	goto lab11 ;
	tfmtemp = getc ( tfmfile ) ;
	bc = bc * 256 + tfmtemp ;
      } 
      tfmtemp = getc ( tfmfile ) ;
      {
	ec = tfmtemp ;
	if ( ec > 127 ) 
	goto lab11 ;
	tfmtemp = getc ( tfmfile ) ;
	ec = ec * 256 + tfmtemp ;
      } 
      if ( ( bc > ec + 1 ) || ( ec > 255 ) ) 
      goto lab11 ;
      if ( bc > 255 ) 
      {
	bc = 1 ;
	ec = 0 ;
      } 
      tfmtemp = getc ( tfmfile ) ;
      {
	nw = tfmtemp ;
	if ( nw > 127 ) 
	goto lab11 ;
	tfmtemp = getc ( tfmfile ) ;
	nw = nw * 256 + tfmtemp ;
      } 
      tfmtemp = getc ( tfmfile ) ;
      {
	nh = tfmtemp ;
	if ( nh > 127 ) 
	goto lab11 ;
	tfmtemp = getc ( tfmfile ) ;
	nh = nh * 256 + tfmtemp ;
      } 
      tfmtemp = getc ( tfmfile ) ;
      {
	nd = tfmtemp ;
	if ( nd > 127 ) 
	goto lab11 ;
	tfmtemp = getc ( tfmfile ) ;
	nd = nd * 256 + tfmtemp ;
      } 
      tfmtemp = getc ( tfmfile ) ;
      {
	ni = tfmtemp ;
	if ( ni > 127 ) 
	goto lab11 ;
	tfmtemp = getc ( tfmfile ) ;
	ni = ni * 256 + tfmtemp ;
      } 
      tfmtemp = getc ( tfmfile ) ;
      {
	nl = tfmtemp ;
	if ( nl > 127 ) 
	goto lab11 ;
	tfmtemp = getc ( tfmfile ) ;
	nl = nl * 256 + tfmtemp ;
      } 
      tfmtemp = getc ( tfmfile ) ;
      {
	nk = tfmtemp ;
	if ( nk > 127 ) 
	goto lab11 ;
	tfmtemp = getc ( tfmfile ) ;
	nk = nk * 256 + tfmtemp ;
      } 
      tfmtemp = getc ( tfmfile ) ;
      {
	ne = tfmtemp ;
	if ( ne > 127 ) 
	goto lab11 ;
	tfmtemp = getc ( tfmfile ) ;
	ne = ne * 256 + tfmtemp ;
      } 
      tfmtemp = getc ( tfmfile ) ;
      {
	np = tfmtemp ;
	if ( np > 127 ) 
	goto lab11 ;
	tfmtemp = getc ( tfmfile ) ;
	np = np * 256 + tfmtemp ;
      } 
      if ( lf != 6 + lh + ( ec - bc + 1 ) + nw + nh + nd + ni + nl + nk + ne + 
      np ) 
      goto lab11 ;
      if ( ( nw == 0 ) || ( nh == 0 ) || ( nd == 0 ) || ( ni == 0 ) ) 
      goto lab11 ;
    } 
    lf = lf - 6 - lh ;
    if ( np < 7 ) 
    lf = lf + 7 - np ;
    if ( ( fontptr == fontmax ) || ( fmemptr + lf > fontmemsize ) ) 
    {
      {
	if ( interaction == 3 ) 
	;
	if ( filelineerrorstylep ) 
	printfileline () ;
	else printnl ( 65544L ) ;
	print ( 66200L ) ;
      } 
      sprintcs ( u ) ;
      printchar ( 61 ) ;
      if ( filenamequotechar != 0 ) 
      printchar ( filenamequotechar ) ;
      printfilename ( nom , aire , curext ) ;
      if ( filenamequotechar != 0 ) 
      printchar ( filenamequotechar ) ;
      if ( s >= 0 ) 
      {
	print ( 66131L ) ;
	printscaled ( s ) ;
	print ( 65698L ) ;
      } 
      else if ( s != -1000 ) 
      {
	print ( 66197L ) ;
	printint ( - (integer) s ) ;
      } 
      print ( 66209L ) ;
      {
	helpptr = 4 ;
	helpline [3 ]= 66210L ;
	helpline [2 ]= 66211L ;
	helpline [1 ]= 66212L ;
	helpline [0 ]= 66213L ;
      } 
      error () ;
      goto lab30 ;
    } 
    f = fontptr + 1 ;
    charbase [f ]= fmemptr - bc ;
    widthbase [f ]= charbase [f ]+ ec + 1 ;
    heightbase [f ]= widthbase [f ]+ nw ;
    depthbase [f ]= heightbase [f ]+ nh ;
    italicbase [f ]= depthbase [f ]+ nd ;
    ligkernbase [f ]= italicbase [f ]+ ni ;
    kernbase [f ]= ligkernbase [f ]+ nl - 256 * ( 128 ) ;
    extenbase [f ]= kernbase [f ]+ 256 * ( 128 ) + nk ;
    parambase [f ]= extenbase [f ]+ ne ;
    {
      if ( lh < 2 ) 
      goto lab11 ;
      {
	tfmtemp = getc ( tfmfile ) ;
	a = tfmtemp ;
	qw .b0 = a ;
	tfmtemp = getc ( tfmfile ) ;
	b = tfmtemp ;
	qw .b1 = b ;
	tfmtemp = getc ( tfmfile ) ;
	c = tfmtemp ;
	qw .b2 = c ;
	tfmtemp = getc ( tfmfile ) ;
	d = tfmtemp ;
	qw .b3 = d ;
	fontcheck [f ]= qw ;
      } 
      tfmtemp = getc ( tfmfile ) ;
      {
	z = tfmtemp ;
	if ( z > 127 ) 
	goto lab11 ;
	tfmtemp = getc ( tfmfile ) ;
	z = z * 256 + tfmtemp ;
      } 
      tfmtemp = getc ( tfmfile ) ;
      z = z * 256 + tfmtemp ;
      tfmtemp = getc ( tfmfile ) ;
      z = ( z * 16 ) + ( tfmtemp / 16 ) ;
      if ( z < 65536L ) 
      goto lab11 ;
      while ( lh > 2 ) {
	  
	tfmtemp = getc ( tfmfile ) ;
	tfmtemp = getc ( tfmfile ) ;
	tfmtemp = getc ( tfmfile ) ;
	tfmtemp = getc ( tfmfile ) ;
	decr ( lh ) ;
      } 
      fontdsize [f ]= z ;
      if ( s != -1000 ) {
	  
	if ( s >= 0 ) 
	z = s ;
	else {
	    
	  savearitherror = aritherror ;
	  sw = z ;
	  z = xnoverd ( z , - (integer) s , 1000 ) ;
	  if ( aritherror || z >= 134217728L ) 
	  {
	    {
	      if ( interaction == 3 ) 
	      ;
	      if ( filelineerrorstylep ) 
	      printfileline () ;
	      else printnl ( 65544L ) ;
	      print ( 66200L ) ;
	    } 
	    sprintcs ( u ) ;
	    printchar ( 61 ) ;
	    if ( filenamequotechar != 0 ) 
	    printchar ( filenamequotechar ) ;
	    printfilename ( nom , aire , curext ) ;
	    if ( filenamequotechar != 0 ) 
	    printchar ( filenamequotechar ) ;
	    if ( s >= 0 ) 
	    {
	      print ( 66131L ) ;
	      printscaled ( s ) ;
	      print ( 65698L ) ;
	    } 
	    else if ( s != -1000 ) 
	    {
	      print ( 66197L ) ;
	      printint ( - (integer) s ) ;
	    } 
	    print ( 66214L ) ;
	    {
	      helpptr = 1 ;
	      helpline [0 ]= 66215L ;
	    } 
	    error () ;
	    z = sw ;
	  } 
	  aritherror = savearitherror ;
	} 
      } 
      fontsize [f ]= z ;
    } 
    {register integer for_end; k = fmemptr ;for_end = widthbase [f ]- 1 
    ; if ( k <= for_end) do 
      {
	{
	  tfmtemp = getc ( tfmfile ) ;
	  a = tfmtemp ;
	  qw .b0 = a ;
	  tfmtemp = getc ( tfmfile ) ;
	  b = tfmtemp ;
	  qw .b1 = b ;
	  tfmtemp = getc ( tfmfile ) ;
	  c = tfmtemp ;
	  qw .b2 = c ;
	  tfmtemp = getc ( tfmfile ) ;
	  d = tfmtemp ;
	  qw .b3 = d ;
	  fontinfo [k ].qqqq = qw ;
	} 
	if ( ( a >= nw ) || ( b / 16 >= nh ) || ( b % 16 >= nd ) || ( c / 4 >= 
	ni ) ) 
	goto lab11 ;
	switch ( c % 4 ) 
	{case 1 : 
	  if ( d >= nl ) 
	  goto lab11 ;
	  break ;
	case 3 : 
	  if ( d >= ne ) 
	  goto lab11 ;
	  break ;
	case 2 : 
	  {
	    {
	      if ( ( d < bc ) || ( d > ec ) ) 
	      goto lab11 ;
	    } 
	    while ( d < k + bc - fmemptr ) {
		
	      qw = fontinfo [charbase [f ]+ d ].qqqq ;
	      if ( ( ( qw .b2 ) % 4 ) != 2 ) 
	      goto lab45 ;
	      d = qw .b3 ;
	    } 
	    if ( d == k + bc - fmemptr ) 
	    goto lab11 ;
	    lab45: ;
	  } 
	  break ;
	  default: 
	  ;
	  break ;
	} 
      } 
    while ( k++ < for_end ) ;} 
    {
      {
	alpha = 16 ;
	while ( z >= 8388608L ) {
	    
	  z = z / 2 ;
	  alpha = alpha + alpha ;
	} 
	beta = 256 / alpha ;
	alpha = alpha * z ;
      } 
      {register integer for_end; k = widthbase [f ];for_end = ligkernbase 
      [f ]- 1 ; if ( k <= for_end) do 
	{
	  tfmtemp = getc ( tfmfile ) ;
	  a = tfmtemp ;
	  tfmtemp = getc ( tfmfile ) ;
	  b = tfmtemp ;
	  tfmtemp = getc ( tfmfile ) ;
	  c = tfmtemp ;
	  tfmtemp = getc ( tfmfile ) ;
	  d = tfmtemp ;
	  sw = ( ( ( ( ( d * z ) / 256 ) + ( c * z ) ) / 256 ) + ( b * z ) ) / 
	  beta ;
	  if ( a == 0 ) 
	  fontinfo [k ].cint = sw ;
	  else if ( a == 255 ) 
	  fontinfo [k ].cint = sw - alpha ;
	  else goto lab11 ;
	} 
      while ( k++ < for_end ) ;} 
      if ( fontinfo [widthbase [f ]].cint != 0 ) 
      goto lab11 ;
      if ( fontinfo [heightbase [f ]].cint != 0 ) 
      goto lab11 ;
      if ( fontinfo [depthbase [f ]].cint != 0 ) 
      goto lab11 ;
      if ( fontinfo [italicbase [f ]].cint != 0 ) 
      goto lab11 ;
    } 
    bchlabel = 32767 ;
    bchar = 256 ;
    if ( nl > 0 ) 
    {
      {register integer for_end; k = ligkernbase [f ];for_end = kernbase [
      f ]+ 256 * ( 128 ) - 1 ; if ( k <= for_end) do 
	{
	  {
	    tfmtemp = getc ( tfmfile ) ;
	    a = tfmtemp ;
	    qw .b0 = a ;
	    tfmtemp = getc ( tfmfile ) ;
	    b = tfmtemp ;
	    qw .b1 = b ;
	    tfmtemp = getc ( tfmfile ) ;
	    c = tfmtemp ;
	    qw .b2 = c ;
	    tfmtemp = getc ( tfmfile ) ;
	    d = tfmtemp ;
	    qw .b3 = d ;
	    fontinfo [k ].qqqq = qw ;
	  } 
	  if ( a > 128 ) 
	  {
	    if ( 256 * c + d >= nl ) 
	    goto lab11 ;
	    if ( a == 255 ) {
		
	      if ( k == ligkernbase [f ]) 
	      bchar = b ;
	    } 
	  } 
	  else {
	      
	    if ( b != bchar ) 
	    {
	      {
		if ( ( b < bc ) || ( b > ec ) ) 
		goto lab11 ;
	      } 
	      qw = fontinfo [charbase [f ]+ b ].qqqq ;
	      if ( ! ( qw .b0 > 0 ) ) 
	      goto lab11 ;
	    } 
	    if ( c < 128 ) 
	    {
	      {
		if ( ( d < bc ) || ( d > ec ) ) 
		goto lab11 ;
	      } 
	      qw = fontinfo [charbase [f ]+ d ].qqqq ;
	      if ( ! ( qw .b0 > 0 ) ) 
	      goto lab11 ;
	    } 
	    else if ( 256 * ( c - 128 ) + d >= nk ) 
	    goto lab11 ;
	    if ( a < 128 ) {
		
	      if ( k - ligkernbase [f ]+ a + 1 >= nl ) 
	      goto lab11 ;
	    } 
	  } 
	} 
      while ( k++ < for_end ) ;} 
      if ( a == 255 ) 
      bchlabel = 256 * c + d ;
    } 
    {register integer for_end; k = kernbase [f ]+ 256 * ( 128 ) ;for_end = 
    extenbase [f ]- 1 ; if ( k <= for_end) do 
      {
	tfmtemp = getc ( tfmfile ) ;
	a = tfmtemp ;
	tfmtemp = getc ( tfmfile ) ;
	b = tfmtemp ;
	tfmtemp = getc ( tfmfile ) ;
	c = tfmtemp ;
	tfmtemp = getc ( tfmfile ) ;
	d = tfmtemp ;
	sw = ( ( ( ( ( d * z ) / 256 ) + ( c * z ) ) / 256 ) + ( b * z ) ) / 
	beta ;
	if ( a == 0 ) 
	fontinfo [k ].cint = sw ;
	else if ( a == 255 ) 
	fontinfo [k ].cint = sw - alpha ;
	else goto lab11 ;
      } 
    while ( k++ < for_end ) ;} 
    {register integer for_end; k = extenbase [f ];for_end = parambase [f 
    ]- 1 ; if ( k <= for_end) do 
      {
	{
	  tfmtemp = getc ( tfmfile ) ;
	  a = tfmtemp ;
	  qw .b0 = a ;
	  tfmtemp = getc ( tfmfile ) ;
	  b = tfmtemp ;
	  qw .b1 = b ;
	  tfmtemp = getc ( tfmfile ) ;
	  c = tfmtemp ;
	  qw .b2 = c ;
	  tfmtemp = getc ( tfmfile ) ;
	  d = tfmtemp ;
	  qw .b3 = d ;
	  fontinfo [k ].qqqq = qw ;
	} 
	if ( a != 0 ) 
	{
	  {
	    if ( ( a < bc ) || ( a > ec ) ) 
	    goto lab11 ;
	  } 
	  qw = fontinfo [charbase [f ]+ a ].qqqq ;
	  if ( ! ( qw .b0 > 0 ) ) 
	  goto lab11 ;
	} 
	if ( b != 0 ) 
	{
	  {
	    if ( ( b < bc ) || ( b > ec ) ) 
	    goto lab11 ;
	  } 
	  qw = fontinfo [charbase [f ]+ b ].qqqq ;
	  if ( ! ( qw .b0 > 0 ) ) 
	  goto lab11 ;
	} 
	if ( c != 0 ) 
	{
	  {
	    if ( ( c < bc ) || ( c > ec ) ) 
	    goto lab11 ;
	  } 
	  qw = fontinfo [charbase [f ]+ c ].qqqq ;
	  if ( ! ( qw .b0 > 0 ) ) 
	  goto lab11 ;
	} 
	{
	  {
	    if ( ( d < bc ) || ( d > ec ) ) 
	    goto lab11 ;
	  } 
	  qw = fontinfo [charbase [f ]+ d ].qqqq ;
	  if ( ! ( qw .b0 > 0 ) ) 
	  goto lab11 ;
	} 
      } 
    while ( k++ < for_end ) ;} 
    {
      {register integer for_end; k = 1 ;for_end = np ; if ( k <= for_end) do 
	if ( k == 1 ) 
	{
	  tfmtemp = getc ( tfmfile ) ;
	  sw = tfmtemp ;
	  if ( sw > 127 ) 
	  sw = sw - 256 ;
	  tfmtemp = getc ( tfmfile ) ;
	  sw = sw * 256 + tfmtemp ;
	  tfmtemp = getc ( tfmfile ) ;
	  sw = sw * 256 + tfmtemp ;
	  tfmtemp = getc ( tfmfile ) ;
	  fontinfo [parambase [f ]].cint = ( sw * 16 ) + ( tfmtemp / 16 ) 
	  ;
	} 
	else {
	    
	  tfmtemp = getc ( tfmfile ) ;
	  a = tfmtemp ;
	  tfmtemp = getc ( tfmfile ) ;
	  b = tfmtemp ;
	  tfmtemp = getc ( tfmfile ) ;
	  c = tfmtemp ;
	  tfmtemp = getc ( tfmfile ) ;
	  d = tfmtemp ;
	  sw = ( ( ( ( ( d * z ) / 256 ) + ( c * z ) ) / 256 ) + ( b * z ) ) / 
	  beta ;
	  if ( a == 0 ) 
	  fontinfo [parambase [f ]+ k - 1 ].cint = sw ;
	  else if ( a == 255 ) 
	  fontinfo [parambase [f ]+ k - 1 ].cint = sw - alpha ;
	  else goto lab11 ;
	} 
      while ( k++ < for_end ) ;} 
      if ( feof ( tfmfile ) ) 
      goto lab11 ;
      {register integer for_end; k = np + 1 ;for_end = 7 ; if ( k <= 
      for_end) do 
	fontinfo [parambase [f ]+ k - 1 ].cint = 0 ;
      while ( k++ < for_end ) ;} 
    } 
    if ( np >= 7 ) 
    fontparams [f ]= np ;
    else fontparams [f ]= 7 ;
    hyphenchar [f ]= eqtb [7892310L ].cint ;
    skewchar [f ]= eqtb [7892311L ].cint ;
    if ( bchlabel < nl ) 
    bcharlabel [f ]= bchlabel + ligkernbase [f ];
    else bcharlabel [f ]= 0 ;
    fontbchar [f ]= bchar ;
    fontfalsebchar [f ]= bchar ;
    if ( bchar <= ec ) {
	
      if ( bchar >= bc ) 
      {
	qw = fontinfo [charbase [f ]+ bchar ].qqqq ;
	if ( ( qw .b0 > 0 ) ) 
	fontfalsebchar [f ]= 65536L ;
      } 
    } 
    fontname [f ]= nom ;
    fontarea [f ]= aire ;
    fontbc [f ]= bc ;
    fontec [f ]= ec ;
    fontglue [f ]= -268435455L ;
    charbase [f ]= charbase [f ];
    widthbase [f ]= widthbase [f ];
    ligkernbase [f ]= ligkernbase [f ];
    kernbase [f ]= kernbase [f ];
    extenbase [f ]= extenbase [f ];
    decr ( parambase [f ]) ;
    fmemptr = fmemptr + lf ;
    fontptr = f ;
    g = f ;
    fontmapping [f ]= loadtfmfontmapping () ;
    goto lab30 ;
  } 
  if ( g != 0 ) 
  goto lab30 ;
  if ( ! quotedfilename ) 
  {
    g = loadnativefont ( u , nom , aire , s ) ;
    if ( g != 0 ) 
    goto lab30 ;
  } 
  lab11: if ( eqtb [7892334L ].cint == 0 ) 
  {
    {
      if ( interaction == 3 ) 
      ;
      if ( filelineerrorstylep ) 
      printfileline () ;
      else printnl ( 65544L ) ;
      print ( 66200L ) ;
    } 
    sprintcs ( u ) ;
    printchar ( 61 ) ;
    if ( filenamequotechar != 0 ) 
    printchar ( filenamequotechar ) ;
    printfilename ( nom , aire , curext ) ;
    if ( filenamequotechar != 0 ) 
    printchar ( filenamequotechar ) ;
    if ( s >= 0 ) 
    {
      print ( 66131L ) ;
      printscaled ( s ) ;
      print ( 65698L ) ;
    } 
    else if ( s != -1000 ) 
    {
      print ( 66197L ) ;
      printint ( - (integer) s ) ;
    } 
    if ( fileopened ) 
    print ( 66201L ) ;
    else if ( nametoolong ) 
    print ( 66202L ) ;
    else print ( 66203L ) ;
    {
      helpptr = 5 ;
      helpline [4 ]= 66204L ;
      helpline [3 ]= 66205L ;
      helpline [2 ]= 66206L ;
      helpline [1 ]= 66207L ;
      helpline [0 ]= 66208L ;
    } 
    error () ;
  } 
  lab30: if ( fileopened ) 
  bclose ( tfmfile ) ;
  if ( eqtb [7892347L ].cint > 0 ) 
  {
    if ( g == 0 ) 
    {
      begindiagnostic () ;
      printnl ( 66198L ) ;
      enddiagnostic ( false ) ;
    } 
    else if ( fileopened ) 
    {
      begindiagnostic () ;
      printnl ( 66199L ) ;
      printcstring ( stringcast ( nameoffile + 1 ) ) ;
      enddiagnostic ( false ) ;
    } 
  } 
  Result = g ;
  return Result ;
} 
halfword 
znewcharacter ( internalfontnumber f , UTF16code c ) 
{
  /* 10 */ register halfword Result; newcharacter_regmem 
  halfword p  ;
  quarterword ec  ;
  if ( ( ( fontarea [f ]== 65535L ) || ( fontarea [f ]== 65534L ) ) ) 
  {
    Result = newnativecharacter ( f , c ) ;
    return Result ;
  } 
  ec = effectivechar ( false , f , c ) ;
  if ( fontbc [f ]<= ec ) {
      
    if ( fontec [f ]>= ec ) {
	
      if ( ( fontinfo [charbase [f ]+ ec ].qqqq .b0 > 0 ) ) 
      {
	p = getavail () ;
	mem [p ].hh.b0 = f ;
	mem [p ].hh.b1 = c ;
	Result = p ;
	return Result ;
      } 
    } 
  } 
  charwarning ( f , c ) ;
  Result = -268435455L ;
  return Result ;
} 
void 
dviswap ( void ) 
{
  dviswap_regmem 
  if ( dviptr > ( 2147483647L - dvioffset ) ) 
  {
    curs = -2 ;
    fatalerror ( 66227L ) ;
  } 
  if ( dvilimit == dvibufsize ) 
  {
    writedvi ( 0 , halfbuf - 1 ) ;
    dvilimit = halfbuf ;
    dvioffset = dvioffset + dvibufsize ;
    dviptr = 0 ;
  } 
  else {
      
    writedvi ( halfbuf , dvibufsize - 1 ) ;
    dvilimit = dvibufsize ;
  } 
  dvigone = dvigone + halfbuf ;
} 
void 
zdvifour ( integer x ) 
{
  dvifour_regmem 
  if ( x >= 0 ) 
  {
    dvibuf [dviptr ]= x / 16777216L ;
    incr ( dviptr ) ;
    if ( dviptr == dvilimit ) 
    dviswap () ;
  } 
  else {
      
    x = x + 1073741824L ;
    x = x + 1073741824L ;
    {
      dvibuf [dviptr ]= ( x / 16777216L ) + 128 ;
      incr ( dviptr ) ;
      if ( dviptr == dvilimit ) 
      dviswap () ;
    } 
  } 
  x = x % 16777216L ;
  {
    dvibuf [dviptr ]= x / 65536L ;
    incr ( dviptr ) ;
    if ( dviptr == dvilimit ) 
    dviswap () ;
  } 
  x = x % 65536L ;
  {
    dvibuf [dviptr ]= x / 256 ;
    incr ( dviptr ) ;
    if ( dviptr == dvilimit ) 
    dviswap () ;
  } 
  {
    dvibuf [dviptr ]= x % 256 ;
    incr ( dviptr ) ;
    if ( dviptr == dvilimit ) 
    dviswap () ;
  } 
} 
void 
zdvitwo ( UTF16code s ) 
{
  dvitwo_regmem 
  {
    dvibuf [dviptr ]= s / 256 ;
    incr ( dviptr ) ;
    if ( dviptr == dvilimit ) 
    dviswap () ;
  } 
  {
    dvibuf [dviptr ]= s % 256 ;
    incr ( dviptr ) ;
    if ( dviptr == dvilimit ) 
    dviswap () ;
  } 
} 
void 
zdvipop ( integer l ) 
{
  dvipop_regmem 
  if ( ( l == dvioffset + dviptr ) && ( dviptr > 0 ) ) 
  decr ( dviptr ) ;
  else {
      
    dvibuf [dviptr ]= 142 ;
    incr ( dviptr ) ;
    if ( dviptr == dvilimit ) 
    dviswap () ;
  } 
} 
void 
zdvinativefontdef ( internalfontnumber f ) 
{
  dvinativefontdef_regmem 
  integer fontdeflength, i  ;
  {
    dvibuf [dviptr ]= 252 ;
    incr ( dviptr ) ;
    if ( dviptr == dvilimit ) 
    dviswap () ;
  } 
  dvifour ( f - 1 ) ;
  fontdeflength = makefontdef ( f ) ;
  {register integer for_end; i = 0 ;for_end = fontdeflength - 1 ; if ( i <= 
  for_end) do 
    {
      dvibuf [dviptr ]= xdvbuffer [i ];
      incr ( dviptr ) ;
      if ( dviptr == dvilimit ) 
      dviswap () ;
    } 
  while ( i++ < for_end ) ;} 
} 
void 
zdvifontdef ( internalfontnumber f ) 
{
  dvifontdef_regmem 
  poolpointer k  ;
  integer l  ;
  if ( ( ( fontarea [f ]== 65535L ) || ( fontarea [f ]== 65534L ) ) ) 
  dvinativefontdef ( f ) ;
  else {
      
    if ( f <= 256 ) 
    {
      {
	dvibuf [dviptr ]= 243 ;
	incr ( dviptr ) ;
	if ( dviptr == dvilimit ) 
	dviswap () ;
      } 
      {
	dvibuf [dviptr ]= f - 1 ;
	incr ( dviptr ) ;
	if ( dviptr == dvilimit ) 
	dviswap () ;
      } 
    } 
    else {
	
      {
	dvibuf [dviptr ]= 244 ;
	incr ( dviptr ) ;
	if ( dviptr == dvilimit ) 
	dviswap () ;
      } 
      {
	dvibuf [dviptr ]= ( f - 1 ) / 256 ;
	incr ( dviptr ) ;
	if ( dviptr == dvilimit ) 
	dviswap () ;
      } 
      {
	dvibuf [dviptr ]= ( f - 1 ) % 256 ;
	incr ( dviptr ) ;
	if ( dviptr == dvilimit ) 
	dviswap () ;
      } 
    } 
    {
      dvibuf [dviptr ]= fontcheck [f ].b0 ;
      incr ( dviptr ) ;
      if ( dviptr == dvilimit ) 
      dviswap () ;
    } 
    {
      dvibuf [dviptr ]= fontcheck [f ].b1 ;
      incr ( dviptr ) ;
      if ( dviptr == dvilimit ) 
      dviswap () ;
    } 
    {
      dvibuf [dviptr ]= fontcheck [f ].b2 ;
      incr ( dviptr ) ;
      if ( dviptr == dvilimit ) 
      dviswap () ;
    } 
    {
      dvibuf [dviptr ]= fontcheck [f ].b3 ;
      incr ( dviptr ) ;
      if ( dviptr == dvilimit ) 
      dviswap () ;
    } 
    dvifour ( fontsize [f ]) ;
    dvifour ( fontdsize [f ]) ;
    {
      dvibuf [dviptr ]= length ( fontarea [f ]) ;
      incr ( dviptr ) ;
      if ( dviptr == dvilimit ) 
      dviswap () ;
    } 
    l = 0 ;
    k = strstart [( fontname [f ]) - 65536L ];
    while ( ( l == 0 ) && ( k < strstart [( fontname [f ]+ 1 ) - 65536L ]) 
    ) {
	
      if ( strpool [k ]== 58 ) 
      l = k - strstart [( fontname [f ]) - 65536L ];
      incr ( k ) ;
    } 
    if ( l == 0 ) 
    l = length ( fontname [f ]) ;
    {
      dvibuf [dviptr ]= l ;
      incr ( dviptr ) ;
      if ( dviptr == dvilimit ) 
      dviswap () ;
    } 
    {register integer for_end; k = strstart [( fontarea [f ]) - 65536L ];
    for_end = strstart [( fontarea [f ]+ 1 ) - 65536L ]- 1 ; if ( k <= 
    for_end) do 
      {
	dvibuf [dviptr ]= strpool [k ];
	incr ( dviptr ) ;
	if ( dviptr == dvilimit ) 
	dviswap () ;
      } 
    while ( k++ < for_end ) ;} 
    {register integer for_end; k = strstart [( fontname [f ]) - 65536L ];
    for_end = strstart [( fontname [f ]) - 65536L ]+ l - 1 ; if ( k <= 
    for_end) do 
      {
	dvibuf [dviptr ]= strpool [k ];
	incr ( dviptr ) ;
	if ( dviptr == dvilimit ) 
	dviswap () ;
      } 
    while ( k++ < for_end ) ;} 
  } 
} 
void 
zmovement ( scaled w , eightbits o ) 
{
  /* 10 40 45 2 1 */ movement_regmem 
  smallnumber mstate  ;
  halfword p, q  ;
  integer k  ;
  q = getnode ( 3 ) ;
  mem [q + 1 ].cint = w ;
  mem [q + 2 ].cint = dvioffset + dviptr ;
  if ( o == 157 ) 
  {
    mem [q ].hh .v.RH = downptr ;
    downptr = q ;
  } 
  else {
      
    mem [q ].hh .v.RH = rightptr ;
    rightptr = q ;
  } 
  p = mem [q ].hh .v.RH ;
  mstate = 0 ;
  while ( p != -268435455L ) {
      
    if ( mem [p + 1 ].cint == w ) 
    switch ( mstate + mem [p ].hh .v.LH ) 
    {case 3 : 
    case 4 : 
    case 15 : 
    case 16 : 
      if ( mem [p + 2 ].cint < dvigone ) 
      goto lab45 ;
      else {
	  
	k = mem [p + 2 ].cint - dvioffset ;
	if ( k < 0 ) 
	k = k + dvibufsize ;
	dvibuf [k ]= dvibuf [k ]+ 5 ;
	mem [p ].hh .v.LH = 1 ;
	goto lab40 ;
      } 
      break ;
    case 5 : 
    case 9 : 
    case 11 : 
      if ( mem [p + 2 ].cint < dvigone ) 
      goto lab45 ;
      else {
	  
	k = mem [p + 2 ].cint - dvioffset ;
	if ( k < 0 ) 
	k = k + dvibufsize ;
	dvibuf [k ]= dvibuf [k ]+ 10 ;
	mem [p ].hh .v.LH = 2 ;
	goto lab40 ;
      } 
      break ;
    case 1 : 
    case 2 : 
    case 8 : 
    case 13 : 
      goto lab40 ;
      break ;
      default: 
      ;
      break ;
    } 
    else switch ( mstate + mem [p ].hh .v.LH ) 
    {case 1 : 
      mstate = 6 ;
      break ;
    case 2 : 
      mstate = 12 ;
      break ;
    case 8 : 
    case 13 : 
      goto lab45 ;
      break ;
      default: 
      ;
      break ;
    } 
    p = mem [p ].hh .v.RH ;
  } 
  lab45: ;
  mem [q ].hh .v.LH = 3 ;
  if ( abs ( w ) >= 8388608L ) 
  {
    {
      dvibuf [dviptr ]= o + 3 ;
      incr ( dviptr ) ;
      if ( dviptr == dvilimit ) 
      dviswap () ;
    } 
    dvifour ( w ) ;
    return ;
  } 
  if ( abs ( w ) >= 32768L ) 
  {
    {
      dvibuf [dviptr ]= o + 2 ;
      incr ( dviptr ) ;
      if ( dviptr == dvilimit ) 
      dviswap () ;
    } 
    if ( w < 0 ) 
    w = w + 16777216L ;
    {
      dvibuf [dviptr ]= w / 65536L ;
      incr ( dviptr ) ;
      if ( dviptr == dvilimit ) 
      dviswap () ;
    } 
    w = w % 65536L ;
    goto lab2 ;
  } 
  if ( abs ( w ) >= 128 ) 
  {
    {
      dvibuf [dviptr ]= o + 1 ;
      incr ( dviptr ) ;
      if ( dviptr == dvilimit ) 
      dviswap () ;
    } 
    if ( w < 0 ) 
    w = w + 65536L ;
    goto lab2 ;
  } 
  {
    dvibuf [dviptr ]= o ;
    incr ( dviptr ) ;
    if ( dviptr == dvilimit ) 
    dviswap () ;
  } 
  if ( w < 0 ) 
  w = w + 256 ;
  goto lab1 ;
  lab2: {
      
    dvibuf [dviptr ]= w / 256 ;
    incr ( dviptr ) ;
    if ( dviptr == dvilimit ) 
    dviswap () ;
  } 
  lab1: {
      
    dvibuf [dviptr ]= w % 256 ;
    incr ( dviptr ) ;
    if ( dviptr == dvilimit ) 
    dviswap () ;
  } 
  return ;
  lab40: mem [q ].hh .v.LH = mem [p ].hh .v.LH ;
  if ( mem [q ].hh .v.LH == 1 ) 
  {
    {
      dvibuf [dviptr ]= o + 4 ;
      incr ( dviptr ) ;
      if ( dviptr == dvilimit ) 
      dviswap () ;
    } 
    while ( mem [q ].hh .v.RH != p ) {
	
      q = mem [q ].hh .v.RH ;
      switch ( mem [q ].hh .v.LH ) 
      {case 3 : 
	mem [q ].hh .v.LH = 5 ;
	break ;
      case 4 : 
	mem [q ].hh .v.LH = 6 ;
	break ;
	default: 
	;
	break ;
      } 
    } 
  } 
  else {
      
    {
      dvibuf [dviptr ]= o + 9 ;
      incr ( dviptr ) ;
      if ( dviptr == dvilimit ) 
      dviswap () ;
    } 
    while ( mem [q ].hh .v.RH != p ) {
	
      q = mem [q ].hh .v.RH ;
      switch ( mem [q ].hh .v.LH ) 
      {case 3 : 
	mem [q ].hh .v.LH = 4 ;
	break ;
      case 5 : 
	mem [q ].hh .v.LH = 6 ;
	break ;
	default: 
	;
	break ;
      } 
    } 
  } 
} 
void 
zprunemovements ( integer l ) 
{
  /* 30 10 */ prunemovements_regmem 
  halfword p  ;
  while ( downptr != -268435455L ) {
      
    if ( mem [downptr + 2 ].cint < l ) 
    goto lab30 ;
    p = downptr ;
    downptr = mem [p ].hh .v.RH ;
    freenode ( p , 3 ) ;
  } 
  lab30: while ( rightptr != -268435455L ) {
      
    if ( mem [rightptr + 2 ].cint < l ) 
    return ;
    p = rightptr ;
    rightptr = mem [p ].hh .v.RH ;
    freenode ( p , 3 ) ;
  } 
} 
void 
zspecialout ( halfword p ) 
{
  specialout_regmem 
  unsigned char oldsetting  ;
  poolpointer k  ;
  halfword h  ;
  halfword q, r  ;
  integer oldmode  ;
  if ( curh != dvih ) 
  {
    movement ( curh - dvih , 143 ) ;
    dvih = curh ;
  } 
  if ( curv != dviv ) 
  {
    movement ( curv - dviv , 157 ) ;
    dviv = curv ;
  } 
  doingspecial = true ;
  oldsetting = selector ;
  if ( mem [p ].hh.b1 == 4 ) 
  {
    q = getavail () ;
    mem [q ].hh .v.LH = 4194429L ;
    r = getavail () ;
    mem [q ].hh .v.RH = r ;
    mem [r ].hh .v.LH = 34749089L ;
    begintokenlist ( q , 5 ) ;
    begintokenlist ( mem [p + 1 ].hh .v.RH , 18 ) ;
    q = getavail () ;
    mem [q ].hh .v.LH = 2097275L ;
    begintokenlist ( q , 5 ) ;
    oldmode = curlist .modefield ;
    curlist .modefield = 0 ;
    curcs = writeloc ;
    q = scantoks ( false , true ) ;
    curlist .modefield = oldmode ;
    gettoken () ;
    if ( curtok != 34749089L ) 
    {
      {
	if ( interaction == 3 ) 
	;
	if ( filelineerrorstylep ) 
	printfileline () ;
	else printnl ( 65544L ) ;
	print ( 65948L ) ;
      } 
      {
	helpptr = 2 ;
	helpline [1 ]= 66782L ;
	helpline [0 ]= 66448L ;
      } 
      error () ;
      do {
	  gettoken () ;
      } while ( ! ( curtok == 34749089L ) ) ;
    } 
    endtokenlist () ;
    h = defref ;
  } 
  else h = mem [p + 1 ].hh .v.RH ;
  selector = 21 ;
  showtokenlist ( mem [h ].hh .v.RH , -268435455L , poolsize - poolptr ) ;
  selector = oldsetting ;
  {
    if ( poolptr + 1 > poolsize ) 
    overflow ( 65539L , poolsize - initpoolptr ) ;
  } 
  if ( ( poolptr - strstart [( strptr ) - 65536L ]) < 256 ) 
  {
    {
      dvibuf [dviptr ]= 239 ;
      incr ( dviptr ) ;
      if ( dviptr == dvilimit ) 
      dviswap () ;
    } 
    {
      dvibuf [dviptr ]= ( poolptr - strstart [( strptr ) - 65536L ]) ;
      incr ( dviptr ) ;
      if ( dviptr == dvilimit ) 
      dviswap () ;
    } 
  } 
  else {
      
    {
      dvibuf [dviptr ]= 242 ;
      incr ( dviptr ) ;
      if ( dviptr == dvilimit ) 
      dviswap () ;
    } 
    dvifour ( ( poolptr - strstart [( strptr ) - 65536L ]) ) ;
  } 
  {register integer for_end; k = strstart [( strptr ) - 65536L ];for_end = 
  poolptr - 1 ; if ( k <= for_end) do 
    {
      dvibuf [dviptr ]= strpool [k ];
      incr ( dviptr ) ;
      if ( dviptr == dvilimit ) 
      dviswap () ;
    } 
  while ( k++ < for_end ) ;} 
  poolptr = strstart [( strptr ) - 65536L ];
  if ( mem [p ].hh.b1 == 4 ) 
  flushlist ( defref ) ;
  doingspecial = false ;
} 
void 
zwriteout ( halfword p ) 
{
  writeout_regmem 
  unsigned char oldsetting  ;
  integer oldmode  ;
  smallnumber j  ;
  integer k  ;
  halfword q, r  ;
  integer d  ;
  boolean clobbered  ;
  integer runsystemret  ;
  q = getavail () ;
  mem [q ].hh .v.LH = 4194429L ;
  r = getavail () ;
  mem [q ].hh .v.RH = r ;
  mem [r ].hh .v.LH = 34749089L ;
  begintokenlist ( q , 5 ) ;
  begintokenlist ( mem [p + 1 ].hh .v.RH , 18 ) ;
  q = getavail () ;
  mem [q ].hh .v.LH = 2097275L ;
  begintokenlist ( q , 5 ) ;
  oldmode = curlist .modefield ;
  curlist .modefield = 0 ;
  curcs = writeloc ;
  q = scantoks ( false , true ) ;
  curlist .modefield = oldmode ;
  gettoken () ;
  if ( curtok != 34749089L ) 
  {
    {
      if ( interaction == 3 ) 
      ;
      if ( filelineerrorstylep ) 
      printfileline () ;
      else printnl ( 65544L ) ;
      print ( 65948L ) ;
    } 
    {
      helpptr = 2 ;
      helpline [1 ]= 66782L ;
      helpline [0 ]= 66448L ;
    } 
    error () ;
    do {
	gettoken () ;
    } while ( ! ( curtok == 34749089L ) ) ;
  } 
  endtokenlist () ;
  oldsetting = selector ;
  j = mem [p + 1 ].hh .v.LH ;
  if ( j == 18 ) 
  selector = 21 ;
  else if ( writeopen [j ]) 
  selector = j ;
  else {
      
    if ( ( j == 17 ) && ( selector == 19 ) ) 
    selector = 18 ;
    printnl ( 65545L ) ;
  } 
  tokenshow ( defref ) ;
  println () ;
  flushlist ( defref ) ;
  if ( j == 18 ) 
  {
    if ( ( eqtb [7892293L ].cint <= 0 ) ) 
    selector = 18 ;
    else selector = 19 ;
    if ( ! logopened ) 
    selector = 17 ;
    printnl ( 66774L ) ;
    {register integer for_end; d = 0 ;for_end = ( poolptr - strstart [( 
    strptr ) - 65536L ]) - 1 ; if ( d <= for_end) do 
      {
	print ( strpool [strstart [( strptr ) - 65536L ]+ d ]) ;
      } 
    while ( d++ < for_end ) ;} 
    print ( 66775L ) ;
    if ( shellenabledp ) 
    {
      {
	if ( poolptr + 1 > poolsize ) 
	overflow ( 65539L , poolsize - initpoolptr ) ;
      } 
      {
	if ( ( 0 > 65535L ) ) 
	{
	  strpool [poolptr ]= ( -65536L ) / 1024 + 55296L ;
	  incr ( poolptr ) ;
	  strpool [poolptr ]= ( 0 ) % 1024 + 56320L ;
	  incr ( poolptr ) ;
	} 
	else {
	    
	  strpool [poolptr ]= 0 ;
	  incr ( poolptr ) ;
	} 
      } 
      clobbered = false ;
      {register integer for_end; d = 0 ;for_end = ( poolptr - strstart [( 
      strptr ) - 65536L ]) - 1 ; if ( d <= for_end) do 
	{
	  if ( ( strpool [strstart [( strptr ) - 65536L ]+ d ]== 0 ) && ( 
	  d < ( poolptr - strstart [( strptr ) - 65536L ]) - 1 ) ) 
	  clobbered = true ;
	} 
      while ( d++ < for_end ) ;} 
      if ( clobbered ) 
      print ( 66776L ) ;
      else {
	  
	if ( nameoffile ) 
	libcfree ( nameoffile ) ;
	nameoffile = xmalloc ( ( poolptr - strstart [( strptr ) - 65536L ]) 
	* 3 + 2 ) ;
	k = 0 ;
	{register integer for_end; d = 0 ;for_end = ( poolptr - strstart [( 
	strptr ) - 65536L ]) - 1 ; if ( d <= for_end) do 
	  {
	    c = strpool [strstart [( strptr ) - 65536L ]+ d ];
	    incr ( k ) ;
	    if ( k <= maxint ) 
	    {
	      if ( ( c < 128 ) ) 
	      nameoffile [k ]= c ;
	      else if ( ( c < 2048 ) ) 
	      {
		nameoffile [k ]= 192 + c / 64 ;
		incr ( k ) ;
		nameoffile [k ]= 128 + c % 64 ;
	      } 
	      else if ( ( c < 55296L ) ) 
	      {
		nameoffile [k ]= 224 + c / 4096 ;
		incr ( k ) ;
		nameoffile [k ]= 128 + ( c % 4096 ) / 64 ;
		incr ( k ) ;
		nameoffile [k ]= 128 + c % 64 ;
	      } 
	      else if ( ( c < 56320L ) && ( k + 3 < maxint ) ) 
	      {
		nameoffile [k ]= 240 + ( c - 55232L ) / 4096 ;
		incr ( k ) ;
		nameoffile [k ]= 128 + ( ( c - 55232L ) % 4096 ) / 4 ;
		incr ( k ) ;
		nameoffile [k ]= 128 + ( c - 55232L ) % 4 * 16 ;
		incr ( k ) ;
		nameoffile [k ]= 128 ;
	      } 
	      else if ( ( c < 57344L ) && ( k > 4 ) ) 
	      {
		decr ( k ) ;
		nameoffile [k - 1 ]= nameoffile [k - 1 ]+ ( c - 56320L ) / 
		64 ;
		nameoffile [k ]= nameoffile [k ]+ ( c - 56320L ) % 64 ;
	      } 
	      else if ( ( c < 65536L ) ) 
	      {
		nameoffile [k ]= 224 + c / 4096 ;
		incr ( k ) ;
		nameoffile [k ]= 128 + ( c % 4096 ) / 64 ;
		incr ( k ) ;
		nameoffile [k ]= 128 + c % 64 ;
	      } 
	      else {
		  
		nameoffile [k ]= 239 ;
		incr ( k ) ;
		nameoffile [k ]= 191 ;
		incr ( k ) ;
		nameoffile [k ]= 189 ;
	      } 
	    } 
	  } 
	while ( d++ < for_end ) ;} 
	nameoffile [k + 1 ]= 0 ;
	runsystemret = runsystem ( conststringcast ( nameoffile + 1 ) ) ;
	if ( runsystemret == -1 ) 
	print ( 66777L ) ;
	else if ( runsystemret == 0 ) 
	print ( 66778L ) ;
	else if ( runsystemret == 1 ) 
	print ( 66779L ) ;
	else if ( runsystemret == 2 ) 
	print ( 66780L ) ;
      } 
    } 
    else {
	
      print ( 66781L ) ;
    } 
    printchar ( 46 ) ;
    printnl ( 65545L ) ;
    println () ;
    poolptr = strstart [( strptr ) - 65536L ];
  } 
  selector = oldsetting ;
} 
void 
zpicout ( halfword p ) 
{
  picout_regmem 
  unsigned char oldsetting  ;
  integer i  ;
  poolpointer k  ;
  if ( curh != dvih ) 
  {
    movement ( curh - dvih , 143 ) ;
    dvih = curh ;
  } 
  if ( curv != dviv ) 
  {
    movement ( curv - dviv , 157 ) ;
    dviv = curv ;
  } 
  oldsetting = selector ;
  selector = 21 ;
  print ( 66783L ) ;
  print ( 66784L ) ;
  printscaled ( mem [p + 5 ].hh .v.LH ) ;
  print ( 32 ) ;
  printscaled ( mem [p + 5 ].hh .v.RH ) ;
  print ( 32 ) ;
  printscaled ( mem [p + 6 ].hh .v.LH ) ;
  print ( 32 ) ;
  printscaled ( mem [p + 6 ].hh .v.RH ) ;
  print ( 32 ) ;
  printscaled ( mem [p + 7 ].hh .v.LH ) ;
  print ( 32 ) ;
  printscaled ( mem [p + 7 ].hh .v.RH ) ;
  print ( 32 ) ;
  print ( 66785L ) ;
  printint ( mem [p + 4 ].hh.b1 ) ;
  print ( 32 ) ;
  switch ( mem [p + 8 ].hh.b0 ) 
  {case 1 : 
    print ( 66786L ) ;
    break ;
  case 2 : 
    print ( 66787L ) ;
    break ;
  case 3 : 
    print ( 66788L ) ;
    break ;
  case 5 : 
    print ( 66789L ) ;
    break ;
  case 4 : 
    print ( 66790L ) ;
    break ;
    default: 
    ;
    break ;
  } 
  print ( 40 ) ;
  {register integer for_end; i = 0 ;for_end = mem [p + 4 ].hh.b0 - 1 
  ; if ( i <= for_end) do 
    printrawchar ( picpathbyte ( p , i ) , true ) ;
  while ( i++ < for_end ) ;} 
  print ( 41 ) ;
  selector = oldsetting ;
  if ( ( poolptr - strstart [( strptr ) - 65536L ]) < 256 ) 
  {
    {
      dvibuf [dviptr ]= 239 ;
      incr ( dviptr ) ;
      if ( dviptr == dvilimit ) 
      dviswap () ;
    } 
    {
      dvibuf [dviptr ]= ( poolptr - strstart [( strptr ) - 65536L ]) ;
      incr ( dviptr ) ;
      if ( dviptr == dvilimit ) 
      dviswap () ;
    } 
  } 
  else {
      
    {
      dvibuf [dviptr ]= 242 ;
      incr ( dviptr ) ;
      if ( dviptr == dvilimit ) 
      dviswap () ;
    } 
    dvifour ( ( poolptr - strstart [( strptr ) - 65536L ]) ) ;
  } 
  {register integer for_end; k = strstart [( strptr ) - 65536L ];for_end = 
  poolptr - 1 ; if ( k <= for_end) do 
    {
      dvibuf [dviptr ]= strpool [k ];
      incr ( dviptr ) ;
      if ( dviptr == dvilimit ) 
      dviswap () ;
    } 
  while ( k++ < for_end ) ;} 
  poolptr = strstart [( strptr ) - 65536L ];
} 
void 
zoutwhat ( halfword p ) 
{
  outwhat_regmem 
  smallnumber j  ;
  unsigned char oldsetting  ;
  switch ( mem [p ].hh.b1 ) 
  {case 0 : 
  case 1 : 
  case 2 : 
    if ( ! doingleaders ) 
    {
      j = mem [p + 1 ].hh .v.LH ;
      if ( mem [p ].hh.b1 == 1 ) 
      writeout ( p ) ;
      else {
	  
	if ( writeopen [j ]) 
	{
	  aclose ( writefile [j ]) ;
	  writeopen [j ]= false ;
	} 
	if ( mem [p ].hh.b1 == 2 ) 
	;
	else if ( j < 16 ) 
	{
	  curname = mem [p + 1 ].hh .v.RH ;
	  curarea = mem [p + 2 ].hh .v.LH ;
	  curext = mem [p + 2 ].hh .v.RH ;
	  if ( curext == 65545L ) 
	  curext = 66181L ;
	  packfilename ( curname , curarea , curext ) ;
	  while ( ! kpseoutnameok ( stringcast ( nameoffile + 1 ) ) || ! 
	  aopenout ( writefile [j ]) ) promptfilename ( 66792L , 66181L ) ;
	  writeopen [j ]= true ;
	  if ( logopened && texmfyesno ( "log_openout" ) ) 
	  {
	    oldsetting = selector ;
	    if ( ( eqtb [7892293L ].cint <= 0 ) ) 
	    selector = 18 ;
	    else selector = 19 ;
	    printnl ( 66793L ) ;
	    printint ( j ) ;
	    print ( 66794L ) ;
	    printfilename ( curname , curarea , curext ) ;
	    print ( 66180L ) ;
	    printnl ( 65545L ) ;
	    println () ;
	    selector = oldsetting ;
	  } 
	} 
      } 
    } 
    break ;
  case 3 : 
  case 4 : 
    specialout ( p ) ;
    break ;
  case 5 : 
    ;
    break ;
    default: 
    confusion ( 66791L ) ;
    break ;
  } 
} 
halfword 
znewedge ( smallnumber s , scaled w ) 
{
  register halfword Result; newedge_regmem 
  halfword p  ;
  p = getnode ( 3 ) ;
  mem [p ].hh.b0 = 14 ;
  mem [p ].hh.b1 = s ;
  mem [p + 1 ].cint = w ;
  mem [p + 2 ].cint = 0 ;
  Result = p ;
  return Result ;
} 
halfword 
zzreverse ( halfword thisbox , halfword t , scaled * curg , real * curglue ) 
{
  /* 21 15 30 */ register halfword Result; reverse_regmem 
  halfword l  ;
  halfword p  ;
  halfword q  ;
  glueord gorder  ;
  unsigned char gsign  ;
  real gluetemp  ;
  halfword m, n  ;
  gorder = mem [thisbox + 5 ].hh.b1 ;
  gsign = mem [thisbox + 5 ].hh.b0 ;
  l = t ;
  p = tempptr ;
  m = -268435455L ;
  n = -268435455L ;
  while ( true ) {
      
    while ( p != -268435455L ) lab21: if ( ( p >= himemmin ) ) 
    do {
	f = mem [p ].hh.b0 ;
      c = mem [p ].hh.b1 ;
      curh = curh + fontinfo [widthbase [f ]+ fontinfo [charbase [f ]+ 
      effectivechar ( true , f , c ) ].qqqq .b0 ].cint ;
      q = mem [p ].hh .v.RH ;
      mem [p ].hh .v.RH = l ;
      l = p ;
      p = q ;
    } while ( ! ( ! ( p >= himemmin ) ) ) ;
    else {
	
      q = mem [p ].hh .v.RH ;
      switch ( mem [p ].hh.b0 ) 
      {case 0 : 
      case 1 : 
      case 2 : 
      case 11 : 
	rulewd = mem [p + 1 ].cint ;
	break ;
      case 8 : 
	if ( ( ( ( mem [p ].hh.b1 >= 40 ) && ( mem [p ].hh.b1 <= 41 ) ) ) 
	|| ( mem [p ].hh.b1 == 42 ) || ( mem [p ].hh.b1 == 43 ) || ( mem [
	p ].hh.b1 == 44 ) ) 
	rulewd = mem [p + 1 ].cint ;
	else goto lab15 ;
	break ;
      case 10 : 
	{
	  g = mem [p + 1 ].hh .v.LH ;
	  rulewd = mem [g + 1 ].cint - *curg ;
	  if ( gsign != 0 ) 
	  {
	    if ( gsign == 1 ) 
	    {
	      if ( mem [g ].hh.b0 == gorder ) 
	      {
*                curglue = *curglue + mem [g + 2 ].cint ;
		gluetemp = mem [thisbox + 6 ].gr * *curglue ;
		if ( gluetemp > 1000000000.0 ) 
		gluetemp = 1000000000.0 ;
		else if ( gluetemp < -1000000000.0 ) 
		gluetemp = -1000000000.0 ;
*                curg = round ( gluetemp ) ;
	      } 
	    } 
	    else if ( mem [g ].hh.b1 == gorder ) 
	    {
*              curglue = *curglue - mem [g + 3 ].cint ;
	      gluetemp = mem [thisbox + 6 ].gr * *curglue ;
	      if ( gluetemp > 1000000000.0 ) 
	      gluetemp = 1000000000.0 ;
	      else if ( gluetemp < -1000000000.0 ) 
	      gluetemp = -1000000000.0 ;
*              curg = round ( gluetemp ) ;
	    } 
	  } 
	  rulewd = rulewd + *curg ;
	  if ( ( ( ( gsign == 1 ) && ( mem [g ].hh.b0 == gorder ) ) || ( ( 
	  gsign == 2 ) && ( mem [g ].hh.b1 == gorder ) ) ) ) 
	  {
	    {
	      if ( mem [g ].hh .v.RH == -268435455L ) 
	      freenode ( g , 4 ) ;
	      else decr ( mem [g ].hh .v.RH ) ;
	    } 
	    if ( mem [p ].hh.b1 < 100 ) 
	    {
	      mem [p ].hh.b0 = 11 ;
	      mem [p + 1 ].cint = rulewd ;
	    } 
	    else {
		
	      g = getnode ( 4 ) ;
	      mem [g ].hh.b0 = 4 ;
	      mem [g ].hh.b1 = 4 ;
	      mem [g + 1 ].cint = rulewd ;
	      mem [g + 2 ].cint = 0 ;
	      mem [g + 3 ].cint = 0 ;
	      mem [p + 1 ].hh .v.LH = g ;
	    } 
	  } 
	} 
	break ;
      case 6 : 
	{
	  flushnodelist ( mem [p + 1 ].hh .v.RH ) ;
	  tempptr = p ;
	  p = getavail () ;
	  mem [p ]= mem [tempptr + 1 ];
	  mem [p ].hh .v.RH = q ;
	  freenode ( tempptr , 2 ) ;
	  goto lab21 ;
	} 
	break ;
      case 9 : 
	{
	  rulewd = mem [p + 1 ].cint ;
	  if ( odd ( mem [p ].hh.b1 ) ) {
	      
	    if ( mem [LRptr ].hh .v.LH != ( 4 * ( mem [p ].hh.b1 / 4 ) + 3 
	    ) ) 
	    {
	      mem [p ].hh.b0 = 11 ;
	      incr ( LRproblems ) ;
	    } 
	    else {
		
	      {
		tempptr = LRptr ;
		LRptr = mem [tempptr ].hh .v.RH ;
		{
		  mem [tempptr ].hh .v.RH = avail ;
		  avail = tempptr ;
	;
#ifdef STAT
		  decr ( dynused ) ;
#endif /* STAT */
		} 
	      } 
	      if ( n > -268435455L ) 
	      {
		decr ( n ) ;
		decr ( mem [p ].hh.b1 ) ;
	      } 
	      else {
		  
		mem [p ].hh.b0 = 11 ;
		if ( m > -268435455L ) 
		decr ( m ) ;
		else {
		    
		  freenode ( p , 3 ) ;
		  mem [t ].hh .v.RH = q ;
		  mem [t + 1 ].cint = rulewd ;
		  mem [t + 2 ].cint = - (integer) curh - rulewd ;
		  goto lab30 ;
		} 
	      } 
	    } 
	  } 
	  else {
	      
	    {
	      tempptr = getavail () ;
	      mem [tempptr ].hh .v.LH = ( 4 * ( mem [p ].hh.b1 / 4 ) + 3 ) 
	      ;
	      mem [tempptr ].hh .v.RH = LRptr ;
	      LRptr = tempptr ;
	    } 
	    if ( ( n > -268435455L ) || ( ( mem [p ].hh.b1 / 8 ) != curdir ) 
	    ) 
	    {
	      incr ( n ) ;
	      incr ( mem [p ].hh.b1 ) ;
	    } 
	    else {
		
	      mem [p ].hh.b0 = 11 ;
	      incr ( m ) ;
	    } 
	  } 
	} 
	break ;
      case 14 : 
	confusion ( 66931L ) ;
	break ;
	default: 
	goto lab15 ;
	break ;
      } 
      curh = curh + rulewd ;
      lab15: mem [p ].hh .v.RH = l ;
      if ( mem [p ].hh.b0 == 11 ) {
	  
	if ( ( rulewd == 0 ) || ( l == -268435455L ) ) 
	{
	  freenode ( p , 3 ) ;
	  p = l ;
	} 
      } 
      l = p ;
      p = q ;
    } 
    if ( ( t == -268435455L ) && ( m == -268435455L ) && ( n == -268435455L ) 
    ) 
    goto lab30 ;
    p = newmath ( 0 , mem [LRptr ].hh .v.LH ) ;
    LRproblems = LRproblems + 10000 ;
  } 
  lab30: Result = l ;
  return Result ;
} 
void 
hlistout ( void ) 
{
  /* 21 13 14 15 22 40 1236 1237 */ hlistout_regmem 
  scaled baseline  ;
  scaled leftedge  ;
  scaled saveh, savev  ;
  halfword thisbox  ;
  glueord gorder  ;
  unsigned char gsign  ;
  halfword p  ;
  integer saveloc  ;
  halfword leaderbox  ;
  scaled leaderwd  ;
  scaled lx  ;
  boolean outerdoingleaders  ;
  scaled edge  ;
  halfword prevp  ;
  integer len  ;
  halfword q, r  ;
  integer k, j  ;
  real gluetemp  ;
  real curglue  ;
  scaled curg  ;
  curg = 0 ;
  curglue = 0.0 ;
  thisbox = tempptr ;
  gorder = mem [thisbox + 5 ].hh.b1 ;
  gsign = mem [thisbox + 5 ].hh.b0 ;
  if ( eqtb [7892348L ].cint > 1 ) 
  {
    p = mem [thisbox + 5 ].hh .v.RH ;
    prevp = thisbox + 5 ;
    while ( p != -268435455L ) {
	
      if ( mem [p ].hh .v.RH != -268435455L ) 
      {
	if ( ( ( ( p ) != -268435455L ) && ( ! ( p >= himemmin ) ) && ( mem [
	p ].hh.b0 == 8 ) && ( ( ( mem [p ].hh.b1 >= 40 ) && ( mem [p ]
	.hh.b1 <= 41 ) ) ) ) && ( fontletterspace [mem [p + 4 ].qqqq .b1 ]
	== 0 ) ) 
	{
	  r = p ;
	  k = mem [r + 4 ].qqqq .b2 ;
	  q = mem [p ].hh .v.RH ;
	  lab1236: while ( ( q != -268435455L ) && ! ( q >= himemmin ) && ( ( 
	  mem [q ].hh.b0 == 12 ) || ( mem [q ].hh.b0 == 3 ) || ( mem [q ]
	  .hh.b0 == 4 ) || ( mem [q ].hh.b0 == 5 ) || ( ( mem [q ].hh.b0 
	  == 8 ) && ( mem [q ].hh.b1 <= 4 ) ) ) ) q = mem [q ].hh .v.RH ;
	  if ( ( q != -268435455L ) && ! ( q >= himemmin ) ) 
	  {
	    if ( ( mem [q ].hh.b0 == 10 ) && ( mem [q ].hh.b1 == 0 ) ) 
	    {
	      if ( ( mem [q + 1 ].hh .v.LH == fontglue [mem [r + 4 ].qqqq 
	      .b1 ]) ) 
	      {
		q = mem [q ].hh .v.RH ;
		while ( ( q != -268435455L ) && ! ( q >= himemmin ) && ( ( mem 
		[q ].hh.b0 == 12 ) || ( mem [q ].hh.b0 == 3 ) || ( mem [q 
		].hh.b0 == 4 ) || ( mem [q ].hh.b0 == 5 ) || ( ( mem [q ]
		.hh.b0 == 8 ) && ( mem [q ].hh.b1 <= 4 ) ) ) ) q = mem [q ]
		.hh .v.RH ;
		if ( ( ( ( q ) != -268435455L ) && ( ! ( q >= himemmin ) ) && 
		( mem [q ].hh.b0 == 8 ) && ( ( ( mem [q ].hh.b1 >= 40 ) && 
		( mem [q ].hh.b1 <= 41 ) ) ) ) && ( mem [q + 4 ].qqqq .b1 
		== mem [r + 4 ].qqqq .b1 ) ) 
		{
		  p = q ;
		  k = k + 1 + mem [q + 4 ].qqqq .b2 ;
		  q = mem [q ].hh .v.RH ;
		  goto lab1236 ;
		} 
	      } 
	      else q = mem [q ].hh .v.RH ;
	      if ( ( q != -268435455L ) && ! ( q >= himemmin ) && ( mem [q ]
	      .hh.b0 == 11 ) && ( mem [q ].hh.b1 == 3 ) ) 
	      {
		q = mem [q ].hh .v.RH ;
		while ( ( q != -268435455L ) && ! ( q >= himemmin ) && ( ( mem 
		[q ].hh.b0 == 12 ) || ( mem [q ].hh.b0 == 3 ) || ( mem [q 
		].hh.b0 == 4 ) || ( mem [q ].hh.b0 == 5 ) || ( ( mem [q ]
		.hh.b0 == 8 ) && ( mem [q ].hh.b1 <= 4 ) ) ) ) q = mem [q ]
		.hh .v.RH ;
		if ( ( ( ( q ) != -268435455L ) && ( ! ( q >= himemmin ) ) && 
		( mem [q ].hh.b0 == 8 ) && ( ( ( mem [q ].hh.b1 >= 40 ) && 
		( mem [q ].hh.b1 <= 41 ) ) ) ) && ( mem [q + 4 ].qqqq .b1 
		== mem [r + 4 ].qqqq .b1 ) ) 
		{
		  p = q ;
		  k = k + 1 + mem [q + 4 ].qqqq .b2 ;
		  q = mem [q ].hh .v.RH ;
		  goto lab1236 ;
		} 
	      } 
	      goto lab1237 ;
	    } 
	    if ( ( ( ( q ) != -268435455L ) && ( ! ( q >= himemmin ) ) && ( 
	    mem [q ].hh.b0 == 8 ) && ( ( ( mem [q ].hh.b1 >= 40 ) && ( mem 
	    [q ].hh.b1 <= 41 ) ) ) ) && ( mem [q + 4 ].qqqq .b1 == mem [r 
	    + 4 ].qqqq .b1 ) ) 
	    {
	      p = q ;
	      q = mem [q ].hh .v.RH ;
	      goto lab1236 ;
	    } 
	  } 
	  lab1237: if ( p != r ) 
	  {
	    {
	      if ( poolptr + k > poolsize ) 
	      overflow ( 65539L , poolsize - initpoolptr ) ;
	    } 
	    k = 0 ;
	    q = r ;
	    while ( true ) {
		
	      if ( mem [q ].hh.b0 == 8 ) 
	      {
		if ( ( ( ( mem [q ].hh.b1 >= 40 ) && ( mem [q ].hh.b1 <= 
		41 ) ) ) ) 
		{
		  {register integer for_end; j = 0 ;for_end = mem [q + 4 ]
		  .qqqq .b2 - 1 ; if ( j <= for_end) do 
		    {
		      if ( ( getnativechar ( q , j ) > 65535L ) ) 
		      {
			strpool [poolptr ]= ( getnativechar ( q , j ) - 
			65536L ) / 1024 + 55296L ;
			incr ( poolptr ) ;
			strpool [poolptr ]= ( getnativechar ( q , j ) ) % 
			1024 + 56320L ;
			incr ( poolptr ) ;
		      } 
		      else {
			  
			strpool [poolptr ]= getnativechar ( q , j ) ;
			incr ( poolptr ) ;
		      } 
		    } 
		  while ( j++ < for_end ) ;} 
		  k = k + mem [q + 1 ].cint ;
		} 
	      } 
	      else if ( mem [q ].hh.b0 == 10 ) 
	      {
		{
		  if ( ( 32 > 65535L ) ) 
		  {
		    strpool [poolptr ]= ( -65504L ) / 1024 + 55296L ;
		    incr ( poolptr ) ;
		    strpool [poolptr ]= ( 32 ) % 1024 + 56320L ;
		    incr ( poolptr ) ;
		  } 
		  else {
		      
		    strpool [poolptr ]= 32 ;
		    incr ( poolptr ) ;
		  } 
		} 
		g = mem [q + 1 ].hh .v.LH ;
		k = k + mem [g + 1 ].cint ;
		if ( gsign != 0 ) 
		{
		  if ( gsign == 1 ) 
		  {
		    if ( mem [g ].hh.b0 == gorder ) 
		    {
		      k = k + round ( mem [thisbox + 6 ].gr * mem [g + 2 ]
		      .cint ) ;
		    } 
		  } 
		  else {
		      
		    if ( mem [g ].hh.b1 == gorder ) 
		    {
		      k = k - round ( mem [thisbox + 6 ].gr * mem [g + 3 ]
		      .cint ) ;
		    } 
		  } 
		} 
	      } 
	      else if ( mem [q ].hh.b0 == 11 ) 
	      {
		k = k + mem [q + 1 ].cint ;
	      } 
	      if ( q == p ) 
	      break ;
	      else q = mem [q ].hh .v.RH ;
	    } 
	    q = newnativewordnode ( mem [r + 4 ].qqqq .b1 , ( poolptr - 
	    strstart [( strptr ) - 65536L ]) ) ;
	    mem [q ].hh.b1 = mem [r ].hh.b1 ;
	    {register integer for_end; j = 0 ;for_end = ( poolptr - strstart 
	    [( strptr ) - 65536L ]) - 1 ; if ( j <= for_end) do 
	      setnativechar ( q , j , strpool [strstart [( strptr ) - 65536L 
	      ]+ j ]) ;
	    while ( j++ < for_end ) ;} 
	    mem [q + 1 ].cint = k ;
	    setjustifiednativeglyphs ( q ) ;
	    mem [prevp ].hh .v.RH = q ;
	    mem [q ].hh .v.RH = mem [p ].hh .v.RH ;
	    mem [p ].hh .v.RH = -268435455L ;
	    prevp = r ;
	    p = mem [r ].hh .v.RH ;
	    while ( p != -268435455L ) {
		
	      if ( ! ( p >= himemmin ) && ( ( mem [p ].hh.b0 == 12 ) || ( 
	      mem [p ].hh.b0 == 3 ) || ( mem [p ].hh.b0 == 4 ) || ( mem [
	      p ].hh.b0 == 5 ) || ( ( mem [p ].hh.b0 == 8 ) && ( mem [p ]
	      .hh.b1 <= 4 ) ) ) ) 
	      {
		mem [prevp ].hh .v.RH = mem [p ].hh .v.RH ;
		mem [p ].hh .v.RH = mem [q ].hh .v.RH ;
		mem [q ].hh .v.RH = p ;
		q = p ;
	      } 
	      prevp = p ;
	      p = mem [p ].hh .v.RH ;
	    } 
	    flushnodelist ( r ) ;
	    poolptr = strstart [( strptr ) - 65536L ];
	    p = q ;
	  } 
	} 
	prevp = p ;
      } 
      p = mem [p ].hh .v.RH ;
    } 
  } 
  p = mem [thisbox + 5 ].hh .v.RH ;
  incr ( curs ) ;
  if ( curs > 0 ) 
  {
    dvibuf [dviptr ]= 141 ;
    incr ( dviptr ) ;
    if ( dviptr == dvilimit ) 
    dviswap () ;
  } 
  if ( curs > maxpush ) 
  maxpush = curs ;
  saveloc = dvioffset + dviptr ;
  baseline = curv ;
  prevp = thisbox + 5 ;
  if ( ( eTeXmode == 1 ) ) 
  {
    {
      tempptr = getavail () ;
      mem [tempptr ].hh .v.LH = 0 ;
      mem [tempptr ].hh .v.RH = LRptr ;
      LRptr = tempptr ;
    } 
    if ( ( mem [thisbox ].hh.b1 ) == 2 ) {
	
      if ( curdir == 1 ) 
      {
	curdir = 0 ;
	curh = curh - mem [thisbox + 1 ].cint ;
      } 
      else mem [thisbox ].hh.b1 = 0 ;
    } 
    if ( ( curdir == 1 ) && ( ( mem [thisbox ].hh.b1 ) != 1 ) ) 
    {
      saveh = curh ;
      tempptr = p ;
      p = newkern ( 0 ) ;
      mem [p + 2 ].hh .v.LH = 0 ;
      mem [prevp ].hh .v.RH = p ;
      curh = 0 ;
      mem [p ].hh .v.RH = reverse ( thisbox , -268435455L , curg , curglue ) 
      ;
      mem [p + 1 ].cint = - (integer) curh ;
      curh = saveh ;
      mem [thisbox ].hh.b1 = 1 ;
    } 
  } 
  leftedge = curh ;
  synctexhlist ( thisbox ) ;
  while ( p != -268435455L ) lab21: if ( ( p >= himemmin ) ) 
  {
    if ( curh != dvih ) 
    {
      movement ( curh - dvih , 143 ) ;
      dvih = curh ;
    } 
    if ( curv != dviv ) 
    {
      movement ( curv - dviv , 157 ) ;
      dviv = curv ;
    } 
    do {
	f = mem [p ].hh.b0 ;
      c = mem [p ].hh.b1 ;
      if ( ( p != memtop - 12 ) && ( fontmapping [f ]!= nil ) ) 
      c = applytfmfontmapping ( fontmapping [f ], c ) ;
      if ( f != dvif ) 
      {
	if ( ! fontused [f ]) 
	{
	  dvifontdef ( f ) ;
	  fontused [f ]= true ;
	} 
	if ( f <= 64 ) 
	{
	  dvibuf [dviptr ]= f + 170 ;
	  incr ( dviptr ) ;
	  if ( dviptr == dvilimit ) 
	  dviswap () ;
	} 
	else if ( f <= 256 ) 
	{
	  {
	    dvibuf [dviptr ]= 235 ;
	    incr ( dviptr ) ;
	    if ( dviptr == dvilimit ) 
	    dviswap () ;
	  } 
	  {
	    dvibuf [dviptr ]= f - 1 ;
	    incr ( dviptr ) ;
	    if ( dviptr == dvilimit ) 
	    dviswap () ;
	  } 
	} 
	else {
	    
	  {
	    dvibuf [dviptr ]= 236 ;
	    incr ( dviptr ) ;
	    if ( dviptr == dvilimit ) 
	    dviswap () ;
	  } 
	  {
	    dvibuf [dviptr ]= ( f - 1 ) / 256 ;
	    incr ( dviptr ) ;
	    if ( dviptr == dvilimit ) 
	    dviswap () ;
	  } 
	  {
	    dvibuf [dviptr ]= ( f - 1 ) % 256 ;
	    incr ( dviptr ) ;
	    if ( dviptr == dvilimit ) 
	    dviswap () ;
	  } 
	} 
	dvif = f ;
      } 
      if ( fontec [f ]>= c ) {
	  
	if ( fontbc [f ]<= c ) {
	    
	  if ( ( fontinfo [charbase [f ]+ c ].qqqq .b0 > 0 ) ) 
	  {
	    if ( c >= 128 ) 
	    {
	      dvibuf [dviptr ]= 128 ;
	      incr ( dviptr ) ;
	      if ( dviptr == dvilimit ) 
	      dviswap () ;
	    } 
	    {
	      dvibuf [dviptr ]= c ;
	      incr ( dviptr ) ;
	      if ( dviptr == dvilimit ) 
	      dviswap () ;
	    } 
	    curh = curh + fontinfo [widthbase [f ]+ fontinfo [charbase [f 
	    ]+ c ].qqqq .b0 ].cint ;
	    goto lab22 ;
	  } 
	} 
      } 
      if ( mltexenabledp ) 
      {
	if ( c >= eqtb [7892319L ].cint ) {
	    
	  if ( c <= eqtb [7892320L ].cint ) {
	      
	    if ( ( eqtb [6778152L + c ].hh .v.RH > 0 ) ) 
	    {
	      basec = ( eqtb [6778152L + c ].hh .v.RH % 256 ) ;
	      accentc = ( eqtb [6778152L + c ].hh .v.RH / 256 ) ;
	      if ( ( fontec [f ]>= basec ) ) {
		  
		if ( ( fontbc [f ]<= basec ) ) {
		    
		  if ( ( fontec [f ]>= accentc ) ) {
		      
		    if ( ( fontbc [f ]<= accentc ) ) 
		    {
		      iac = fontinfo [charbase [f ]+ effectivechar ( true , 
		      f , accentc ) ].qqqq ;
		      ibc = fontinfo [charbase [f ]+ effectivechar ( true , 
		      f , basec ) ].qqqq ;
		      if ( ( ibc .b0 > 0 ) ) {
			  
			if ( ( iac .b0 > 0 ) ) 
			goto lab40 ;
		      } 
		    } 
		  } 
		} 
	      } 
	      begindiagnostic () ;
	      printnl ( 66976L ) ;
	      print ( c ) ;
	      print ( 66648L ) ;
	      print ( accentc ) ;
	      print ( 32 ) ;
	      print ( basec ) ;
	      print ( 66226L ) ;
	      print ( fontname [f ]) ;
	      printchar ( 33 ) ;
	      enddiagnostic ( false ) ;
	      goto lab22 ;
	    } 
	  } 
	} 
	begindiagnostic () ;
	printnl ( 66225L ) ;
	print ( 66975L ) ;
	print ( c ) ;
	print ( 66226L ) ;
	print ( fontname [f ]) ;
	printchar ( 33 ) ;
	enddiagnostic ( false ) ;
	goto lab22 ;
	lab40: if ( eqtb [7892299L ].cint > 99 ) 
	{
	  begindiagnostic () ;
	  printnl ( 66977L ) ;
	  print ( c ) ;
	  print ( 66648L ) ;
	  print ( accentc ) ;
	  print ( 32 ) ;
	  print ( basec ) ;
	  print ( 66226L ) ;
	  print ( fontname [f ]) ;
	  printchar ( 46 ) ;
	  enddiagnostic ( false ) ;
	} 
	basexheight = fontinfo [5 + parambase [f ]].cint ;
	baseslant = fontinfo [1 + parambase [f ]].cint / ((double) 65536.0 
	) ;
	accentslant = baseslant ;
	basewidth = fontinfo [widthbase [f ]+ ibc .b0 ].cint ;
	baseheight = fontinfo [heightbase [f ]+ ( ibc .b1 ) / 16 ].cint ;
	accentwidth = fontinfo [widthbase [f ]+ iac .b0 ].cint ;
	accentheight = fontinfo [heightbase [f ]+ ( iac .b1 ) / 16 ].cint 
	;
	delta = round ( ( basewidth - accentwidth ) / ((double) 2.0 ) + 
	baseheight * baseslant - basexheight * accentslant ) ;
	dvih = curh ;
	curh = curh + delta ;
	if ( curh != dvih ) 
	{
	  movement ( curh - dvih , 143 ) ;
	  dvih = curh ;
	} 
	if ( ( ( baseheight != basexheight ) && ( accentheight > 0 ) ) ) 
	{
	  curv = baseline + ( basexheight - baseheight ) ;
	  if ( curv != dviv ) 
	  {
	    movement ( curv - dviv , 157 ) ;
	    dviv = curv ;
	  } 
	  if ( accentc >= 128 ) 
	  {
	    dvibuf [dviptr ]= 128 ;
	    incr ( dviptr ) ;
	    if ( dviptr == dvilimit ) 
	    dviswap () ;
	  } 
	  {
	    dvibuf [dviptr ]= accentc ;
	    incr ( dviptr ) ;
	    if ( dviptr == dvilimit ) 
	    dviswap () ;
	  } 
	  curv = baseline ;
	} 
	else {
	    
	  if ( curv != dviv ) 
	  {
	    movement ( curv - dviv , 157 ) ;
	    dviv = curv ;
	  } 
	  if ( accentc >= 128 ) 
	  {
	    dvibuf [dviptr ]= 128 ;
	    incr ( dviptr ) ;
	    if ( dviptr == dvilimit ) 
	    dviswap () ;
	  } 
	  {
	    dvibuf [dviptr ]= accentc ;
	    incr ( dviptr ) ;
	    if ( dviptr == dvilimit ) 
	    dviswap () ;
	  } 
	} 
	curh = curh + accentwidth ;
	dvih = curh ;
	curh = curh + ( - (integer) accentwidth - delta ) ;
	if ( curh != dvih ) 
	{
	  movement ( curh - dvih , 143 ) ;
	  dvih = curh ;
	} 
	if ( curv != dviv ) 
	{
	  movement ( curv - dviv , 157 ) ;
	  dviv = curv ;
	} 
	if ( basec >= 128 ) 
	{
	  dvibuf [dviptr ]= 128 ;
	  incr ( dviptr ) ;
	  if ( dviptr == dvilimit ) 
	  dviswap () ;
	} 
	{
	  dvibuf [dviptr ]= basec ;
	  incr ( dviptr ) ;
	  if ( dviptr == dvilimit ) 
	  dviswap () ;
	} 
	curh = curh + basewidth ;
	dvih = curh ;
      } 
      lab22: prevp = mem [prevp ].hh .v.RH ;
      p = mem [p ].hh .v.RH ;
    } while ( ! ( ! ( p >= himemmin ) ) ) ;
    synctexcurrent () ;
    dvih = curh ;
  } 
  else {
      
    switch ( mem [p ].hh.b0 ) 
    {case 0 : 
    case 1 : 
      if ( mem [p + 5 ].hh .v.RH == -268435455L ) 
      {
	if ( mem [p ].hh.b0 == 1 ) 
	{
	  synctexvoidvlist ( p , thisbox ) ;
	} 
	else {
	    
	  synctexvoidhlist ( p , thisbox ) ;
	} 
	curh = curh + mem [p + 1 ].cint ;
      } 
      else {
	  
	saveh = dvih ;
	savev = dviv ;
	curv = baseline + mem [p + 4 ].cint ;
	tempptr = p ;
	edge = curh + mem [p + 1 ].cint ;
	if ( curdir == 1 ) 
	curh = edge ;
	if ( mem [p ].hh.b0 == 1 ) 
	vlistout () ;
	else hlistout () ;
	dvih = saveh ;
	dviv = savev ;
	curh = edge ;
	curv = baseline ;
      } 
      break ;
    case 2 : 
      {
	ruleht = mem [p + 3 ].cint ;
	ruledp = mem [p + 2 ].cint ;
	rulewd = mem [p + 1 ].cint ;
	goto lab14 ;
      } 
      break ;
    case 8 : 
      {
	switch ( mem [p ].hh.b1 ) 
	{case 40 : 
	case 41 : 
	case 42 : 
	  {
	    if ( curh != dvih ) 
	    {
	      movement ( curh - dvih , 143 ) ;
	      dvih = curh ;
	    } 
	    if ( curv != dviv ) 
	    {
	      movement ( curv - dviv , 157 ) ;
	      dviv = curv ;
	    } 
	    f = mem [p + 4 ].qqqq .b1 ;
	    if ( f != dvif ) 
	    {
	      if ( ! fontused [f ]) 
	      {
		dvifontdef ( f ) ;
		fontused [f ]= true ;
	      } 
	      if ( f <= 64 ) 
	      {
		dvibuf [dviptr ]= f + 170 ;
		incr ( dviptr ) ;
		if ( dviptr == dvilimit ) 
		dviswap () ;
	      } 
	      else if ( f <= 256 ) 
	      {
		{
		  dvibuf [dviptr ]= 235 ;
		  incr ( dviptr ) ;
		  if ( dviptr == dvilimit ) 
		  dviswap () ;
		} 
		{
		  dvibuf [dviptr ]= f - 1 ;
		  incr ( dviptr ) ;
		  if ( dviptr == dvilimit ) 
		  dviswap () ;
		} 
	      } 
	      else {
		  
		{
		  dvibuf [dviptr ]= 236 ;
		  incr ( dviptr ) ;
		  if ( dviptr == dvilimit ) 
		  dviswap () ;
		} 
		{
		  dvibuf [dviptr ]= ( f - 1 ) / 256 ;
		  incr ( dviptr ) ;
		  if ( dviptr == dvilimit ) 
		  dviswap () ;
		} 
		{
		  dvibuf [dviptr ]= ( f - 1 ) % 256 ;
		  incr ( dviptr ) ;
		  if ( dviptr == dvilimit ) 
		  dviswap () ;
		} 
	      } 
	      dvif = f ;
	    } 
	    if ( mem [p ].hh.b1 == 42 ) 
	    {
	      {
		dvibuf [dviptr ]= 253 ;
		incr ( dviptr ) ;
		if ( dviptr == dvilimit ) 
		dviswap () ;
	      } 
	      dvifour ( mem [p + 1 ].cint ) ;
	      dvitwo ( 1 ) ;
	      dvifour ( 0 ) ;
	      dvifour ( 0 ) ;
	      dvitwo ( mem [p + 4 ].qqqq .b2 ) ;
	      curh = curh + mem [p + 1 ].cint ;
	    } 
	    else {
		
	      if ( mem [p ].hh.b1 == 41 ) 
	      {
		if ( ( mem [p + 4 ].qqqq .b2 > 0 ) || ( mem [p + 5 ].ptr 
		!= nullptr ) ) 
		{
		  {
		    dvibuf [dviptr ]= 254 ;
		    incr ( dviptr ) ;
		    if ( dviptr == dvilimit ) 
		    dviswap () ;
		  } 
		  len = mem [p + 4 ].qqqq .b2 ;
		  dvitwo ( len ) ;
		  {register integer for_end; k = 0 ;for_end = len - 1 ; if ( 
		  k <= for_end) do 
		    {
		      dvitwo ( getnativechar ( p , k ) ) ;
		    } 
		  while ( k++ < for_end ) ;} 
		  len = makexdvglypharraydata ( p ) ;
		  {register integer for_end; k = 0 ;for_end = len - 1 ; if ( 
		  k <= for_end) do 
		    {
		      dvibuf [dviptr ]= xdvbufferbyte ( k ) ;
		      incr ( dviptr ) ;
		      if ( dviptr == dvilimit ) 
		      dviswap () ;
		    } 
		  while ( k++ < for_end ) ;} 
		} 
	      } 
	      else {
		  
		if ( mem [p + 5 ].ptr != nullptr ) 
		{
		  {
		    dvibuf [dviptr ]= 253 ;
		    incr ( dviptr ) ;
		    if ( dviptr == dvilimit ) 
		    dviswap () ;
		  } 
		  len = makexdvglypharraydata ( p ) ;
		  {register integer for_end; k = 0 ;for_end = len - 1 ; if ( 
		  k <= for_end) do 
		    {
		      dvibuf [dviptr ]= xdvbufferbyte ( k ) ;
		      incr ( dviptr ) ;
		      if ( dviptr == dvilimit ) 
		      dviswap () ;
		    } 
		  while ( k++ < for_end ) ;} 
		} 
	      } 
	      curh = curh + mem [p + 1 ].cint ;
	    } 
	    dvih = curh ;
	  } 
	  break ;
	case 43 : 
	case 44 : 
	  {
	    saveh = dvih ;
	    savev = dviv ;
	    curv = baseline ;
	    edge = curh + mem [p + 1 ].cint ;
	    picout ( p ) ;
	    dvih = saveh ;
	    dviv = savev ;
	    curh = edge ;
	    curv = baseline ;
	  } 
	  break ;
	case 23 : 
	  {
	    pdflastxpos = curh + 4736286L ;
	    pdflastypos = curpageheight - curv - 4736286L ;
	  } 
	  break ;
	  default: 
	  outwhat ( p ) ;
	  break ;
	} 
      } 
      break ;
    case 10 : 
      {
	g = mem [p + 1 ].hh .v.LH ;
	rulewd = mem [g + 1 ].cint - curg ;
	if ( gsign != 0 ) 
	{
	  if ( gsign == 1 ) 
	  {
	    if ( mem [g ].hh.b0 == gorder ) 
	    {
	      curglue = curglue + mem [g + 2 ].cint ;
	      gluetemp = mem [thisbox + 6 ].gr * curglue ;
	      if ( gluetemp > 1000000000.0 ) 
	      gluetemp = 1000000000.0 ;
	      else if ( gluetemp < -1000000000.0 ) 
	      gluetemp = -1000000000.0 ;
	      curg = round ( gluetemp ) ;
	    } 
	  } 
	  else if ( mem [g ].hh.b1 == gorder ) 
	  {
	    curglue = curglue - mem [g + 3 ].cint ;
	    gluetemp = mem [thisbox + 6 ].gr * curglue ;
	    if ( gluetemp > 1000000000.0 ) 
	    gluetemp = 1000000000.0 ;
	    else if ( gluetemp < -1000000000.0 ) 
	    gluetemp = -1000000000.0 ;
	    curg = round ( gluetemp ) ;
	  } 
	} 
	rulewd = rulewd + curg ;
	if ( ( eTeXmode == 1 ) ) {
	    
	  if ( ( ( ( gsign == 1 ) && ( mem [g ].hh.b0 == gorder ) ) || ( ( 
	  gsign == 2 ) && ( mem [g ].hh.b1 == gorder ) ) ) ) 
	  {
	    {
	      if ( mem [g ].hh .v.RH == -268435455L ) 
	      freenode ( g , 4 ) ;
	      else decr ( mem [g ].hh .v.RH ) ;
	    } 
	    if ( mem [p ].hh.b1 < 100 ) 
	    {
	      mem [p ].hh.b0 = 11 ;
	      mem [p + 1 ].cint = rulewd ;
	    } 
	    else {
		
	      g = getnode ( 4 ) ;
	      mem [g ].hh.b0 = 4 ;
	      mem [g ].hh.b1 = 4 ;
	      mem [g + 1 ].cint = rulewd ;
	      mem [g + 2 ].cint = 0 ;
	      mem [g + 3 ].cint = 0 ;
	      mem [p + 1 ].hh .v.LH = g ;
	    } 
	  } 
	} 
	if ( mem [p ].hh.b1 >= 100 ) 
	{
	  leaderbox = mem [p + 1 ].hh .v.RH ;
	  if ( mem [leaderbox ].hh.b0 == 2 ) 
	  {
	    ruleht = mem [leaderbox + 3 ].cint ;
	    ruledp = mem [leaderbox + 2 ].cint ;
	    goto lab14 ;
	  } 
	  leaderwd = mem [leaderbox + 1 ].cint ;
	  if ( ( leaderwd > 0 ) && ( rulewd > 0 ) ) 
	  {
	    rulewd = rulewd + 10 ;
	    if ( curdir == 1 ) 
	    curh = curh - 10 ;
	    edge = curh + rulewd ;
	    lx = 0 ;
	    if ( mem [p ].hh.b1 == 100 ) 
	    {
	      saveh = curh ;
	      curh = leftedge + leaderwd * ( ( curh - leftedge ) / leaderwd ) 
	      ;
	      if ( curh < saveh ) 
	      curh = curh + leaderwd ;
	    } 
	    else {
		
	      lq = rulewd / leaderwd ;
	      lr = rulewd % leaderwd ;
	      if ( mem [p ].hh.b1 == 101 ) 
	      curh = curh + ( lr / 2 ) ;
	      else {
		  
		lx = lr / ( lq + 1 ) ;
		curh = curh + ( ( lr - ( lq - 1 ) * lx ) / 2 ) ;
	      } 
	    } 
	    while ( curh + leaderwd <= edge ) {
		
	      curv = baseline + mem [leaderbox + 4 ].cint ;
	      if ( curv != dviv ) 
	      {
		movement ( curv - dviv , 157 ) ;
		dviv = curv ;
	      } 
	      savev = dviv ;
	      if ( curh != dvih ) 
	      {
		movement ( curh - dvih , 143 ) ;
		dvih = curh ;
	      } 
	      saveh = dvih ;
	      tempptr = leaderbox ;
	      if ( curdir == 1 ) 
	      curh = curh + leaderwd ;
	      outerdoingleaders = doingleaders ;
	      doingleaders = true ;
	      if ( mem [leaderbox ].hh.b0 == 1 ) 
	      vlistout () ;
	      else hlistout () ;
	      doingleaders = outerdoingleaders ;
	      dviv = savev ;
	      dvih = saveh ;
	      curv = baseline ;
	      curh = saveh + leaderwd + lx ;
	    } 
	    if ( curdir == 1 ) 
	    curh = edge ;
	    else curh = edge - 10 ;
	    goto lab15 ;
	  } 
	} 
	goto lab13 ;
      } 
      break ;
    case 40 : 
      {
	curh = curh + mem [p + 1 ].cint ;
      } 
      break ;
    case 11 : 
      {
	synctexkern ( p , thisbox ) ;
	curh = curh + mem [p + 1 ].cint ;
      } 
      break ;
    case 9 : 
      {
	synctexmath ( p , thisbox ) ;
	{
	  if ( ( eTeXmode == 1 ) ) 
	  {
	    if ( odd ( mem [p ].hh.b1 ) ) {
		
	      if ( mem [LRptr ].hh .v.LH == ( 4 * ( mem [p ].hh.b1 / 4 ) + 
	      3 ) ) 
	      {
		tempptr = LRptr ;
		LRptr = mem [tempptr ].hh .v.RH ;
		{
		  mem [tempptr ].hh .v.RH = avail ;
		  avail = tempptr ;
	;
#ifdef STAT
		  decr ( dynused ) ;
#endif /* STAT */
		} 
	      } 
	      else {
		  
		if ( mem [p ].hh.b1 > 4 ) 
		incr ( LRproblems ) ;
	      } 
	    } 
	    else {
		
	      {
		tempptr = getavail () ;
		mem [tempptr ].hh .v.LH = ( 4 * ( mem [p ].hh.b1 / 4 ) + 3 
		) ;
		mem [tempptr ].hh .v.RH = LRptr ;
		LRptr = tempptr ;
	      } 
	      if ( ( mem [p ].hh.b1 / 8 ) != curdir ) 
	      {
		saveh = curh ;
		tempptr = mem [p ].hh .v.RH ;
		rulewd = mem [p + 1 ].cint ;
		freenode ( p , 3 ) ;
		curdir = 1 - curdir ;
		p = newedge ( curdir , rulewd ) ;
		mem [prevp ].hh .v.RH = p ;
		curh = curh - leftedge + rulewd ;
		mem [p ].hh .v.RH = reverse ( thisbox , newedge ( 1 - curdir 
		, 0 ) , curg , curglue ) ;
		mem [p + 2 ].cint = curh ;
		curdir = 1 - curdir ;
		curh = saveh ;
		goto lab21 ;
	      } 
	    } 
	    mem [p ].hh.b0 = 11 ;
	  } 
	  curh = curh + mem [p + 1 ].cint ;
	} 
      } 
      break ;
    case 6 : 
      {
	mem [memtop - 12 ]= mem [p + 1 ];
	mem [memtop - 12 ].hh .v.RH = mem [p ].hh .v.RH ;
	p = memtop - 12 ;
	xtxligaturepresent = true ;
	goto lab21 ;
      } 
      break ;
    case 14 : 
      {
	curh = curh + mem [p + 1 ].cint ;
	leftedge = curh + mem [p + 2 ].cint ;
	curdir = mem [p ].hh.b1 ;
      } 
      break ;
      default: 
      ;
      break ;
    } 
    goto lab15 ;
    lab14: if ( ( ruleht == -1073741824L ) ) 
    ruleht = mem [thisbox + 3 ].cint ;
    if ( ( ruledp == -1073741824L ) ) 
    ruledp = mem [thisbox + 2 ].cint ;
    ruleht = ruleht + ruledp ;
    if ( ( ruleht > 0 ) && ( rulewd > 0 ) ) 
    {
      if ( curh != dvih ) 
      {
	movement ( curh - dvih , 143 ) ;
	dvih = curh ;
      } 
      curv = baseline + ruledp ;
      if ( curv != dviv ) 
      {
	movement ( curv - dviv , 157 ) ;
	dviv = curv ;
      } 
      {
	dvibuf [dviptr ]= 132 ;
	incr ( dviptr ) ;
	if ( dviptr == dvilimit ) 
	dviswap () ;
      } 
      dvifour ( ruleht ) ;
      dvifour ( rulewd ) ;
      curv = baseline ;
      dvih = dvih + rulewd ;
    } 
    lab13: {
	
      curh = curh + rulewd ;
      synctexhorizontalruleorglue ( p , thisbox ) ;
    } 
    lab15: prevp = p ;
    p = mem [p ].hh .v.RH ;
  } 
  synctextsilh ( thisbox ) ;
  if ( ( eTeXmode == 1 ) ) 
  {
    {
      while ( mem [LRptr ].hh .v.LH != 0 ) {
	  
	if ( mem [LRptr ].hh .v.LH > 4 ) 
	LRproblems = LRproblems + 10000 ;
	{
	  tempptr = LRptr ;
	  LRptr = mem [tempptr ].hh .v.RH ;
	  {
	    mem [tempptr ].hh .v.RH = avail ;
	    avail = tempptr ;
	;
#ifdef STAT
	    decr ( dynused ) ;
#endif /* STAT */
	  } 
	} 
      } 
      {
	tempptr = LRptr ;
	LRptr = mem [tempptr ].hh .v.RH ;
	{
	  mem [tempptr ].hh .v.RH = avail ;
	  avail = tempptr ;
	;
#ifdef STAT
	  decr ( dynused ) ;
#endif /* STAT */
	} 
      } 
    } 
    if ( ( mem [thisbox ].hh.b1 ) == 2 ) 
    curdir = 1 ;
  } 
  prunemovements ( saveloc ) ;
  if ( curs > 0 ) 
  dvipop ( saveloc ) ;
  decr ( curs ) ;
} 
void 
vlistout ( void ) 
{
  /* 13 14 15 */ vlistout_regmem 
  scaled leftedge  ;
  scaled topedge  ;
  scaled saveh, savev  ;
  halfword thisbox  ;
  glueord gorder  ;
  unsigned char gsign  ;
  halfword p  ;
  integer saveloc  ;
  halfword leaderbox  ;
  scaled leaderht  ;
  scaled lx  ;
  boolean outerdoingleaders  ;
  scaled edge  ;
  real gluetemp  ;
  real curglue  ;
  scaled curg  ;
  boolean upwards  ;
  curg = 0 ;
  curglue = 0.0 ;
  thisbox = tempptr ;
  gorder = mem [thisbox + 5 ].hh.b1 ;
  gsign = mem [thisbox + 5 ].hh.b0 ;
  p = mem [thisbox + 5 ].hh .v.RH ;
  upwards = ( mem [thisbox ].hh.b1 == 1 ) ;
  incr ( curs ) ;
  if ( curs > 0 ) 
  {
    dvibuf [dviptr ]= 141 ;
    incr ( dviptr ) ;
    if ( dviptr == dvilimit ) 
    dviswap () ;
  } 
  if ( curs > maxpush ) 
  maxpush = curs ;
  saveloc = dvioffset + dviptr ;
  leftedge = curh ;
  synctexvlist ( thisbox ) ;
  if ( upwards ) 
  curv = curv + mem [thisbox + 2 ].cint ;
  else curv = curv - mem [thisbox + 3 ].cint ;
  topedge = curv ;
  while ( p != -268435455L ) {
      
    if ( ( p >= himemmin ) ) 
    confusion ( 66229L ) ;
    else {
	
      switch ( mem [p ].hh.b0 ) 
      {case 0 : 
      case 1 : 
	if ( mem [p + 5 ].hh .v.RH == -268435455L ) 
	{
	  if ( upwards ) 
	  curv = curv - mem [p + 2 ].cint ;
	  else curv = curv + mem [p + 3 ].cint ;
	  if ( mem [p ].hh.b0 == 1 ) 
	  {
	    synctexvoidvlist ( p , thisbox ) ;
	  } 
	  else {
	      
	    synctexvoidhlist ( p , thisbox ) ;
	  } 
	  if ( upwards ) 
	  curv = curv - mem [p + 3 ].cint ;
	  else curv = curv + mem [p + 2 ].cint ;
	} 
	else {
	    
	  if ( upwards ) 
	  curv = curv - mem [p + 2 ].cint ;
	  else curv = curv + mem [p + 3 ].cint ;
	  if ( curv != dviv ) 
	  {
	    movement ( curv - dviv , 157 ) ;
	    dviv = curv ;
	  } 
	  saveh = dvih ;
	  savev = dviv ;
	  if ( curdir == 1 ) 
	  curh = leftedge - mem [p + 4 ].cint ;
	  else curh = leftedge + mem [p + 4 ].cint ;
	  tempptr = p ;
	  if ( mem [p ].hh.b0 == 1 ) 
	  vlistout () ;
	  else hlistout () ;
	  dvih = saveh ;
	  dviv = savev ;
	  if ( upwards ) 
	  curv = savev - mem [p + 3 ].cint ;
	  else curv = savev + mem [p + 2 ].cint ;
	  curh = leftedge ;
	} 
	break ;
      case 2 : 
	{
	  ruleht = mem [p + 3 ].cint ;
	  ruledp = mem [p + 2 ].cint ;
	  rulewd = mem [p + 1 ].cint ;
	  goto lab14 ;
	} 
	break ;
      case 8 : 
	{
	  switch ( mem [p ].hh.b1 ) 
	  {case 42 : 
	    {
	      curv = curv + mem [p + 3 ].cint ;
	      curh = leftedge ;
	      if ( curh != dvih ) 
	      {
		movement ( curh - dvih , 143 ) ;
		dvih = curh ;
	      } 
	      if ( curv != dviv ) 
	      {
		movement ( curv - dviv , 157 ) ;
		dviv = curv ;
	      } 
	      f = mem [p + 4 ].qqqq .b1 ;
	      if ( f != dvif ) 
	      {
		if ( ! fontused [f ]) 
		{
		  dvifontdef ( f ) ;
		  fontused [f ]= true ;
		} 
		if ( f <= 64 ) 
		{
		  dvibuf [dviptr ]= f + 170 ;
		  incr ( dviptr ) ;
		  if ( dviptr == dvilimit ) 
		  dviswap () ;
		} 
		else if ( f <= 256 ) 
		{
		  {
		    dvibuf [dviptr ]= 235 ;
		    incr ( dviptr ) ;
		    if ( dviptr == dvilimit ) 
		    dviswap () ;
		  } 
		  {
		    dvibuf [dviptr ]= f - 1 ;
		    incr ( dviptr ) ;
		    if ( dviptr == dvilimit ) 
		    dviswap () ;
		  } 
		} 
		else {
		    
		  {
		    dvibuf [dviptr ]= 236 ;
		    incr ( dviptr ) ;
		    if ( dviptr == dvilimit ) 
		    dviswap () ;
		  } 
		  {
		    dvibuf [dviptr ]= ( f - 1 ) / 256 ;
		    incr ( dviptr ) ;
		    if ( dviptr == dvilimit ) 
		    dviswap () ;
		  } 
		  {
		    dvibuf [dviptr ]= ( f - 1 ) % 256 ;
		    incr ( dviptr ) ;
		    if ( dviptr == dvilimit ) 
		    dviswap () ;
		  } 
		} 
		dvif = f ;
	      } 
	      {
		dvibuf [dviptr ]= 253 ;
		incr ( dviptr ) ;
		if ( dviptr == dvilimit ) 
		dviswap () ;
	      } 
	      dvifour ( 0 ) ;
	      dvitwo ( 1 ) ;
	      dvifour ( 0 ) ;
	      dvifour ( 0 ) ;
	      dvitwo ( mem [p + 4 ].qqqq .b2 ) ;
	      curv = curv + mem [p + 2 ].cint ;
	      curh = leftedge ;
	    } 
	    break ;
	  case 43 : 
	  case 44 : 
	    {
	      saveh = dvih ;
	      savev = dviv ;
	      curv = curv + mem [p + 3 ].cint ;
	      picout ( p ) ;
	      dvih = saveh ;
	      dviv = savev ;
	      curv = savev + mem [p + 2 ].cint ;
	      curh = leftedge ;
	    } 
	    break ;
	  case 23 : 
	    {
	      pdflastxpos = curh + 4736286L ;
	      pdflastypos = curpageheight - curv - 4736286L ;
	    } 
	    break ;
	    default: 
	    outwhat ( p ) ;
	    break ;
	  } 
	} 
	break ;
      case 10 : 
	{
	  g = mem [p + 1 ].hh .v.LH ;
	  ruleht = mem [g + 1 ].cint - curg ;
	  if ( gsign != 0 ) 
	  {
	    if ( gsign == 1 ) 
	    {
	      if ( mem [g ].hh.b0 == gorder ) 
	      {
		curglue = curglue + mem [g + 2 ].cint ;
		gluetemp = mem [thisbox + 6 ].gr * curglue ;
		if ( gluetemp > 1000000000.0 ) 
		gluetemp = 1000000000.0 ;
		else if ( gluetemp < -1000000000.0 ) 
		gluetemp = -1000000000.0 ;
		curg = round ( gluetemp ) ;
	      } 
	    } 
	    else if ( mem [g ].hh.b1 == gorder ) 
	    {
	      curglue = curglue - mem [g + 3 ].cint ;
	      gluetemp = mem [thisbox + 6 ].gr * curglue ;
	      if ( gluetemp > 1000000000.0 ) 
	      gluetemp = 1000000000.0 ;
	      else if ( gluetemp < -1000000000.0 ) 
	      gluetemp = -1000000000.0 ;
	      curg = round ( gluetemp ) ;
	    } 
	  } 
	  ruleht = ruleht + curg ;
	  if ( mem [p ].hh.b1 >= 100 ) 
	  {
	    leaderbox = mem [p + 1 ].hh .v.RH ;
	    if ( mem [leaderbox ].hh.b0 == 2 ) 
	    {
	      rulewd = mem [leaderbox + 1 ].cint ;
	      ruledp = 0 ;
	      goto lab14 ;
	    } 
	    leaderht = mem [leaderbox + 3 ].cint + mem [leaderbox + 2 ]
	    .cint ;
	    if ( ( leaderht > 0 ) && ( ruleht > 0 ) ) 
	    {
	      ruleht = ruleht + 10 ;
	      edge = curv + ruleht ;
	      lx = 0 ;
	      if ( mem [p ].hh.b1 == 100 ) 
	      {
		savev = curv ;
		curv = topedge + leaderht * ( ( curv - topedge ) / leaderht ) 
		;
		if ( curv < savev ) 
		curv = curv + leaderht ;
	      } 
	      else {
		  
		lq = ruleht / leaderht ;
		lr = ruleht % leaderht ;
		if ( mem [p ].hh.b1 == 101 ) 
		curv = curv + ( lr / 2 ) ;
		else {
		    
		  lx = lr / ( lq + 1 ) ;
		  curv = curv + ( ( lr - ( lq - 1 ) * lx ) / 2 ) ;
		} 
	      } 
	      while ( curv + leaderht <= edge ) {
		  
		if ( curdir == 1 ) 
		curh = leftedge - mem [leaderbox + 4 ].cint ;
		else curh = leftedge + mem [leaderbox + 4 ].cint ;
		if ( curh != dvih ) 
		{
		  movement ( curh - dvih , 143 ) ;
		  dvih = curh ;
		} 
		saveh = dvih ;
		curv = curv + mem [leaderbox + 3 ].cint ;
		if ( curv != dviv ) 
		{
		  movement ( curv - dviv , 157 ) ;
		  dviv = curv ;
		} 
		savev = dviv ;
		tempptr = leaderbox ;
		outerdoingleaders = doingleaders ;
		doingleaders = true ;
		if ( mem [leaderbox ].hh.b0 == 1 ) 
		vlistout () ;
		else hlistout () ;
		doingleaders = outerdoingleaders ;
		dviv = savev ;
		dvih = saveh ;
		curh = leftedge ;
		curv = savev - mem [leaderbox + 3 ].cint + leaderht + lx ;
	      } 
	      curv = edge - 10 ;
	      goto lab15 ;
	    } 
	  } 
	  goto lab13 ;
	} 
	break ;
      case 11 : 
	if ( upwards ) 
	curv = curv - mem [p + 1 ].cint ;
	else curv = curv + mem [p + 1 ].cint ;
	break ;
	default: 
	;
	break ;
      } 
      goto lab15 ;
      lab14: if ( ( rulewd == -1073741824L ) ) 
      rulewd = mem [thisbox + 1 ].cint ;
      ruleht = ruleht + ruledp ;
      if ( upwards ) 
      curv = curv - ruleht ;
      else curv = curv + ruleht ;
      if ( ( ruleht > 0 ) && ( rulewd > 0 ) ) 
      {
	if ( curdir == 1 ) 
	curh = curh - rulewd ;
	if ( curh != dvih ) 
	{
	  movement ( curh - dvih , 143 ) ;
	  dvih = curh ;
	} 
	if ( curv != dviv ) 
	{
	  movement ( curv - dviv , 157 ) ;
	  dviv = curv ;
	} 
	{
	  dvibuf [dviptr ]= 137 ;
	  incr ( dviptr ) ;
	  if ( dviptr == dvilimit ) 
	  dviswap () ;
	} 
	dvifour ( ruleht ) ;
	dvifour ( rulewd ) ;
	curh = leftedge ;
      } 
      goto lab15 ;
      lab13: if ( upwards ) 
      curv = curv - ruleht ;
      else curv = curv + ruleht ;
    } 
    lab15: p = mem [p ].hh .v.RH ;
  } 
  synctextsilv ( thisbox ) ;
  prunemovements ( saveloc ) ;
  if ( curs > 0 ) 
  dvipop ( saveloc ) ;
  decr ( curs ) ;
} 
void 
zshipout ( halfword p ) 
{
  /* 30 */ shipout_regmem 
  integer pageloc  ;
  unsigned char j, k  ;
  poolpointer s  ;
  unsigned char oldsetting  ;
  synctexsheet ( eqtb [7892281L ].cint ) ;
  {
    if ( jobname == 0 ) 
    openlogfile () ;
    if ( eqtb [7892298L ].cint > 0 ) 
    {
      printnl ( 65545L ) ;
      println () ;
      print ( 66230L ) ;
    } 
    if ( termoffset > maxprintline - 9 ) 
    println () ;
    else if ( ( termoffset > 0 ) || ( fileoffset > 0 ) ) 
    printchar ( 32 ) ;
    printchar ( 91 ) ;
    j = 9 ;
    while ( ( eqtb [7892352L + j ].cint == 0 ) && ( j > 0 ) ) decr ( j ) ;
    {register integer for_end; k = 0 ;for_end = j ; if ( k <= for_end) do 
      {
	printint ( eqtb [7892352L + k ].cint ) ;
	if ( k < j ) 
	printchar ( 46 ) ;
      } 
    while ( k++ < for_end ) ;} 
    fflush ( stdout ) ;
    if ( eqtb [7892298L ].cint > 0 ) 
    {
      printchar ( 93 ) ;
      begindiagnostic () ;
      showbox ( p ) ;
      enddiagnostic ( true ) ;
    } 
    if ( ( mem [p + 3 ].cint > 1073741823L ) || ( mem [p + 2 ].cint > 
    1073741823L ) || ( mem [p + 3 ].cint + mem [p + 2 ].cint + eqtb [
    9006739L ].cint > 1073741823L ) || ( mem [p + 1 ].cint + eqtb [
    9006738L ].cint > 1073741823L ) ) 
    {
      {
	if ( interaction == 3 ) 
	;
	if ( filelineerrorstylep ) 
	printfileline () ;
	else printnl ( 65544L ) ;
	print ( 66236L ) ;
      } 
      {
	helpptr = 2 ;
	helpline [1 ]= 66237L ;
	helpline [0 ]= 66238L ;
      } 
      error () ;
      if ( eqtb [7892298L ].cint <= 0 ) 
      {
	begindiagnostic () ;
	printnl ( 66239L ) ;
	showbox ( p ) ;
	enddiagnostic ( true ) ;
      } 
      goto lab30 ;
    } 
    if ( mem [p + 3 ].cint + mem [p + 2 ].cint + eqtb [9006739L ].cint > 
    maxv ) 
    maxv = mem [p + 3 ].cint + mem [p + 2 ].cint + eqtb [9006739L ].cint 
    ;
    if ( mem [p + 1 ].cint + eqtb [9006738L ].cint > maxh ) 
    maxh = mem [p + 1 ].cint + eqtb [9006738L ].cint ;
    dvih = 0 ;
    dviv = 0 ;
    curh = eqtb [9006738L ].cint ;
    dvif = 0 ;
    curhoffset = eqtb [9006738L ].cint + ( 65536L * 7227 ) / ((double) 100 ) 
    ;
    curvoffset = eqtb [9006739L ].cint + ( 65536L * 7227 ) / ((double) 100 ) 
    ;
    if ( eqtb [9006741L ].cint != 0 ) 
    curpagewidth = eqtb [9006741L ].cint ;
    else curpagewidth = mem [p + 1 ].cint + 2 * curhoffset ;
    if ( eqtb [9006742L ].cint != 0 ) 
    curpageheight = eqtb [9006742L ].cint ;
    else curpageheight = mem [p + 3 ].cint + mem [p + 2 ].cint + 2 * 
    curvoffset ;
    if ( outputfilename == 0 ) 
    {
      if ( jobname == 0 ) 
      openlogfile () ;
      packjobname ( outputfileextension ) ;
      while ( ! dviopenout ( dvifile ) ) promptfilename ( 66185L , 
      outputfileextension ) ;
      outputfilename = bmakenamestring ( dvifile ) ;
    } 
    if ( totalpages == 0 ) 
    {
      {
	dvibuf [dviptr ]= 247 ;
	incr ( dviptr ) ;
	if ( dviptr == dvilimit ) 
	dviswap () ;
      } 
      {
	dvibuf [dviptr ]= 7 ;
	incr ( dviptr ) ;
	if ( dviptr == dvilimit ) 
	dviswap () ;
      } 
      dvifour ( 25400000L ) ;
      dvifour ( 473628672L ) ;
      preparemag () ;
      dvifour ( eqtb [7892281L ].cint ) ;
      if ( outputcomment ) 
      {
	l = strlen ( outputcomment ) ;
	{
	  dvibuf [dviptr ]= l ;
	  incr ( dviptr ) ;
	  if ( dviptr == dvilimit ) 
	  dviswap () ;
	} 
	{register integer for_end; s = 0 ;for_end = l - 1 ; if ( s <= 
	for_end) do 
	  {
	    dvibuf [dviptr ]= outputcomment [s ];
	    incr ( dviptr ) ;
	    if ( dviptr == dvilimit ) 
	    dviswap () ;
	  } 
	while ( s++ < for_end ) ;} 
      } 
      else {
	  
	oldsetting = selector ;
	selector = 21 ;
	print ( 66228L ) ;
	printint ( eqtb [7892287L ].cint ) ;
	printchar ( 46 ) ;
	printtwo ( eqtb [7892286L ].cint ) ;
	printchar ( 46 ) ;
	printtwo ( eqtb [7892285L ].cint ) ;
	printchar ( 58 ) ;
	printtwo ( eqtb [7892284L ].cint / 60 ) ;
	printtwo ( eqtb [7892284L ].cint % 60 ) ;
	selector = oldsetting ;
	{
	  dvibuf [dviptr ]= ( poolptr - strstart [( strptr ) - 65536L ]) ;
	  incr ( dviptr ) ;
	  if ( dviptr == dvilimit ) 
	  dviswap () ;
	} 
	{register integer for_end; s = strstart [( strptr ) - 65536L ];
	for_end = poolptr - 1 ; if ( s <= for_end) do 
	  {
	    dvibuf [dviptr ]= strpool [s ];
	    incr ( dviptr ) ;
	    if ( dviptr == dvilimit ) 
	    dviswap () ;
	  } 
	while ( s++ < for_end ) ;} 
	poolptr = strstart [( strptr ) - 65536L ];
      } 
    } 
    pageloc = dvioffset + dviptr ;
    {
      dvibuf [dviptr ]= 139 ;
      incr ( dviptr ) ;
      if ( dviptr == dvilimit ) 
      dviswap () ;
    } 
    {register integer for_end; k = 0 ;for_end = 9 ; if ( k <= for_end) do 
      dvifour ( eqtb [7892352L + k ].cint ) ;
    while ( k++ < for_end ) ;} 
    dvifour ( lastbop ) ;
    lastbop = pageloc ;
    oldsetting = selector ;
    selector = 21 ;
    print ( 66234L ) ;
    if ( ( eqtb [9006741L ].cint > 0 ) && ( eqtb [9006742L ].cint > 0 ) ) 
    {
      print ( 66094L ) ;
      print ( 32 ) ;
      printscaled ( eqtb [9006741L ].cint ) ;
      print ( 65698L ) ;
      print ( 32 ) ;
      print ( 66095L ) ;
      print ( 32 ) ;
      printscaled ( eqtb [9006742L ].cint ) ;
      print ( 65698L ) ;
    } 
    else print ( 66235L ) ;
    selector = oldsetting ;
    {
      dvibuf [dviptr ]= 239 ;
      incr ( dviptr ) ;
      if ( dviptr == dvilimit ) 
      dviswap () ;
    } 
    {
      dvibuf [dviptr ]= ( poolptr - strstart [( strptr ) - 65536L ]) ;
      incr ( dviptr ) ;
      if ( dviptr == dvilimit ) 
      dviswap () ;
    } 
    {register integer for_end; s = strstart [( strptr ) - 65536L ];for_end 
    = poolptr - 1 ; if ( s <= for_end) do 
      {
	dvibuf [dviptr ]= strpool [s ];
	incr ( dviptr ) ;
	if ( dviptr == dvilimit ) 
	dviswap () ;
      } 
    while ( s++ < for_end ) ;} 
    poolptr = strstart [( strptr ) - 65536L ];
    curv = mem [p + 3 ].cint + eqtb [9006739L ].cint ;
    tempptr = p ;
    if ( mem [p ].hh.b0 == 1 ) 
    vlistout () ;
    else hlistout () ;
    {
      dvibuf [dviptr ]= 140 ;
      incr ( dviptr ) ;
      if ( dviptr == dvilimit ) 
      dviswap () ;
    } 
    incr ( totalpages ) ;
    curs = -1 ;
    if ( ! nopdfoutput ) 
    fflush ( dvifile ) ;
	;
#ifdef IPC
    if ( ipcon > 0 ) 
    {
      if ( dvilimit == halfbuf ) 
      {
	writedvi ( halfbuf , dvibufsize - 1 ) ;
	flushdvi () ;
	dvigone = dvigone + halfbuf ;
      } 
      if ( dviptr > ( 2147483647L - dvioffset ) ) 
      {
	curs = -2 ;
	fatalerror ( 66227L ) ;
      } 
      if ( dviptr > 0 ) 
      {
	writedvi ( 0 , dviptr - 1 ) ;
	flushdvi () ;
	dvioffset = dvioffset + dviptr ;
	dvigone = dvigone + dviptr ;
      } 
      dviptr = 0 ;
      dvilimit = dvibufsize ;
      ipcpage ( dvigone ) ;
    } 
#endif /* IPC */
    lab30: ;
    if ( ( eTeXmode == 1 ) ) 
    {
      if ( LRproblems > 0 ) 
      {
	{
	  println () ;
	  printnl ( 66928L ) ;
	  printint ( LRproblems / 10000 ) ;
	  print ( 66929L ) ;
	  printint ( LRproblems % 10000 ) ;
	  print ( 66930L ) ;
	  LRproblems = 0 ;
	} 
	printchar ( 41 ) ;
	println () ;
      } 
      if ( ( LRptr != -268435455L ) || ( curdir != 0 ) ) 
      confusion ( 66932L ) ;
    } 
    if ( eqtb [7892298L ].cint <= 0 ) 
    printchar ( 93 ) ;
    deadcycles = 0 ;
    fflush ( stdout ) ;
	;
#ifdef STAT
    if ( eqtb [7892295L ].cint > 1 ) 
    {
      printnl ( 66231L ) ;
      printint ( varused ) ;
      printchar ( 38 ) ;
      printint ( dynused ) ;
      printchar ( 59 ) ;
    } 
#endif /* STAT */
    flushnodelist ( p ) ;
	;
#ifdef STAT
    if ( eqtb [7892295L ].cint > 1 ) 
    {
      print ( 66232L ) ;
      printint ( varused ) ;
      printchar ( 38 ) ;
      printint ( dynused ) ;
      print ( 66233L ) ;
      printint ( himemmin - lomemmax - 1 ) ;
      println () ;
    } 
#endif /* STAT */
  } 
  synctexteehs () ;
} 
void 
zscanspec ( groupcode c , boolean threecodes ) 
{
  /* 40 */ scanspec_regmem 
  integer s  ;
  unsigned char speccode  ;
  if ( threecodes ) 
  s = savestack [saveptr + 0 ].cint ;
  if ( scankeyword ( 66252L ) ) 
  speccode = 0 ;
  else if ( scankeyword ( 66253L ) ) 
  speccode = 1 ;
  else {
      
    speccode = 1 ;
    curval = 0 ;
    goto lab40 ;
  } 
  scandimen ( false , false , false ) ;
  lab40: if ( threecodes ) 
  {
    savestack [saveptr + 0 ].cint = s ;
    incr ( saveptr ) ;
  } 
  savestack [saveptr + 0 ].cint = speccode ;
  savestack [saveptr + 1 ].cint = curval ;
  saveptr = saveptr + 2 ;
  newsavelevel ( c ) ;
  scanleftbrace () ;
} 
scaled 
zcharpw ( halfword p , smallnumber side ) 
{
  register scaled Result; charpw_regmem 
  internalfontnumber f  ;
  integer c  ;
  Result = 0 ;
  if ( side == 0 ) 
  lastleftmostchar = -268435455L ;
  else lastrightmostchar = -268435455L ;
  if ( p == -268435455L ) 
  return Result ;
  if ( ( ( ( p ) != -268435455L ) && ( ! ( p >= himemmin ) ) && ( mem [p ]
  .hh.b0 == 8 ) && ( ( ( mem [p ].hh.b1 >= 40 ) && ( mem [p ].hh.b1 <= 41 
  ) ) ) ) ) 
  {
    if ( mem [p + 5 ].ptr != nullptr ) 
    {
      f = mem [p + 4 ].qqqq .b1 ;
      Result = roundxnoverd ( fontinfo [6 + parambase [f ]].cint , 
      getnativewordcp ( p , side ) , 1000 ) ;
    } 
    return Result ;
  } 
  if ( ( ( ( p ) != -268435455L && ( ! ( p >= himemmin ) ) && ( mem [p ]
  .hh.b0 == 8 ) && ( mem [p ].hh.b1 == 42 ) ) ) ) 
  {
    f = mem [p + 4 ].qqqq .b1 ;
    Result = roundxnoverd ( fontinfo [6 + parambase [f ]].cint , getcpcode 
    ( f , mem [p + 4 ].qqqq .b2 , side ) , 1000 ) ;
    return Result ;
  } 
  if ( ! ( p >= himemmin ) ) 
  {
    if ( mem [p ].hh.b0 == 6 ) 
    p = p + 1 ;
    else return Result ;
  } 
  f = mem [p ].hh.b0 ;
  c = getcpcode ( f , mem [p ].hh.b1 , side ) ;
  switch ( side ) 
  {case 0 : 
    lastleftmostchar = p ;
    break ;
  case 1 : 
    lastrightmostchar = p ;
    break ;
  } 
  if ( c == 0 ) 
  return Result ;
  Result = roundxnoverd ( fontinfo [6 + parambase [f ]].cint , c , 1000 ) 
  ;
  return Result ;
} 
halfword 
znewmarginkern ( scaled w , halfword p , smallnumber side ) 
{
  register halfword Result; newmarginkern_regmem 
  halfword k  ;
  k = getnode ( 3 ) ;
  mem [k ].hh.b0 = 40 ;
  mem [k ].hh.b1 = side ;
  mem [k + 1 ].cint = w ;
  Result = k ;
  return Result ;
} 
halfword 
zhpack ( halfword p , scaled w , smallnumber m ) 
{
  /* 21 50 10 20 */ register halfword Result; hpack_regmem 
  halfword r  ;
  halfword q  ;
  scaled h, d, x  ;
  scaled s  ;
  halfword g  ;
  glueord o  ;
  internalfontnumber f  ;
  fourquarters i  ;
  eightbits hd  ;
  halfword pp, ppp  ;
  integer totalchars, k  ;
  lastbadness = 0 ;
  r = getnode ( 8 ) ;
  mem [r ].hh.b0 = 0 ;
  mem [r ].hh.b1 = 0 ;
  mem [r + 4 ].cint = 0 ;
  q = r + 5 ;
  mem [q ].hh .v.RH = p ;
  h = 0 ;
  d = 0 ;
  x = 0 ;
  totalstretch [0 ]= 0 ;
  totalshrink [0 ]= 0 ;
  totalstretch [1 ]= 0 ;
  totalshrink [1 ]= 0 ;
  totalstretch [2 ]= 0 ;
  totalshrink [2 ]= 0 ;
  totalstretch [3 ]= 0 ;
  totalshrink [3 ]= 0 ;
  if ( ( eqtb [7892339L ].cint > 0 ) ) 
  {
    tempptr = getavail () ;
    mem [tempptr ].hh .v.LH = 0 ;
    mem [tempptr ].hh .v.RH = LRptr ;
    LRptr = tempptr ;
  } 
  while ( p != -268435455L ) {
      
    lab21: while ( ( p >= himemmin ) ) {
	
      f = mem [p ].hh.b0 ;
      i = fontinfo [charbase [f ]+ effectivechar ( true , f , mem [p ]
      .hh.b1 ) ].qqqq ;
      hd = i .b1 ;
      x = x + fontinfo [widthbase [f ]+ i .b0 ].cint ;
      s = fontinfo [heightbase [f ]+ ( hd ) / 16 ].cint ;
      if ( s > h ) 
      h = s ;
      s = fontinfo [depthbase [f ]+ ( hd ) % 16 ].cint ;
      if ( s > d ) 
      d = s ;
      p = mem [p ].hh .v.RH ;
    } 
    if ( p != -268435455L ) 
    {
      switch ( mem [p ].hh.b0 ) 
      {case 0 : 
      case 1 : 
      case 2 : 
      case 13 : 
	{
	  x = x + mem [p + 1 ].cint ;
	  if ( mem [p ].hh.b0 >= 2 ) 
	  s = 0 ;
	  else s = mem [p + 4 ].cint ;
	  if ( mem [p + 3 ].cint - s > h ) 
	  h = mem [p + 3 ].cint - s ;
	  if ( mem [p + 2 ].cint + s > d ) 
	  d = mem [p + 2 ].cint + s ;
	} 
	break ;
      case 3 : 
      case 4 : 
      case 5 : 
	if ( ( adjusttail != -268435455L ) || ( preadjusttail != -268435455L ) 
	) 
	{
	  while ( mem [q ].hh .v.RH != p ) q = mem [q ].hh .v.RH ;
	  if ( mem [p ].hh.b0 == 5 ) 
	  {
	    if ( mem [p ].hh.b1 != 0 ) 
	    {
	      if ( preadjusttail == -268435455L ) 
	      confusion ( 66254L ) ;
	      mem [preadjusttail ].hh .v.RH = mem [p + 1 ].cint ;
	      while ( mem [preadjusttail ].hh .v.RH != -268435455L ) 
	      preadjusttail = mem [preadjusttail ].hh .v.RH ;
	    } 
	    else {
		
	      if ( adjusttail == -268435455L ) 
	      confusion ( 66254L ) ;
	      mem [adjusttail ].hh .v.RH = mem [p + 1 ].cint ;
	      while ( mem [adjusttail ].hh .v.RH != -268435455L ) adjusttail 
	      = mem [adjusttail ].hh .v.RH ;
	    } 
	    p = mem [p ].hh .v.RH ;
	    freenode ( mem [q ].hh .v.RH , 2 ) ;
	  } 
	  else {
	      
	    mem [adjusttail ].hh .v.RH = p ;
	    adjusttail = p ;
	    p = mem [p ].hh .v.RH ;
	  } 
	  mem [q ].hh .v.RH = p ;
	  p = q ;
	} 
	break ;
      case 8 : 
	{
	  switch ( mem [p ].hh.b1 ) 
	  {case 40 : 
	  case 41 : 
	    {
	      if ( ( q != r + 5 ) && ( mem [q ].hh.b0 == 7 ) ) 
	      k = mem [q ].hh.b1 ;
	      else k = 0 ;
	      while ( ( mem [q ].hh .v.RH != p ) ) {
		  
		decr ( k ) ;
		q = mem [q ].hh .v.RH ;
		if ( mem [q ].hh.b0 == 7 ) 
		k = mem [q ].hh.b1 ;
	      } 
	      pp = mem [p ].hh .v.RH ;
	      lab20: if ( ( k <= 0 ) && ( pp != -268435455L ) && ( ! ( pp >= 
	      himemmin ) ) ) 
	      {
		if ( ( mem [pp ].hh.b0 == 8 ) && ( ( ( mem [pp ].hh.b1 >= 
		40 ) && ( mem [pp ].hh.b1 <= 41 ) ) ) && ( mem [pp + 4 ]
		.qqqq .b1 == mem [p + 4 ].qqqq .b1 ) ) 
		{
		  pp = mem [pp ].hh .v.RH ;
		  goto lab20 ;
		} 
		else if ( ( mem [pp ].hh.b0 == 7 ) ) 
		{
		  ppp = mem [pp ].hh .v.RH ;
		  if ( ( ( ( ppp ) != -268435455L ) && ( ! ( ppp >= himemmin ) 
		  ) && ( mem [ppp ].hh.b0 == 8 ) && ( ( ( mem [ppp ].hh.b1 
		  >= 40 ) && ( mem [ppp ].hh.b1 <= 41 ) ) ) ) && ( mem [ppp 
		  + 4 ].qqqq .b1 == mem [p + 4 ].qqqq .b1 ) ) 
		  {
		    pp = mem [ppp ].hh .v.RH ;
		    goto lab20 ;
		  } 
		} 
	      } 
	      if ( ( pp != mem [p ].hh .v.RH ) ) 
	      {
		totalchars = 0 ;
		p = mem [q ].hh .v.RH ;
		while ( ( p != pp ) ) {
		    
		  if ( ( mem [p ].hh.b0 == 8 ) ) 
		  totalchars = totalchars + mem [p + 4 ].qqqq .b2 ;
		  ppp = p ;
		  p = mem [p ].hh .v.RH ;
		} 
		p = mem [q ].hh .v.RH ;
		pp = newnativewordnode ( mem [p + 4 ].qqqq .b1 , totalchars 
		) ;
		mem [pp ].hh.b1 = mem [p ].hh.b1 ;
		mem [q ].hh .v.RH = pp ;
		mem [pp ].hh .v.RH = mem [ppp ].hh .v.RH ;
		mem [ppp ].hh .v.RH = -268435455L ;
		totalchars = 0 ;
		ppp = p ;
		do {
		    if ( ( mem [ppp ].hh.b0 == 8 ) ) 
		  {register integer for_end; k = 0 ;for_end = mem [ppp + 4 
		  ].qqqq .b2 - 1 ; if ( k <= for_end) do 
		    {
		      setnativechar ( pp , totalchars , getnativechar ( ppp , 
		      k ) ) ;
		      incr ( totalchars ) ;
		    } 
		  while ( k++ < for_end ) ;} 
		  ppp = mem [ppp ].hh .v.RH ;
		} while ( ! ( ( ppp == -268435455L ) ) ) ;
		flushnodelist ( p ) ;
		p = mem [q ].hh .v.RH ;
		setnativemetrics ( p , ( eqtb [7892342L ].cint > 0 ) ) ;
	      } 
	      if ( mem [p + 3 ].cint > h ) 
	      h = mem [p + 3 ].cint ;
	      if ( mem [p + 2 ].cint > d ) 
	      d = mem [p + 2 ].cint ;
	      x = x + mem [p + 1 ].cint ;
	    } 
	    break ;
	  case 42 : 
	  case 43 : 
	  case 44 : 
	    {
	      if ( mem [p + 3 ].cint > h ) 
	      h = mem [p + 3 ].cint ;
	      if ( mem [p + 2 ].cint > d ) 
	      d = mem [p + 2 ].cint ;
	      x = x + mem [p + 1 ].cint ;
	    } 
	    break ;
	    default: 
	    ;
	    break ;
	  } 
	} 
	break ;
      case 10 : 
	{
	  g = mem [p + 1 ].hh .v.LH ;
	  x = x + mem [g + 1 ].cint ;
	  o = mem [g ].hh.b0 ;
	  totalstretch [o ]= totalstretch [o ]+ mem [g + 2 ].cint ;
	  o = mem [g ].hh.b1 ;
	  totalshrink [o ]= totalshrink [o ]+ mem [g + 3 ].cint ;
	  if ( mem [p ].hh.b1 >= 100 ) 
	  {
	    g = mem [p + 1 ].hh .v.RH ;
	    if ( mem [g + 3 ].cint > h ) 
	    h = mem [g + 3 ].cint ;
	    if ( mem [g + 2 ].cint > d ) 
	    d = mem [g + 2 ].cint ;
	  } 
	} 
	break ;
      case 11 : 
	x = x + mem [p + 1 ].cint ;
	break ;
      case 40 : 
	x = x + mem [p + 1 ].cint ;
	break ;
      case 9 : 
	{
	  x = x + mem [p + 1 ].cint ;
	  if ( ( eqtb [7892339L ].cint > 0 ) ) {
	      
	    if ( odd ( mem [p ].hh.b1 ) ) {
		
	      if ( mem [LRptr ].hh .v.LH == ( 4 * ( mem [p ].hh.b1 / 4 ) + 
	      3 ) ) 
	      {
		tempptr = LRptr ;
		LRptr = mem [tempptr ].hh .v.RH ;
		{
		  mem [tempptr ].hh .v.RH = avail ;
		  avail = tempptr ;
	;
#ifdef STAT
		  decr ( dynused ) ;
#endif /* STAT */
		} 
	      } 
	      else {
		  
		incr ( LRproblems ) ;
		mem [p ].hh.b0 = 11 ;
		mem [p ].hh.b1 = 1 ;
	      } 
	    } 
	    else {
		
	      tempptr = getavail () ;
	      mem [tempptr ].hh .v.LH = ( 4 * ( mem [p ].hh.b1 / 4 ) + 3 ) 
	      ;
	      mem [tempptr ].hh .v.RH = LRptr ;
	      LRptr = tempptr ;
	    } 
	  } 
	} 
	break ;
      case 6 : 
	{
	  mem [memtop - 12 ]= mem [p + 1 ];
	  mem [memtop - 12 ].hh .v.RH = mem [p ].hh .v.RH ;
	  p = memtop - 12 ;
	  xtxligaturepresent = true ;
	  goto lab21 ;
	} 
	break ;
	default: 
	;
	break ;
      } 
      p = mem [p ].hh .v.RH ;
    } 
  } 
  if ( adjusttail != -268435455L ) 
  mem [adjusttail ].hh .v.RH = -268435455L ;
  if ( preadjusttail != -268435455L ) 
  mem [preadjusttail ].hh .v.RH = -268435455L ;
  mem [r + 3 ].cint = h ;
  mem [r + 2 ].cint = d ;
  if ( m == 1 ) 
  w = x + w ;
  mem [r + 1 ].cint = w ;
  x = w - x ;
  if ( x == 0 ) 
  {
    mem [r + 5 ].hh.b0 = 0 ;
    mem [r + 5 ].hh.b1 = 0 ;
    mem [r + 6 ].gr = 0.0 ;
    goto lab10 ;
  } 
  else if ( x > 0 ) 
  {
    if ( totalstretch [3 ]!= 0 ) 
    o = 3 ;
    else if ( totalstretch [2 ]!= 0 ) 
    o = 2 ;
    else if ( totalstretch [1 ]!= 0 ) 
    o = 1 ;
    else o = 0 ;
    mem [r + 5 ].hh.b1 = o ;
    mem [r + 5 ].hh.b0 = 1 ;
    if ( totalstretch [o ]!= 0 ) 
    mem [r + 6 ].gr = x / ((double) totalstretch [o ]) ;
    else {
	
      mem [r + 5 ].hh.b0 = 0 ;
      mem [r + 6 ].gr = 0.0 ;
    } 
    if ( o == 0 ) {
	
      if ( mem [r + 5 ].hh .v.RH != -268435455L ) 
      {
	lastbadness = badness ( x , totalstretch [0 ]) ;
	if ( lastbadness > eqtb [7892290L ].cint ) 
	{
	  println () ;
	  if ( lastbadness > 100 ) 
	  printnl ( 66255L ) ;
	  else printnl ( 66256L ) ;
	  print ( 66257L ) ;
	  printint ( lastbadness ) ;
	  goto lab50 ;
	} 
      } 
    } 
    goto lab10 ;
  } 
  else {
      
    if ( totalshrink [3 ]!= 0 ) 
    o = 3 ;
    else if ( totalshrink [2 ]!= 0 ) 
    o = 2 ;
    else if ( totalshrink [1 ]!= 0 ) 
    o = 1 ;
    else o = 0 ;
    mem [r + 5 ].hh.b1 = o ;
    mem [r + 5 ].hh.b0 = 2 ;
    if ( totalshrink [o ]!= 0 ) 
    mem [r + 6 ].gr = ( - (integer) x ) / ((double) totalshrink [o ]) ;
    else {
	
      mem [r + 5 ].hh.b0 = 0 ;
      mem [r + 6 ].gr = 0.0 ;
    } 
    if ( ( totalshrink [o ]< - (integer) x ) && ( o == 0 ) && ( mem [r + 5 
    ].hh .v.RH != -268435455L ) ) 
    {
      lastbadness = 1000000L ;
      mem [r + 6 ].gr = 1.0 ;
      if ( ( - (integer) x - totalshrink [0 ]> eqtb [9006728L ].cint ) || 
      ( eqtb [7892290L ].cint < 100 ) ) 
      {
	if ( ( eqtb [9006736L ].cint > 0 ) && ( - (integer) x - totalshrink 
	[0 ]> eqtb [9006728L ].cint ) ) 
	{
	  while ( mem [q ].hh .v.RH != -268435455L ) q = mem [q ].hh .v.RH 
	  ;
	  mem [q ].hh .v.RH = newrule () ;
	  mem [mem [q ].hh .v.RH + 1 ].cint = eqtb [9006736L ].cint ;
	} 
	println () ;
	printnl ( 66263L ) ;
	printscaled ( - (integer) x - totalshrink [0 ]) ;
	print ( 66264L ) ;
	goto lab50 ;
      } 
    } 
    else if ( o == 0 ) {
	
      if ( mem [r + 5 ].hh .v.RH != -268435455L ) 
      {
	lastbadness = badness ( - (integer) x , totalshrink [0 ]) ;
	if ( lastbadness > eqtb [7892290L ].cint ) 
	{
	  println () ;
	  printnl ( 66265L ) ;
	  printint ( lastbadness ) ;
	  goto lab50 ;
	} 
      } 
    } 
    goto lab10 ;
  } 
  lab50: if ( outputactive ) 
  print ( 66258L ) ;
  else {
      
    if ( packbeginline != 0 ) 
    {
      if ( packbeginline > 0 ) 
      print ( 66259L ) ;
      else print ( 66260L ) ;
      printint ( abs ( packbeginline ) ) ;
      print ( 66261L ) ;
    } 
    else print ( 66262L ) ;
    printint ( line ) ;
  } 
  println () ;
  fontinshortdisplay = 0 ;
  shortdisplay ( mem [r + 5 ].hh .v.RH ) ;
  println () ;
  begindiagnostic () ;
  showbox ( r ) ;
  enddiagnostic ( true ) ;
  lab10: if ( ( eqtb [7892339L ].cint > 0 ) ) 
  {
    if ( mem [LRptr ].hh .v.LH != 0 ) 
    {
      while ( mem [q ].hh .v.RH != -268435455L ) q = mem [q ].hh .v.RH ;
      do {
	  tempptr = q ;
	q = newmath ( 0 , mem [LRptr ].hh .v.LH ) ;
	mem [tempptr ].hh .v.RH = q ;
	LRproblems = LRproblems + 10000 ;
	{
	  tempptr = LRptr ;
	  LRptr = mem [tempptr ].hh .v.RH ;
	  {
	    mem [tempptr ].hh .v.RH = avail ;
	    avail = tempptr ;
	;
#ifdef STAT
	    decr ( dynused ) ;
#endif /* STAT */
	  } 
	} 
      } while ( ! ( mem [LRptr ].hh .v.LH == 0 ) ) ;
    } 
    if ( LRproblems > 0 ) 
    {
      {
	println () ;
	printnl ( 66928L ) ;
	printint ( LRproblems / 10000 ) ;
	print ( 66929L ) ;
	printint ( LRproblems % 10000 ) ;
	print ( 66930L ) ;
	LRproblems = 0 ;
      } 
      goto lab50 ;
    } 
    {
      tempptr = LRptr ;
      LRptr = mem [tempptr ].hh .v.RH ;
      {
	mem [tempptr ].hh .v.RH = avail ;
	avail = tempptr ;
	;
#ifdef STAT
	decr ( dynused ) ;
#endif /* STAT */
      } 
    } 
    if ( LRptr != -268435455L ) 
    confusion ( 66927L ) ;
  } 
  Result = r ;
  return Result ;
} 
halfword 
zvpackage ( halfword p , scaled h , smallnumber m , scaled l ) 
{
  /* 50 10 */ register halfword Result; vpackage_regmem 
  halfword r  ;
  scaled w, d, x  ;
  scaled s  ;
  halfword g  ;
  glueord o  ;
  lastbadness = 0 ;
  r = getnode ( 8 ) ;
  mem [r ].hh.b0 = 1 ;
  if ( ( eqtb [7892341L ].cint > 0 ) ) 
  mem [r ].hh.b1 = 1 ;
  else mem [r ].hh.b1 = 0 ;
  mem [r + 4 ].cint = 0 ;
  mem [r + 5 ].hh .v.RH = p ;
  w = 0 ;
  d = 0 ;
  x = 0 ;
  totalstretch [0 ]= 0 ;
  totalshrink [0 ]= 0 ;
  totalstretch [1 ]= 0 ;
  totalshrink [1 ]= 0 ;
  totalstretch [2 ]= 0 ;
  totalshrink [2 ]= 0 ;
  totalstretch [3 ]= 0 ;
  totalshrink [3 ]= 0 ;
  while ( p != -268435455L ) {
      
    if ( ( p >= himemmin ) ) 
    confusion ( 66266L ) ;
    else switch ( mem [p ].hh.b0 ) 
    {case 0 : 
    case 1 : 
    case 2 : 
    case 13 : 
      {
	x = x + d + mem [p + 3 ].cint ;
	d = mem [p + 2 ].cint ;
	if ( mem [p ].hh.b0 >= 2 ) 
	s = 0 ;
	else s = mem [p + 4 ].cint ;
	if ( mem [p + 1 ].cint + s > w ) 
	w = mem [p + 1 ].cint + s ;
      } 
      break ;
    case 8 : 
      {
	if ( ( mem [p ].hh.b1 == 43 ) || ( mem [p ].hh.b1 == 44 ) ) 
	{
	  x = x + d + mem [p + 3 ].cint ;
	  d = mem [p + 2 ].cint ;
	  if ( mem [p + 1 ].cint > w ) 
	  w = mem [p + 1 ].cint ;
	} 
      } 
      break ;
    case 10 : 
      {
	x = x + d ;
	d = 0 ;
	g = mem [p + 1 ].hh .v.LH ;
	x = x + mem [g + 1 ].cint ;
	o = mem [g ].hh.b0 ;
	totalstretch [o ]= totalstretch [o ]+ mem [g + 2 ].cint ;
	o = mem [g ].hh.b1 ;
	totalshrink [o ]= totalshrink [o ]+ mem [g + 3 ].cint ;
	if ( mem [p ].hh.b1 >= 100 ) 
	{
	  g = mem [p + 1 ].hh .v.RH ;
	  if ( mem [g + 1 ].cint > w ) 
	  w = mem [g + 1 ].cint ;
	} 
      } 
      break ;
    case 11 : 
      {
	x = x + d + mem [p + 1 ].cint ;
	d = 0 ;
      } 
      break ;
      default: 
      ;
      break ;
    } 
    p = mem [p ].hh .v.RH ;
  } 
  mem [r + 1 ].cint = w ;
  if ( d > l ) 
  {
    x = x + d - l ;
    mem [r + 2 ].cint = l ;
  } 
  else mem [r + 2 ].cint = d ;
  if ( m == 1 ) 
  h = x + h ;
  mem [r + 3 ].cint = h ;
  x = h - x ;
  if ( x == 0 ) 
  {
    mem [r + 5 ].hh.b0 = 0 ;
    mem [r + 5 ].hh.b1 = 0 ;
    mem [r + 6 ].gr = 0.0 ;
    goto lab10 ;
  } 
  else if ( x > 0 ) 
  {
    if ( totalstretch [3 ]!= 0 ) 
    o = 3 ;
    else if ( totalstretch [2 ]!= 0 ) 
    o = 2 ;
    else if ( totalstretch [1 ]!= 0 ) 
    o = 1 ;
    else o = 0 ;
    mem [r + 5 ].hh.b1 = o ;
    mem [r + 5 ].hh.b0 = 1 ;
    if ( totalstretch [o ]!= 0 ) 
    mem [r + 6 ].gr = x / ((double) totalstretch [o ]) ;
    else {
	
      mem [r + 5 ].hh.b0 = 0 ;
      mem [r + 6 ].gr = 0.0 ;
    } 
    if ( o == 0 ) {
	
      if ( mem [r + 5 ].hh .v.RH != -268435455L ) 
      {
	lastbadness = badness ( x , totalstretch [0 ]) ;
	if ( lastbadness > eqtb [7892291L ].cint ) 
	{
	  println () ;
	  if ( lastbadness > 100 ) 
	  printnl ( 66255L ) ;
	  else printnl ( 66256L ) ;
	  print ( 66267L ) ;
	  printint ( lastbadness ) ;
	  goto lab50 ;
	} 
      } 
    } 
    goto lab10 ;
  } 
  else {
      
    if ( totalshrink [3 ]!= 0 ) 
    o = 3 ;
    else if ( totalshrink [2 ]!= 0 ) 
    o = 2 ;
    else if ( totalshrink [1 ]!= 0 ) 
    o = 1 ;
    else o = 0 ;
    mem [r + 5 ].hh.b1 = o ;
    mem [r + 5 ].hh.b0 = 2 ;
    if ( totalshrink [o ]!= 0 ) 
    mem [r + 6 ].gr = ( - (integer) x ) / ((double) totalshrink [o ]) ;
    else {
	
      mem [r + 5 ].hh.b0 = 0 ;
      mem [r + 6 ].gr = 0.0 ;
    } 
    if ( ( totalshrink [o ]< - (integer) x ) && ( o == 0 ) && ( mem [r + 5 
    ].hh .v.RH != -268435455L ) ) 
    {
      lastbadness = 1000000L ;
      mem [r + 6 ].gr = 1.0 ;
      if ( ( - (integer) x - totalshrink [0 ]> eqtb [9006729L ].cint ) || 
      ( eqtb [7892291L ].cint < 100 ) ) 
      {
	println () ;
	printnl ( 66268L ) ;
	printscaled ( - (integer) x - totalshrink [0 ]) ;
	print ( 66269L ) ;
	goto lab50 ;
      } 
    } 
    else if ( o == 0 ) {
	
      if ( mem [r + 5 ].hh .v.RH != -268435455L ) 
      {
	lastbadness = badness ( - (integer) x , totalshrink [0 ]) ;
	if ( lastbadness > eqtb [7892291L ].cint ) 
	{
	  println () ;
	  printnl ( 66270L ) ;
	  printint ( lastbadness ) ;
	  goto lab50 ;
	} 
      } 
    } 
    goto lab10 ;
  } 
  lab50: if ( outputactive ) 
  print ( 66258L ) ;
  else {
      
    if ( packbeginline != 0 ) 
    {
      print ( 66260L ) ;
      printint ( abs ( packbeginline ) ) ;
      print ( 66261L ) ;
    } 
    else print ( 66262L ) ;
    printint ( line ) ;
    println () ;
  } 
  begindiagnostic () ;
  showbox ( r ) ;
  enddiagnostic ( true ) ;
  lab10: Result = r ;
  return Result ;
} 
void 
zappendtovlist ( halfword b ) 
{
  appendtovlist_regmem 
  scaled d  ;
  halfword p  ;
  boolean upwards  ;
  upwards = ( eqtb [7892341L ].cint > 0 ) ;
  if ( curlist .auxfield .cint > -65536000L ) 
  {
    if ( upwards ) 
    d = mem [eqtb [1205765L ].hh .v.RH + 1 ].cint - curlist .auxfield 
    .cint - mem [b + 2 ].cint ;
    else d = mem [eqtb [1205765L ].hh .v.RH + 1 ].cint - curlist .auxfield 
    .cint - mem [b + 3 ].cint ;
    if ( d < eqtb [9006722L ].cint ) 
    p = newparamglue ( 0 ) ;
    else {
	
      p = newskipparam ( 1 ) ;
      mem [tempptr + 1 ].cint = d ;
    } 
    mem [curlist .tailfield ].hh .v.RH = p ;
    curlist .tailfield = p ;
  } 
  mem [curlist .tailfield ].hh .v.RH = b ;
  curlist .tailfield = b ;
  if ( upwards ) 
  curlist .auxfield .cint = mem [b + 3 ].cint ;
  else curlist .auxfield .cint = mem [b + 2 ].cint ;
} 
halfword 
newnoad ( void ) 
{
  register halfword Result; newnoad_regmem 
  halfword p  ;
  p = getnode ( 4 ) ;
  mem [p ].hh.b0 = 16 ;
  mem [p ].hh.b1 = 0 ;
  mem [p + 1 ].hh = emptyfield ;
  mem [p + 3 ].hh = emptyfield ;
  mem [p + 2 ].hh = emptyfield ;
  Result = p ;
  return Result ;
} 
halfword 
znewstyle ( smallnumber s ) 
{
  register halfword Result; newstyle_regmem 
  halfword p  ;
  p = getnode ( 3 ) ;
  mem [p ].hh.b0 = 14 ;
  mem [p ].hh.b1 = s ;
  mem [p + 1 ].cint = 0 ;
  mem [p + 2 ].cint = 0 ;
  Result = p ;
  return Result ;
} 
halfword 
newchoice ( void ) 
{
  register halfword Result; newchoice_regmem 
  halfword p  ;
  p = getnode ( 3 ) ;
  mem [p ].hh.b0 = 15 ;
  mem [p ].hh.b1 = 0 ;
  mem [p + 1 ].hh .v.LH = -268435455L ;
  mem [p + 1 ].hh .v.RH = -268435455L ;
  mem [p + 2 ].hh .v.LH = -268435455L ;
  mem [p + 2 ].hh .v.RH = -268435455L ;
  Result = p ;
  return Result ;
} 
void 
showinfo ( void ) 
{
  showinfo_regmem 
  shownodelist ( mem [tempptr ].hh .v.LH ) ;
} 
scaled 
zmathxheight ( integer sizecode ) 
{
  register scaled Result; mathxheight_regmem 
  integer f  ;
  scaled rval  ;
  f = eqtb [1206826L + sizecode ].hh .v.RH ;
  if ( ( ( fontarea [f ]== 65534L ) && ( isOpenTypeMathFont ( 
  fontlayoutengine [f ]) ) ) ) 
  rval = getnativemathsyparam ( f , 5 ) ;
  else rval = fontinfo [5 + parambase [f ]].cint ;
  Result = rval ;
  return Result ;
} 
scaled 
zmathquad ( integer sizecode ) 
{
  register scaled Result; mathquad_regmem 
  integer f  ;
  scaled rval  ;
  f = eqtb [1206826L + sizecode ].hh .v.RH ;
  if ( ( ( fontarea [f ]== 65534L ) && ( isOpenTypeMathFont ( 
  fontlayoutengine [f ]) ) ) ) 
  rval = getnativemathsyparam ( f , 6 ) ;
  else rval = fontinfo [6 + parambase [f ]].cint ;
  Result = rval ;
  return Result ;
} 
scaled 
znum1 ( integer sizecode ) 
{
  register scaled Result; num1_regmem 
  integer f  ;
  scaled rval  ;
  f = eqtb [1206826L + sizecode ].hh .v.RH ;
  if ( ( ( fontarea [f ]== 65534L ) && ( isOpenTypeMathFont ( 
  fontlayoutengine [f ]) ) ) ) 
  rval = getnativemathsyparam ( f , 8 ) ;
  else rval = fontinfo [8 + parambase [f ]].cint ;
  Result = rval ;
  return Result ;
} 
scaled 
znum2 ( integer sizecode ) 
{
  register scaled Result; num2_regmem 
  integer f  ;
  scaled rval  ;
  f = eqtb [1206826L + sizecode ].hh .v.RH ;
  if ( ( ( fontarea [f ]== 65534L ) && ( isOpenTypeMathFont ( 
  fontlayoutengine [f ]) ) ) ) 
  rval = getnativemathsyparam ( f , 9 ) ;
  else rval = fontinfo [9 + parambase [f ]].cint ;
  Result = rval ;
  return Result ;
} 
scaled 
znum3 ( integer sizecode ) 
{
  register scaled Result; num3_regmem 
  integer f  ;
  scaled rval  ;
  f = eqtb [1206826L + sizecode ].hh .v.RH ;
  if ( ( ( fontarea [f ]== 65534L ) && ( isOpenTypeMathFont ( 
  fontlayoutengine [f ]) ) ) ) 
  rval = getnativemathsyparam ( f , 10 ) ;
  else rval = fontinfo [10 + parambase [f ]].cint ;
  Result = rval ;
  return Result ;
} 
scaled 
zdenom1 ( integer sizecode ) 
{
  register scaled Result; denom1_regmem 
  integer f  ;
  scaled rval  ;
  f = eqtb [1206826L + sizecode ].hh .v.RH ;
  if ( ( ( fontarea [f ]== 65534L ) && ( isOpenTypeMathFont ( 
  fontlayoutengine [f ]) ) ) ) 
  rval = getnativemathsyparam ( f , 11 ) ;
  else rval = fontinfo [11 + parambase [f ]].cint ;
  Result = rval ;
  return Result ;
} 
scaled 
zdenom2 ( integer sizecode ) 
{
  register scaled Result; denom2_regmem 
  integer f  ;
  scaled rval  ;
  f = eqtb [1206826L + sizecode ].hh .v.RH ;
  if ( ( ( fontarea [f ]== 65534L ) && ( isOpenTypeMathFont ( 
  fontlayoutengine [f ]) ) ) ) 
  rval = getnativemathsyparam ( f , 12 ) ;
  else rval = fontinfo [12 + parambase [f ]].cint ;
  Result = rval ;
  return Result ;
} 
scaled 
zsup1 ( integer sizecode ) 
{
  register scaled Result; sup1_regmem 
  integer f  ;
  scaled rval  ;
  f = eqtb [1206826L + sizecode ].hh .v.RH ;
  if ( ( ( fontarea [f ]== 65534L ) && ( isOpenTypeMathFont ( 
  fontlayoutengine [f ]) ) ) ) 
  rval = getnativemathsyparam ( f , 13 ) ;
  else rval = fontinfo [13 + parambase [f ]].cint ;
  Result = rval ;
  return Result ;
} 
scaled 
zsup2 ( integer sizecode ) 
{
  register scaled Result; sup2_regmem 
  integer f  ;
  scaled rval  ;
  f = eqtb [1206826L + sizecode ].hh .v.RH ;
  if ( ( ( fontarea [f ]== 65534L ) && ( isOpenTypeMathFont ( 
  fontlayoutengine [f ]) ) ) ) 
  rval = getnativemathsyparam ( f , 14 ) ;
  else rval = fontinfo [14 + parambase [f ]].cint ;
  Result = rval ;
  return Result ;
} 
scaled 
zsup3 ( integer sizecode ) 
{
  register scaled Result; sup3_regmem 
  integer f  ;
  scaled rval  ;
  f = eqtb [1206826L + sizecode ].hh .v.RH ;
  if ( ( ( fontarea [f ]== 65534L ) && ( isOpenTypeMathFont ( 
  fontlayoutengine [f ]) ) ) ) 
  rval = getnativemathsyparam ( f , 15 ) ;
  else rval = fontinfo [15 + parambase [f ]].cint ;
  Result = rval ;
  return Result ;
} 
scaled 
zsub1 ( integer sizecode ) 
{
  register scaled Result; sub1_regmem 
  integer f  ;
  scaled rval  ;
  f = eqtb [1206826L + sizecode ].hh .v.RH ;
  if ( ( ( fontarea [f ]== 65534L ) && ( isOpenTypeMathFont ( 
  fontlayoutengine [f ]) ) ) ) 
  rval = getnativemathsyparam ( f , 16 ) ;
  else rval = fontinfo [16 + parambase [f ]].cint ;
  Result = rval ;
  return Result ;
} 
scaled 
zsub2 ( integer sizecode ) 
{
  register scaled Result; sub2_regmem 
  integer f  ;
  scaled rval  ;
  f = eqtb [1206826L + sizecode ].hh .v.RH ;
  if ( ( ( fontarea [f ]== 65534L ) && ( isOpenTypeMathFont ( 
  fontlayoutengine [f ]) ) ) ) 
  rval = getnativemathsyparam ( f , 17 ) ;
  else rval = fontinfo [17 + parambase [f ]].cint ;
  Result = rval ;
  return Result ;
} 
scaled 
zsupdrop ( integer sizecode ) 
{
  register scaled Result; supdrop_regmem 
  integer f  ;
  scaled rval  ;
  f = eqtb [1206826L + sizecode ].hh .v.RH ;
  if ( ( ( fontarea [f ]== 65534L ) && ( isOpenTypeMathFont ( 
  fontlayoutengine [f ]) ) ) ) 
  rval = getnativemathsyparam ( f , 18 ) ;
  else rval = fontinfo [18 + parambase [f ]].cint ;
  Result = rval ;
  return Result ;
} 
scaled 
zsubdrop ( integer sizecode ) 
{
  register scaled Result; subdrop_regmem 
  integer f  ;
  scaled rval  ;
  f = eqtb [1206826L + sizecode ].hh .v.RH ;
  if ( ( ( fontarea [f ]== 65534L ) && ( isOpenTypeMathFont ( 
  fontlayoutengine [f ]) ) ) ) 
  rval = getnativemathsyparam ( f , 19 ) ;
  else rval = fontinfo [19 + parambase [f ]].cint ;
  Result = rval ;
  return Result ;
} 
scaled 
zdelim1 ( integer sizecode ) 
{
  register scaled Result; delim1_regmem 
  integer f  ;
  scaled rval  ;
  f = eqtb [1206826L + sizecode ].hh .v.RH ;
  if ( ( ( fontarea [f ]== 65534L ) && ( isOpenTypeMathFont ( 
  fontlayoutengine [f ]) ) ) ) 
  rval = getnativemathsyparam ( f , 20 ) ;
  else rval = fontinfo [20 + parambase [f ]].cint ;
  Result = rval ;
  return Result ;
} 
scaled 
zdelim2 ( integer sizecode ) 
{
  register scaled Result; delim2_regmem 
  integer f  ;
  scaled rval  ;
  f = eqtb [1206826L + sizecode ].hh .v.RH ;
  if ( ( ( fontarea [f ]== 65534L ) && ( isOpenTypeMathFont ( 
  fontlayoutengine [f ]) ) ) ) 
  rval = getnativemathsyparam ( f , 21 ) ;
  else rval = fontinfo [21 + parambase [f ]].cint ;
  Result = rval ;
  return Result ;
} 
scaled 
zaxisheight ( integer sizecode ) 
{
  register scaled Result; axisheight_regmem 
  integer f  ;
  scaled rval  ;
  f = eqtb [1206826L + sizecode ].hh .v.RH ;
  if ( ( ( fontarea [f ]== 65534L ) && ( isOpenTypeMathFont ( 
  fontlayoutengine [f ]) ) ) ) 
  rval = getnativemathsyparam ( f , 22 ) ;
  else rval = fontinfo [22 + parambase [f ]].cint ;
  Result = rval ;
  return Result ;
} 
scaled 
defaultrulethickness ( void ) 
{
  register scaled Result; defaultrulethickness_regmem 
  integer f  ;
  scaled rval  ;
  f = eqtb [1206827L + cursize ].hh .v.RH ;
  if ( ( ( fontarea [f ]== 65534L ) && ( isOpenTypeMathFont ( 
  fontlayoutengine [f ]) ) ) ) 
  rval = getnativemathexparam ( f , 8 ) ;
  else rval = fontinfo [8 + parambase [f ]].cint ;
  Result = rval ;
  return Result ;
} 
scaled 
bigopspacing1 ( void ) 
{
  register scaled Result; bigopspacing1_regmem 
  integer f  ;
  scaled rval  ;
  f = eqtb [1206827L + cursize ].hh .v.RH ;
  if ( ( ( fontarea [f ]== 65534L ) && ( isOpenTypeMathFont ( 
  fontlayoutengine [f ]) ) ) ) 
  rval = getnativemathexparam ( f , 9 ) ;
  else rval = fontinfo [9 + parambase [f ]].cint ;
  Result = rval ;
  return Result ;
} 
scaled 
bigopspacing2 ( void ) 
{
  register scaled Result; bigopspacing2_regmem 
  integer f  ;
  scaled rval  ;
  f = eqtb [1206827L + cursize ].hh .v.RH ;
  if ( ( ( fontarea [f ]== 65534L ) && ( isOpenTypeMathFont ( 
  fontlayoutengine [f ]) ) ) ) 
  rval = getnativemathexparam ( f , 10 ) ;
  else rval = fontinfo [10 + parambase [f ]].cint ;
  Result = rval ;
  return Result ;
} 
scaled 
bigopspacing3 ( void ) 
{
  register scaled Result; bigopspacing3_regmem 
  integer f  ;
  scaled rval  ;
  f = eqtb [1206827L + cursize ].hh .v.RH ;
  if ( ( ( fontarea [f ]== 65534L ) && ( isOpenTypeMathFont ( 
  fontlayoutengine [f ]) ) ) ) 
  rval = getnativemathexparam ( f , 11 ) ;
  else rval = fontinfo [11 + parambase [f ]].cint ;
  Result = rval ;
  return Result ;
} 
scaled 
bigopspacing4 ( void ) 
{
  register scaled Result; bigopspacing4_regmem 
  integer f  ;
  scaled rval  ;
  f = eqtb [1206827L + cursize ].hh .v.RH ;
  if ( ( ( fontarea [f ]== 65534L ) && ( isOpenTypeMathFont ( 
  fontlayoutengine [f ]) ) ) ) 
  rval = getnativemathexparam ( f , 12 ) ;
  else rval = fontinfo [12 + parambase [f ]].cint ;
  Result = rval ;
  return Result ;
} 
scaled 
bigopspacing5 ( void ) 
{
  register scaled Result; bigopspacing5_regmem 
  integer f  ;
  scaled rval  ;
  f = eqtb [1206827L + cursize ].hh .v.RH ;
  if ( ( ( fontarea [f ]== 65534L ) && ( isOpenTypeMathFont ( 
  fontlayoutengine [f ]) ) ) ) 
  rval = getnativemathexparam ( f , 13 ) ;
  else rval = fontinfo [13 + parambase [f ]].cint ;
  Result = rval ;
  return Result ;
} 
halfword 
zfractionrule ( scaled t ) 
{
  register halfword Result; fractionrule_regmem 
  halfword p  ;
  p = newrule () ;
  mem [p + 3 ].cint = t ;
  mem [p + 2 ].cint = 0 ;
  Result = p ;
  return Result ;
} 
halfword 
zoverbar ( halfword b , scaled k , scaled t ) 
{
  register halfword Result; overbar_regmem 
  halfword p, q  ;
  p = newkern ( k ) ;
  mem [p ].hh .v.RH = b ;
  q = fractionrule ( t ) ;
  mem [q ].hh .v.RH = p ;
  p = newkern ( t ) ;
  mem [p ].hh .v.RH = q ;
  Result = vpackage ( p , 0 , 1 , 1073741823L ) ;
  return Result ;
} 
halfword 
zcharbox ( internalfontnumber f , integer c ) 
{
  register halfword Result; charbox_regmem 
  fourquarters q  ;
  eightbits hd  ;
  halfword b, p  ;
  if ( ( ( fontarea [f ]== 65535L ) || ( fontarea [f ]== 65534L ) ) ) 
  {
    b = newnullbox () ;
    p = newnativecharacter ( f , c ) ;
    mem [b + 5 ].hh .v.RH = p ;
    mem [b + 3 ].cint = mem [p + 3 ].cint ;
    mem [b + 1 ].cint = mem [p + 1 ].cint ;
    if ( mem [p + 2 ].cint < 0 ) 
    mem [b + 2 ].cint = 0 ;
    else mem [b + 2 ].cint = mem [p + 2 ].cint ;
  } 
  else {
      
    q = fontinfo [charbase [f ]+ effectivechar ( true , f , c ) ].qqqq ;
    hd = q .b1 ;
    b = newnullbox () ;
    mem [b + 1 ].cint = fontinfo [widthbase [f ]+ q .b0 ].cint + 
    fontinfo [italicbase [f ]+ ( q .b2 ) / 4 ].cint ;
    mem [b + 3 ].cint = fontinfo [heightbase [f ]+ ( hd ) / 16 ].cint ;
    mem [b + 2 ].cint = fontinfo [depthbase [f ]+ ( hd ) % 16 ].cint ;
    p = getavail () ;
    mem [p ].hh.b1 = c ;
    mem [p ].hh.b0 = f ;
  } 
  mem [b + 5 ].hh .v.RH = p ;
  Result = b ;
  return Result ;
} 
void 
zstackintobox ( halfword b , internalfontnumber f , quarterword c ) 
{
  stackintobox_regmem 
  halfword p  ;
  p = charbox ( f , c ) ;
  mem [p ].hh .v.RH = mem [b + 5 ].hh .v.RH ;
  mem [b + 5 ].hh .v.RH = p ;
  mem [b + 3 ].cint = mem [p + 3 ].cint ;
} 
scaled 
zheightplusdepth ( internalfontnumber f , quarterword c ) 
{
  register scaled Result; heightplusdepth_regmem 
  fourquarters q  ;
  eightbits hd  ;
  q = fontinfo [charbase [f ]+ effectivechar ( true , f , c ) ].qqqq ;
  hd = q .b1 ;
  Result = fontinfo [heightbase [f ]+ ( hd ) / 16 ].cint + fontinfo [
  depthbase [f ]+ ( hd ) % 16 ].cint ;
  return Result ;
} 
void 
zstackglyphintobox ( halfword b , internalfontnumber f , integer g ) 
{
  stackglyphintobox_regmem 
  halfword p, q  ;
  p = getnode ( 5 ) ;
  mem [p ].hh.b0 = 8 ;
  mem [p ].hh.b1 = 42 ;
  mem [p + 4 ].qqqq .b1 = f ;
  mem [p + 4 ].qqqq .b2 = g ;
  setnativeglyphmetrics ( p , 1 ) ;
  if ( mem [b ].hh.b0 == 0 ) 
  {
    q = mem [b + 5 ].hh .v.RH ;
    if ( q == -268435455L ) 
    mem [b + 5 ].hh .v.RH = p ;
    else {
	
      while ( mem [q ].hh .v.RH != -268435455L ) q = mem [q ].hh .v.RH ;
      mem [q ].hh .v.RH = p ;
      if ( ( mem [b + 3 ].cint < mem [p + 3 ].cint ) ) 
      mem [b + 3 ].cint = mem [p + 3 ].cint ;
      if ( ( mem [b + 2 ].cint < mem [p + 2 ].cint ) ) 
      mem [b + 2 ].cint = mem [p + 2 ].cint ;
    } 
  } 
  else {
      
    mem [p ].hh .v.RH = mem [b + 5 ].hh .v.RH ;
    mem [b + 5 ].hh .v.RH = p ;
    mem [b + 3 ].cint = mem [p + 3 ].cint ;
    if ( ( mem [b + 1 ].cint < mem [p + 1 ].cint ) ) 
    mem [b + 1 ].cint = mem [p + 1 ].cint ;
  } 
} 
void 
zstackglueintobox ( halfword b , scaled min , scaled max ) 
{
  stackglueintobox_regmem 
  halfword p, q  ;
  q = newspec ( membot ) ;
  mem [q + 1 ].cint = min ;
  mem [q + 2 ].cint = max - min ;
  p = newglue ( q ) ;
  if ( mem [b ].hh.b0 == 0 ) 
  {
    q = mem [b + 5 ].hh .v.RH ;
    if ( q == -268435455L ) 
    mem [b + 5 ].hh .v.RH = p ;
    else {
	
      while ( mem [q ].hh .v.RH != -268435455L ) q = mem [q ].hh .v.RH ;
      mem [q ].hh .v.RH = p ;
    } 
  } 
  else {
      
    mem [p ].hh .v.RH = mem [b + 5 ].hh .v.RH ;
    mem [b + 5 ].hh .v.RH = p ;
    mem [b + 3 ].cint = mem [p + 3 ].cint ;
    mem [b + 1 ].cint = mem [p + 1 ].cint ;
  } 
} 
halfword 
zbuildopentypeassembly ( internalfontnumber f , voidpointer a , scaled s , 
boolean horiz ) 
{
  register halfword Result; buildopentypeassembly_regmem 
  halfword b  ;
  integer n  ;
  integer i, j  ;
  integer g  ;
  halfword p  ;
  scaled smax, o, oo, prevo, mino  ;
  boolean noextenders  ;
  scaled nat, str  ;
  b = newnullbox () ;
  if ( horiz ) 
  mem [b ].hh.b0 = 0 ;
  else mem [b ].hh.b0 = 1 ;
  n = -1 ;
  noextenders = true ;
  mino = otminconnectoroverlap ( f ) ;
  do {
      n = n + 1 ;
    smax = 0 ;
    prevo = 0 ;
    {register integer for_end; i = 0 ;for_end = otpartcount ( a ) - 1 ; if ( 
    i <= for_end) do 
      {
	if ( otpartisextender ( a , i ) ) 
	{
	  noextenders = false ;
	  {register integer for_end; j = 1 ;for_end = n ; if ( j <= for_end) 
	  do 
	    {
	      o = otpartstartconnector ( f , a , i ) ;
	      if ( mino < o ) 
	      o = mino ;
	      if ( prevo < o ) 
	      o = prevo ;
	      smax = smax - o + otpartfulladvance ( f , a , i ) ;
	      prevo = otpartendconnector ( f , a , i ) ;
	    } 
	  while ( j++ < for_end ) ;} 
	} 
	else {
	    
	  o = otpartstartconnector ( f , a , i ) ;
	  if ( mino < o ) 
	  o = mino ;
	  if ( prevo < o ) 
	  o = prevo ;
	  smax = smax - o + otpartfulladvance ( f , a , i ) ;
	  prevo = otpartendconnector ( f , a , i ) ;
	} 
      } 
    while ( i++ < for_end ) ;} 
  } while ( ! ( ( smax >= s ) || noextenders ) ) ;
  prevo = 0 ;
  {register integer for_end; i = 0 ;for_end = otpartcount ( a ) - 1 ; if ( i 
  <= for_end) do 
    {
      if ( otpartisextender ( a , i ) ) 
      {
	{register integer for_end; j = 1 ;for_end = n ; if ( j <= for_end) 
	do 
	  {
	    o = otpartstartconnector ( f , a , i ) ;
	    if ( prevo < o ) 
	    o = prevo ;
	    oo = o ;
	    if ( mino < o ) 
	    o = mino ;
	    if ( oo > 0 ) 
	    stackglueintobox ( b , - (integer) oo , - (integer) o ) ;
	    g = otpartglyph ( a , i ) ;
	    stackglyphintobox ( b , f , g ) ;
	    prevo = otpartendconnector ( f , a , i ) ;
	  } 
	while ( j++ < for_end ) ;} 
      } 
      else {
	  
	o = otpartstartconnector ( f , a , i ) ;
	if ( prevo < o ) 
	o = prevo ;
	oo = o ;
	if ( mino < o ) 
	o = mino ;
	if ( oo > 0 ) 
	stackglueintobox ( b , - (integer) oo , - (integer) o ) ;
	g = otpartglyph ( a , i ) ;
	stackglyphintobox ( b , f , g ) ;
	prevo = otpartendconnector ( f , a , i ) ;
      } 
    } 
  while ( i++ < for_end ) ;} 
  p = mem [b + 5 ].hh .v.RH ;
  nat = 0 ;
  str = 0 ;
  while ( p != -268435455L ) {
      
    if ( mem [p ].hh.b0 == 8 ) 
    {
      if ( horiz ) 
      nat = nat + mem [p + 1 ].cint ;
      else nat = nat + mem [p + 3 ].cint + mem [p + 2 ].cint ;
    } 
    else if ( mem [p ].hh.b0 == 10 ) 
    {
      nat = nat + mem [mem [p + 1 ].hh .v.LH + 1 ].cint ;
      str = str + mem [mem [p + 1 ].hh .v.LH + 2 ].cint ;
    } 
    p = mem [p ].hh .v.RH ;
  } 
  o = 0 ;
  if ( ( s > nat ) && ( str > 0 ) ) 
  {
    o = ( s - nat ) ;
    if ( ( o > str ) ) 
    o = str ;
    mem [b + 5 ].hh.b1 = 0 ;
    mem [b + 5 ].hh.b0 = 1 ;
    mem [b + 6 ].gr = o / ((double) str ) ;
    if ( horiz ) 
    mem [b + 1 ].cint = nat + round ( str * mem [b + 6 ].gr ) ;
    else mem [b + 3 ].cint = nat + round ( str * mem [b + 6 ].gr ) ;
  } 
  else if ( horiz ) 
  mem [b + 1 ].cint = nat ;
  else mem [b + 3 ].cint = nat ;
  Result = b ;
  return Result ;
} 
halfword 
zvardelimiter ( halfword d , integer s , scaled v ) 
{
  /* 40 22 */ register halfword Result; vardelimiter_regmem 
  halfword b  ;
  voidpointer otassemblyptr  ;
  internalfontnumber f, g  ;
  quarterword c, x, y  ;
  integer m, n  ;
  scaled u  ;
  scaled w  ;
  fourquarters q  ;
  eightbits hd  ;
  fourquarters r  ;
  integer z  ;
  boolean largeattempt  ;
  f = 0 ;
  w = 0 ;
  largeattempt = false ;
  z = ( mem [d ].qqqq .b0 % 256 ) ;
  x = ( mem [d ].qqqq .b1 + ( mem [d ].qqqq .b0 / 256 ) * 65536L ) ;
  otassemblyptr = nil ;
  while ( true ) {
      
    if ( ( z != 0 ) || ( x != 0 ) ) 
    {
      z = z + s + 256 ;
      do {
	  z = z - 256 ;
	g = eqtb [1206824L + z ].hh .v.RH ;
	if ( g != 0 ) {
	    
	  if ( ( ( fontarea [g ]== 65534L ) && ( usingOpenType ( 
	  fontlayoutengine [g ]) ) ) ) 
	  {
	    x = mapchartoglyph ( g , x ) ;
	    f = g ;
	    c = x ;
	    w = 0 ;
	    n = 0 ;
	    do {
		y = getotmathvariant ( g , x , n , addressof ( u ) , 0 ) ;
	      if ( u > w ) 
	      {
		c = y ;
		w = u ;
		if ( u >= v ) 
		goto lab40 ;
	      } 
	      n = n + 1 ;
	    } while ( ! ( u < 0 ) ) ;
	    otassemblyptr = getotassemblyptr ( g , x , 0 ) ;
	    if ( otassemblyptr != nil ) 
	    goto lab40 ;
	  } 
	  else {
	      
	    y = x ;
	    if ( ( y >= fontbc [g ]) && ( y <= fontec [g ]) ) 
	    {
	      lab22: q = fontinfo [charbase [g ]+ y ].qqqq ;
	      if ( ( q .b0 > 0 ) ) 
	      {
		if ( ( ( q .b2 ) % 4 ) == 3 ) 
		{
		  f = g ;
		  c = y ;
		  goto lab40 ;
		} 
		hd = q .b1 ;
		u = fontinfo [heightbase [g ]+ ( hd ) / 16 ].cint + 
		fontinfo [depthbase [g ]+ ( hd ) % 16 ].cint ;
		if ( u > w ) 
		{
		  f = g ;
		  c = y ;
		  w = u ;
		  if ( u >= v ) 
		  goto lab40 ;
		} 
		if ( ( ( q .b2 ) % 4 ) == 2 ) 
		{
		  y = q .b3 ;
		  goto lab22 ;
		} 
	      } 
	    } 
	  } 
	} 
      } while ( ! ( z < 256 ) ) ;
    } 
    if ( largeattempt ) 
    goto lab40 ;
    largeattempt = true ;
    z = ( mem [d ].qqqq .b2 % 256 ) ;
    x = ( mem [d ].qqqq .b3 + ( mem [d ].qqqq .b2 / 256 ) * 65536L ) ;
  } 
  lab40: if ( f != 0 ) 
  {
    if ( ! ( ( fontarea [f ]== 65534L ) && ( usingOpenType ( 
    fontlayoutengine [f ]) ) ) ) {
	
      if ( ( ( q .b2 ) % 4 ) == 3 ) 
      {
	b = newnullbox () ;
	mem [b ].hh.b0 = 1 ;
	r = fontinfo [extenbase [f ]+ q .b3 ].qqqq ;
	c = r .b3 ;
	u = heightplusdepth ( f , c ) ;
	w = 0 ;
	q = fontinfo [charbase [f ]+ effectivechar ( true , f , c ) ].qqqq 
	;
	mem [b + 1 ].cint = fontinfo [widthbase [f ]+ q .b0 ].cint + 
	fontinfo [italicbase [f ]+ ( q .b2 ) / 4 ].cint ;
	c = r .b2 ;
	if ( c != 0 ) 
	w = w + heightplusdepth ( f , c ) ;
	c = r .b1 ;
	if ( c != 0 ) 
	w = w + heightplusdepth ( f , c ) ;
	c = r .b0 ;
	if ( c != 0 ) 
	w = w + heightplusdepth ( f , c ) ;
	n = 0 ;
	if ( u > 0 ) 
	while ( w < v ) {
	    
	  w = w + u ;
	  incr ( n ) ;
	  if ( r .b1 != 0 ) 
	  w = w + u ;
	} 
	c = r .b2 ;
	if ( c != 0 ) 
	stackintobox ( b , f , c ) ;
	c = r .b3 ;
	{register integer for_end; m = 1 ;for_end = n ; if ( m <= for_end) 
	do 
	  stackintobox ( b , f , c ) ;
	while ( m++ < for_end ) ;} 
	c = r .b1 ;
	if ( c != 0 ) 
	{
	  stackintobox ( b , f , c ) ;
	  c = r .b3 ;
	  {register integer for_end; m = 1 ;for_end = n ; if ( m <= for_end) 
	  do 
	    stackintobox ( b , f , c ) ;
	  while ( m++ < for_end ) ;} 
	} 
	c = r .b0 ;
	if ( c != 0 ) 
	stackintobox ( b , f , c ) ;
	mem [b + 2 ].cint = w - mem [b + 3 ].cint ;
      } 
      else b = charbox ( f , c ) ;
    } 
    else {
	
      if ( otassemblyptr != nil ) 
      b = buildopentypeassembly ( f , otassemblyptr , v , 0 ) ;
      else {
	  
	b = newnullbox () ;
	mem [b ].hh.b0 = 1 ;
	mem [b + 5 ].hh .v.RH = getnode ( 5 ) ;
	mem [mem [b + 5 ].hh .v.RH ].hh.b0 = 8 ;
	mem [mem [b + 5 ].hh .v.RH ].hh.b1 = 42 ;
	mem [mem [b + 5 ].hh .v.RH + 4 ].qqqq .b1 = f ;
	mem [mem [b + 5 ].hh .v.RH + 4 ].qqqq .b2 = c ;
	setnativeglyphmetrics ( mem [b + 5 ].hh .v.RH , 1 ) ;
	mem [b + 1 ].cint = mem [mem [b + 5 ].hh .v.RH + 1 ].cint ;
	mem [b + 3 ].cint = mem [mem [b + 5 ].hh .v.RH + 3 ].cint ;
	mem [b + 2 ].cint = mem [mem [b + 5 ].hh .v.RH + 2 ].cint ;
      } 
    } 
  } 
  else {
      
    b = newnullbox () ;
    mem [b + 1 ].cint = eqtb [9006731L ].cint ;
  } 
  mem [b + 4 ].cint = half ( mem [b + 3 ].cint - mem [b + 2 ].cint ) - 
  axisheight ( s ) ;
  freeotassembly ( otassemblyptr ) ;
  Result = b ;
  return Result ;
} 
halfword 
zrebox ( halfword b , scaled w ) 
{
  register halfword Result; rebox_regmem 
  halfword p  ;
  internalfontnumber f  ;
  scaled v  ;
  if ( ( mem [b + 1 ].cint != w ) && ( mem [b + 5 ].hh .v.RH != 
  -268435455L ) ) 
  {
    if ( mem [b ].hh.b0 == 1 ) 
    b = hpack ( b , 0 , 1 ) ;
    p = mem [b + 5 ].hh .v.RH ;
    if ( ( ( p >= himemmin ) ) && ( mem [p ].hh .v.RH == -268435455L ) ) 
    {
      f = mem [p ].hh.b0 ;
      v = fontinfo [widthbase [f ]+ fontinfo [charbase [f ]+ 
      effectivechar ( true , f , mem [p ].hh.b1 ) ].qqqq .b0 ].cint ;
      if ( v != mem [b + 1 ].cint ) 
      mem [p ].hh .v.RH = newkern ( mem [b + 1 ].cint - v ) ;
    } 
    freenode ( b , 8 ) ;
    b = newglue ( membot + 12 ) ;
    mem [b ].hh .v.RH = p ;
    while ( mem [p ].hh .v.RH != -268435455L ) p = mem [p ].hh .v.RH ;
    mem [p ].hh .v.RH = newglue ( membot + 12 ) ;
    Result = hpack ( b , w , 0 ) ;
  } 
  else {
      
    mem [b + 1 ].cint = w ;
    Result = b ;
  } 
  return Result ;
} 
halfword 
zmathglue ( halfword g , scaled m ) 
{
  register halfword Result; mathglue_regmem 
  halfword p  ;
  integer n  ;
  scaled f  ;
  n = xovern ( m , 65536L ) ;
  f = texremainder ;
  if ( f < 0 ) 
  {
    decr ( n ) ;
    f = f + 65536L ;
  } 
  p = getnode ( 4 ) ;
  mem [p + 1 ].cint = multandadd ( n , mem [g + 1 ].cint , xnoverd ( mem [
  g + 1 ].cint , f , 65536L ) , 1073741823L ) ;
  mem [p ].hh.b0 = mem [g ].hh.b0 ;
  if ( mem [p ].hh.b0 == 0 ) 
  mem [p + 2 ].cint = multandadd ( n , mem [g + 2 ].cint , xnoverd ( mem [
  g + 2 ].cint , f , 65536L ) , 1073741823L ) ;
  else mem [p + 2 ].cint = mem [g + 2 ].cint ;
  mem [p ].hh.b1 = mem [g ].hh.b1 ;
  if ( mem [p ].hh.b1 == 0 ) 
  mem [p + 3 ].cint = multandadd ( n , mem [g + 3 ].cint , xnoverd ( mem [
  g + 3 ].cint , f , 65536L ) , 1073741823L ) ;
  else mem [p + 3 ].cint = mem [g + 3 ].cint ;
  Result = p ;
  return Result ;
} 
void 
zmathkern ( halfword p , scaled m ) 
{
  mathkern_regmem 
  integer n  ;
  scaled f  ;
  if ( mem [p ].hh.b1 == 99 ) 
  {
    n = xovern ( m , 65536L ) ;
    f = texremainder ;
    if ( f < 0 ) 
    {
      decr ( n ) ;
      f = f + 65536L ;
    } 
    mem [p + 1 ].cint = multandadd ( n , mem [p + 1 ].cint , xnoverd ( mem 
    [p + 1 ].cint , f , 65536L ) , 1073741823L ) ;
    mem [p ].hh.b1 = 1 ;
  } 
} 
void 
flushmath ( void ) 
{
  flushmath_regmem 
  flushnodelist ( mem [curlist .headfield ].hh .v.RH ) ;
  flushnodelist ( curlist .auxfield .cint ) ;
  mem [curlist .headfield ].hh .v.RH = -268435455L ;
  curlist .tailfield = curlist .headfield ;
  curlist .auxfield .cint = -268435455L ;
} 
halfword 
zcleanbox ( halfword p , smallnumber s ) 
{
  /* 40 */ register halfword Result; cleanbox_regmem 
  halfword q  ;
  smallnumber savestyle  ;
  halfword x  ;
  halfword r  ;
  switch ( mem [p ].hh .v.RH ) 
  {case 1 : 
    {
      curmlist = newnoad () ;
      mem [curmlist + 1 ]= mem [p ];
    } 
    break ;
  case 2 : 
    {
      q = mem [p ].hh .v.LH ;
      goto lab40 ;
    } 
    break ;
  case 3 : 
    curmlist = mem [p ].hh .v.LH ;
    break ;
    default: 
    {
      q = newnullbox () ;
      goto lab40 ;
    } 
    break ;
  } 
  savestyle = curstyle ;
  curstyle = s ;
  mlistpenalties = false ;
  mlisttohlist () ;
  q = mem [memtop - 3 ].hh .v.RH ;
  curstyle = savestyle ;
  {
    if ( curstyle < 4 ) 
    cursize = 0 ;
    else cursize = 256 * ( ( curstyle - 2 ) / 2 ) ;
    curmu = xovern ( mathquad ( cursize ) , 18 ) ;
  } 
  lab40: if ( ( q >= himemmin ) || ( q == -268435455L ) ) 
  x = hpack ( q , 0 , 1 ) ;
  else if ( ( mem [q ].hh .v.RH == -268435455L ) && ( mem [q ].hh.b0 <= 1 
  ) && ( mem [q + 4 ].cint == 0 ) ) 
  x = q ;
  else x = hpack ( q , 0 , 1 ) ;
  q = mem [x + 5 ].hh .v.RH ;
  if ( ( q >= himemmin ) ) 
  {
    r = mem [q ].hh .v.RH ;
    if ( r != -268435455L ) {
	
      if ( mem [r ].hh .v.RH == -268435455L ) {
	  
	if ( ! ( r >= himemmin ) ) {
	    
	  if ( mem [r ].hh.b0 == 11 ) 
	  {
	    freenode ( r , 3 ) ;
	    mem [q ].hh .v.RH = -268435455L ;
	  } 
	} 
      } 
    } 
  } 
  Result = x ;
  return Result ;
} 
void 
zfetch ( halfword a ) 
{
  fetch_regmem 
  curc = casttoushort ( mem [a ].hh.b1 ) ;
  curf = eqtb [1206824L + ( mem [a ].hh.b0 % 256 ) + cursize ].hh .v.RH ;
  curc = curc + ( mem [a ].hh.b0 / 256 ) * 65536L ;
  if ( curf == 0 ) 
  {
    {
      if ( interaction == 3 ) 
      ;
      if ( filelineerrorstylep ) 
      printfileline () ;
      else printnl ( 65544L ) ;
      print ( 65545L ) ;
    } 
    printsize ( cursize ) ;
    printchar ( 32 ) ;
    printint ( ( mem [a ].hh.b0 % 256 ) ) ;
    print ( 66313L ) ;
    print ( curc ) ;
    printchar ( 41 ) ;
    {
      helpptr = 4 ;
      helpline [3 ]= 66314L ;
      helpline [2 ]= 66315L ;
      helpline [1 ]= 66316L ;
      helpline [0 ]= 66317L ;
    } 
    error () ;
    curi = nullcharacter ;
    mem [a ].hh .v.RH = 0 ;
  } 
  else if ( ( ( fontarea [curf ]== 65535L ) || ( fontarea [curf ]== 65534L 
  ) ) ) 
  {
    curi = nullcharacter ;
  } 
  else {
      
    if ( ( curc >= fontbc [curf ]) && ( curc <= fontec [curf ]) ) 
    curi = fontinfo [charbase [curf ]+ curc ].qqqq ;
    else curi = nullcharacter ;
    if ( ! ( ( curi .b0 > 0 ) ) ) 
    {
      charwarning ( curf , curc ) ;
      mem [a ].hh .v.RH = 0 ;
      curi = nullcharacter ;
    } 
  } 
} 
void 
zmakeover ( halfword q ) 
{
  makeover_regmem 
  mem [q + 1 ].hh .v.LH = overbar ( cleanbox ( q + 1 , 2 * ( curstyle / 2 ) 
  + 1 ) , 3 * defaultrulethickness () , defaultrulethickness () ) ;
  mem [q + 1 ].hh .v.RH = 2 ;
} 
void 
zmakeunder ( halfword q ) 
{
  makeunder_regmem 
  halfword p, x, y  ;
  scaled delta  ;
  x = cleanbox ( q + 1 , curstyle ) ;
  p = newkern ( 3 * defaultrulethickness () ) ;
  mem [x ].hh .v.RH = p ;
  mem [p ].hh .v.RH = fractionrule ( defaultrulethickness () ) ;
  y = vpackage ( x , 0 , 1 , 1073741823L ) ;
  delta = mem [y + 3 ].cint + mem [y + 2 ].cint + defaultrulethickness () 
  ;
  mem [y + 3 ].cint = mem [x + 3 ].cint ;
  mem [y + 2 ].cint = delta - mem [y + 3 ].cint ;
  mem [q + 1 ].hh .v.LH = y ;
  mem [q + 1 ].hh .v.RH = 2 ;
} 
void 
zmakevcenter ( halfword q ) 
{
  makevcenter_regmem 
  halfword v  ;
  scaled delta  ;
  v = mem [q + 1 ].hh .v.LH ;
  if ( mem [v ].hh.b0 != 1 ) 
  confusion ( 65864L ) ;
  delta = mem [v + 3 ].cint + mem [v + 2 ].cint ;
  mem [v + 3 ].cint = axisheight ( cursize ) + half ( delta ) ;
  mem [v + 2 ].cint = delta - mem [v + 3 ].cint ;
} 
void 
zmakeradical ( halfword q ) 
{
  makeradical_regmem 
  halfword x, y  ;
  internalfontnumber f  ;
  scaled rulethickness  ;
  scaled delta, clr  ;
  f = eqtb [1206824L + ( mem [q + 4 ].qqqq .b0 % 256 ) + cursize ].hh 
  .v.RH ;
  if ( ( ( fontarea [f ]== 65534L ) && ( isOpenTypeMathFont ( 
  fontlayoutengine [f ]) ) ) ) 
  rulethickness = getotmathconstant ( f , 51 ) ;
  else rulethickness = defaultrulethickness () ;
  x = cleanbox ( q + 1 , 2 * ( curstyle / 2 ) + 1 ) ;
  if ( ( ( fontarea [f ]== 65534L ) && ( isOpenTypeMathFont ( 
  fontlayoutengine [f ]) ) ) ) 
  {
    if ( curstyle < 2 ) 
    clr = getotmathconstant ( f , 50 ) ;
    else clr = getotmathconstant ( f , 49 ) ;
  } 
  else {
      
    if ( curstyle < 2 ) 
    clr = rulethickness + ( abs ( mathxheight ( cursize ) ) / 4 ) ;
    else {
	
      clr = rulethickness ;
      clr = clr + ( abs ( clr ) / 4 ) ;
    } 
  } 
  y = vardelimiter ( q + 4 , cursize , mem [x + 3 ].cint + mem [x + 2 ]
  .cint + clr + rulethickness ) ;
  if ( ( ( fontarea [f ]== 65534L ) && ( isOpenTypeMathFont ( 
  fontlayoutengine [f ]) ) ) ) 
  {
    mem [y + 2 ].cint = mem [y + 3 ].cint + mem [y + 2 ].cint - 
    rulethickness ;
    mem [y + 3 ].cint = rulethickness ;
  } 
  delta = mem [y + 2 ].cint - ( mem [x + 3 ].cint + mem [x + 2 ].cint + 
  clr ) ;
  if ( delta > 0 ) 
  clr = clr + half ( delta ) ;
  mem [y + 4 ].cint = - (integer) ( mem [x + 3 ].cint + clr ) ;
  mem [y ].hh .v.RH = overbar ( x , clr , mem [y + 3 ].cint ) ;
  mem [q + 1 ].hh .v.LH = hpack ( y , 0 , 1 ) ;
  mem [q + 1 ].hh .v.RH = 2 ;
} 
scaled 
zcomputeotmathaccentpos ( halfword p ) 
{
  register scaled Result; computeotmathaccentpos_regmem 
  halfword q, r  ;
  scaled s, g  ;
  if ( ( mem [p + 1 ].hh .v.RH == 1 ) ) 
  {
    fetch ( p + 1 ) ;
    q = newnativecharacter ( curf , curc ) ;
    g = getnativeglyph ( q , 0 ) ;
    s = getotmathaccentpos ( curf , g ) ;
  } 
  else {
      
    if ( ( mem [p + 1 ].hh .v.RH == 3 ) ) 
    {
      r = mem [p + 1 ].hh .v.LH ;
      if ( ( r != -268435455L ) && ( mem [r ].hh.b0 == 28 ) ) 
      s = computeotmathaccentpos ( r ) ;
      else s = 2147483647L ;
    } 
    else s = 2147483647L ;
  } 
  Result = s ;
  return Result ;
} 
void 
zmakemathaccent ( halfword q ) 
{
  /* 30 31 */ makemathaccent_regmem 
  halfword p, x, y  ;
  integer a  ;
  integer c, g  ;
  internalfontnumber f  ;
  fourquarters i  ;
  scaled s, sa  ;
  scaled h  ;
  scaled delta  ;
  scaled w, w2  ;
  voidpointer otassemblyptr  ;
  fetch ( q + 4 ) ;
  x = -268435455L ;
  otassemblyptr = nil ;
  if ( ( ( fontarea [curf ]== 65535L ) || ( fontarea [curf ]== 65534L ) ) 
  ) 
  {
    c = curc ;
    f = curf ;
    if ( ! ( ( mem [q ].hh.b1 == 2 ) || ( mem [q ].hh.b1 == 3 ) ) ) 
    s = computeotmathaccentpos ( q ) ;
    else s = 0 ;
    x = cleanbox ( q + 1 , 2 * ( curstyle / 2 ) + 1 ) ;
    w = mem [x + 1 ].cint ;
    h = mem [x + 3 ].cint ;
  } 
  else if ( ( curi .b0 > 0 ) ) 
  {
    i = curi ;
    c = curc ;
    f = curf ;
    s = 0 ;
    if ( mem [q + 1 ].hh .v.RH == 1 ) 
    {
      fetch ( q + 1 ) ;
      if ( ( ( curi .b2 ) % 4 ) == 1 ) 
      {
	a = ligkernbase [curf ]+ curi .b3 ;
	curi = fontinfo [a ].qqqq ;
	if ( curi .b0 > 128 ) 
	{
	  a = ligkernbase [curf ]+ 256 * curi .b2 + curi .b3 + 32768L - 256 
	  * ( 128 ) ;
	  curi = fontinfo [a ].qqqq ;
	} 
	while ( true ) {
	    
	  if ( curi .b1 == skewchar [curf ]) 
	  {
	    if ( curi .b2 >= 128 ) {
		
	      if ( curi .b0 <= 128 ) 
	      s = fontinfo [kernbase [curf ]+ 256 * curi .b2 + curi .b3 ]
	      .cint ;
	    } 
	    goto lab31 ;
	  } 
	  if ( curi .b0 >= 128 ) 
	  goto lab31 ;
	  a = a + curi .b0 + 1 ;
	  curi = fontinfo [a ].qqqq ;
	} 
      } 
    } 
    lab31: ;
    x = cleanbox ( q + 1 , 2 * ( curstyle / 2 ) + 1 ) ;
    w = mem [x + 1 ].cint ;
    h = mem [x + 3 ].cint ;
    while ( true ) {
	
      if ( ( ( i .b2 ) % 4 ) != 2 ) 
      goto lab30 ;
      y = i .b3 ;
      i = fontinfo [charbase [f ]+ y ].qqqq ;
      if ( ! ( i .b0 > 0 ) ) 
      goto lab30 ;
      if ( fontinfo [widthbase [f ]+ i .b0 ].cint > w ) 
      goto lab30 ;
      c = y ;
    } 
    lab30: ;
  } 
  if ( x != -268435455L ) 
  {
    if ( ( ( fontarea [f ]== 65534L ) && ( isOpenTypeMathFont ( 
    fontlayoutengine [f ]) ) ) ) {
	
      if ( ( ( mem [q ].hh.b1 == 2 ) || ( mem [q ].hh.b1 == 3 ) ) ) 
      delta = 0 ;
      else if ( h < getotmathconstant ( f , 6 ) ) 
      delta = h ;
      else delta = getotmathconstant ( f , 6 ) ;
    } 
    else if ( h < fontinfo [5 + parambase [f ]].cint ) 
    delta = h ;
    else delta = fontinfo [5 + parambase [f ]].cint ;
    if ( ( mem [q + 2 ].hh .v.RH != 0 ) || ( mem [q + 3 ].hh .v.RH != 0 ) 
    ) {
	
      if ( mem [q + 1 ].hh .v.RH == 1 ) 
      {
	flushnodelist ( x ) ;
	x = newnoad () ;
	mem [x + 1 ]= mem [q + 1 ];
	mem [x + 2 ]= mem [q + 2 ];
	mem [x + 3 ]= mem [q + 3 ];
	mem [q + 2 ].hh = emptyfield ;
	mem [q + 3 ].hh = emptyfield ;
	mem [q + 1 ].hh .v.RH = 3 ;
	mem [q + 1 ].hh .v.LH = x ;
	x = cleanbox ( q + 1 , curstyle ) ;
	delta = delta + mem [x + 3 ].cint - h ;
	h = mem [x + 3 ].cint ;
      } 
    } 
    y = charbox ( f , c ) ;
    if ( ( ( fontarea [f ]== 65535L ) || ( fontarea [f ]== 65534L ) ) ) 
    {
      p = getnode ( 5 ) ;
      mem [p ].hh.b0 = 8 ;
      mem [p ].hh.b1 = 42 ;
      mem [p + 4 ].qqqq .b1 = f ;
      mem [p + 4 ].qqqq .b2 = getnativeglyph ( mem [y + 5 ].hh .v.RH , 0 ) 
      ;
      setnativeglyphmetrics ( p , 1 ) ;
      freenode ( mem [y + 5 ].hh .v.RH , mem [mem [y + 5 ].hh .v.RH + 4 ]
      .qqqq .b0 ) ;
      mem [y + 5 ].hh .v.RH = p ;
      if ( odd ( mem [q ].hh.b1 ) ) 
      setnativeglyphmetrics ( p , 1 ) ;
      else {
	  
	c = mem [p + 4 ].qqqq .b2 ;
	a = 0 ;
	do {
	    g = getotmathvariant ( f , c , a , addressof ( w2 ) , 1 ) ;
	  if ( ( w2 > 0 ) && ( w2 <= w ) ) 
	  {
	    mem [p + 4 ].qqqq .b2 = g ;
	    setnativeglyphmetrics ( p , 1 ) ;
	    incr ( a ) ;
	  } 
	} while ( ! ( ( w2 < 0 ) || ( w2 >= w ) ) ) ;
	if ( ( w2 < 0 ) ) 
	{
	  otassemblyptr = getotassemblyptr ( f , c , 1 ) ;
	  if ( otassemblyptr != nil ) 
	  {
	    freenode ( p , 5 ) ;
	    p = buildopentypeassembly ( f , otassemblyptr , w , 1 ) ;
	    mem [y + 5 ].hh .v.RH = p ;
	    goto lab40 ;
	  } 
	} 
	else setnativeglyphmetrics ( p , 1 ) ;
      } 
      lab40: mem [y + 1 ].cint = mem [p + 1 ].cint ;
      mem [y + 3 ].cint = mem [p + 3 ].cint ;
      mem [y + 2 ].cint = mem [p + 2 ].cint ;
      if ( ( ( mem [q ].hh.b1 == 2 ) || ( mem [q ].hh.b1 == 3 ) ) ) 
      {
	if ( mem [y + 3 ].cint < 0 ) 
	mem [y + 3 ].cint = 0 ;
      } 
      else if ( mem [y + 2 ].cint < 0 ) 
      mem [y + 2 ].cint = 0 ;
      if ( ( ( ( p ) != -268435455L && ( ! ( p >= himemmin ) ) && ( mem [p ]
      .hh.b0 == 8 ) && ( mem [p ].hh.b1 == 42 ) ) ) ) 
      {
	sa = getotmathaccentpos ( f , mem [p + 4 ].qqqq .b2 ) ;
	if ( sa == 2147483647L ) 
	sa = half ( mem [y + 1 ].cint ) ;
      } 
      else sa = half ( mem [y + 1 ].cint ) ;
      if ( ( ( mem [q ].hh.b1 == 2 ) || ( mem [q ].hh.b1 == 3 ) ) || ( s 
      == 2147483647L ) ) 
      s = half ( w ) ;
      mem [y + 4 ].cint = s - sa ;
    } 
    else mem [y + 4 ].cint = s + half ( w - mem [y + 1 ].cint ) ;
    mem [y + 1 ].cint = 0 ;
    if ( ( ( mem [q ].hh.b1 == 2 ) || ( mem [q ].hh.b1 == 3 ) ) ) 
    {
      mem [x ].hh .v.RH = y ;
      y = vpackage ( x , 0 , 1 , 1073741823L ) ;
      mem [y + 4 ].cint = - (integer) ( h - mem [y + 3 ].cint ) ;
    } 
    else {
	
      p = newkern ( - (integer) delta ) ;
      mem [p ].hh .v.RH = x ;
      mem [y ].hh .v.RH = p ;
      y = vpackage ( y , 0 , 1 , 1073741823L ) ;
      if ( mem [y + 3 ].cint < h ) 
      {
	p = newkern ( h - mem [y + 3 ].cint ) ;
	mem [p ].hh .v.RH = mem [y + 5 ].hh .v.RH ;
	mem [y + 5 ].hh .v.RH = p ;
	mem [y + 3 ].cint = h ;
      } 
    } 
    mem [y + 1 ].cint = mem [x + 1 ].cint ;
    mem [q + 1 ].hh .v.LH = y ;
    mem [q + 1 ].hh .v.RH = 2 ;
  } 
  freeotassembly ( otassemblyptr ) ;
} 
void 
zmakefraction ( halfword q ) 
{
  makefraction_regmem 
  halfword p, v, x, y, z  ;
  scaled delta, delta1, delta2, shiftup, shiftdown, clr  ;
  if ( mem [q + 1 ].cint == 1073741824L ) 
  mem [q + 1 ].cint = defaultrulethickness () ;
  x = cleanbox ( q + 2 , curstyle + 2 - 2 * ( curstyle / 6 ) ) ;
  z = cleanbox ( q + 3 , 2 * ( curstyle / 2 ) + 3 - 2 * ( curstyle / 6 ) ) ;
  if ( mem [x + 1 ].cint < mem [z + 1 ].cint ) 
  x = rebox ( x , mem [z + 1 ].cint ) ;
  else z = rebox ( z , mem [x + 1 ].cint ) ;
  if ( curstyle < 2 ) 
  {
    shiftup = num1 ( cursize ) ;
    shiftdown = denom1 ( cursize ) ;
  } 
  else {
      
    shiftdown = denom2 ( cursize ) ;
    if ( mem [q + 1 ].cint != 0 ) 
    shiftup = num2 ( cursize ) ;
    else shiftup = num3 ( cursize ) ;
  } 
  if ( mem [q + 1 ].cint == 0 ) 
  {
    if ( ( ( fontarea [curf ]== 65534L ) && ( isOpenTypeMathFont ( 
    fontlayoutengine [curf ]) ) ) ) 
    {
      if ( curstyle < 2 ) 
      clr = getotmathconstant ( curf , 27 ) ;
      else clr = getotmathconstant ( curf , 26 ) ;
    } 
    else {
	
      if ( curstyle < 2 ) 
      clr = 7 * defaultrulethickness () ;
      else clr = 3 * defaultrulethickness () ;
    } 
    delta = half ( clr - ( ( shiftup - mem [x + 2 ].cint ) - ( mem [z + 3 ]
    .cint - shiftdown ) ) ) ;
    if ( delta > 0 ) 
    {
      shiftup = shiftup + delta ;
      shiftdown = shiftdown + delta ;
    } 
  } 
  else {
      
    if ( ( ( fontarea [curf ]== 65534L ) && ( isOpenTypeMathFont ( 
    fontlayoutengine [curf ]) ) ) ) 
    {
      delta = half ( mem [q + 1 ].cint ) ;
      if ( curstyle < 2 ) 
      clr = getotmathconstant ( curf , 37 ) ;
      else clr = getotmathconstant ( curf , 36 ) ;
      delta1 = clr - ( ( shiftup - mem [x + 2 ].cint ) - ( axisheight ( 
      cursize ) + delta ) ) ;
      if ( curstyle < 2 ) 
      clr = getotmathconstant ( curf , 40 ) ;
      else clr = getotmathconstant ( curf , 39 ) ;
      delta2 = clr - ( ( axisheight ( cursize ) - delta ) - ( mem [z + 3 ]
      .cint - shiftdown ) ) ;
    } 
    else {
	
      if ( curstyle < 2 ) 
      clr = 3 * mem [q + 1 ].cint ;
      else clr = mem [q + 1 ].cint ;
      delta = half ( mem [q + 1 ].cint ) ;
      delta1 = clr - ( ( shiftup - mem [x + 2 ].cint ) - ( axisheight ( 
      cursize ) + delta ) ) ;
      delta2 = clr - ( ( axisheight ( cursize ) - delta ) - ( mem [z + 3 ]
      .cint - shiftdown ) ) ;
    } 
    if ( delta1 > 0 ) 
    shiftup = shiftup + delta1 ;
    if ( delta2 > 0 ) 
    shiftdown = shiftdown + delta2 ;
  } 
  v = newnullbox () ;
  mem [v ].hh.b0 = 1 ;
  mem [v + 3 ].cint = shiftup + mem [x + 3 ].cint ;
  mem [v + 2 ].cint = mem [z + 2 ].cint + shiftdown ;
  mem [v + 1 ].cint = mem [x + 1 ].cint ;
  if ( mem [q + 1 ].cint == 0 ) 
  {
    p = newkern ( ( shiftup - mem [x + 2 ].cint ) - ( mem [z + 3 ].cint - 
    shiftdown ) ) ;
    mem [p ].hh .v.RH = z ;
  } 
  else {
      
    y = fractionrule ( mem [q + 1 ].cint ) ;
    p = newkern ( ( axisheight ( cursize ) - delta ) - ( mem [z + 3 ].cint - 
    shiftdown ) ) ;
    mem [y ].hh .v.RH = p ;
    mem [p ].hh .v.RH = z ;
    p = newkern ( ( shiftup - mem [x + 2 ].cint ) - ( axisheight ( cursize ) 
    + delta ) ) ;
    mem [p ].hh .v.RH = y ;
  } 
  mem [x ].hh .v.RH = p ;
  mem [v + 5 ].hh .v.RH = x ;
  if ( curstyle < 2 ) 
  delta = delim1 ( cursize ) ;
  else delta = delim2 ( cursize ) ;
  x = vardelimiter ( q + 4 , cursize , delta ) ;
  mem [x ].hh .v.RH = v ;
  z = vardelimiter ( q + 5 , cursize , delta ) ;
  mem [v ].hh .v.RH = z ;
  mem [q + 1 ].cint = hpack ( x , 0 , 1 ) ;
} 
scaled 
zmakeop ( halfword q ) 
{
  /* 40 */ register scaled Result; makeop_regmem 
  scaled delta  ;
  halfword p, v, x, y, z  ;
  quarterword c  ;
  fourquarters i  ;
  scaled shiftup, shiftdown  ;
  scaled h1, h2  ;
  integer n, g  ;
  voidpointer otassemblyptr  ;
  internalfontnumber savef  ;
  if ( ( mem [q ].hh.b1 == 0 ) && ( curstyle < 2 ) ) 
  mem [q ].hh.b1 = 1 ;
  delta = 0 ;
  otassemblyptr = nil ;
  if ( mem [q + 1 ].hh .v.RH == 1 ) 
  {
    fetch ( q + 1 ) ;
    if ( ! ( ( fontarea [curf ]== 65534L ) && ( usingOpenType ( 
    fontlayoutengine [curf ]) ) ) ) 
    {
      if ( ( curstyle < 2 ) && ( ( ( curi .b2 ) % 4 ) == 2 ) ) 
      {
	c = curi .b3 ;
	i = fontinfo [charbase [curf ]+ c ].qqqq ;
	if ( ( i .b0 > 0 ) ) 
	{
	  curc = c ;
	  curi = i ;
	  mem [q + 1 ].hh.b1 = c ;
	} 
      } 
      delta = fontinfo [italicbase [curf ]+ ( curi .b2 ) / 4 ].cint ;
    } 
    x = cleanbox ( q + 1 , curstyle ) ;
    if ( ( ( fontarea [curf ]== 65534L ) && ( isOpenTypeMathFont ( 
    fontlayoutengine [curf ]) ) ) ) 
    {
      p = mem [x + 5 ].hh .v.RH ;
      if ( ( ( ( p ) != -268435455L && ( ! ( p >= himemmin ) ) && ( mem [p ]
      .hh.b0 == 8 ) && ( mem [p ].hh.b1 == 42 ) ) ) ) 
      {
	if ( curstyle < 2 ) 
	{
	  h1 = getotmathconstant ( curf , 3 ) ;
	  if ( h1 < ( mem [p + 3 ].cint + mem [p + 2 ].cint ) * 5 
	  / ((double) 4 ) ) 
	  h1 = ( mem [p + 3 ].cint + mem [p + 2 ].cint ) * 5 / ((double) 4 
	  ) ;
	  c = mem [p + 4 ].qqqq .b2 ;
	  n = 0 ;
	  do {
	      g = getotmathvariant ( curf , c , n , addressof ( h2 ) , 0 ) ;
	    if ( h2 > 0 ) 
	    {
	      mem [p + 4 ].qqqq .b2 = g ;
	      setnativeglyphmetrics ( p , 1 ) ;
	    } 
	    incr ( n ) ;
	  } while ( ! ( ( h2 < 0 ) || ( h2 >= h1 ) ) ) ;
	  if ( ( h2 < 0 ) ) 
	  {
	    otassemblyptr = getotassemblyptr ( curf , c , 0 ) ;
	    if ( otassemblyptr != nil ) 
	    {
	      freenode ( p , 5 ) ;
	      p = buildopentypeassembly ( curf , otassemblyptr , h1 , 0 ) ;
	      mem [x + 5 ].hh .v.RH = p ;
	      delta = 0 ;
	      goto lab40 ;
	    } 
	  } 
	  else setnativeglyphmetrics ( p , 1 ) ;
	} 
	delta = getotmathitalcorr ( curf , mem [p + 4 ].qqqq .b2 ) ;
	lab40: mem [x + 1 ].cint = mem [p + 1 ].cint ;
	mem [x + 3 ].cint = mem [p + 3 ].cint ;
	mem [x + 2 ].cint = mem [p + 2 ].cint ;
      } 
    } 
    if ( ( mem [q + 3 ].hh .v.RH != 0 ) && ( mem [q ].hh.b1 != 1 ) ) 
    mem [x + 1 ].cint = mem [x + 1 ].cint - delta ;
    mem [x + 4 ].cint = half ( mem [x + 3 ].cint - mem [x + 2 ].cint ) - 
    axisheight ( cursize ) ;
    mem [q + 1 ].hh .v.RH = 2 ;
    mem [q + 1 ].hh .v.LH = x ;
  } 
  savef = curf ;
  if ( mem [q ].hh.b1 == 1 ) 
  {
    x = cleanbox ( q + 2 , 2 * ( curstyle / 4 ) + 4 + ( curstyle % 2 ) ) ;
    y = cleanbox ( q + 1 , curstyle ) ;
    z = cleanbox ( q + 3 , 2 * ( curstyle / 4 ) + 5 ) ;
    v = newnullbox () ;
    mem [v ].hh.b0 = 1 ;
    mem [v + 1 ].cint = mem [y + 1 ].cint ;
    if ( mem [x + 1 ].cint > mem [v + 1 ].cint ) 
    mem [v + 1 ].cint = mem [x + 1 ].cint ;
    if ( mem [z + 1 ].cint > mem [v + 1 ].cint ) 
    mem [v + 1 ].cint = mem [z + 1 ].cint ;
    x = rebox ( x , mem [v + 1 ].cint ) ;
    y = rebox ( y , mem [v + 1 ].cint ) ;
    z = rebox ( z , mem [v + 1 ].cint ) ;
    mem [x + 4 ].cint = half ( delta ) ;
    mem [z + 4 ].cint = - (integer) mem [x + 4 ].cint ;
    mem [v + 3 ].cint = mem [y + 3 ].cint ;
    mem [v + 2 ].cint = mem [y + 2 ].cint ;
    curf = savef ;
    if ( mem [q + 2 ].hh .v.RH == 0 ) 
    {
      freenode ( x , 8 ) ;
      mem [v + 5 ].hh .v.RH = y ;
    } 
    else {
	
      shiftup = bigopspacing3 () - mem [x + 2 ].cint ;
      if ( shiftup < bigopspacing1 () ) 
      shiftup = bigopspacing1 () ;
      p = newkern ( shiftup ) ;
      mem [p ].hh .v.RH = y ;
      mem [x ].hh .v.RH = p ;
      p = newkern ( bigopspacing5 () ) ;
      mem [p ].hh .v.RH = x ;
      mem [v + 5 ].hh .v.RH = p ;
      mem [v + 3 ].cint = mem [v + 3 ].cint + bigopspacing5 () + mem [x + 
      3 ].cint + mem [x + 2 ].cint + shiftup ;
    } 
    if ( mem [q + 3 ].hh .v.RH == 0 ) 
    freenode ( z , 8 ) ;
    else {
	
      shiftdown = bigopspacing4 () - mem [z + 3 ].cint ;
      if ( shiftdown < bigopspacing2 () ) 
      shiftdown = bigopspacing2 () ;
      p = newkern ( shiftdown ) ;
      mem [y ].hh .v.RH = p ;
      mem [p ].hh .v.RH = z ;
      p = newkern ( bigopspacing5 () ) ;
      mem [z ].hh .v.RH = p ;
      mem [v + 2 ].cint = mem [v + 2 ].cint + bigopspacing5 () + mem [z + 
      3 ].cint + mem [z + 2 ].cint + shiftdown ;
    } 
    mem [q + 1 ].cint = v ;
  } 
  freeotassembly ( otassemblyptr ) ;
  Result = delta ;
  return Result ;
} 
void 
zmakeord ( halfword q ) 
{
  /* 20 10 */ makeord_regmem 
  integer a  ;
  halfword p, r  ;
  lab20: if ( mem [q + 3 ].hh .v.RH == 0 ) {
      
    if ( mem [q + 2 ].hh .v.RH == 0 ) {
	
      if ( mem [q + 1 ].hh .v.RH == 1 ) 
      {
	p = mem [q ].hh .v.RH ;
	if ( p != -268435455L ) {
	    
	  if ( ( mem [p ].hh.b0 >= 16 ) && ( mem [p ].hh.b0 <= 22 ) ) {
	      
	    if ( mem [p + 1 ].hh .v.RH == 1 ) {
		
	      if ( ( mem [p + 1 ].hh.b0 % 256 ) == ( mem [q + 1 ].hh.b0 % 
	      256 ) ) 
	      {
		mem [q + 1 ].hh .v.RH = 4 ;
		fetch ( q + 1 ) ;
		if ( ( ( curi .b2 ) % 4 ) == 1 ) 
		{
		  a = ligkernbase [curf ]+ curi .b3 ;
		  curc = mem [p + 1 ].hh.b1 ;
		  curi = fontinfo [a ].qqqq ;
		  if ( curi .b0 > 128 ) 
		  {
		    a = ligkernbase [curf ]+ 256 * curi .b2 + curi .b3 + 
		    32768L - 256 * ( 128 ) ;
		    curi = fontinfo [a ].qqqq ;
		  } 
		  while ( true ) {
		      
		    if ( curi .b1 == curc ) {
			
		      if ( curi .b0 <= 128 ) {
			  
			if ( curi .b2 >= 128 ) 
			{
			  p = newkern ( fontinfo [kernbase [curf ]+ 256 * 
			  curi .b2 + curi .b3 ].cint ) ;
			  mem [p ].hh .v.RH = mem [q ].hh .v.RH ;
			  mem [q ].hh .v.RH = p ;
			  return ;
			} 
			else {
			    
			  {
			    if ( interrupt != 0 ) 
			    pauseforinstructions () ;
			  } 
			  switch ( curi .b2 ) 
			  {case 1 : 
			  case 5 : 
			    mem [q + 1 ].hh.b1 = curi .b3 ;
			    break ;
			  case 2 : 
			  case 6 : 
			    mem [p + 1 ].hh.b1 = curi .b3 ;
			    break ;
			  case 3 : 
			  case 7 : 
			  case 11 : 
			    {
			      r = newnoad () ;
			      mem [r + 1 ].hh.b1 = curi .b3 ;
			      mem [r + 1 ].hh.b0 = ( mem [q + 1 ].hh.b0 % 
			      256 ) ;
			      mem [q ].hh .v.RH = r ;
			      mem [r ].hh .v.RH = p ;
			      if ( curi .b2 < 11 ) 
			      mem [r + 1 ].hh .v.RH = 1 ;
			      else mem [r + 1 ].hh .v.RH = 4 ;
			    } 
			    break ;
			    default: 
			    {
			      mem [q ].hh .v.RH = mem [p ].hh .v.RH ;
			      mem [q + 1 ].hh.b1 = curi .b3 ;
			      mem [q + 3 ]= mem [p + 3 ];
			      mem [q + 2 ]= mem [p + 2 ];
			      freenode ( p , 4 ) ;
			    } 
			    break ;
			  } 
			  if ( curi .b2 > 3 ) 
			  return ;
			  mem [q + 1 ].hh .v.RH = 1 ;
			  goto lab20 ;
			} 
		      } 
		    } 
		    if ( curi .b0 >= 128 ) 
		    return ;
		    a = a + curi .b0 + 1 ;
		    curi = fontinfo [a ].qqqq ;
		  } 
		} 
	      } 
	    } 
	  } 
	} 
      } 
    } 
  } 
} 
halfword 
zattachhkerntonewhlist ( halfword q , scaled delta ) 
{
  register halfword Result; attachhkerntonewhlist_regmem 
  halfword y, z  ;
  z = newkern ( delta ) ;
  if ( mem [q + 1 ].cint == -268435455L ) 
  mem [q + 1 ].cint = z ;
  else {
      
    y = mem [q + 1 ].cint ;
    while ( mem [y ].hh .v.RH != -268435455L ) y = mem [y ].hh .v.RH ;
    mem [y ].hh .v.RH = z ;
  } 
  Result = mem [q + 1 ].cint ;
  return Result ;
} 
void 
zmakescripts ( halfword q , scaled delta ) 
{
  makescripts_regmem 
  halfword p, x, y, z  ;
  scaled shiftup, shiftdown, clr, subkern, supkern  ;
  halfword scriptc  ;
  quarterword scriptg  ;
  internalfontnumber scriptf  ;
  quarterword supg  ;
  internalfontnumber supf  ;
  quarterword subg  ;
  internalfontnumber subf  ;
  integer t  ;
  internalfontnumber savef  ;
  halfword scripthead  ;
  halfword scriptptr  ;
  smallnumber savedmathstyle  ;
  smallnumber thismathstyle  ;
  p = mem [q + 1 ].cint ;
  scriptc = -268435455L ;
  scriptg = 0 ;
  scriptf = 0 ;
  supkern = 0 ;
  subkern = 0 ;
  if ( ( p >= himemmin ) || ( ( ( p ) != -268435455L && ( ! ( p >= himemmin ) 
  ) && ( mem [p ].hh.b0 == 8 ) && ( mem [p ].hh.b1 == 42 ) ) ) ) 
  {
    shiftup = 0 ;
    shiftdown = 0 ;
  } 
  else {
      
    z = hpack ( p , 0 , 1 ) ;
    if ( curstyle < 4 ) 
    t = 256 ;
    else t = 512 ;
    shiftup = mem [z + 3 ].cint - supdrop ( t ) ;
    shiftdown = mem [z + 2 ].cint + subdrop ( t ) ;
    freenode ( z , 8 ) ;
  } 
  if ( mem [q + 2 ].hh .v.RH == 0 ) 
  {
    scripthead = q + 3 ;
    scriptc = -268435455L ;
    scriptg = 0 ;
    scriptf = 0 ;
    thismathstyle = 2 * ( curstyle / 4 ) + 5 ;
    if ( mem [scripthead ].hh .v.RH == 3 ) 
    {
      scriptptr = mem [scripthead ].hh .v.LH ;
      scripthead = -268435455L ;
      while ( ( ( scriptptr >= memmin ) && ( scriptptr <= memend ) ) ) {
	  
	switch ( mem [scriptptr ].hh.b0 ) 
	{case 11 : 
	case 10 : 
	  ;
	  break ;
	case 14 : 
	  {
	    thismathstyle = mem [scriptptr ].hh.b1 ;
	  } 
	  break ;
	case 15 : 
	  ;
	  break ;
	case 16 : 
	case 17 : 
	case 18 : 
	case 19 : 
	case 20 : 
	case 21 : 
	case 22 : 
	  {
	    scripthead = scriptptr + 1 ;
	    scriptptr = -268435455L ;
	  } 
	  break ;
	  default: 
	  scriptptr = -268435455L ;
	  break ;
	} 
	if ( ( ( scriptptr >= memmin ) && ( scriptptr <= memend ) ) ) {
	    
	  if ( mem [scriptptr ].hh.b0 == 15 ) 
	  switch ( thismathstyle / 2 ) 
	  {case 0 : 
	    scriptptr = mem [scriptptr + 1 ].hh .v.LH ;
	    break ;
	  case 1 : 
	    scriptptr = mem [scriptptr + 1 ].hh .v.RH ;
	    break ;
	  case 2 : 
	    scriptptr = mem [scriptptr + 2 ].hh .v.LH ;
	    break ;
	  case 3 : 
	    scriptptr = mem [scriptptr + 2 ].hh .v.RH ;
	    break ;
	  } 
	  else scriptptr = mem [scriptptr ].hh .v.RH ;
	} 
      } 
    } 
    if ( ( ( scripthead >= memmin ) && ( scripthead <= memend ) ) && mem [
    scripthead ].hh .v.RH == 1 ) 
    {
      savef = curf ;
      savedmathstyle = curstyle ;
      curstyle = thismathstyle ;
      {
	if ( curstyle < 4 ) 
	cursize = 0 ;
	else cursize = 256 * ( ( curstyle - 2 ) / 2 ) ;
	curmu = xovern ( mathquad ( cursize ) , 18 ) ;
      } 
      fetch ( scripthead ) ;
      if ( ( ( fontarea [curf ]== 65534L ) && ( isOpenTypeMathFont ( 
      fontlayoutengine [curf ]) ) ) ) 
      {
	scriptc = newnativecharacter ( curf , curc ) ;
	scriptg = getnativeglyph ( scriptc , 0 ) ;
	scriptf = curf ;
      } 
      curf = savef ;
      curstyle = savedmathstyle ;
      {
	if ( curstyle < 4 ) 
	cursize = 0 ;
	else cursize = 256 * ( ( curstyle - 2 ) / 2 ) ;
	curmu = xovern ( mathquad ( cursize ) , 18 ) ;
      } 
    } 
    subg = scriptg ;
    subf = scriptf ;
    savef = curf ;
    x = cleanbox ( q + 3 , 2 * ( curstyle / 4 ) + 5 ) ;
    curf = savef ;
    mem [x + 1 ].cint = mem [x + 1 ].cint + eqtb [9006732L ].cint ;
    if ( shiftdown < sub1 ( cursize ) ) 
    shiftdown = sub1 ( cursize ) ;
    if ( ( ( fontarea [curf ]== 65534L ) && ( isOpenTypeMathFont ( 
    fontlayoutengine [curf ]) ) ) ) 
    clr = mem [x + 3 ].cint - getotmathconstant ( curf , 9 ) ;
    else clr = mem [x + 3 ].cint - ( abs ( mathxheight ( cursize ) * 4 ) / 5 
    ) ;
    if ( shiftdown < clr ) 
    shiftdown = clr ;
    mem [x + 4 ].cint = shiftdown ;
    if ( ( ( fontarea [curf ]== 65534L ) && ( isOpenTypeMathFont ( 
    fontlayoutengine [curf ]) ) ) ) 
    {
      if ( ( ( ( p ) != -268435455L && ( ! ( p >= himemmin ) ) && ( mem [p ]
      .hh.b0 == 8 ) && ( mem [p ].hh.b1 == 42 ) ) ) ) 
      {
	subkern = getotmathkern ( mem [p + 4 ].qqqq .b1 , mem [p + 4 ]
	.qqqq .b2 , subf , subg , 1 , shiftdown ) ;
	if ( subkern != 0 ) 
	p = attachhkerntonewhlist ( q , subkern ) ;
      } 
    } 
  } 
  else {
      
    {
      scripthead = q + 2 ;
      scriptc = -268435455L ;
      scriptg = 0 ;
      scriptf = 0 ;
      thismathstyle = 2 * ( curstyle / 4 ) + 5 ;
      if ( mem [scripthead ].hh .v.RH == 3 ) 
      {
	scriptptr = mem [scripthead ].hh .v.LH ;
	scripthead = -268435455L ;
	while ( ( ( scriptptr >= memmin ) && ( scriptptr <= memend ) ) ) {
	    
	  switch ( mem [scriptptr ].hh.b0 ) 
	  {case 11 : 
	  case 10 : 
	    ;
	    break ;
	  case 14 : 
	    {
	      thismathstyle = mem [scriptptr ].hh.b1 ;
	    } 
	    break ;
	  case 15 : 
	    ;
	    break ;
	  case 16 : 
	  case 17 : 
	  case 18 : 
	  case 19 : 
	  case 20 : 
	  case 21 : 
	  case 22 : 
	    {
	      scripthead = scriptptr + 1 ;
	      scriptptr = -268435455L ;
	    } 
	    break ;
	    default: 
	    scriptptr = -268435455L ;
	    break ;
	  } 
	  if ( ( ( scriptptr >= memmin ) && ( scriptptr <= memend ) ) ) {
	      
	    if ( mem [scriptptr ].hh.b0 == 15 ) 
	    switch ( thismathstyle / 2 ) 
	    {case 0 : 
	      scriptptr = mem [scriptptr + 1 ].hh .v.LH ;
	      break ;
	    case 1 : 
	      scriptptr = mem [scriptptr + 1 ].hh .v.RH ;
	      break ;
	    case 2 : 
	      scriptptr = mem [scriptptr + 2 ].hh .v.LH ;
	      break ;
	    case 3 : 
	      scriptptr = mem [scriptptr + 2 ].hh .v.RH ;
	      break ;
	    } 
	    else scriptptr = mem [scriptptr ].hh .v.RH ;
	  } 
	} 
      } 
      if ( ( ( scripthead >= memmin ) && ( scripthead <= memend ) ) && mem [
      scripthead ].hh .v.RH == 1 ) 
      {
	savef = curf ;
	savedmathstyle = curstyle ;
	curstyle = thismathstyle ;
	{
	  if ( curstyle < 4 ) 
	  cursize = 0 ;
	  else cursize = 256 * ( ( curstyle - 2 ) / 2 ) ;
	  curmu = xovern ( mathquad ( cursize ) , 18 ) ;
	} 
	fetch ( scripthead ) ;
	if ( ( ( fontarea [curf ]== 65534L ) && ( isOpenTypeMathFont ( 
	fontlayoutengine [curf ]) ) ) ) 
	{
	  scriptc = newnativecharacter ( curf , curc ) ;
	  scriptg = getnativeglyph ( scriptc , 0 ) ;
	  scriptf = curf ;
	} 
	curf = savef ;
	curstyle = savedmathstyle ;
	{
	  if ( curstyle < 4 ) 
	  cursize = 0 ;
	  else cursize = 256 * ( ( curstyle - 2 ) / 2 ) ;
	  curmu = xovern ( mathquad ( cursize ) , 18 ) ;
	} 
      } 
      supg = scriptg ;
      supf = scriptf ;
      savef = curf ;
      x = cleanbox ( q + 2 , 2 * ( curstyle / 4 ) + 4 + ( curstyle % 2 ) ) ;
      curf = savef ;
      mem [x + 1 ].cint = mem [x + 1 ].cint + eqtb [9006732L ].cint ;
      if ( odd ( curstyle ) ) 
      clr = sup3 ( cursize ) ;
      else if ( curstyle < 2 ) 
      clr = sup1 ( cursize ) ;
      else clr = sup2 ( cursize ) ;
      if ( shiftup < clr ) 
      shiftup = clr ;
      if ( ( ( fontarea [curf ]== 65534L ) && ( isOpenTypeMathFont ( 
      fontlayoutengine [curf ]) ) ) ) 
      clr = mem [x + 2 ].cint + getotmathconstant ( curf , 13 ) ;
      else clr = mem [x + 2 ].cint + ( abs ( mathxheight ( cursize ) ) / 4 ) 
      ;
      if ( shiftup < clr ) 
      shiftup = clr ;
      if ( ( ( fontarea [curf ]== 65534L ) && ( isOpenTypeMathFont ( 
      fontlayoutengine [curf ]) ) ) ) 
      {
	if ( mem [q + 3 ].hh .v.RH == 0 ) {
	    
	  if ( ( ( ( p ) != -268435455L && ( ! ( p >= himemmin ) ) && ( mem [
	  p ].hh.b0 == 8 ) && ( mem [p ].hh.b1 == 42 ) ) ) ) 
	  {
	    supkern = getotmathkern ( mem [p + 4 ].qqqq .b1 , mem [p + 4 ]
	    .qqqq .b2 , supf , supg , 0 , shiftup ) ;
	    if ( supkern != 0 ) 
	    p = attachhkerntonewhlist ( q , supkern ) ;
	  } 
	} 
      } 
    } 
    if ( mem [q + 3 ].hh .v.RH == 0 ) 
    mem [x + 4 ].cint = - (integer) shiftup ;
    else {
	
      savef = curf ;
      scripthead = q + 3 ;
      scriptc = -268435455L ;
      scriptg = 0 ;
      scriptf = 0 ;
      thismathstyle = 2 * ( curstyle / 4 ) + 5 ;
      if ( mem [scripthead ].hh .v.RH == 3 ) 
      {
	scriptptr = mem [scripthead ].hh .v.LH ;
	scripthead = -268435455L ;
	while ( ( ( scriptptr >= memmin ) && ( scriptptr <= memend ) ) ) {
	    
	  switch ( mem [scriptptr ].hh.b0 ) 
	  {case 11 : 
	  case 10 : 
	    ;
	    break ;
	  case 14 : 
	    {
	      thismathstyle = mem [scriptptr ].hh.b1 ;
	    } 
	    break ;
	  case 15 : 
	    ;
	    break ;
	  case 16 : 
	  case 17 : 
	  case 18 : 
	  case 19 : 
	  case 20 : 
	  case 21 : 
	  case 22 : 
	    {
	      scripthead = scriptptr + 1 ;
	      scriptptr = -268435455L ;
	    } 
	    break ;
	    default: 
	    scriptptr = -268435455L ;
	    break ;
	  } 
	  if ( ( ( scriptptr >= memmin ) && ( scriptptr <= memend ) ) ) {
	      
	    if ( mem [scriptptr ].hh.b0 == 15 ) 
	    switch ( thismathstyle / 2 ) 
	    {case 0 : 
	      scriptptr = mem [scriptptr + 1 ].hh .v.LH ;
	      break ;
	    case 1 : 
	      scriptptr = mem [scriptptr + 1 ].hh .v.RH ;
	      break ;
	    case 2 : 
	      scriptptr = mem [scriptptr + 2 ].hh .v.LH ;
	      break ;
	    case 3 : 
	      scriptptr = mem [scriptptr + 2 ].hh .v.RH ;
	      break ;
	    } 
	    else scriptptr = mem [scriptptr ].hh .v.RH ;
	  } 
	} 
      } 
      if ( ( ( scripthead >= memmin ) && ( scripthead <= memend ) ) && mem [
      scripthead ].hh .v.RH == 1 ) 
      {
	savef = curf ;
	savedmathstyle = curstyle ;
	curstyle = thismathstyle ;
	{
	  if ( curstyle < 4 ) 
	  cursize = 0 ;
	  else cursize = 256 * ( ( curstyle - 2 ) / 2 ) ;
	  curmu = xovern ( mathquad ( cursize ) , 18 ) ;
	} 
	fetch ( scripthead ) ;
	if ( ( ( fontarea [curf ]== 65534L ) && ( isOpenTypeMathFont ( 
	fontlayoutengine [curf ]) ) ) ) 
	{
	  scriptc = newnativecharacter ( curf , curc ) ;
	  scriptg = getnativeglyph ( scriptc , 0 ) ;
	  scriptf = curf ;
	} 
	curf = savef ;
	curstyle = savedmathstyle ;
	{
	  if ( curstyle < 4 ) 
	  cursize = 0 ;
	  else cursize = 256 * ( ( curstyle - 2 ) / 2 ) ;
	  curmu = xovern ( mathquad ( cursize ) , 18 ) ;
	} 
      } 
      subg = scriptg ;
      subf = scriptf ;
      y = cleanbox ( q + 3 , 2 * ( curstyle / 4 ) + 5 ) ;
      curf = savef ;
      mem [y + 1 ].cint = mem [y + 1 ].cint + eqtb [9006732L ].cint ;
      if ( shiftdown < sub2 ( cursize ) ) 
      shiftdown = sub2 ( cursize ) ;
      if ( ( ( fontarea [curf ]== 65534L ) && ( isOpenTypeMathFont ( 
      fontlayoutengine [curf ]) ) ) ) 
      clr = getotmathconstant ( curf , 15 ) - ( ( shiftup - mem [x + 2 ]
      .cint ) - ( mem [y + 3 ].cint - shiftdown ) ) ;
      else clr = 4 * defaultrulethickness () - ( ( shiftup - mem [x + 2 ]
      .cint ) - ( mem [y + 3 ].cint - shiftdown ) ) ;
      if ( clr > 0 ) 
      {
	shiftdown = shiftdown + clr ;
	if ( ( ( fontarea [curf ]== 65534L ) && ( isOpenTypeMathFont ( 
	fontlayoutengine [curf ]) ) ) ) 
	clr = getotmathconstant ( curf , 16 ) - ( shiftup - mem [x + 2 ]
	.cint ) ;
	else clr = ( abs ( mathxheight ( cursize ) * 4 ) / 5 ) - ( shiftup - 
	mem [x + 2 ].cint ) ;
	if ( clr > 0 ) 
	{
	  shiftup = shiftup + clr ;
	  shiftdown = shiftdown - clr ;
	} 
      } 
      if ( ( ( fontarea [curf ]== 65534L ) && ( isOpenTypeMathFont ( 
      fontlayoutengine [curf ]) ) ) ) 
      {
	{
	  if ( ( ( ( p ) != -268435455L && ( ! ( p >= himemmin ) ) && ( mem [
	  p ].hh.b0 == 8 ) && ( mem [p ].hh.b1 == 42 ) ) ) ) 
	  {
	    subkern = getotmathkern ( mem [p + 4 ].qqqq .b1 , mem [p + 4 ]
	    .qqqq .b2 , subf , subg , 1 , shiftdown ) ;
	    if ( subkern != 0 ) 
	    p = attachhkerntonewhlist ( q , subkern ) ;
	  } 
	} 
	{
	  if ( mem [q + 3 ].hh .v.RH == 0 ) {
	      
	    if ( ( ( ( p ) != -268435455L && ( ! ( p >= himemmin ) ) && ( mem 
	    [p ].hh.b0 == 8 ) && ( mem [p ].hh.b1 == 42 ) ) ) ) 
	    {
	      supkern = getotmathkern ( mem [p + 4 ].qqqq .b1 , mem [p + 4 
	      ].qqqq .b2 , supf , supg , 0 , shiftup ) ;
	      if ( supkern != 0 ) 
	      p = attachhkerntonewhlist ( q , supkern ) ;
	    } 
	  } 
	} 
      } 
      else {
	  
	supkern = 0 ;
	subkern = 0 ;
      } 
      mem [x + 4 ].cint = supkern + delta - subkern ;
      p = newkern ( ( shiftup - mem [x + 2 ].cint ) - ( mem [y + 3 ].cint 
      - shiftdown ) ) ;
      mem [x ].hh .v.RH = p ;
      mem [p ].hh .v.RH = y ;
      x = vpackage ( x , 0 , 1 , 1073741823L ) ;
      mem [x + 4 ].cint = shiftdown ;
    } 
  } 
  if ( mem [q + 1 ].cint == -268435455L ) 
  mem [q + 1 ].cint = x ;
  else {
      
    p = mem [q + 1 ].cint ;
    while ( mem [p ].hh .v.RH != -268435455L ) p = mem [p ].hh .v.RH ;
    mem [p ].hh .v.RH = x ;
  } 
} 
smallnumber 
zmakeleftright ( halfword q , smallnumber style , scaled maxd , scaled maxh ) 
{
  register smallnumber Result; makeleftright_regmem 
  scaled delta, delta1, delta2  ;
  curstyle = style ;
  {
    if ( curstyle < 4 ) 
    cursize = 0 ;
    else cursize = 256 * ( ( curstyle - 2 ) / 2 ) ;
    curmu = xovern ( mathquad ( cursize ) , 18 ) ;
  } 
  delta2 = maxd + axisheight ( cursize ) ;
  delta1 = maxh + maxd - delta2 ;
  if ( delta2 > delta1 ) 
  delta1 = delta2 ;
  delta = ( delta1 / 500 ) * eqtb [7892282L ].cint ;
  delta2 = delta1 + delta1 - eqtb [9006730L ].cint ;
  if ( delta < delta2 ) 
  delta = delta2 ;
  mem [q + 1 ].cint = vardelimiter ( q + 1 , cursize , delta ) ;
  Result = mem [q ].hh.b0 - ( 10 ) ;
  return Result ;
} 
void 
mlisttohlist ( void ) 
{
  /* 21 82 80 81 83 30 */ mlisttohlist_regmem 
  halfword mlist  ;
  boolean penalties  ;
  smallnumber style  ;
  smallnumber savestyle  ;
  halfword q  ;
  halfword r  ;
  smallnumber rtype  ;
  smallnumber t  ;
  halfword p, x, y, z  ;
  integer pen  ;
  smallnumber s  ;
  scaled maxh, maxd  ;
  scaled delta  ;
  mlist = curmlist ;
  penalties = mlistpenalties ;
  style = curstyle ;
  q = mlist ;
  r = -268435455L ;
  rtype = 17 ;
  maxh = 0 ;
  maxd = 0 ;
  {
    if ( curstyle < 4 ) 
    cursize = 0 ;
    else cursize = 256 * ( ( curstyle - 2 ) / 2 ) ;
    curmu = xovern ( mathquad ( cursize ) , 18 ) ;
  } 
  while ( q != -268435455L ) {
      
    lab21: delta = 0 ;
    switch ( mem [q ].hh.b0 ) 
    {case 18 : 
      switch ( rtype ) 
      {case 18 : 
      case 17 : 
      case 19 : 
      case 20 : 
      case 22 : 
      case 30 : 
	{
	  mem [q ].hh.b0 = 16 ;
	  goto lab21 ;
	} 
	break ;
	default: 
	;
	break ;
      } 
      break ;
    case 19 : 
    case 21 : 
    case 22 : 
    case 31 : 
      {
	if ( rtype == 18 ) 
	mem [r ].hh.b0 = 16 ;
	if ( mem [q ].hh.b0 == 31 ) 
	goto lab80 ;
      } 
      break ;
    case 30 : 
      goto lab80 ;
      break ;
    case 25 : 
      {
	makefraction ( q ) ;
	goto lab82 ;
      } 
      break ;
    case 17 : 
      {
	delta = makeop ( q ) ;
	if ( mem [q ].hh.b1 == 1 ) 
	goto lab82 ;
      } 
      break ;
    case 16 : 
      makeord ( q ) ;
      break ;
    case 20 : 
    case 23 : 
      ;
      break ;
    case 24 : 
      makeradical ( q ) ;
      break ;
    case 27 : 
      makeover ( q ) ;
      break ;
    case 26 : 
      makeunder ( q ) ;
      break ;
    case 28 : 
      makemathaccent ( q ) ;
      break ;
    case 29 : 
      makevcenter ( q ) ;
      break ;
    case 14 : 
      {
	curstyle = mem [q ].hh.b1 ;
	{
	  if ( curstyle < 4 ) 
	  cursize = 0 ;
	  else cursize = 256 * ( ( curstyle - 2 ) / 2 ) ;
	  curmu = xovern ( mathquad ( cursize ) , 18 ) ;
	} 
	goto lab81 ;
      } 
      break ;
    case 15 : 
      {
	switch ( curstyle / 2 ) 
	{case 0 : 
	  {
	    p = mem [q + 1 ].hh .v.LH ;
	    mem [q + 1 ].hh .v.LH = -268435455L ;
	  } 
	  break ;
	case 1 : 
	  {
	    p = mem [q + 1 ].hh .v.RH ;
	    mem [q + 1 ].hh .v.RH = -268435455L ;
	  } 
	  break ;
	case 2 : 
	  {
	    p = mem [q + 2 ].hh .v.LH ;
	    mem [q + 2 ].hh .v.LH = -268435455L ;
	  } 
	  break ;
	case 3 : 
	  {
	    p = mem [q + 2 ].hh .v.RH ;
	    mem [q + 2 ].hh .v.RH = -268435455L ;
	  } 
	  break ;
	} 
	flushnodelist ( mem [q + 1 ].hh .v.LH ) ;
	flushnodelist ( mem [q + 1 ].hh .v.RH ) ;
	flushnodelist ( mem [q + 2 ].hh .v.LH ) ;
	flushnodelist ( mem [q + 2 ].hh .v.RH ) ;
	mem [q ].hh.b0 = 14 ;
	mem [q ].hh.b1 = curstyle ;
	mem [q + 1 ].cint = 0 ;
	mem [q + 2 ].cint = 0 ;
	if ( p != -268435455L ) 
	{
	  z = mem [q ].hh .v.RH ;
	  mem [q ].hh .v.RH = p ;
	  while ( mem [p ].hh .v.RH != -268435455L ) p = mem [p ].hh .v.RH 
	  ;
	  mem [p ].hh .v.RH = z ;
	} 
	goto lab81 ;
      } 
      break ;
    case 3 : 
    case 4 : 
    case 5 : 
    case 8 : 
    case 12 : 
    case 7 : 
      goto lab81 ;
      break ;
    case 2 : 
      {
	if ( mem [q + 3 ].cint > maxh ) 
	maxh = mem [q + 3 ].cint ;
	if ( mem [q + 2 ].cint > maxd ) 
	maxd = mem [q + 2 ].cint ;
	goto lab81 ;
      } 
      break ;
    case 10 : 
      {
	if ( mem [q ].hh.b1 == 99 ) 
	{
	  x = mem [q + 1 ].hh .v.LH ;
	  y = mathglue ( x , curmu ) ;
	  deleteglueref ( x ) ;
	  mem [q + 1 ].hh .v.LH = y ;
	  mem [q ].hh.b1 = 0 ;
	} 
	else if ( ( cursize != 0 ) && ( mem [q ].hh.b1 == 98 ) ) 
	{
	  p = mem [q ].hh .v.RH ;
	  if ( p != -268435455L ) {
	      
	    if ( ( mem [p ].hh.b0 == 10 ) || ( mem [p ].hh.b0 == 11 ) ) 
	    {
	      mem [q ].hh .v.RH = mem [p ].hh .v.RH ;
	      mem [p ].hh .v.RH = -268435455L ;
	      flushnodelist ( p ) ;
	    } 
	  } 
	} 
	goto lab81 ;
      } 
      break ;
    case 11 : 
      {
	mathkern ( q , curmu ) ;
	goto lab81 ;
      } 
      break ;
      default: 
      confusion ( 66318L ) ;
      break ;
    } 
    switch ( mem [q + 1 ].hh .v.RH ) 
    {case 1 : 
    case 4 : 
      {
	fetch ( q + 1 ) ;
	if ( ( ( fontarea [curf ]== 65535L ) || ( fontarea [curf ]== 
	65534L ) ) ) 
	{
	  z = newnativecharacter ( curf , curc ) ;
	  p = getnode ( 5 ) ;
	  mem [p ].hh.b0 = 8 ;
	  mem [p ].hh.b1 = 42 ;
	  mem [p + 4 ].qqqq .b1 = curf ;
	  mem [p + 4 ].qqqq .b2 = getnativeglyph ( z , 0 ) ;
	  setnativeglyphmetrics ( p , 1 ) ;
	  freenode ( z , mem [z + 4 ].qqqq .b0 ) ;
	  delta = getotmathitalcorr ( curf , mem [p + 4 ].qqqq .b2 ) ;
	  if ( ( mem [q + 1 ].hh .v.RH == 4 ) && ( ! ( ( fontarea [curf ]
	  == 65534L ) && ( isOpenTypeMathFont ( fontlayoutengine [curf ]) ) 
	  ) != 0 ) ) 
	  delta = 0 ;
	  if ( ( mem [q + 3 ].hh .v.RH == 0 ) && ( delta != 0 ) ) 
	  {
	    mem [p ].hh .v.RH = newkern ( delta ) ;
	    delta = 0 ;
	  } 
	} 
	else if ( ( curi .b0 > 0 ) ) 
	{
	  delta = fontinfo [italicbase [curf ]+ ( curi .b2 ) / 4 ].cint ;
	  p = newcharacter ( curf , curc ) ;
	  if ( ( mem [q + 1 ].hh .v.RH == 4 ) && ( fontinfo [2 + parambase 
	  [curf ]].cint != 0 ) ) 
	  delta = 0 ;
	  if ( ( mem [q + 3 ].hh .v.RH == 0 ) && ( delta != 0 ) ) 
	  {
	    mem [p ].hh .v.RH = newkern ( delta ) ;
	    delta = 0 ;
	  } 
	} 
	else p = -268435455L ;
      } 
      break ;
    case 0 : 
      p = -268435455L ;
      break ;
    case 2 : 
      p = mem [q + 1 ].hh .v.LH ;
      break ;
    case 3 : 
      {
	curmlist = mem [q + 1 ].hh .v.LH ;
	savestyle = curstyle ;
	mlistpenalties = false ;
	mlisttohlist () ;
	curstyle = savestyle ;
	{
	  if ( curstyle < 4 ) 
	  cursize = 0 ;
	  else cursize = 256 * ( ( curstyle - 2 ) / 2 ) ;
	  curmu = xovern ( mathquad ( cursize ) , 18 ) ;
	} 
	p = hpack ( mem [memtop - 3 ].hh .v.RH , 0 , 1 ) ;
      } 
      break ;
      default: 
      confusion ( 66319L ) ;
      break ;
    } 
    mem [q + 1 ].cint = p ;
    if ( ( mem [q + 3 ].hh .v.RH == 0 ) && ( mem [q + 2 ].hh .v.RH == 0 ) 
    ) 
    goto lab82 ;
    makescripts ( q , delta ) ;
    lab82: z = hpack ( mem [q + 1 ].cint , 0 , 1 ) ;
    if ( mem [z + 3 ].cint > maxh ) 
    maxh = mem [z + 3 ].cint ;
    if ( mem [z + 2 ].cint > maxd ) 
    maxd = mem [z + 2 ].cint ;
    freenode ( z , 8 ) ;
    lab80: r = q ;
    rtype = mem [r ].hh.b0 ;
    if ( rtype == 31 ) 
    {
      rtype = 30 ;
      curstyle = style ;
      {
	if ( curstyle < 4 ) 
	cursize = 0 ;
	else cursize = 256 * ( ( curstyle - 2 ) / 2 ) ;
	curmu = xovern ( mathquad ( cursize ) , 18 ) ;
      } 
    } 
    lab81: q = mem [q ].hh .v.RH ;
  } 
  if ( rtype == 18 ) 
  mem [r ].hh.b0 = 16 ;
  p = memtop - 3 ;
  mem [p ].hh .v.RH = -268435455L ;
  q = mlist ;
  rtype = 0 ;
  curstyle = style ;
  {
    if ( curstyle < 4 ) 
    cursize = 0 ;
    else cursize = 256 * ( ( curstyle - 2 ) / 2 ) ;
    curmu = xovern ( mathquad ( cursize ) , 18 ) ;
  } 
  while ( q != -268435455L ) {
      
    t = 16 ;
    s = 4 ;
    pen = 10000 ;
    switch ( mem [q ].hh.b0 ) 
    {case 17 : 
    case 20 : 
    case 21 : 
    case 22 : 
    case 23 : 
      t = mem [q ].hh.b0 ;
      break ;
    case 18 : 
      {
	t = 18 ;
	pen = eqtb [7892273L ].cint ;
      } 
      break ;
    case 19 : 
      {
	t = 19 ;
	pen = eqtb [7892274L ].cint ;
      } 
      break ;
    case 16 : 
    case 29 : 
    case 27 : 
    case 26 : 
      ;
      break ;
    case 24 : 
      s = 5 ;
      break ;
    case 28 : 
      s = 5 ;
      break ;
    case 25 : 
      s = 6 ;
      break ;
    case 30 : 
    case 31 : 
      t = makeleftright ( q , style , maxd , maxh ) ;
      break ;
    case 14 : 
      {
	curstyle = mem [q ].hh.b1 ;
	s = 3 ;
	{
	  if ( curstyle < 4 ) 
	  cursize = 0 ;
	  else cursize = 256 * ( ( curstyle - 2 ) / 2 ) ;
	  curmu = xovern ( mathquad ( cursize ) , 18 ) ;
	} 
	goto lab83 ;
      } 
      break ;
    case 8 : 
    case 12 : 
    case 2 : 
    case 7 : 
    case 5 : 
    case 3 : 
    case 4 : 
    case 10 : 
    case 11 : 
      {
	mem [p ].hh .v.RH = q ;
	p = q ;
	q = mem [q ].hh .v.RH ;
	mem [p ].hh .v.RH = -268435455L ;
	goto lab30 ;
      } 
      break ;
      default: 
      confusion ( 66320L ) ;
      break ;
    } 
    if ( rtype > 0 ) 
    {
      switch ( strpool [rtype * 8 + t + magicoffset ]) 
      {case 48 : 
	x = 0 ;
	break ;
      case 49 : 
	if ( curstyle < 4 ) 
	x = 16 ;
	else x = 0 ;
	break ;
      case 50 : 
	x = 16 ;
	break ;
      case 51 : 
	if ( curstyle < 4 ) 
	x = 17 ;
	else x = 0 ;
	break ;
      case 52 : 
	if ( curstyle < 4 ) 
	x = 18 ;
	else x = 0 ;
	break ;
	default: 
	confusion ( 66322L ) ;
	break ;
      } 
      if ( x != 0 ) 
      {
	y = mathglue ( eqtb [1205764L + x ].hh .v.RH , curmu ) ;
	z = newglue ( y ) ;
	mem [y ].hh .v.RH = -268435455L ;
	mem [p ].hh .v.RH = z ;
	p = z ;
	mem [z ].hh.b1 = x + 1 ;
      } 
    } 
    if ( mem [q + 1 ].cint != -268435455L ) 
    {
      mem [p ].hh .v.RH = mem [q + 1 ].cint ;
      do {
	  p = mem [p ].hh .v.RH ;
      } while ( ! ( mem [p ].hh .v.RH == -268435455L ) ) ;
    } 
    if ( penalties ) {
	
      if ( mem [q ].hh .v.RH != -268435455L ) {
	  
	if ( pen < 10000 ) 
	{
	  rtype = mem [mem [q ].hh .v.RH ].hh.b0 ;
	  if ( rtype != 12 ) {
	      
	    if ( rtype != 19 ) 
	    {
	      z = newpenalty ( pen ) ;
	      mem [p ].hh .v.RH = z ;
	      p = z ;
	    } 
	  } 
	} 
      } 
    } 
    if ( mem [q ].hh.b0 == 31 ) 
    t = 20 ;
    rtype = t ;
    lab83: r = q ;
    q = mem [q ].hh .v.RH ;
    freenode ( r , s ) ;
    lab30: ;
  } 
} 
void 
pushalignment ( void ) 
{
  pushalignment_regmem 
  halfword p  ;
  p = getnode ( 6 ) ;
  mem [p ].hh .v.RH = alignptr ;
  mem [p ].hh .v.LH = curalign ;
  mem [p + 1 ].hh .v.LH = mem [memtop - 8 ].hh .v.RH ;
  mem [p + 1 ].hh .v.RH = curspan ;
  mem [p + 2 ].cint = curloop ;
  mem [p + 3 ].cint = alignstate ;
  mem [p + 4 ].hh .v.LH = curhead ;
  mem [p + 4 ].hh .v.RH = curtail ;
  mem [p + 5 ].hh .v.LH = curprehead ;
  mem [p + 5 ].hh .v.RH = curpretail ;
  alignptr = p ;
  curhead = getavail () ;
  curprehead = getavail () ;
} 
void 
popalignment ( void ) 
{
  popalignment_regmem 
  halfword p  ;
  {
    mem [curhead ].hh .v.RH = avail ;
    avail = curhead ;
	;
#ifdef STAT
    decr ( dynused ) ;
#endif /* STAT */
  } 
  {
    mem [curprehead ].hh .v.RH = avail ;
    avail = curprehead ;
	;
#ifdef STAT
    decr ( dynused ) ;
#endif /* STAT */
  } 
  p = alignptr ;
  curtail = mem [p + 4 ].hh .v.RH ;
  curhead = mem [p + 4 ].hh .v.LH ;
  curpretail = mem [p + 5 ].hh .v.RH ;
  curprehead = mem [p + 5 ].hh .v.LH ;
  alignstate = mem [p + 3 ].cint ;
  curloop = mem [p + 2 ].cint ;
  curspan = mem [p + 1 ].hh .v.RH ;
  mem [memtop - 8 ].hh .v.RH = mem [p + 1 ].hh .v.LH ;
  curalign = mem [p ].hh .v.LH ;
  alignptr = mem [p ].hh .v.RH ;
  freenode ( p , 6 ) ;
} 
void 
getpreambletoken ( void ) 
{
  /* 20 */ getpreambletoken_regmem 
  lab20: gettoken () ;
  while ( ( curchr == 1114113L ) && ( curcmd == 4 ) ) {
      
    gettoken () ;
    if ( curcmd > 103 ) 
    {
      expand () ;
      gettoken () ;
    } 
  } 
  if ( curcmd == 9 ) 
  fatalerror ( 65925L ) ;
  if ( ( curcmd == 76 ) && ( curchr == 1205775L ) ) 
  {
    scanoptionalequals () ;
    scanglue ( 2 ) ;
    if ( eqtb [7892307L ].cint > 0 ) 
    geqdefine ( 1205775L , 120 , curval ) ;
    else eqdefine ( 1205775L , 120 , curval ) ;
    goto lab20 ;
  } 
} 
void 
initalign ( void ) 
{
  /* 30 31 32 22 */ initalign_regmem 
  halfword savecsptr  ;
  halfword p  ;
  savecsptr = curcs ;
  pushalignment () ;
  alignstate = -1000000L ;
  if ( ( curlist .modefield == 209 ) && ( ( curlist .tailfield != curlist 
  .headfield ) || ( curlist .auxfield .cint != -268435455L ) ) ) 
  {
    {
      if ( interaction == 3 ) 
      ;
      if ( filelineerrorstylep ) 
      printfileline () ;
      else printnl ( 65544L ) ;
      print ( 66030L ) ;
    } 
    printesc ( 65836L ) ;
    print ( 66323L ) ;
    {
      helpptr = 3 ;
      helpline [2 ]= 66324L ;
      helpline [1 ]= 66325L ;
      helpline [0 ]= 66326L ;
    } 
    error () ;
    flushmath () ;
  } 
  pushnest () ;
  if ( curlist .modefield == 209 ) 
  {
    curlist .modefield = -1 ;
    curlist .auxfield .cint = nest [nestptr - 2 ].auxfield .cint ;
  } 
  else if ( curlist .modefield > 0 ) 
  curlist .modefield = - (integer) curlist .modefield ;
  scanspec ( 6 , false ) ;
  mem [memtop - 8 ].hh .v.RH = -268435455L ;
  curalign = memtop - 8 ;
  curloop = -268435455L ;
  scannerstatus = 4 ;
  warningindex = savecsptr ;
  alignstate = -1000000L ;
  while ( true ) {
      
    mem [curalign ].hh .v.RH = newparamglue ( 11 ) ;
    curalign = mem [curalign ].hh .v.RH ;
    if ( curcmd == 5 ) 
    goto lab30 ;
    p = memtop - 4 ;
    mem [p ].hh .v.RH = -268435455L ;
    while ( true ) {
	
      getpreambletoken () ;
      if ( curcmd == 6 ) 
      goto lab31 ;
      if ( ( curcmd <= 5 ) && ( curcmd >= 4 ) && ( alignstate == -1000000L ) ) 
      {
	if ( ( p == memtop - 4 ) && ( curloop == -268435455L ) && ( curcmd == 
	4 ) ) 
	curloop = curalign ;
	else {
	    
	  {
	    if ( interaction == 3 ) 
	    ;
	    if ( filelineerrorstylep ) 
	    printfileline () ;
	    else printnl ( 65544L ) ;
	    print ( 66332L ) ;
	  } 
	  {
	    helpptr = 3 ;
	    helpline [2 ]= 66333L ;
	    helpline [1 ]= 66334L ;
	    helpline [0 ]= 66335L ;
	  } 
	  backerror () ;
	  goto lab31 ;
	} 
      } 
      else if ( ( curcmd != 10 ) || ( p != memtop - 4 ) ) 
      {
	mem [p ].hh .v.RH = getavail () ;
	p = mem [p ].hh .v.RH ;
	mem [p ].hh .v.LH = curtok ;
      } 
    } 
    lab31: ;
    mem [curalign ].hh .v.RH = newnullbox () ;
    curalign = mem [curalign ].hh .v.RH ;
    mem [curalign ].hh .v.LH = memtop - 9 ;
    mem [curalign + 1 ].cint = -1073741824L ;
    mem [curalign + 3 ].cint = mem [memtop - 4 ].hh .v.RH ;
    p = memtop - 4 ;
    mem [p ].hh .v.RH = -268435455L ;
    while ( true ) {
	
      lab22: getpreambletoken () ;
      if ( ( curcmd <= 5 ) && ( curcmd >= 4 ) && ( alignstate == -1000000L ) ) 
      goto lab32 ;
      if ( curcmd == 6 ) 
      {
	{
	  if ( interaction == 3 ) 
	  ;
	  if ( filelineerrorstylep ) 
	  printfileline () ;
	  else printnl ( 65544L ) ;
	  print ( 66336L ) ;
	} 
	{
	  helpptr = 3 ;
	  helpline [2 ]= 66333L ;
	  helpline [1 ]= 66334L ;
	  helpline [0 ]= 66337L ;
	} 
	error () ;
	goto lab22 ;
      } 
      mem [p ].hh .v.RH = getavail () ;
      p = mem [p ].hh .v.RH ;
      mem [p ].hh .v.LH = curtok ;
    } 
    lab32: mem [p ].hh .v.RH = getavail () ;
    p = mem [p ].hh .v.RH ;
    mem [p ].hh .v.LH = 34749086L ;
    mem [curalign + 2 ].cint = mem [memtop - 4 ].hh .v.RH ;
  } 
  lab30: scannerstatus = 0 ;
  newsavelevel ( 6 ) ;
  if ( eqtb [1206303L ].hh .v.RH != -268435455L ) 
  begintokenlist ( eqtb [1206303L ].hh .v.RH , 14 ) ;
  alignpeek () ;
} 
void 
zinitspan ( halfword p ) 
{
  initspan_regmem 
  pushnest () ;
  if ( curlist .modefield == -105 ) 
  curlist .auxfield .hh .v.LH = 1000 ;
  else {
      
    curlist .auxfield .cint = -65536000L ;
    normalparagraph () ;
  } 
  curspan = p ;
} 
void 
initrow ( void ) 
{
  initrow_regmem 
  pushnest () ;
  curlist .modefield = ( -106 ) - curlist .modefield ;
  if ( curlist .modefield == -105 ) 
  curlist .auxfield .hh .v.LH = 0 ;
  else curlist .auxfield .cint = 0 ;
  {
    mem [curlist .tailfield ].hh .v.RH = newglue ( mem [mem [memtop - 8 ]
    .hh .v.RH + 1 ].hh .v.LH ) ;
    curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
  } 
  mem [curlist .tailfield ].hh.b1 = 12 ;
  curalign = mem [mem [memtop - 8 ].hh .v.RH ].hh .v.RH ;
  curtail = curhead ;
  curpretail = curprehead ;
  initspan ( curalign ) ;
} 
void 
initcol ( void ) 
{
  initcol_regmem 
  mem [curalign + 5 ].hh .v.LH = curcmd ;
  if ( curcmd == 63 ) 
  alignstate = 0 ;
  else {
      
    backinput () ;
    begintokenlist ( mem [curalign + 3 ].cint , 1 ) ;
  } 
} 
boolean 
fincol ( void ) 
{
  /* 10 */ register boolean Result; fincol_regmem 
  halfword p  ;
  halfword q, r  ;
  halfword s  ;
  halfword u  ;
  scaled w  ;
  glueord o  ;
  halfword n  ;
  if ( curalign == -268435455L ) 
  confusion ( 66338L ) ;
  q = mem [curalign ].hh .v.RH ;
  if ( q == -268435455L ) 
  confusion ( 66338L ) ;
  if ( alignstate < 500000L ) 
  fatalerror ( 65925L ) ;
  p = mem [q ].hh .v.RH ;
  if ( ( p == -268435455L ) && ( mem [curalign + 5 ].hh .v.LH < 1114114L ) ) 
  {
    if ( curloop != -268435455L ) 
    {
      mem [q ].hh .v.RH = newnullbox () ;
      p = mem [q ].hh .v.RH ;
      mem [p ].hh .v.LH = memtop - 9 ;
      mem [p + 1 ].cint = -1073741824L ;
      curloop = mem [curloop ].hh .v.RH ;
      q = memtop - 4 ;
      r = mem [curloop + 3 ].cint ;
      while ( r != -268435455L ) {
	  
	mem [q ].hh .v.RH = getavail () ;
	q = mem [q ].hh .v.RH ;
	mem [q ].hh .v.LH = mem [r ].hh .v.LH ;
	r = mem [r ].hh .v.RH ;
      } 
      mem [q ].hh .v.RH = -268435455L ;
      mem [p + 3 ].cint = mem [memtop - 4 ].hh .v.RH ;
      q = memtop - 4 ;
      r = mem [curloop + 2 ].cint ;
      while ( r != -268435455L ) {
	  
	mem [q ].hh .v.RH = getavail () ;
	q = mem [q ].hh .v.RH ;
	mem [q ].hh .v.LH = mem [r ].hh .v.LH ;
	r = mem [r ].hh .v.RH ;
      } 
      mem [q ].hh .v.RH = -268435455L ;
      mem [p + 2 ].cint = mem [memtop - 4 ].hh .v.RH ;
      curloop = mem [curloop ].hh .v.RH ;
      mem [p ].hh .v.RH = newglue ( mem [curloop + 1 ].hh .v.LH ) ;
      mem [mem [p ].hh .v.RH ].hh.b1 = 12 ;
    } 
    else {
	
      {
	if ( interaction == 3 ) 
	;
	if ( filelineerrorstylep ) 
	printfileline () ;
	else printnl ( 65544L ) ;
	print ( 66339L ) ;
      } 
      printesc ( 66328L ) ;
      {
	helpptr = 3 ;
	helpline [2 ]= 66340L ;
	helpline [1 ]= 66341L ;
	helpline [0 ]= 66342L ;
      } 
      mem [curalign + 5 ].hh .v.LH = 1114114L ;
      error () ;
    } 
  } 
  if ( mem [curalign + 5 ].hh .v.LH != 1114113L ) 
  {
    unsave () ;
    newsavelevel ( 6 ) ;
    {
      if ( curlist .modefield == -105 ) 
      {
	adjusttail = curtail ;
	preadjusttail = curpretail ;
	u = hpack ( mem [curlist .headfield ].hh .v.RH , 0 , 1 ) ;
	w = mem [u + 1 ].cint ;
	curtail = adjusttail ;
	adjusttail = -268435455L ;
	curpretail = preadjusttail ;
	preadjusttail = -268435455L ;
      } 
      else {
	  
	u = vpackage ( mem [curlist .headfield ].hh .v.RH , 0 , 1 , 0 ) ;
	w = mem [u + 3 ].cint ;
      } 
      n = 0 ;
      if ( curspan != curalign ) 
      {
	q = curspan ;
	do {
	    incr ( n ) ;
	  q = mem [mem [q ].hh .v.RH ].hh .v.RH ;
	} while ( ! ( q == curalign ) ) ;
	if ( n > 65535L ) 
	confusion ( 66343L ) ;
	q = curspan ;
	while ( mem [mem [q ].hh .v.LH ].hh .v.RH < n ) q = mem [q ].hh 
	.v.LH ;
	if ( mem [mem [q ].hh .v.LH ].hh .v.RH > n ) 
	{
	  s = getnode ( 2 ) ;
	  mem [s ].hh .v.LH = mem [q ].hh .v.LH ;
	  mem [s ].hh .v.RH = n ;
	  mem [q ].hh .v.LH = s ;
	  mem [s + 1 ].cint = w ;
	} 
	else if ( mem [mem [q ].hh .v.LH + 1 ].cint < w ) 
	mem [mem [q ].hh .v.LH + 1 ].cint = w ;
      } 
      else if ( w > mem [curalign + 1 ].cint ) 
      mem [curalign + 1 ].cint = w ;
      mem [u ].hh.b0 = 13 ;
      mem [u ].hh.b1 = n ;
      if ( totalstretch [3 ]!= 0 ) 
      o = 3 ;
      else if ( totalstretch [2 ]!= 0 ) 
      o = 2 ;
      else if ( totalstretch [1 ]!= 0 ) 
      o = 1 ;
      else o = 0 ;
      mem [u + 5 ].hh.b1 = o ;
      mem [u + 6 ].cint = totalstretch [o ];
      if ( totalshrink [3 ]!= 0 ) 
      o = 3 ;
      else if ( totalshrink [2 ]!= 0 ) 
      o = 2 ;
      else if ( totalshrink [1 ]!= 0 ) 
      o = 1 ;
      else o = 0 ;
      mem [u + 5 ].hh.b0 = o ;
      mem [u + 4 ].cint = totalshrink [o ];
      popnest () ;
      mem [curlist .tailfield ].hh .v.RH = u ;
      curlist .tailfield = u ;
    } 
    {
      mem [curlist .tailfield ].hh .v.RH = newglue ( mem [mem [curalign ]
      .hh .v.RH + 1 ].hh .v.LH ) ;
      curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
    } 
    mem [curlist .tailfield ].hh.b1 = 12 ;
    if ( mem [curalign + 5 ].hh .v.LH >= 1114114L ) 
    {
      Result = true ;
      return Result ;
    } 
    initspan ( p ) ;
  } 
  alignstate = 1000000L ;
  do {
      getxorprotected () ;
  } while ( ! ( curcmd != 10 ) ) ;
  curalign = p ;
  initcol () ;
  Result = false ;
  return Result ;
} 
void 
finrow ( void ) 
{
  finrow_regmem 
  halfword p  ;
  if ( curlist .modefield == -105 ) 
  {
    p = hpack ( mem [curlist .headfield ].hh .v.RH , 0 , 1 ) ;
    popnest () ;
    if ( curprehead != curpretail ) 
    {
      mem [curlist .tailfield ].hh .v.RH = mem [curprehead ].hh .v.RH ;
      curlist .tailfield = curpretail ;
    } 
    appendtovlist ( p ) ;
    if ( curhead != curtail ) 
    {
      mem [curlist .tailfield ].hh .v.RH = mem [curhead ].hh .v.RH ;
      curlist .tailfield = curtail ;
    } 
  } 
  else {
      
    p = vpackage ( mem [curlist .headfield ].hh .v.RH , 0 , 1 , 1073741823L 
    ) ;
    popnest () ;
    mem [curlist .tailfield ].hh .v.RH = p ;
    curlist .tailfield = p ;
    curlist .auxfield .hh .v.LH = 1000 ;
  } 
  mem [p ].hh.b0 = 13 ;
  mem [p + 6 ].cint = 0 ;
  if ( eqtb [1206303L ].hh .v.RH != -268435455L ) 
  begintokenlist ( eqtb [1206303L ].hh .v.RH , 14 ) ;
  alignpeek () ;
} 
void 
finalign ( void ) 
{
  finalign_regmem 
  halfword p, q, r, s, u, v  ;
  scaled t, w  ;
  scaled o  ;
  halfword n  ;
  scaled rulesave  ;
  memoryword auxsave  ;
  if ( curgroup != 6 ) 
  confusion ( 66344L ) ;
  unsave () ;
  if ( curgroup != 6 ) 
  confusion ( 66345L ) ;
  unsave () ;
  if ( nest [nestptr - 1 ].modefield == 209 ) 
  o = eqtb [9006735L ].cint ;
  else o = 0 ;
  q = mem [mem [memtop - 8 ].hh .v.RH ].hh .v.RH ;
  do {
      flushlist ( mem [q + 3 ].cint ) ;
    flushlist ( mem [q + 2 ].cint ) ;
    p = mem [mem [q ].hh .v.RH ].hh .v.RH ;
    if ( mem [q + 1 ].cint == -1073741824L ) 
    {
      mem [q + 1 ].cint = 0 ;
      r = mem [q ].hh .v.RH ;
      s = mem [r + 1 ].hh .v.LH ;
      if ( s != membot ) 
      {
	incr ( mem [membot ].hh .v.RH ) ;
	deleteglueref ( s ) ;
	mem [r + 1 ].hh .v.LH = membot ;
      } 
    } 
    if ( mem [q ].hh .v.LH != memtop - 9 ) 
    {
      t = mem [q + 1 ].cint + mem [mem [mem [q ].hh .v.RH + 1 ].hh 
      .v.LH + 1 ].cint ;
      r = mem [q ].hh .v.LH ;
      s = memtop - 9 ;
      mem [s ].hh .v.LH = p ;
      n = 1 ;
      do {
	  mem [r + 1 ].cint = mem [r + 1 ].cint - t ;
	u = mem [r ].hh .v.LH ;
	while ( mem [r ].hh .v.RH > n ) {
	    
	  s = mem [s ].hh .v.LH ;
	  n = mem [mem [s ].hh .v.LH ].hh .v.RH + 1 ;
	} 
	if ( mem [r ].hh .v.RH < n ) 
	{
	  mem [r ].hh .v.LH = mem [s ].hh .v.LH ;
	  mem [s ].hh .v.LH = r ;
	  decr ( mem [r ].hh .v.RH ) ;
	  s = r ;
	} 
	else {
	    
	  if ( mem [r + 1 ].cint > mem [mem [s ].hh .v.LH + 1 ].cint ) 
	  mem [mem [s ].hh .v.LH + 1 ].cint = mem [r + 1 ].cint ;
	  freenode ( r , 2 ) ;
	} 
	r = u ;
      } while ( ! ( r == memtop - 9 ) ) ;
    } 
    mem [q ].hh.b0 = 13 ;
    mem [q ].hh.b1 = 0 ;
    mem [q + 3 ].cint = 0 ;
    mem [q + 2 ].cint = 0 ;
    mem [q + 5 ].hh.b1 = 0 ;
    mem [q + 5 ].hh.b0 = 0 ;
    mem [q + 6 ].cint = 0 ;
    mem [q + 4 ].cint = 0 ;
    q = p ;
  } while ( ! ( q == -268435455L ) ) ;
  saveptr = saveptr - 2 ;
  packbeginline = - (integer) curlist .mlfield ;
  if ( curlist .modefield == -1 ) 
  {
    rulesave = eqtb [9006736L ].cint ;
    eqtb [9006736L ].cint = 0 ;
    p = hpack ( mem [memtop - 8 ].hh .v.RH , savestack [saveptr + 1 ].cint 
    , savestack [saveptr + 0 ].cint ) ;
    eqtb [9006736L ].cint = rulesave ;
  } 
  else {
      
    q = mem [mem [memtop - 8 ].hh .v.RH ].hh .v.RH ;
    do {
	mem [q + 3 ].cint = mem [q + 1 ].cint ;
      mem [q + 1 ].cint = 0 ;
      q = mem [mem [q ].hh .v.RH ].hh .v.RH ;
    } while ( ! ( q == -268435455L ) ) ;
    p = vpackage ( mem [memtop - 8 ].hh .v.RH , savestack [saveptr + 1 ]
    .cint , savestack [saveptr + 0 ].cint , 1073741823L ) ;
    q = mem [mem [memtop - 8 ].hh .v.RH ].hh .v.RH ;
    do {
	mem [q + 1 ].cint = mem [q + 3 ].cint ;
      mem [q + 3 ].cint = 0 ;
      q = mem [mem [q ].hh .v.RH ].hh .v.RH ;
    } while ( ! ( q == -268435455L ) ) ;
  } 
  packbeginline = 0 ;
  q = mem [curlist .headfield ].hh .v.RH ;
  s = curlist .headfield ;
  while ( q != -268435455L ) {
      
    if ( ! ( q >= himemmin ) ) {
	
      if ( mem [q ].hh.b0 == 13 ) 
      {
	if ( curlist .modefield == -1 ) 
	{
	  mem [q ].hh.b0 = 0 ;
	  mem [q + 1 ].cint = mem [p + 1 ].cint ;
	  if ( nest [nestptr - 1 ].modefield == 209 ) 
	  mem [q ].hh.b1 = 2 ;
	} 
	else {
	    
	  mem [q ].hh.b0 = 1 ;
	  mem [q + 3 ].cint = mem [p + 3 ].cint ;
	} 
	mem [q + 5 ].hh.b1 = mem [p + 5 ].hh.b1 ;
	mem [q + 5 ].hh.b0 = mem [p + 5 ].hh.b0 ;
	mem [q + 6 ].gr = mem [p + 6 ].gr ;
	mem [q + 4 ].cint = o ;
	r = mem [mem [q + 5 ].hh .v.RH ].hh .v.RH ;
	s = mem [mem [p + 5 ].hh .v.RH ].hh .v.RH ;
	do {
	    n = mem [r ].hh.b1 ;
	  t = mem [s + 1 ].cint ;
	  w = t ;
	  u = memtop - 4 ;
	  mem [r ].hh.b1 = 0 ;
	  while ( n > 0 ) {
	      
	    decr ( n ) ;
	    s = mem [s ].hh .v.RH ;
	    v = mem [s + 1 ].hh .v.LH ;
	    mem [u ].hh .v.RH = newglue ( v ) ;
	    u = mem [u ].hh .v.RH ;
	    mem [u ].hh.b1 = 12 ;
	    t = t + mem [v + 1 ].cint ;
	    if ( mem [p + 5 ].hh.b0 == 1 ) 
	    {
	      if ( mem [v ].hh.b0 == mem [p + 5 ].hh.b1 ) 
	      t = t + round ( mem [p + 6 ].gr * mem [v + 2 ].cint ) ;
	    } 
	    else if ( mem [p + 5 ].hh.b0 == 2 ) 
	    {
	      if ( mem [v ].hh.b1 == mem [p + 5 ].hh.b1 ) 
	      t = t - round ( mem [p + 6 ].gr * mem [v + 3 ].cint ) ;
	    } 
	    s = mem [s ].hh .v.RH ;
	    mem [u ].hh .v.RH = newnullbox () ;
	    u = mem [u ].hh .v.RH ;
	    t = t + mem [s + 1 ].cint ;
	    if ( curlist .modefield == -1 ) 
	    mem [u + 1 ].cint = mem [s + 1 ].cint ;
	    else {
		
	      mem [u ].hh.b0 = 1 ;
	      mem [u + 3 ].cint = mem [s + 1 ].cint ;
	    } 
	  } 
	  if ( curlist .modefield == -1 ) 
	  {
	    mem [r + 3 ].cint = mem [q + 3 ].cint ;
	    mem [r + 2 ].cint = mem [q + 2 ].cint ;
	    if ( t == mem [r + 1 ].cint ) 
	    {
	      mem [r + 5 ].hh.b0 = 0 ;
	      mem [r + 5 ].hh.b1 = 0 ;
	      mem [r + 6 ].gr = 0.0 ;
	    } 
	    else if ( t > mem [r + 1 ].cint ) 
	    {
	      mem [r + 5 ].hh.b0 = 1 ;
	      if ( mem [r + 6 ].cint == 0 ) 
	      mem [r + 6 ].gr = 0.0 ;
	      else mem [r + 6 ].gr = ( t - mem [r + 1 ].cint ) / ((double) 
	      mem [r + 6 ].cint ) ;
	    } 
	    else {
		
	      mem [r + 5 ].hh.b1 = mem [r + 5 ].hh.b0 ;
	      mem [r + 5 ].hh.b0 = 2 ;
	      if ( mem [r + 4 ].cint == 0 ) 
	      mem [r + 6 ].gr = 0.0 ;
	      else if ( ( mem [r + 5 ].hh.b1 == 0 ) && ( mem [r + 1 ].cint 
	      - t > mem [r + 4 ].cint ) ) 
	      mem [r + 6 ].gr = 1.0 ;
	      else mem [r + 6 ].gr = ( mem [r + 1 ].cint - t ) / ((double) 
	      mem [r + 4 ].cint ) ;
	    } 
	    mem [r + 1 ].cint = w ;
	    mem [r ].hh.b0 = 0 ;
	  } 
	  else {
	      
	    mem [r + 1 ].cint = mem [q + 1 ].cint ;
	    if ( t == mem [r + 3 ].cint ) 
	    {
	      mem [r + 5 ].hh.b0 = 0 ;
	      mem [r + 5 ].hh.b1 = 0 ;
	      mem [r + 6 ].gr = 0.0 ;
	    } 
	    else if ( t > mem [r + 3 ].cint ) 
	    {
	      mem [r + 5 ].hh.b0 = 1 ;
	      if ( mem [r + 6 ].cint == 0 ) 
	      mem [r + 6 ].gr = 0.0 ;
	      else mem [r + 6 ].gr = ( t - mem [r + 3 ].cint ) / ((double) 
	      mem [r + 6 ].cint ) ;
	    } 
	    else {
		
	      mem [r + 5 ].hh.b1 = mem [r + 5 ].hh.b0 ;
	      mem [r + 5 ].hh.b0 = 2 ;
	      if ( mem [r + 4 ].cint == 0 ) 
	      mem [r + 6 ].gr = 0.0 ;
	      else if ( ( mem [r + 5 ].hh.b1 == 0 ) && ( mem [r + 3 ].cint 
	      - t > mem [r + 4 ].cint ) ) 
	      mem [r + 6 ].gr = 1.0 ;
	      else mem [r + 6 ].gr = ( mem [r + 3 ].cint - t ) / ((double) 
	      mem [r + 4 ].cint ) ;
	    } 
	    mem [r + 3 ].cint = w ;
	    mem [r ].hh.b0 = 1 ;
	  } 
	  mem [r + 4 ].cint = 0 ;
	  if ( u != memtop - 4 ) 
	  {
	    mem [u ].hh .v.RH = mem [r ].hh .v.RH ;
	    mem [r ].hh .v.RH = mem [memtop - 4 ].hh .v.RH ;
	    r = u ;
	  } 
	  r = mem [mem [r ].hh .v.RH ].hh .v.RH ;
	  s = mem [mem [s ].hh .v.RH ].hh .v.RH ;
	} while ( ! ( r == -268435455L ) ) ;
      } 
      else if ( mem [q ].hh.b0 == 2 ) 
      {
	if ( ( mem [q + 1 ].cint == -1073741824L ) ) 
	mem [q + 1 ].cint = mem [p + 1 ].cint ;
	if ( ( mem [q + 3 ].cint == -1073741824L ) ) 
	mem [q + 3 ].cint = mem [p + 3 ].cint ;
	if ( ( mem [q + 2 ].cint == -1073741824L ) ) 
	mem [q + 2 ].cint = mem [p + 2 ].cint ;
	if ( o != 0 ) 
	{
	  r = mem [q ].hh .v.RH ;
	  mem [q ].hh .v.RH = -268435455L ;
	  q = hpack ( q , 0 , 1 ) ;
	  mem [q + 4 ].cint = o ;
	  mem [q ].hh .v.RH = r ;
	  mem [s ].hh .v.RH = q ;
	} 
      } 
    } 
    s = q ;
    q = mem [q ].hh .v.RH ;
  } 
  flushnodelist ( p ) ;
  popalignment () ;
  auxsave = curlist .auxfield ;
  p = mem [curlist .headfield ].hh .v.RH ;
  q = curlist .tailfield ;
  popnest () ;
  if ( curlist .modefield == 209 ) 
  {
    doassignments () ;
    if ( curcmd != 3 ) 
    {
      {
	if ( interaction == 3 ) 
	;
	if ( filelineerrorstylep ) 
	printfileline () ;
	else printnl ( 65544L ) ;
	print ( 66609L ) ;
      } 
      {
	helpptr = 2 ;
	helpline [1 ]= 66324L ;
	helpline [0 ]= 66325L ;
      } 
      backerror () ;
    } 
    else {
	
      getxtoken () ;
      if ( curcmd != 3 ) 
      {
	{
	  if ( interaction == 3 ) 
	  ;
	  if ( filelineerrorstylep ) 
	  printfileline () ;
	  else printnl ( 65544L ) ;
	  print ( 66605L ) ;
	} 
	{
	  helpptr = 2 ;
	  helpline [1 ]= 66606L ;
	  helpline [0 ]= 66607L ;
	} 
	backerror () ;
      } 
    } 
    flushnodelist ( curlist .eTeXauxfield ) ;
    popnest () ;
    {
      mem [curlist .tailfield ].hh .v.RH = newpenalty ( eqtb [7892275L ]
      .cint ) ;
      curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
    } 
    {
      mem [curlist .tailfield ].hh .v.RH = newparamglue ( 3 ) ;
      curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
    } 
    mem [curlist .tailfield ].hh .v.RH = p ;
    if ( p != -268435455L ) 
    curlist .tailfield = q ;
    {
      mem [curlist .tailfield ].hh .v.RH = newpenalty ( eqtb [7892276L ]
      .cint ) ;
      curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
    } 
    {
      mem [curlist .tailfield ].hh .v.RH = newparamglue ( 4 ) ;
      curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
    } 
    curlist .auxfield .cint = auxsave .cint ;
    resumeafterdisplay () ;
  } 
  else {
      
    curlist .auxfield = auxsave ;
    mem [curlist .tailfield ].hh .v.RH = p ;
    if ( p != -268435455L ) 
    curlist .tailfield = q ;
    if ( curlist .modefield == 1 ) 
    buildpage () ;
  } 
} 
void 
alignpeek ( void ) 
{
  /* 20 */ alignpeek_regmem 
  lab20: alignstate = 1000000L ;
  do {
      getxorprotected () ;
  } while ( ! ( curcmd != 10 ) ) ;
  if ( curcmd == 34 ) 
  {
    scanleftbrace () ;
    newsavelevel ( 7 ) ;
    if ( curlist .modefield == -1 ) 
    normalparagraph () ;
  } 
  else if ( curcmd == 2 ) 
  finalign () ;
  else if ( ( curcmd == 5 ) && ( curchr == 1114115L ) ) 
  goto lab20 ;
  else {
      
    initrow () ;
    initcol () ;
  } 
} 
halfword 
zfiniteshrink ( halfword p ) 
{
  register halfword Result; finiteshrink_regmem 
  halfword q  ;
  if ( noshrinkerroryet ) 
  {
    noshrinkerroryet = false ;
	;
#ifdef STAT
    if ( eqtb [7892296L ].cint > 0 ) 
    enddiagnostic ( true ) ;
#endif /* STAT */
    {
      if ( interaction == 3 ) 
      ;
      if ( filelineerrorstylep ) 
      printfileline () ;
      else printnl ( 65544L ) ;
      print ( 66346L ) ;
    } 
    {
      helpptr = 5 ;
      helpline [4 ]= 66347L ;
      helpline [3 ]= 66348L ;
      helpline [2 ]= 66349L ;
      helpline [1 ]= 66350L ;
      helpline [0 ]= 66351L ;
    } 
    error () ;
	;
#ifdef STAT
    if ( eqtb [7892296L ].cint > 0 ) 
    begindiagnostic () ;
#endif /* STAT */
  } 
  q = newspec ( p ) ;
  mem [q ].hh.b1 = 0 ;
  deleteglueref ( p ) ;
  Result = q ;
  return Result ;
} 
void 
zpushnode ( halfword p ) 
{
  pushnode_regmem 
  if ( hliststacklevel > 512 ) 
  pdferror ( 66352L , 66353L ) ;
  hliststack [hliststacklevel ]= p ;
  hliststacklevel = hliststacklevel + 1 ;
} 
halfword 
popnode ( void ) 
{
  register halfword Result; popnode_regmem 
  hliststacklevel = hliststacklevel - 1 ;
  if ( hliststacklevel < 0 ) 
  pdferror ( 66354L , 66355L ) ;
  Result = hliststack [hliststacklevel ];
  return Result ;
} 
halfword 
zfindprotcharleft ( halfword l , boolean d ) 
{
  register halfword Result; findprotcharleft_regmem 
  halfword t  ;
  boolean run  ;
  if ( ( mem [l ].hh .v.RH != -268435455L ) && ( mem [l ].hh.b0 == 0 ) && 
  ( mem [l + 1 ].cint == 0 ) && ( mem [l + 3 ].cint == 0 ) && ( mem [l + 
  2 ].cint == 0 ) && ( mem [l + 5 ].hh .v.RH == -268435455L ) ) 
  l = mem [l ].hh .v.RH ;
  else if ( d ) 
  while ( ( mem [l ].hh .v.RH != -268435455L ) && ( ! ( ( l >= himemmin ) || 
  ( mem [l ].hh.b0 < 9 ) ) ) ) l = mem [l ].hh .v.RH ;
  hliststacklevel = 0 ;
  run = true ;
  do {
      t = l ;
    while ( run && ( mem [l ].hh.b0 == 0 ) && ( mem [l + 5 ].hh .v.RH != 
    -268435455L ) ) {
	
      pushnode ( l ) ;
      l = mem [l + 5 ].hh .v.RH ;
    } 
    while ( run && ( ! ( l >= himemmin ) && ( ( mem [l ].hh.b0 == 3 ) || ( 
    mem [l ].hh.b0 == 4 ) || ( mem [l ].hh.b0 == 5 ) || ( mem [l ].hh.b0 
    == 12 ) || ( ( mem [l ].hh.b0 == 7 ) && ( mem [l + 1 ].hh .v.LH == 
    -268435455L ) && ( mem [l + 1 ].hh .v.RH == -268435455L ) && ( mem [l ]
    .hh.b1 == 0 ) ) || ( ( mem [l ].hh.b0 == 9 ) && ( mem [l + 1 ].cint == 
    0 ) ) || ( ( mem [l ].hh.b0 == 11 ) && ( ( mem [l + 1 ].cint == 0 ) || 
    ( mem [l ].hh.b1 == 0 ) ) ) || ( ( mem [l ].hh.b0 == 10 ) && ( mem [l 
    + 1 ].hh .v.LH == membot ) ) || ( ( mem [l ].hh.b0 == 0 ) && ( mem [l 
    + 1 ].cint == 0 ) && ( mem [l + 3 ].cint == 0 ) && ( mem [l + 2 ]
    .cint == 0 ) && ( mem [l + 5 ].hh .v.RH == -268435455L ) ) ) ) ) {
	
      while ( ( mem [l ].hh .v.RH == -268435455L ) && ( hliststacklevel > 0 
      ) ) {
	  
	l = popnode () ;
      } 
      if ( mem [l ].hh .v.RH != -268435455L ) 
      l = mem [l ].hh .v.RH ;
      else if ( hliststacklevel == 0 ) 
      run = false ;
    } 
  } while ( ! ( t == l ) ) ;
  Result = l ;
  return Result ;
} 
halfword 
zfindprotcharright ( halfword l , halfword r ) 
{
  register halfword Result; findprotcharright_regmem 
  halfword t  ;
  boolean run  ;
  Result = -268435455L ;
  if ( r == -268435455L ) 
  return Result ;
  hliststacklevel = 0 ;
  run = true ;
  do {
      t = r ;
    while ( run && ( mem [r ].hh.b0 == 0 ) && ( mem [r + 5 ].hh .v.RH != 
    -268435455L ) ) {
	
      pushnode ( l ) ;
      pushnode ( r ) ;
      l = mem [r + 5 ].hh .v.RH ;
      r = l ;
      while ( mem [r ].hh .v.RH != -268435455L ) r = mem [r ].hh .v.RH ;
    } 
    while ( run && ( ! ( r >= himemmin ) && ( ( mem [r ].hh.b0 == 3 ) || ( 
    mem [r ].hh.b0 == 4 ) || ( mem [r ].hh.b0 == 5 ) || ( mem [r ].hh.b0 
    == 12 ) || ( ( mem [r ].hh.b0 == 7 ) && ( mem [r + 1 ].hh .v.LH == 
    -268435455L ) && ( mem [r + 1 ].hh .v.RH == -268435455L ) && ( mem [r ]
    .hh.b1 == 0 ) ) || ( ( mem [r ].hh.b0 == 9 ) && ( mem [r + 1 ].cint == 
    0 ) ) || ( ( mem [r ].hh.b0 == 11 ) && ( ( mem [r + 1 ].cint == 0 ) || 
    ( mem [r ].hh.b1 == 0 ) ) ) || ( ( mem [r ].hh.b0 == 10 ) && ( mem [r 
    + 1 ].hh .v.LH == membot ) ) || ( ( mem [r ].hh.b0 == 0 ) && ( mem [r 
    + 1 ].cint == 0 ) && ( mem [r + 3 ].cint == 0 ) && ( mem [r + 2 ]
    .cint == 0 ) && ( mem [r + 5 ].hh .v.RH == -268435455L ) ) ) ) ) {
	
      while ( ( r == l ) && ( hliststacklevel > 0 ) ) {
	  
	r = popnode () ;
	l = popnode () ;
      } 
      if ( ( r != l ) && ( r != -268435455L ) ) 
      r = prevrightmost ( l , r ) ;
      else if ( ( r == l ) && ( hliststacklevel == 0 ) ) 
      run = false ;
    } 
  } while ( ! ( t == r ) ) ;
  Result = r ;
  return Result ;
} 
scaled 
ztotalpw ( halfword q , halfword p ) 
{
  register scaled Result; totalpw_regmem 
  halfword l, r  ;
  integer n  ;
  if ( mem [q + 1 ].hh .v.RH == -268435455L ) 
  l = firstp ;
  else l = mem [mem [q + 1 ].hh .v.RH + 1 ].hh .v.RH ;
  r = prevrightmost ( globalprevp , p ) ;
  if ( ( p != -268435455L ) && ( mem [p ].hh.b0 == 7 ) && ( mem [p + 1 ]
  .hh .v.LH != -268435455L ) ) 
  {
    r = mem [p + 1 ].hh .v.LH ;
    while ( mem [r ].hh .v.RH != -268435455L ) r = mem [r ].hh .v.RH ;
  } 
  else r = findprotcharright ( l , r ) ;
  if ( ( l != -268435455L ) && ( mem [l ].hh.b0 == 7 ) ) 
  {
    if ( mem [l + 1 ].hh .v.RH != -268435455L ) 
    {
      l = mem [l + 1 ].hh .v.RH ;
      goto lab30 ;
    } 
    else {
	
      n = mem [l ].hh.b1 ;
      l = mem [l ].hh .v.RH ;
      while ( n > 0 ) {
	  
	if ( mem [l ].hh .v.RH != -268435455L ) 
	l = mem [l ].hh .v.RH ;
	decr ( n ) ;
      } 
    } 
  } 
  l = findprotcharleft ( l , true ) ;
  lab30: Result = charpw ( l , 0 ) + charpw ( r , 1 ) ;
  return Result ;
} 
void 
ztrybreak ( integer pi , smallnumber breaktype ) 
{
  /* 10 30 31 22 60 40 45 */ trybreak_regmem 
  halfword r  ;
  halfword prevr  ;
  halfword oldl  ;
  boolean nobreakyet  ;
  halfword prevprevr  ;
  halfword s  ;
  halfword q  ;
  halfword v  ;
  integer t  ;
  internalfontnumber f  ;
  halfword l  ;
  boolean noderstaysactive  ;
  scaled linewidth  ;
  unsigned char fitclass  ;
  halfword b  ;
  integer d  ;
  boolean artificialdemerits  ;
  halfword savelink  ;
  scaled shortfall  ;
  scaled g  ;
  if ( abs ( pi ) >= 10000 ) {
      
    if ( pi > 0 ) 
    goto lab10 ;
    else pi = -10000 ;
  } 
  nobreakyet = true ;
  prevr = memtop - 7 ;
  oldl = 0 ;
  curactivewidth [1 ]= activewidth [1 ];
  curactivewidth [2 ]= activewidth [2 ];
  curactivewidth [3 ]= activewidth [3 ];
  curactivewidth [4 ]= activewidth [4 ];
  curactivewidth [5 ]= activewidth [5 ];
  curactivewidth [6 ]= activewidth [6 ];
  while ( true ) {
      
    lab22: r = mem [prevr ].hh .v.RH ;
    if ( mem [r ].hh.b0 == 2 ) 
    {
      curactivewidth [1 ]= curactivewidth [1 ]+ mem [r + 1 ].cint ;
      curactivewidth [2 ]= curactivewidth [2 ]+ mem [r + 2 ].cint ;
      curactivewidth [3 ]= curactivewidth [3 ]+ mem [r + 3 ].cint ;
      curactivewidth [4 ]= curactivewidth [4 ]+ mem [r + 4 ].cint ;
      curactivewidth [5 ]= curactivewidth [5 ]+ mem [r + 5 ].cint ;
      curactivewidth [6 ]= curactivewidth [6 ]+ mem [r + 6 ].cint ;
      prevprevr = prevr ;
      prevr = r ;
      goto lab22 ;
    } 
    {
      l = mem [r + 1 ].hh .v.LH ;
      if ( l > oldl ) 
      {
	if ( ( minimumdemerits < 1073741823L ) && ( ( oldl != easyline ) || ( 
	r == memtop - 7 ) ) ) 
	{
	  if ( nobreakyet ) 
	  {
	    nobreakyet = false ;
	    breakwidth [1 ]= background [1 ];
	    breakwidth [2 ]= background [2 ];
	    breakwidth [3 ]= background [3 ];
	    breakwidth [4 ]= background [4 ];
	    breakwidth [5 ]= background [5 ];
	    breakwidth [6 ]= background [6 ];
	    s = curp ;
	    if ( breaktype > 0 ) {
		
	      if ( curp != -268435455L ) 
	      {
		t = mem [curp ].hh.b1 ;
		v = curp ;
		s = mem [curp + 1 ].hh .v.RH ;
		while ( t > 0 ) {
		    
		  decr ( t ) ;
		  v = mem [v ].hh .v.RH ;
		  if ( ( v >= himemmin ) ) 
		  {
		    f = mem [v ].hh.b0 ;
		    breakwidth [1 ]= breakwidth [1 ]- fontinfo [widthbase 
		    [f ]+ fontinfo [charbase [f ]+ effectivechar ( true , 
		    f , mem [v ].hh.b1 ) ].qqqq .b0 ].cint ;
		  } 
		  else switch ( mem [v ].hh.b0 ) 
		  {case 6 : 
		    {
		      f = mem [v + 1 ].hh.b0 ;
		      xtxligaturepresent = true ;
		      breakwidth [1 ]= breakwidth [1 ]- fontinfo [
		      widthbase [f ]+ fontinfo [charbase [f ]+ 
		      effectivechar ( true , f , mem [v + 1 ].hh.b1 ) ]
		      .qqqq .b0 ].cint ;
		    } 
		    break ;
		  case 0 : 
		  case 1 : 
		  case 2 : 
		  case 11 : 
		    breakwidth [1 ]= breakwidth [1 ]- mem [v + 1 ].cint 
		    ;
		    break ;
		  case 8 : 
		    if ( ( ( ( mem [v ].hh.b1 >= 40 ) && ( mem [v ].hh.b1 
		    <= 41 ) ) ) || ( mem [v ].hh.b1 == 42 ) || ( mem [v ]
		    .hh.b1 == 43 ) || ( mem [v ].hh.b1 == 44 ) ) 
		    breakwidth [1 ]= breakwidth [1 ]- mem [v + 1 ].cint 
		    ;
		    else confusion ( 66356L ) ;
		    break ;
		    default: 
		    confusion ( 66357L ) ;
		    break ;
		  } 
		} 
		while ( s != -268435455L ) {
		    
		  if ( ( s >= himemmin ) ) 
		  {
		    f = mem [s ].hh.b0 ;
		    breakwidth [1 ]= breakwidth [1 ]+ fontinfo [widthbase 
		    [f ]+ fontinfo [charbase [f ]+ effectivechar ( true , 
		    f , mem [s ].hh.b1 ) ].qqqq .b0 ].cint ;
		  } 
		  else switch ( mem [s ].hh.b0 ) 
		  {case 6 : 
		    {
		      f = mem [s + 1 ].hh.b0 ;
		      xtxligaturepresent = true ;
		      breakwidth [1 ]= breakwidth [1 ]+ fontinfo [
		      widthbase [f ]+ fontinfo [charbase [f ]+ 
		      effectivechar ( true , f , mem [s + 1 ].hh.b1 ) ]
		      .qqqq .b0 ].cint ;
		    } 
		    break ;
		  case 0 : 
		  case 1 : 
		  case 2 : 
		  case 11 : 
		    breakwidth [1 ]= breakwidth [1 ]+ mem [s + 1 ].cint 
		    ;
		    break ;
		  case 8 : 
		    if ( ( ( ( mem [s ].hh.b1 >= 40 ) && ( mem [s ].hh.b1 
		    <= 41 ) ) ) || ( mem [s ].hh.b1 == 42 ) || ( mem [s ]
		    .hh.b1 == 43 ) || ( mem [s ].hh.b1 == 44 ) ) 
		    breakwidth [1 ]= breakwidth [1 ]+ mem [s + 1 ].cint 
		    ;
		    else confusion ( 66358L ) ;
		    break ;
		    default: 
		    confusion ( 66359L ) ;
		    break ;
		  } 
		  s = mem [s ].hh .v.RH ;
		} 
		breakwidth [1 ]= breakwidth [1 ]+ discwidth ;
		if ( mem [curp + 1 ].hh .v.RH == -268435455L ) 
		s = mem [v ].hh .v.RH ;
	      } 
	    } 
	    while ( s != -268435455L ) {
		
	      if ( ( s >= himemmin ) ) 
	      goto lab30 ;
	      switch ( mem [s ].hh.b0 ) 
	      {case 10 : 
		{
		  v = mem [s + 1 ].hh .v.LH ;
		  breakwidth [1 ]= breakwidth [1 ]- mem [v + 1 ].cint ;
		  breakwidth [2 + mem [v ].hh.b0 ]= breakwidth [2 + mem [
		  v ].hh.b0 ]- mem [v + 2 ].cint ;
		  breakwidth [6 ]= breakwidth [6 ]- mem [v + 3 ].cint ;
		} 
		break ;
	      case 12 : 
		;
		break ;
	      case 9 : 
		breakwidth [1 ]= breakwidth [1 ]- mem [s + 1 ].cint ;
		break ;
	      case 11 : 
		if ( mem [s ].hh.b1 != 1 ) 
		goto lab30 ;
		else breakwidth [1 ]= breakwidth [1 ]- mem [s + 1 ].cint 
		;
		break ;
		default: 
		goto lab30 ;
		break ;
	      } 
	      s = mem [s ].hh .v.RH ;
	    } 
	    lab30: ;
	  } 
	  if ( mem [prevr ].hh.b0 == 2 ) 
	  {
	    mem [prevr + 1 ].cint = mem [prevr + 1 ].cint - curactivewidth 
	    [1 ]+ breakwidth [1 ];
	    mem [prevr + 2 ].cint = mem [prevr + 2 ].cint - curactivewidth 
	    [2 ]+ breakwidth [2 ];
	    mem [prevr + 3 ].cint = mem [prevr + 3 ].cint - curactivewidth 
	    [3 ]+ breakwidth [3 ];
	    mem [prevr + 4 ].cint = mem [prevr + 4 ].cint - curactivewidth 
	    [4 ]+ breakwidth [4 ];
	    mem [prevr + 5 ].cint = mem [prevr + 5 ].cint - curactivewidth 
	    [5 ]+ breakwidth [5 ];
	    mem [prevr + 6 ].cint = mem [prevr + 6 ].cint - curactivewidth 
	    [6 ]+ breakwidth [6 ];
	  } 
	  else if ( prevr == memtop - 7 ) 
	  {
	    activewidth [1 ]= breakwidth [1 ];
	    activewidth [2 ]= breakwidth [2 ];
	    activewidth [3 ]= breakwidth [3 ];
	    activewidth [4 ]= breakwidth [4 ];
	    activewidth [5 ]= breakwidth [5 ];
	    activewidth [6 ]= breakwidth [6 ];
	  } 
	  else {
	      
	    q = getnode ( 7 ) ;
	    mem [q ].hh .v.RH = r ;
	    mem [q ].hh.b0 = 2 ;
	    mem [q ].hh.b1 = 0 ;
	    mem [q + 1 ].cint = breakwidth [1 ]- curactivewidth [1 ];
	    mem [q + 2 ].cint = breakwidth [2 ]- curactivewidth [2 ];
	    mem [q + 3 ].cint = breakwidth [3 ]- curactivewidth [3 ];
	    mem [q + 4 ].cint = breakwidth [4 ]- curactivewidth [4 ];
	    mem [q + 5 ].cint = breakwidth [5 ]- curactivewidth [5 ];
	    mem [q + 6 ].cint = breakwidth [6 ]- curactivewidth [6 ];
	    mem [prevr ].hh .v.RH = q ;
	    prevprevr = prevr ;
	    prevr = q ;
	  } 
	  if ( abs ( eqtb [7892280L ].cint ) >= 1073741823L - 
	  minimumdemerits ) 
	  minimumdemerits = 1073741822L ;
	  else minimumdemerits = minimumdemerits + abs ( eqtb [7892280L ]
	  .cint ) ;
	  {register integer for_end; fitclass = 0 ;for_end = 3 ; if ( 
	  fitclass <= for_end) do 
	    {
	      if ( minimaldemerits [fitclass ]<= minimumdemerits ) 
	      {
		q = getnode ( 2 ) ;
		mem [q ].hh .v.RH = passive ;
		passive = q ;
		mem [q + 1 ].hh .v.RH = curp ;
	;
#ifdef STAT
		incr ( passnumber ) ;
		mem [q ].hh .v.LH = passnumber ;
#endif /* STAT */
		mem [q + 1 ].hh .v.LH = bestplace [fitclass ];
		q = getnode ( activenodesize ) ;
		mem [q + 1 ].hh .v.RH = passive ;
		mem [q + 1 ].hh .v.LH = bestplline [fitclass ]+ 1 ;
		mem [q ].hh.b1 = fitclass ;
		mem [q ].hh.b0 = breaktype ;
		mem [q + 2 ].cint = minimaldemerits [fitclass ];
		if ( dolastlinefit ) 
		{
		  mem [q + 3 ].cint = bestplshort [fitclass ];
		  mem [q + 4 ].cint = bestplglue [fitclass ];
		} 
		mem [q ].hh .v.RH = r ;
		mem [prevr ].hh .v.RH = q ;
		prevr = q ;
	;
#ifdef STAT
		if ( eqtb [7892296L ].cint > 0 ) 
		{
		  printnl ( 66360L ) ;
		  printint ( mem [passive ].hh .v.LH ) ;
		  print ( 66361L ) ;
		  printint ( mem [q + 1 ].hh .v.LH - 1 ) ;
		  printchar ( 46 ) ;
		  printint ( fitclass ) ;
		  if ( breaktype == 1 ) 
		  printchar ( 45 ) ;
		  print ( 66362L ) ;
		  printint ( mem [q + 2 ].cint ) ;
		  if ( dolastlinefit ) 
		  {
		    print ( 66967L ) ;
		    printscaled ( mem [q + 3 ].cint ) ;
		    if ( curp == -268435455L ) 
		    print ( 66968L ) ;
		    else print ( 66433L ) ;
		    printscaled ( mem [q + 4 ].cint ) ;
		  } 
		  print ( 66363L ) ;
		  if ( mem [passive + 1 ].hh .v.LH == -268435455L ) 
		  printchar ( 48 ) ;
		  else printint ( mem [mem [passive + 1 ].hh .v.LH ].hh 
		  .v.LH ) ;
		} 
#endif /* STAT */
	      } 
	      minimaldemerits [fitclass ]= 1073741823L ;
	    } 
	  while ( fitclass++ < for_end ) ;} 
	  minimumdemerits = 1073741823L ;
	  if ( r != memtop - 7 ) 
	  {
	    q = getnode ( 7 ) ;
	    mem [q ].hh .v.RH = r ;
	    mem [q ].hh.b0 = 2 ;
	    mem [q ].hh.b1 = 0 ;
	    mem [q + 1 ].cint = curactivewidth [1 ]- breakwidth [1 ];
	    mem [q + 2 ].cint = curactivewidth [2 ]- breakwidth [2 ];
	    mem [q + 3 ].cint = curactivewidth [3 ]- breakwidth [3 ];
	    mem [q + 4 ].cint = curactivewidth [4 ]- breakwidth [4 ];
	    mem [q + 5 ].cint = curactivewidth [5 ]- breakwidth [5 ];
	    mem [q + 6 ].cint = curactivewidth [6 ]- breakwidth [6 ];
	    mem [prevr ].hh .v.RH = q ;
	    prevprevr = prevr ;
	    prevr = q ;
	  } 
	} 
	if ( r == memtop - 7 ) 
	goto lab10 ;
	if ( l > easyline ) 
	{
	  linewidth = secondwidth ;
	  oldl = 1073741822L ;
	} 
	else {
	    
	  oldl = l ;
	  if ( l > lastspecialline ) 
	  linewidth = secondwidth ;
	  else if ( eqtb [1206295L ].hh .v.RH == -268435455L ) 
	  linewidth = firstwidth ;
	  else linewidth = mem [eqtb [1206295L ].hh .v.RH + 2 * l ].cint ;
	} 
      } 
    } 
    {
      artificialdemerits = false ;
      shortfall = linewidth - curactivewidth [1 ];
      if ( eqtb [7892338L ].cint > 1 ) 
      shortfall = shortfall + totalpw ( r , curp ) ;
      if ( shortfall > 0 ) {
	  
	if ( ( curactivewidth [3 ]!= 0 ) || ( curactivewidth [4 ]!= 0 ) || 
	( curactivewidth [5 ]!= 0 ) ) 
	{
	  if ( dolastlinefit ) 
	  {
	    if ( curp == -268435455L ) 
	    {
	      if ( ( mem [r + 3 ].cint == 0 ) || ( mem [r + 4 ].cint <= 0 
	      ) ) 
	      goto lab45 ;
	      if ( ( curactivewidth [3 ]!= fillwidth [0 ]) || ( 
	      curactivewidth [4 ]!= fillwidth [1 ]) || ( curactivewidth [
	      5 ]!= fillwidth [2 ]) ) 
	      goto lab45 ;
	      if ( mem [r + 3 ].cint > 0 ) 
	      g = curactivewidth [2 ];
	      else g = curactivewidth [6 ];
	      if ( g <= 0 ) 
	      goto lab45 ;
	      aritherror = false ;
	      g = fract ( g , mem [r + 3 ].cint , mem [r + 4 ].cint , 
	      1073741823L ) ;
	      if ( eqtb [7892331L ].cint < 1000 ) 
	      g = fract ( g , eqtb [7892331L ].cint , 1000 , 1073741823L ) ;
	      if ( aritherror ) {
		  
		if ( mem [r + 3 ].cint > 0 ) 
		g = 1073741823L ;
		else g = -1073741823L ;
	      } 
	      if ( g > 0 ) 
	      {
		if ( g > shortfall ) 
		g = shortfall ;
		if ( g > 7230584L ) {
		    
		  if ( curactivewidth [2 ]< 1663497L ) 
		  {
		    b = 10000 ;
		    fitclass = 0 ;
		    goto lab40 ;
		  } 
		} 
		b = badness ( g , curactivewidth [2 ]) ;
		if ( b > 12 ) {
		    
		  if ( b > 99 ) 
		  fitclass = 0 ;
		  else fitclass = 1 ;
		} 
		else fitclass = 2 ;
		goto lab40 ;
	      } 
	      else if ( g < 0 ) 
	      {
		if ( - (integer) g > curactivewidth [6 ]) 
		g = - (integer) curactivewidth [6 ];
		b = badness ( - (integer) g , curactivewidth [6 ]) ;
		if ( b > 12 ) 
		fitclass = 3 ;
		else fitclass = 2 ;
		goto lab40 ;
	      } 
	      lab45: ;
	    } 
	    shortfall = 0 ;
	  } 
	  b = 0 ;
	  fitclass = 2 ;
	} 
	else {
	    
	  if ( shortfall > 7230584L ) {
	      
	    if ( curactivewidth [2 ]< 1663497L ) 
	    {
	      b = 10000 ;
	      fitclass = 0 ;
	      goto lab31 ;
	    } 
	  } 
	  b = badness ( shortfall , curactivewidth [2 ]) ;
	  if ( b > 12 ) {
	      
	    if ( b > 99 ) 
	    fitclass = 0 ;
	    else fitclass = 1 ;
	  } 
	  else fitclass = 2 ;
	  lab31: ;
	} 
      } 
      else {
	  
	if ( - (integer) shortfall > curactivewidth [6 ]) 
	b = 10001 ;
	else b = badness ( - (integer) shortfall , curactivewidth [6 ]) ;
	if ( b > 12 ) 
	fitclass = 3 ;
	else fitclass = 2 ;
      } 
      if ( dolastlinefit ) 
      {
	if ( curp == -268435455L ) 
	shortfall = 0 ;
	if ( shortfall > 0 ) 
	g = curactivewidth [2 ];
	else if ( shortfall < 0 ) 
	g = curactivewidth [6 ];
	else g = 0 ;
      } 
      lab40: if ( ( b > 10000 ) || ( pi == -10000 ) ) 
      {
	if ( finalpass && ( minimumdemerits == 1073741823L ) && ( mem [r ]
	.hh .v.RH == memtop - 7 ) && ( prevr == memtop - 7 ) ) 
	artificialdemerits = true ;
	else if ( b > threshold ) 
	goto lab60 ;
	noderstaysactive = false ;
      } 
      else {
	  
	prevr = r ;
	if ( b > threshold ) 
	goto lab22 ;
	noderstaysactive = true ;
      } 
      if ( artificialdemerits ) 
      d = 0 ;
      else {
	  
	d = eqtb [7892266L ].cint + b ;
	if ( abs ( d ) >= 10000 ) 
	d = 100000000L ;
	else d = d * d ;
	if ( pi != 0 ) {
	    
	  if ( pi > 0 ) 
	  d = d + pi * pi ;
	  else if ( pi > -10000 ) 
	  d = d - pi * pi ;
	} 
	if ( ( breaktype == 1 ) && ( mem [r ].hh.b0 == 1 ) ) {
	    
	  if ( curp != -268435455L ) 
	  d = d + eqtb [7892278L ].cint ;
	  else d = d + eqtb [7892279L ].cint ;
	} 
	if ( abs ( fitclass - mem [r ].hh.b1 ) > 1 ) 
	d = d + eqtb [7892280L ].cint ;
      } 
	;
#ifdef STAT
      if ( eqtb [7892296L ].cint > 0 ) 
      {
	if ( printednode != curp ) 
	{
	  printnl ( 65545L ) ;
	  if ( curp == -268435455L ) 
	  shortdisplay ( mem [printednode ].hh .v.RH ) ;
	  else {
	      
	    savelink = mem [curp ].hh .v.RH ;
	    mem [curp ].hh .v.RH = -268435455L ;
	    printnl ( 65545L ) ;
	    shortdisplay ( mem [printednode ].hh .v.RH ) ;
	    mem [curp ].hh .v.RH = savelink ;
	  } 
	  printednode = curp ;
	} 
	printnl ( 64 ) ;
	if ( curp == -268435455L ) 
	printesc ( 65927L ) ;
	else if ( mem [curp ].hh.b0 != 10 ) 
	{
	  if ( mem [curp ].hh.b0 == 12 ) 
	  printesc ( 65854L ) ;
	  else if ( mem [curp ].hh.b0 == 7 ) 
	  printesc ( 65640L ) ;
	  else if ( mem [curp ].hh.b0 == 11 ) 
	  printesc ( 65605L ) ;
	  else printesc ( 65634L ) ;
	} 
	print ( 66364L ) ;
	if ( mem [r + 1 ].hh .v.RH == -268435455L ) 
	printchar ( 48 ) ;
	else printint ( mem [mem [r + 1 ].hh .v.RH ].hh .v.LH ) ;
	print ( 66365L ) ;
	if ( b > 10000 ) 
	printchar ( 42 ) ;
	else printint ( b ) ;
	print ( 66366L ) ;
	printint ( pi ) ;
	print ( 66367L ) ;
	if ( artificialdemerits ) 
	printchar ( 42 ) ;
	else printint ( d ) ;
      } 
#endif /* STAT */
      d = d + mem [r + 2 ].cint ;
      if ( d <= minimaldemerits [fitclass ]) 
      {
	minimaldemerits [fitclass ]= d ;
	bestplace [fitclass ]= mem [r + 1 ].hh .v.RH ;
	bestplline [fitclass ]= l ;
	if ( dolastlinefit ) 
	{
	  bestplshort [fitclass ]= shortfall ;
	  bestplglue [fitclass ]= g ;
	} 
	if ( d < minimumdemerits ) 
	minimumdemerits = d ;
      } 
      if ( noderstaysactive ) 
      goto lab22 ;
      lab60: mem [prevr ].hh .v.RH = mem [r ].hh .v.RH ;
      freenode ( r , activenodesize ) ;
      if ( prevr == memtop - 7 ) 
      {
	r = mem [memtop - 7 ].hh .v.RH ;
	if ( mem [r ].hh.b0 == 2 ) 
	{
	  activewidth [1 ]= activewidth [1 ]+ mem [r + 1 ].cint ;
	  activewidth [2 ]= activewidth [2 ]+ mem [r + 2 ].cint ;
	  activewidth [3 ]= activewidth [3 ]+ mem [r + 3 ].cint ;
	  activewidth [4 ]= activewidth [4 ]+ mem [r + 4 ].cint ;
	  activewidth [5 ]= activewidth [5 ]+ mem [r + 5 ].cint ;
	  activewidth [6 ]= activewidth [6 ]+ mem [r + 6 ].cint ;
	  curactivewidth [1 ]= activewidth [1 ];
	  curactivewidth [2 ]= activewidth [2 ];
	  curactivewidth [3 ]= activewidth [3 ];
	  curactivewidth [4 ]= activewidth [4 ];
	  curactivewidth [5 ]= activewidth [5 ];
	  curactivewidth [6 ]= activewidth [6 ];
	  mem [memtop - 7 ].hh .v.RH = mem [r ].hh .v.RH ;
	  freenode ( r , 7 ) ;
	} 
      } 
      else if ( mem [prevr ].hh.b0 == 2 ) 
      {
	r = mem [prevr ].hh .v.RH ;
	if ( r == memtop - 7 ) 
	{
	  curactivewidth [1 ]= curactivewidth [1 ]- mem [prevr + 1 ]
	  .cint ;
	  curactivewidth [2 ]= curactivewidth [2 ]- mem [prevr + 2 ]
	  .cint ;
	  curactivewidth [3 ]= curactivewidth [3 ]- mem [prevr + 3 ]
	  .cint ;
	  curactivewidth [4 ]= curactivewidth [4 ]- mem [prevr + 4 ]
	  .cint ;
	  curactivewidth [5 ]= curactivewidth [5 ]- mem [prevr + 5 ]
	  .cint ;
	  curactivewidth [6 ]= curactivewidth [6 ]- mem [prevr + 6 ]
	  .cint ;
	  mem [prevprevr ].hh .v.RH = memtop - 7 ;
	  freenode ( prevr , 7 ) ;
	  prevr = prevprevr ;
	} 
	else if ( mem [r ].hh.b0 == 2 ) 
	{
	  curactivewidth [1 ]= curactivewidth [1 ]+ mem [r + 1 ].cint ;
	  curactivewidth [2 ]= curactivewidth [2 ]+ mem [r + 2 ].cint ;
	  curactivewidth [3 ]= curactivewidth [3 ]+ mem [r + 3 ].cint ;
	  curactivewidth [4 ]= curactivewidth [4 ]+ mem [r + 4 ].cint ;
	  curactivewidth [5 ]= curactivewidth [5 ]+ mem [r + 5 ].cint ;
	  curactivewidth [6 ]= curactivewidth [6 ]+ mem [r + 6 ].cint ;
	  mem [prevr + 1 ].cint = mem [prevr + 1 ].cint + mem [r + 1 ]
	  .cint ;
	  mem [prevr + 2 ].cint = mem [prevr + 2 ].cint + mem [r + 2 ]
	  .cint ;
	  mem [prevr + 3 ].cint = mem [prevr + 3 ].cint + mem [r + 3 ]
	  .cint ;
	  mem [prevr + 4 ].cint = mem [prevr + 4 ].cint + mem [r + 4 ]
	  .cint ;
	  mem [prevr + 5 ].cint = mem [prevr + 5 ].cint + mem [r + 5 ]
	  .cint ;
	  mem [prevr + 6 ].cint = mem [prevr + 6 ].cint + mem [r + 6 ]
	  .cint ;
	  mem [prevr ].hh .v.RH = mem [r ].hh .v.RH ;
	  freenode ( r , 7 ) ;
	} 
      } 
    } 
  } 
  lab10: 
	;
#ifdef STAT
  if ( curp == printednode ) {
      
    if ( curp != -268435455L ) {
	
      if ( mem [curp ].hh.b0 == 7 ) 
      {
	t = mem [curp ].hh.b1 ;
	while ( t > 0 ) {
	    
	  decr ( t ) ;
	  printednode = mem [printednode ].hh .v.RH ;
	} 
      } 
#endif /* STAT */
    } 
  } 
} 
void 
zpostlinebreak ( boolean d ) 
{
  /* 30 31 */ postlinebreak_regmem 
  halfword q, r, s  ;
  halfword p, k  ;
  scaled w  ;
  boolean gluebreak  ;
  halfword ptmp  ;
  boolean discbreak  ;
  boolean postdiscbreak  ;
  scaled curwidth  ;
  scaled curindent  ;
  quarterword t  ;
  integer pen  ;
  halfword curline  ;
  halfword LRptr  ;
  LRptr = curlist .eTeXauxfield ;
  q = mem [bestbet + 1 ].hh .v.RH ;
  curp = -268435455L ;
  do {
      r = q ;
    q = mem [q + 1 ].hh .v.LH ;
    mem [r + 1 ].hh .v.LH = curp ;
    curp = r ;
  } while ( ! ( q == -268435455L ) ) ;
  curline = curlist .pgfield + 1 ;
  do {
      if ( ( eqtb [7892339L ].cint > 0 ) ) 
    {
      q = mem [memtop - 3 ].hh .v.RH ;
      if ( LRptr != -268435455L ) 
      {
	tempptr = LRptr ;
	r = q ;
	do {
	    s = newmath ( 0 , ( mem [tempptr ].hh .v.LH - 1 ) ) ;
	  mem [s ].hh .v.RH = r ;
	  r = s ;
	  tempptr = mem [tempptr ].hh .v.RH ;
	} while ( ! ( tempptr == -268435455L ) ) ;
	mem [memtop - 3 ].hh .v.RH = r ;
      } 
      while ( q != mem [curp + 1 ].hh .v.RH ) {
	  
	if ( ! ( q >= himemmin ) ) {
	    
	  if ( mem [q ].hh.b0 == 9 ) {
	      
	    if ( odd ( mem [q ].hh.b1 ) ) 
	    {
	      if ( LRptr != -268435455L ) {
		  
		if ( mem [LRptr ].hh .v.LH == ( 4 * ( mem [q ].hh.b1 / 4 ) 
		+ 3 ) ) 
		{
		  tempptr = LRptr ;
		  LRptr = mem [tempptr ].hh .v.RH ;
		  {
		    mem [tempptr ].hh .v.RH = avail ;
		    avail = tempptr ;
	;
#ifdef STAT
		    decr ( dynused ) ;
#endif /* STAT */
		  } 
		} 
	      } 
	    } 
	    else {
		
	      tempptr = getavail () ;
	      mem [tempptr ].hh .v.LH = ( 4 * ( mem [q ].hh.b1 / 4 ) + 3 ) 
	      ;
	      mem [tempptr ].hh .v.RH = LRptr ;
	      LRptr = tempptr ;
	    } 
	  } 
	} 
	q = mem [q ].hh .v.RH ;
      } 
    } 
    q = mem [curp + 1 ].hh .v.RH ;
    discbreak = false ;
    postdiscbreak = false ;
    gluebreak = false ;
    if ( q != -268435455L ) {
	
      if ( mem [q ].hh.b0 == 10 ) 
      {
	deleteglueref ( mem [q + 1 ].hh .v.LH ) ;
	mem [q + 1 ].hh .v.LH = eqtb [1205772L ].hh .v.RH ;
	mem [q ].hh.b1 = 9 ;
	incr ( mem [eqtb [1205772L ].hh .v.RH ].hh .v.RH ) ;
	gluebreak = true ;
	goto lab30 ;
      } 
      else {
	  
	if ( mem [q ].hh.b0 == 7 ) 
	{
	  t = mem [q ].hh.b1 ;
	  if ( t == 0 ) 
	  r = mem [q ].hh .v.RH ;
	  else {
	      
	    r = q ;
	    while ( t > 1 ) {
		
	      r = mem [r ].hh .v.RH ;
	      decr ( t ) ;
	    } 
	    s = mem [r ].hh .v.RH ;
	    r = mem [s ].hh .v.RH ;
	    mem [s ].hh .v.RH = -268435455L ;
	    flushnodelist ( mem [q ].hh .v.RH ) ;
	    mem [q ].hh.b1 = 0 ;
	  } 
	  if ( mem [q + 1 ].hh .v.RH != -268435455L ) 
	  {
	    s = mem [q + 1 ].hh .v.RH ;
	    while ( mem [s ].hh .v.RH != -268435455L ) s = mem [s ].hh 
	    .v.RH ;
	    mem [s ].hh .v.RH = r ;
	    r = mem [q + 1 ].hh .v.RH ;
	    mem [q + 1 ].hh .v.RH = -268435455L ;
	    postdiscbreak = true ;
	  } 
	  if ( mem [q + 1 ].hh .v.LH != -268435455L ) 
	  {
	    s = mem [q + 1 ].hh .v.LH ;
	    mem [q ].hh .v.RH = s ;
	    while ( mem [s ].hh .v.RH != -268435455L ) s = mem [s ].hh 
	    .v.RH ;
	    mem [q + 1 ].hh .v.LH = -268435455L ;
	    q = s ;
	  } 
	  mem [q ].hh .v.RH = r ;
	  discbreak = true ;
	} 
	else if ( mem [q ].hh.b0 == 11 ) 
	mem [q + 1 ].cint = 0 ;
	else if ( mem [q ].hh.b0 == 9 ) 
	{
	  mem [q + 1 ].cint = 0 ;
	  if ( ( eqtb [7892339L ].cint > 0 ) ) {
	      
	    if ( odd ( mem [q ].hh.b1 ) ) 
	    {
	      if ( LRptr != -268435455L ) {
		  
		if ( mem [LRptr ].hh .v.LH == ( 4 * ( mem [q ].hh.b1 / 4 ) 
		+ 3 ) ) 
		{
		  tempptr = LRptr ;
		  LRptr = mem [tempptr ].hh .v.RH ;
		  {
		    mem [tempptr ].hh .v.RH = avail ;
		    avail = tempptr ;
	;
#ifdef STAT
		    decr ( dynused ) ;
#endif /* STAT */
		  } 
		} 
	      } 
	    } 
	    else {
		
	      tempptr = getavail () ;
	      mem [tempptr ].hh .v.LH = ( 4 * ( mem [q ].hh.b1 / 4 ) + 3 ) 
	      ;
	      mem [tempptr ].hh .v.RH = LRptr ;
	      LRptr = tempptr ;
	    } 
	  } 
	} 
      } 
    } 
    else {
	
      q = memtop - 3 ;
      while ( mem [q ].hh .v.RH != -268435455L ) q = mem [q ].hh .v.RH ;
    } 
    lab30: if ( eqtb [7892338L ].cint > 0 ) 
    {
      if ( discbreak && ( ( q >= himemmin ) || ( mem [q ].hh.b0 != 7 ) ) ) 
      {
	p = q ;
	ptmp = p ;
      } 
      else {
	  
	p = prevrightmost ( mem [memtop - 3 ].hh .v.RH , q ) ;
	ptmp = p ;
	p = findprotcharright ( mem [memtop - 3 ].hh .v.RH , p ) ;
      } 
      w = charpw ( p , 1 ) ;
      if ( w != 0 ) 
      {
	k = newmarginkern ( - (integer) w , lastrightmostchar , 1 ) ;
	mem [k ].hh .v.RH = mem [ptmp ].hh .v.RH ;
	mem [ptmp ].hh .v.RH = k ;
	if ( ( ptmp == q ) ) 
	q = mem [q ].hh .v.RH ;
      } 
    } 
    if ( ! gluebreak ) 
    {
      r = newparamglue ( 8 ) ;
      mem [r ].hh .v.RH = mem [q ].hh .v.RH ;
      mem [q ].hh .v.RH = r ;
      q = r ;
    } 
    if ( ( eqtb [7892339L ].cint > 0 ) ) {
	
      if ( LRptr != -268435455L ) 
      {
	s = memtop - 3 ;
	r = mem [s ].hh .v.RH ;
	while ( r != q ) {
	    
	  s = r ;
	  r = mem [s ].hh .v.RH ;
	} 
	r = LRptr ;
	while ( r != -268435455L ) {
	    
	  tempptr = newmath ( 0 , mem [r ].hh .v.LH ) ;
	  mem [s ].hh .v.RH = tempptr ;
	  s = tempptr ;
	  r = mem [r ].hh .v.RH ;
	} 
	mem [s ].hh .v.RH = q ;
      } 
    } 
    r = mem [q ].hh .v.RH ;
    mem [q ].hh .v.RH = -268435455L ;
    q = mem [memtop - 3 ].hh .v.RH ;
    mem [memtop - 3 ].hh .v.RH = r ;
    if ( eqtb [7892338L ].cint > 0 ) 
    {
      p = q ;
      p = findprotcharleft ( p , false ) ;
      w = charpw ( p , 0 ) ;
      if ( w != 0 ) 
      {
	k = newmarginkern ( - (integer) w , lastleftmostchar , 0 ) ;
	mem [k ].hh .v.RH = q ;
	q = k ;
      } 
    } 
    if ( eqtb [1205771L ].hh .v.RH != membot ) 
    {
      r = newparamglue ( 7 ) ;
      mem [r ].hh .v.RH = q ;
      q = r ;
    } 
    if ( curline > lastspecialline ) 
    {
      curwidth = secondwidth ;
      curindent = secondindent ;
    } 
    else if ( eqtb [1206295L ].hh .v.RH == -268435455L ) 
    {
      curwidth = firstwidth ;
      curindent = firstindent ;
    } 
    else {
	
      curwidth = mem [eqtb [1206295L ].hh .v.RH + 2 * curline ].cint ;
      curindent = mem [eqtb [1206295L ].hh .v.RH + 2 * curline - 1 ].cint 
      ;
    } 
    adjusttail = memtop - 5 ;
    preadjusttail = memtop - 14 ;
    justbox = hpack ( q , curwidth , 0 ) ;
    mem [justbox + 4 ].cint = curindent ;
    if ( memtop - 14 != preadjusttail ) 
    {
      mem [curlist .tailfield ].hh .v.RH = mem [memtop - 14 ].hh .v.RH ;
      curlist .tailfield = preadjusttail ;
    } 
    preadjusttail = -268435455L ;
    appendtovlist ( justbox ) ;
    if ( memtop - 5 != adjusttail ) 
    {
      mem [curlist .tailfield ].hh .v.RH = mem [memtop - 5 ].hh .v.RH ;
      curlist .tailfield = adjusttail ;
    } 
    adjusttail = -268435455L ;
    if ( curline + 1 != bestline ) 
    {
      q = eqtb [1206563L ].hh .v.RH ;
      if ( q != -268435455L ) 
      {
	r = curline ;
	if ( r > mem [q + 1 ].cint ) 
	r = mem [q + 1 ].cint ;
	pen = mem [q + r + 1 ].cint ;
      } 
      else pen = eqtb [7892277L ].cint ;
      q = eqtb [1206564L ].hh .v.RH ;
      if ( q != -268435455L ) 
      {
	r = curline - curlist .pgfield ;
	if ( r > mem [q + 1 ].cint ) 
	r = mem [q + 1 ].cint ;
	pen = pen + mem [q + r + 1 ].cint ;
      } 
      else if ( curline == curlist .pgfield + 1 ) 
      pen = pen + eqtb [7892269L ].cint ;
      if ( d ) 
      q = eqtb [1206566L ].hh .v.RH ;
      else q = eqtb [1206565L ].hh .v.RH ;
      if ( q != -268435455L ) 
      {
	r = bestline - curline - 1 ;
	if ( r > mem [q + 1 ].cint ) 
	r = mem [q + 1 ].cint ;
	pen = pen + mem [q + r + 1 ].cint ;
      } 
      else if ( curline + 2 == bestline ) {
	  
	if ( d ) 
	pen = pen + eqtb [7892271L ].cint ;
	else pen = pen + eqtb [7892270L ].cint ;
      } 
      if ( discbreak ) 
      pen = pen + eqtb [7892272L ].cint ;
      if ( pen != 0 ) 
      {
	r = newpenalty ( pen ) ;
	mem [curlist .tailfield ].hh .v.RH = r ;
	curlist .tailfield = r ;
      } 
    } 
    incr ( curline ) ;
    curp = mem [curp + 1 ].hh .v.LH ;
    if ( curp != -268435455L ) {
	
      if ( ! postdiscbreak ) 
      {
	r = memtop - 3 ;
	while ( true ) {
	    
	  q = mem [r ].hh .v.RH ;
	  if ( q == mem [curp + 1 ].hh .v.RH ) 
	  goto lab31 ;
	  if ( ( q >= himemmin ) ) 
	  goto lab31 ;
	  if ( ( mem [q ].hh.b0 < 9 ) ) 
	  goto lab31 ;
	  if ( mem [q ].hh.b0 == 11 ) {
	      
	    if ( ( mem [q ].hh.b1 != 1 ) && ( mem [q ].hh.b1 != 3 ) ) 
	    goto lab31 ;
	  } 
	  r = q ;
	  if ( mem [q ].hh.b0 == 9 ) {
	      
	    if ( ( eqtb [7892339L ].cint > 0 ) ) {
		
	      if ( odd ( mem [q ].hh.b1 ) ) 
	      {
		if ( LRptr != -268435455L ) {
		    
		  if ( mem [LRptr ].hh .v.LH == ( 4 * ( mem [q ].hh.b1 / 4 
		  ) + 3 ) ) 
		  {
		    tempptr = LRptr ;
		    LRptr = mem [tempptr ].hh .v.RH ;
		    {
		      mem [tempptr ].hh .v.RH = avail ;
		      avail = tempptr ;
	;
#ifdef STAT
		      decr ( dynused ) ;
#endif /* STAT */
		    } 
		  } 
		} 
	      } 
	      else {
		  
		tempptr = getavail () ;
		mem [tempptr ].hh .v.LH = ( 4 * ( mem [q ].hh.b1 / 4 ) + 3 
		) ;
		mem [tempptr ].hh .v.RH = LRptr ;
		LRptr = tempptr ;
	      } 
	    } 
	  } 
	} 
	lab31: if ( r != memtop - 3 ) 
	{
	  mem [r ].hh .v.RH = -268435455L ;
	  flushnodelist ( mem [memtop - 3 ].hh .v.RH ) ;
	  mem [memtop - 3 ].hh .v.RH = q ;
	} 
      } 
    } 
  } while ( ! ( curp == -268435455L ) ) ;
  if ( ( curline != bestline ) || ( mem [memtop - 3 ].hh .v.RH != 
  -268435455L ) ) 
  confusion ( 66376L ) ;
  curlist .pgfield = bestline - 1 ;
  curlist .eTeXauxfield = LRptr ;
} 
smallnumber 
zreconstitute ( smallnumber j , smallnumber n , halfword bchar , halfword 
hchar ) 
{
  /* 22 30 */ register smallnumber Result; reconstitute_regmem 
  halfword p  ;
  halfword t  ;
  fourquarters q  ;
  halfword currh  ;
  halfword testchar  ;
  scaled w  ;
  fontindex k  ;
  hyphenpassed = 0 ;
  t = memtop - 4 ;
  w = 0 ;
  mem [memtop - 4 ].hh .v.RH = -268435455L ;
  curl = hu [j ];
  curq = t ;
  if ( j == 0 ) 
  {
    ligaturepresent = initlig ;
    p = initlist ;
    if ( ligaturepresent ) 
    lfthit = initlft ;
    while ( p > -268435455L ) {
	
      {
	mem [t ].hh .v.RH = getavail () ;
	t = mem [t ].hh .v.RH ;
	mem [t ].hh.b0 = hf ;
	mem [t ].hh.b1 = mem [p ].hh.b1 ;
      } 
      p = mem [p ].hh .v.RH ;
    } 
  } 
  else if ( curl < 65536L ) 
  {
    mem [t ].hh .v.RH = getavail () ;
    t = mem [t ].hh .v.RH ;
    mem [t ].hh.b0 = hf ;
    mem [t ].hh.b1 = curl ;
  } 
  ligstack = -268435455L ;
  {
    if ( j < n ) 
    curr = hu [j + 1 ];
    else curr = bchar ;
    if ( odd ( hyf [j ]) ) 
    currh = hchar ;
    else currh = 65536L ;
  } 
  lab22: if ( curl == 65536L ) 
  {
    k = bcharlabel [hf ];
    if ( k == 0 ) 
    goto lab30 ;
    else q = fontinfo [k ].qqqq ;
  } 
  else {
      
    q = fontinfo [charbase [hf ]+ effectivechar ( true , hf , curl ) ]
    .qqqq ;
    if ( ( ( q .b2 ) % 4 ) != 1 ) 
    goto lab30 ;
    k = ligkernbase [hf ]+ q .b3 ;
    q = fontinfo [k ].qqqq ;
    if ( q .b0 > 128 ) 
    {
      k = ligkernbase [hf ]+ 256 * q .b2 + q .b3 + 32768L - 256 * ( 128 ) ;
      q = fontinfo [k ].qqqq ;
    } 
  } 
  if ( currh < 65536L ) 
  testchar = currh ;
  else testchar = curr ;
  while ( true ) {
      
    if ( q .b1 == testchar ) {
	
      if ( q .b0 <= 128 ) {
	  
	if ( currh < 65536L ) 
	{
	  hyphenpassed = j ;
	  hchar = 65536L ;
	  currh = 65536L ;
	  goto lab22 ;
	} 
	else {
	    
	  if ( hchar < 65536L ) {
	      
	    if ( odd ( hyf [j ]) ) 
	    {
	      hyphenpassed = j ;
	      hchar = 65536L ;
	    } 
	  } 
	  if ( q .b2 < 128 ) 
	  {
	    if ( curl == 65536L ) 
	    lfthit = true ;
	    if ( j == n ) {
		
	      if ( ligstack == -268435455L ) 
	      rthit = true ;
	    } 
	    {
	      if ( interrupt != 0 ) 
	      pauseforinstructions () ;
	    } 
	    switch ( q .b2 ) 
	    {case 1 : 
	    case 5 : 
	      {
		curl = q .b3 ;
		ligaturepresent = true ;
	      } 
	      break ;
	    case 2 : 
	    case 6 : 
	      {
		curr = q .b3 ;
		if ( ligstack > -268435455L ) 
		mem [ligstack ].hh.b1 = curr ;
		else {
		    
		  ligstack = newligitem ( curr ) ;
		  if ( j == n ) 
		  bchar = 65536L ;
		  else {
		      
		    p = getavail () ;
		    mem [ligstack + 1 ].hh .v.RH = p ;
		    mem [p ].hh.b1 = hu [j + 1 ];
		    mem [p ].hh.b0 = hf ;
		  } 
		} 
	      } 
	      break ;
	    case 3 : 
	      {
		curr = q .b3 ;
		p = ligstack ;
		ligstack = newligitem ( curr ) ;
		mem [ligstack ].hh .v.RH = p ;
	      } 
	      break ;
	    case 7 : 
	    case 11 : 
	      {
		if ( ligaturepresent ) 
		{
		  p = newligature ( hf , curl , mem [curq ].hh .v.RH ) ;
		  if ( lfthit ) 
		  {
		    mem [p ].hh.b1 = 2 ;
		    lfthit = false ;
		  } 
		  if ( false ) {
		      
		    if ( ligstack == -268435455L ) 
		    {
		      incr ( mem [p ].hh.b1 ) ;
		      rthit = false ;
		    } 
		  } 
		  mem [curq ].hh .v.RH = p ;
		  t = p ;
		  ligaturepresent = false ;
		} 
		curq = t ;
		curl = q .b3 ;
		ligaturepresent = true ;
	      } 
	      break ;
	      default: 
	      {
		curl = q .b3 ;
		ligaturepresent = true ;
		if ( ligstack > -268435455L ) 
		{
		  if ( mem [ligstack + 1 ].hh .v.RH > -268435455L ) 
		  {
		    mem [t ].hh .v.RH = mem [ligstack + 1 ].hh .v.RH ;
		    t = mem [t ].hh .v.RH ;
		    incr ( j ) ;
		  } 
		  p = ligstack ;
		  ligstack = mem [p ].hh .v.RH ;
		  freenode ( p , 2 ) ;
		  if ( ligstack == -268435455L ) 
		  {
		    if ( j < n ) 
		    curr = hu [j + 1 ];
		    else curr = bchar ;
		    if ( odd ( hyf [j ]) ) 
		    currh = hchar ;
		    else currh = 65536L ;
		  } 
		  else curr = mem [ligstack ].hh.b1 ;
		} 
		else if ( j == n ) 
		goto lab30 ;
		else {
		    
		  {
		    mem [t ].hh .v.RH = getavail () ;
		    t = mem [t ].hh .v.RH ;
		    mem [t ].hh.b0 = hf ;
		    mem [t ].hh.b1 = curr ;
		  } 
		  incr ( j ) ;
		  {
		    if ( j < n ) 
		    curr = hu [j + 1 ];
		    else curr = bchar ;
		    if ( odd ( hyf [j ]) ) 
		    currh = hchar ;
		    else currh = 65536L ;
		  } 
		} 
	      } 
	      break ;
	    } 
	    if ( q .b2 > 4 ) {
		
	      if ( q .b2 != 7 ) 
	      goto lab30 ;
	    } 
	    goto lab22 ;
	  } 
	  w = fontinfo [kernbase [hf ]+ 256 * q .b2 + q .b3 ].cint ;
	  goto lab30 ;
	} 
      } 
    } 
    if ( q .b0 >= 128 ) {
	
      if ( currh == 65536L ) 
      goto lab30 ;
      else {
	  
	currh = 65536L ;
	goto lab22 ;
      } 
    } 
    k = k + q .b0 + 1 ;
    q = fontinfo [k ].qqqq ;
  } 
  lab30: ;
  if ( ligaturepresent ) 
  {
    p = newligature ( hf , curl , mem [curq ].hh .v.RH ) ;
    if ( lfthit ) 
    {
      mem [p ].hh.b1 = 2 ;
      lfthit = false ;
    } 
    if ( rthit ) {
	
      if ( ligstack == -268435455L ) 
      {
	incr ( mem [p ].hh.b1 ) ;
	rthit = false ;
      } 
    } 
    mem [curq ].hh .v.RH = p ;
    t = p ;
    ligaturepresent = false ;
  } 
  if ( w != 0 ) 
  {
    mem [t ].hh .v.RH = newkern ( w ) ;
    t = mem [t ].hh .v.RH ;
    w = 0 ;
    mem [t + 2 ].hh .v.LH = 0 ;
  } 
  if ( ligstack > -268435455L ) 
  {
    curq = t ;
    curl = mem [ligstack ].hh.b1 ;
    ligaturepresent = true ;
    {
      if ( mem [ligstack + 1 ].hh .v.RH > -268435455L ) 
      {
	mem [t ].hh .v.RH = mem [ligstack + 1 ].hh .v.RH ;
	t = mem [t ].hh .v.RH ;
	incr ( j ) ;
      } 
      p = ligstack ;
      ligstack = mem [p ].hh .v.RH ;
      freenode ( p , 2 ) ;
      if ( ligstack == -268435455L ) 
      {
	if ( j < n ) 
	curr = hu [j + 1 ];
	else curr = bchar ;
	if ( odd ( hyf [j ]) ) 
	currh = hchar ;
	else currh = 65536L ;
      } 
      else curr = mem [ligstack ].hh.b1 ;
    } 
    goto lab22 ;
  } 
  Result = j ;
  return Result ;
} 
void 
hyphenate ( void ) 
{
  /* 50 30 40 41 42 45 10 */ hyphenate_regmem 
  short i, j, l  ;
  halfword q, r, s  ;
  halfword bchar  ;
  halfword majortail, minortail  ;
  UnicodeScalar c  ;
  short cloc  ;
  integer rcount  ;
  halfword hyfnode  ;
  triepointer z  ;
  integer v  ;
  hyphpointer h  ;
  strnumber k  ;
  poolpointer u  ;
  {register integer for_end; j = 0 ;for_end = hn ; if ( j <= for_end) do 
    hyf [j ]= 0 ;
  while ( j++ < for_end ) ;} 
  h = hc [1 ];
  incr ( hn ) ;
  hc [hn ]= curlang ;
  {register integer for_end; j = 2 ;for_end = hn ; if ( j <= for_end) do 
    h = ( h + h + hc [j ]) % 607 ;
  while ( j++ < for_end ) ;} 
  while ( true ) {
      
    k = hyphword [h ];
    if ( k == 0 ) 
    goto lab45 ;
    if ( length ( k ) == hn ) 
    {
      j = 1 ;
      u = strstart [( k ) - 65536L ];
      do {
	  if ( strpool [u ]!= hc [j ]) 
	goto lab30 ;
	incr ( j ) ;
	incr ( u ) ;
      } while ( ! ( j > hn ) ) ;
      s = hyphlist [h ];
      while ( s != -268435455L ) {
	  
	hyf [mem [s ].hh .v.LH ]= 1 ;
	s = mem [s ].hh .v.RH ;
      } 
      decr ( hn ) ;
      goto lab40 ;
    } 
    lab30: ;
    h = hyphlink [h ];
    if ( h == 0 ) 
    goto lab45 ;
    decr ( h ) ;
  } 
  lab45: decr ( hn ) ;
  if ( trietrc [curlang + 1 ]!= curlang ) 
  return ;
  hc [0 ]= 0 ;
  hc [hn + 1 ]= 0 ;
  hc [hn + 2 ]= maxhyphchar ;
  {register integer for_end; j = 0 ;for_end = hn - rhyf + 1 ; if ( j <= 
  for_end) do 
    {
      z = trietrl [curlang + 1 ]+ hc [j ];
      l = j ;
      while ( hc [l ]== trietrc [z ]) {
	  
	if ( trietro [z ]!= mintrieop ) 
	{
	  v = trietro [z ];
	  do {
	      v = v + opstart [curlang ];
	    i = l - hyfdistance [v ];
	    if ( hyfnum [v ]> hyf [i ]) 
	    hyf [i ]= hyfnum [v ];
	    v = hyfnext [v ];
	  } while ( ! ( v == mintrieop ) ) ;
	} 
	incr ( l ) ;
	z = trietrl [z ]+ hc [l ];
      } 
    } 
  while ( j++ < for_end ) ;} 
  lab40: {
      register integer for_end; j = 0 ;for_end = lhyf - 1 ; if ( j <= 
  for_end) do 
    hyf [j ]= 0 ;
  while ( j++ < for_end ) ;} 
  {register integer for_end; j = 0 ;for_end = rhyf - 1 ; if ( j <= for_end) 
  do 
    hyf [hn - j ]= 0 ;
  while ( j++ < for_end ) ;} 
  {register integer for_end; j = lhyf ;for_end = hn - rhyf ; if ( j <= 
  for_end) do 
    if ( odd ( hyf [j ]) ) 
    goto lab41 ;
  while ( j++ < for_end ) ;} 
  return ;
  lab41: ;
  if ( ( ( ( ha ) != -268435455L ) && ( ! ( ha >= himemmin ) ) && ( mem [ha ]
  .hh.b0 == 8 ) && ( ( ( mem [ha ].hh.b1 >= 40 ) && ( mem [ha ].hh.b1 <= 
  41 ) ) ) ) ) 
  {
    s = curp ;
    while ( mem [s ].hh .v.RH != ha ) s = mem [s ].hh .v.RH ;
    hyphenpassed = 0 ;
    {register integer for_end; j = lhyf ;for_end = hn - rhyf ; if ( j <= 
    for_end) do 
      {
	if ( odd ( hyf [j ]) ) 
	{
	  q = newnativewordnode ( hf , j - hyphenpassed ) ;
	  mem [q ].hh.b1 = mem [ha ].hh.b1 ;
	  {register integer for_end; i = 0 ;for_end = j - hyphenpassed - 1 
	  ; if ( i <= for_end) do 
	    setnativechar ( q , i , getnativechar ( ha , i + hyphenpassed ) ) 
	    ;
	  while ( i++ < for_end ) ;} 
	  setnativemetrics ( q , ( eqtb [7892342L ].cint > 0 ) ) ;
	  mem [s ].hh .v.RH = q ;
	  s = q ;
	  q = newdisc () ;
	  mem [q + 1 ].hh .v.LH = newnativecharacter ( hf , hyfchar ) ;
	  mem [s ].hh .v.RH = q ;
	  s = q ;
	  hyphenpassed = j ;
	} 
      } 
    while ( j++ < for_end ) ;} 
    hn = mem [ha + 4 ].qqqq .b2 ;
    q = newnativewordnode ( hf , hn - hyphenpassed ) ;
    mem [q ].hh.b1 = mem [ha ].hh.b1 ;
    {register integer for_end; i = 0 ;for_end = hn - hyphenpassed - 1 ; if ( 
    i <= for_end) do 
      setnativechar ( q , i , getnativechar ( ha , i + hyphenpassed ) ) ;
    while ( i++ < for_end ) ;} 
    setnativemetrics ( q , ( eqtb [7892342L ].cint > 0 ) ) ;
    mem [s ].hh .v.RH = q ;
    s = q ;
    q = mem [ha ].hh .v.RH ;
    mem [s ].hh .v.RH = q ;
    mem [ha ].hh .v.RH = -268435455L ;
    flushnodelist ( ha ) ;
  } 
  else {
      
    q = mem [hb ].hh .v.RH ;
    mem [hb ].hh .v.RH = -268435455L ;
    r = mem [ha ].hh .v.RH ;
    mem [ha ].hh .v.RH = -268435455L ;
    bchar = hyfbchar ;
    if ( ( ha >= himemmin ) ) {
	
      if ( mem [ha ].hh.b0 != hf ) 
      goto lab42 ;
      else {
	  
	initlist = ha ;
	initlig = false ;
	hu [0 ]= mem [ha ].hh.b1 ;
      } 
    } 
    else if ( mem [ha ].hh.b0 == 6 ) {
	
      if ( mem [ha + 1 ].hh.b0 != hf ) 
      goto lab42 ;
      else {
	  
	initlist = mem [ha + 1 ].hh .v.RH ;
	initlig = true ;
	initlft = ( mem [ha ].hh.b1 > 1 ) ;
	hu [0 ]= mem [ha + 1 ].hh.b1 ;
	if ( initlist == -268435455L ) {
	    
	  if ( initlft ) 
	  {
	    hu [0 ]= maxhyphchar ;
	    initlig = false ;
	  } 
	} 
	freenode ( ha , 2 ) ;
      } 
    } 
    else {
	
      if ( ! ( r >= himemmin ) ) {
	  
	if ( mem [r ].hh.b0 == 6 ) {
	    
	  if ( mem [r ].hh.b1 > 1 ) 
	  goto lab42 ;
	} 
      } 
      j = 1 ;
      s = ha ;
      initlist = -268435455L ;
      goto lab50 ;
    } 
    s = curp ;
    while ( mem [s ].hh .v.RH != ha ) s = mem [s ].hh .v.RH ;
    j = 0 ;
    goto lab50 ;
    lab42: s = ha ;
    j = 0 ;
    hu [0 ]= maxhyphchar ;
    initlig = false ;
    initlist = -268435455L ;
    lab50: flushnodelist ( r ) ;
    do {
	l = j ;
      j = reconstitute ( j , hn , bchar , hyfchar ) + 1 ;
      if ( hyphenpassed == 0 ) 
      {
	mem [s ].hh .v.RH = mem [memtop - 4 ].hh .v.RH ;
	while ( mem [s ].hh .v.RH > -268435455L ) s = mem [s ].hh .v.RH ;
	if ( odd ( hyf [j - 1 ]) ) 
	{
	  l = j ;
	  hyphenpassed = j - 1 ;
	  mem [memtop - 4 ].hh .v.RH = -268435455L ;
	} 
      } 
      if ( hyphenpassed > 0 ) 
      do {
	  r = getnode ( 2 ) ;
	mem [r ].hh .v.RH = mem [memtop - 4 ].hh .v.RH ;
	mem [r ].hh.b0 = 7 ;
	majortail = r ;
	rcount = 0 ;
	while ( mem [majortail ].hh .v.RH > -268435455L ) {
	    
	  majortail = mem [majortail ].hh .v.RH ;
	  incr ( rcount ) ;
	} 
	i = hyphenpassed ;
	hyf [i ]= 0 ;
	minortail = -268435455L ;
	mem [r + 1 ].hh .v.LH = -268435455L ;
	hyfnode = newcharacter ( hf , hyfchar ) ;
	if ( hyfnode != -268435455L ) 
	{
	  incr ( i ) ;
	  c = hu [i ];
	  hu [i ]= hyfchar ;
	  {
	    mem [hyfnode ].hh .v.RH = avail ;
	    avail = hyfnode ;
	;
#ifdef STAT
	    decr ( dynused ) ;
#endif /* STAT */
	  } 
	} 
	while ( l <= i ) {
	    
	  l = reconstitute ( l , i , fontbchar [hf ], 65536L ) + 1 ;
	  if ( mem [memtop - 4 ].hh .v.RH > -268435455L ) 
	  {
	    if ( minortail == -268435455L ) 
	    mem [r + 1 ].hh .v.LH = mem [memtop - 4 ].hh .v.RH ;
	    else mem [minortail ].hh .v.RH = mem [memtop - 4 ].hh .v.RH ;
	    minortail = mem [memtop - 4 ].hh .v.RH ;
	    while ( mem [minortail ].hh .v.RH > -268435455L ) minortail = 
	    mem [minortail ].hh .v.RH ;
	  } 
	} 
	if ( hyfnode != -268435455L ) 
	{
	  hu [i ]= c ;
	  l = i ;
	  decr ( i ) ;
	} 
	minortail = -268435455L ;
	mem [r + 1 ].hh .v.RH = -268435455L ;
	cloc = 0 ;
	if ( bcharlabel [hf ]!= 0 ) 
	{
	  decr ( l ) ;
	  c = hu [l ];
	  cloc = l ;
	  hu [l ]= maxhyphchar ;
	} 
	while ( l < j ) {
	    
	  do {
	      l = reconstitute ( l , hn , bchar , 65536L ) + 1 ;
	    if ( cloc > 0 ) 
	    {
	      hu [cloc ]= c ;
	      cloc = 0 ;
	    } 
	    if ( mem [memtop - 4 ].hh .v.RH > -268435455L ) 
	    {
	      if ( minortail == -268435455L ) 
	      mem [r + 1 ].hh .v.RH = mem [memtop - 4 ].hh .v.RH ;
	      else mem [minortail ].hh .v.RH = mem [memtop - 4 ].hh .v.RH 
	      ;
	      minortail = mem [memtop - 4 ].hh .v.RH ;
	      while ( mem [minortail ].hh .v.RH > -268435455L ) minortail = 
	      mem [minortail ].hh .v.RH ;
	    } 
	  } while ( ! ( l >= j ) ) ;
	  while ( l > j ) {
	      
	    j = reconstitute ( j , hn , bchar , 65536L ) + 1 ;
	    mem [majortail ].hh .v.RH = mem [memtop - 4 ].hh .v.RH ;
	    while ( mem [majortail ].hh .v.RH > -268435455L ) {
		
	      majortail = mem [majortail ].hh .v.RH ;
	      incr ( rcount ) ;
	    } 
	  } 
	} 
	if ( rcount > 127 ) 
	{
	  mem [s ].hh .v.RH = mem [r ].hh .v.RH ;
	  mem [r ].hh .v.RH = -268435455L ;
	  flushnodelist ( r ) ;
	} 
	else {
	    
	  mem [s ].hh .v.RH = r ;
	  mem [r ].hh.b1 = rcount ;
	} 
	s = majortail ;
	hyphenpassed = j - 1 ;
	mem [memtop - 4 ].hh .v.RH = -268435455L ;
      } while ( ! ( ! odd ( hyf [j - 1 ]) ) ) ;
    } while ( ! ( j > hn ) ) ;
    mem [s ].hh .v.RH = q ;
    flushlist ( initlist ) ;
  } 
} 
integer 
maxhyphenatablelength ( void ) 
{
  register integer Result; maxhyphenatablelength_regmem 
  if ( eqtb [7892350L ].cint > 4095 ) 
  Result = 4095 ;
  else Result = eqtb [7892350L ].cint ;
  return Result ;
} 
boolean 
zeTeXenabled ( boolean b , quarterword j , halfword k ) 
{
  register boolean Result; eTeXenabled_regmem 
  if ( ! b ) 
  {
    {
      if ( interaction == 3 ) 
      ;
      if ( filelineerrorstylep ) 
      printfileline () ;
      else printnl ( 65544L ) ;
      print ( 66030L ) ;
    } 
    printcmdchr ( j , k ) ;
    {
      helpptr = 1 ;
      helpline [0 ]= 66861L ;
    } 
    error () ;
  } 
  Result = b ;
  return Result ;
} 
void 
showsavegroups ( void ) 
{
  /* 41 42 40 30 */ showsavegroups_regmem 
  integer p  ;
  short m  ;
  savepointer v  ;
  quarterword l  ;
  groupcode c  ;
  schar a  ;
  integer i  ;
  quarterword j  ;
  strnumber s  ;
  p = nestptr ;
  nest [p ]= curlist ;
  v = saveptr ;
  l = curlevel ;
  c = curgroup ;
  saveptr = curboundary ;
  decr ( curlevel ) ;
  a = 1 ;
  printnl ( 65545L ) ;
  println () ;
  while ( true ) {
      
    printnl ( 65662L ) ;
    printgroup ( true ) ;
    if ( curgroup == 0 ) 
    goto lab30 ;
    do {
	m = nest [p ].modefield ;
      if ( p > 0 ) 
      decr ( p ) ;
      else m = 1 ;
    } while ( ! ( m != 105 ) ) ;
    print ( 65568L ) ;
    switch ( curgroup ) 
    {case 1 : 
      {
	incr ( p ) ;
	goto lab42 ;
      } 
      break ;
    case 2 : 
    case 3 : 
      s = 66495L ;
      break ;
    case 4 : 
      s = 66404L ;
      break ;
    case 5 : 
      s = 66494L ;
      break ;
    case 6 : 
      if ( a == 0 ) 
      {
	if ( m == -1 ) 
	s = 65836L ;
	else s = 65863L ;
	a = 1 ;
	goto lab41 ;
      } 
      else {
	  
	if ( a == 1 ) 
	print ( 66899L ) ;
	else printesc ( 66328L ) ;
	if ( p >= a ) 
	p = p - a ;
	a = 0 ;
	goto lab40 ;
      } 
      break ;
    case 7 : 
      {
	incr ( p ) ;
	a = -1 ;
	printesc ( 65849L ) ;
	goto lab42 ;
      } 
      break ;
    case 8 : 
      {
	printesc ( 65699L ) ;
	goto lab40 ;
      } 
      break ;
    case 9 : 
      goto lab42 ;
      break ;
    case 10 : 
    case 13 : 
      {
	if ( curgroup == 10 ) 
	printesc ( 65640L ) ;
	else printesc ( 65847L ) ;
	{register integer for_end; i = 1 ;for_end = 3 ; if ( i <= for_end) 
	do 
	  if ( i <= savestack [saveptr - 2 ].cint ) 
	  print ( 66271L ) ;
	while ( i++ < for_end ) ;} 
	goto lab42 ;
      } 
      break ;
    case 11 : 
      {
	if ( savestack [saveptr - 2 ].cint == 255 ) 
	printesc ( 65643L ) ;
	else {
	    
	  printesc ( 65620L ) ;
	  printint ( savestack [saveptr - 2 ].cint ) ;
	} 
	goto lab42 ;
      } 
      break ;
    case 12 : 
      {
	s = 65864L ;
	goto lab41 ;
      } 
      break ;
    case 14 : 
      {
	incr ( p ) ;
	printesc ( 65826L ) ;
	goto lab40 ;
      } 
      break ;
    case 15 : 
      {
	if ( m == 209 ) 
	printchar ( 36 ) ;
	else if ( nest [p ].modefield == 209 ) 
	{
	  printcmdchr ( 48 , savestack [saveptr - 2 ].cint ) ;
	  goto lab40 ;
	} 
	printchar ( 36 ) ;
	goto lab40 ;
      } 
      break ;
    case 16 : 
      {
	if ( mem [nest [p + 1 ].eTeXauxfield ].hh.b0 == 30 ) 
	printesc ( 66287L ) ;
	else printesc ( 66289L ) ;
	goto lab40 ;
      } 
      break ;
    } 
    i = savestack [saveptr - 4 ].cint ;
    if ( i != 0 ) {
	
      if ( i < 1073741824L ) 
      {
	if ( abs ( nest [p ].modefield ) == 1 ) 
	j = 21 ;
	else j = 22 ;
	if ( i > 0 ) 
	printcmdchr ( j , 0 ) ;
	else printcmdchr ( j , 1 ) ;
	printscaled ( abs ( i ) ) ;
	print ( 65698L ) ;
      } 
      else if ( i < 1073807360L ) 
      {
	if ( i >= 1073774592L ) 
	{
	  printesc ( 66612L ) ;
	  i = i - ( 32768L ) ;
	} 
	printesc ( 65861L ) ;
	printint ( i - 1073741824L ) ;
	printchar ( 61 ) ;
      } 
      else printcmdchr ( 31 , i - ( 1073807261L ) ) ;
    } 
    lab41: printesc ( s ) ;
    if ( savestack [saveptr - 2 ].cint != 0 ) 
    {
      printchar ( 32 ) ;
      if ( savestack [saveptr - 3 ].cint == 0 ) 
      print ( 66252L ) ;
      else print ( 66253L ) ;
      printscaled ( savestack [saveptr - 2 ].cint ) ;
      print ( 65698L ) ;
    } 
    lab42: printchar ( 123 ) ;
    lab40: printchar ( 41 ) ;
    decr ( curlevel ) ;
    curgroup = savestack [saveptr ].hh.b1 ;
    saveptr = savestack [saveptr ].hh .v.RH ;
  } 
  lab30: saveptr = v ;
  curlevel = l ;
  curgroup = c ;
} 
halfword 
zprunepagetop ( halfword p , boolean s ) 
{
  register halfword Result; prunepagetop_regmem 
  halfword prevp  ;
  halfword q, r  ;
  prevp = memtop - 3 ;
  mem [memtop - 3 ].hh .v.RH = p ;
  while ( p != -268435455L ) switch ( mem [p ].hh.b0 ) 
  {case 0 : 
  case 1 : 
  case 2 : 
    {
      q = newskipparam ( 10 ) ;
      mem [prevp ].hh .v.RH = q ;
      mem [q ].hh .v.RH = p ;
      if ( ( eqtb [7892341L ].cint > 0 ) ) 
      {
	if ( mem [tempptr + 1 ].cint > mem [p + 2 ].cint ) 
	mem [tempptr + 1 ].cint = mem [tempptr + 1 ].cint - mem [p + 2 ]
	.cint ;
	else mem [tempptr + 1 ].cint = 0 ;
      } 
      else {
	  
	if ( mem [tempptr + 1 ].cint > mem [p + 3 ].cint ) 
	mem [tempptr + 1 ].cint = mem [tempptr + 1 ].cint - mem [p + 3 ]
	.cint ;
	else mem [tempptr + 1 ].cint = 0 ;
      } 
      p = -268435455L ;
    } 
    break ;
  case 8 : 
  case 4 : 
  case 3 : 
    {
      prevp = p ;
      p = mem [prevp ].hh .v.RH ;
    } 
    break ;
  case 10 : 
  case 11 : 
  case 12 : 
    {
      q = p ;
      p = mem [q ].hh .v.RH ;
      mem [q ].hh .v.RH = -268435455L ;
      mem [prevp ].hh .v.RH = p ;
      if ( s ) 
      {
	if ( discptr [3 ]== -268435455L ) 
	discptr [3 ]= q ;
	else mem [r ].hh .v.RH = q ;
	r = q ;
      } 
      else flushnodelist ( q ) ;
    } 
    break ;
    default: 
    confusion ( 66396L ) ;
    break ;
  } 
  Result = mem [memtop - 3 ].hh .v.RH ;
  return Result ;
} 
halfword 
zvertbreak ( halfword p , scaled h , scaled d ) 
{
  /* 30 45 90 */ register halfword Result; vertbreak_regmem 
  halfword prevp  ;
  halfword q, r  ;
  integer pi  ;
  integer b  ;
  integer leastcost  ;
  halfword bestplace  ;
  scaled prevdp  ;
  smallnumber t  ;
  prevp = p ;
  leastcost = 1073741823L ;
  activewidth [1 ]= 0 ;
  activewidth [2 ]= 0 ;
  activewidth [3 ]= 0 ;
  activewidth [4 ]= 0 ;
  activewidth [5 ]= 0 ;
  activewidth [6 ]= 0 ;
  prevdp = 0 ;
  while ( true ) {
      
    if ( p == -268435455L ) 
    pi = -10000 ;
    else switch ( mem [p ].hh.b0 ) 
    {case 0 : 
    case 1 : 
    case 2 : 
      {
	activewidth [1 ]= activewidth [1 ]+ prevdp + mem [p + 3 ].cint ;
	prevdp = mem [p + 2 ].cint ;
	goto lab45 ;
      } 
      break ;
    case 8 : 
      {
	if ( ( mem [p ].hh.b1 == 43 ) || ( mem [p ].hh.b1 == 44 ) ) 
	{
	  activewidth [1 ]= activewidth [1 ]+ prevdp + mem [p + 3 ].cint 
	  ;
	  prevdp = mem [p + 2 ].cint ;
	} 
	goto lab45 ;
      } 
      break ;
    case 10 : 
      if ( ( mem [prevp ].hh.b0 < 9 ) ) 
      pi = 0 ;
      else goto lab90 ;
      break ;
    case 11 : 
      {
	if ( mem [p ].hh .v.RH == -268435455L ) 
	t = 12 ;
	else t = mem [mem [p ].hh .v.RH ].hh.b0 ;
	if ( t == 10 ) 
	pi = 0 ;
	else goto lab90 ;
      } 
      break ;
    case 12 : 
      pi = mem [p + 1 ].cint ;
      break ;
    case 4 : 
    case 3 : 
      goto lab45 ;
      break ;
      default: 
      confusion ( 66397L ) ;
      break ;
    } 
    if ( pi < 10000 ) 
    {
      if ( activewidth [1 ]< h ) {
	  
	if ( ( activewidth [3 ]!= 0 ) || ( activewidth [4 ]!= 0 ) || ( 
	activewidth [5 ]!= 0 ) ) 
	b = 0 ;
	else b = badness ( h - activewidth [1 ], activewidth [2 ]) ;
      } 
      else if ( activewidth [1 ]- h > activewidth [6 ]) 
      b = 1073741823L ;
      else b = badness ( activewidth [1 ]- h , activewidth [6 ]) ;
      if ( b < 1073741823L ) {
	  
	if ( pi <= -10000 ) 
	b = pi ;
	else if ( b < 10000 ) 
	b = b + pi ;
	else b = 100000L ;
      } 
      if ( b <= leastcost ) 
      {
	bestplace = p ;
	leastcost = b ;
	bestheightplusdepth = activewidth [1 ]+ prevdp ;
      } 
      if ( ( b == 1073741823L ) || ( pi <= -10000 ) ) 
      goto lab30 ;
    } 
    if ( ( mem [p ].hh.b0 < 10 ) || ( mem [p ].hh.b0 > 11 ) ) 
    goto lab45 ;
    lab90: if ( mem [p ].hh.b0 == 11 ) 
    q = p ;
    else {
	
      q = mem [p + 1 ].hh .v.LH ;
      activewidth [2 + mem [q ].hh.b0 ]= activewidth [2 + mem [q ]
      .hh.b0 ]+ mem [q + 2 ].cint ;
      activewidth [6 ]= activewidth [6 ]+ mem [q + 3 ].cint ;
      if ( ( mem [q ].hh.b1 != 0 ) && ( mem [q + 3 ].cint != 0 ) ) 
      {
	if ( isbitset ( eqtb [7892335L ].cint , 1 ) ) 
	{
	  if ( interaction == 3 ) 
	  ;
	  if ( filelineerrorstylep ) 
	  printfileline () ;
	  else printnl ( 65545L ) ;
	  print ( 65546L ) ;
	  print ( 66398L ) ;
	} 
	else {
	    
	  {
	    if ( interaction == 3 ) 
	    ;
	    if ( filelineerrorstylep ) 
	    printfileline () ;
	    else printnl ( 65544L ) ;
	    print ( 66398L ) ;
	  } 
	  {
	    helpptr = 4 ;
	    helpline [3 ]= 66399L ;
	    helpline [2 ]= 66400L ;
	    helpline [1 ]= 66401L ;
	    helpline [0 ]= 66351L ;
	  } 
	  error () ;
	} 
	r = newspec ( q ) ;
	mem [r ].hh.b1 = 0 ;
	deleteglueref ( q ) ;
	mem [p + 1 ].hh .v.LH = r ;
	q = r ;
      } 
    } 
    activewidth [1 ]= activewidth [1 ]+ prevdp + mem [q + 1 ].cint ;
    prevdp = 0 ;
    lab45: if ( prevdp > d ) 
    {
      activewidth [1 ]= activewidth [1 ]+ prevdp - d ;
      prevdp = d ;
    } 
    prevp = p ;
    p = mem [prevp ].hh .v.RH ;
  } 
  lab30: Result = bestplace ;
  return Result ;
} 
halfword 
zvsplit ( halfword n , scaled h ) 
{
  /* 10 30 */ register halfword Result; vsplit_regmem 
  halfword v  ;
  halfword p  ;
  halfword q  ;
  curval = n ;
  if ( curval < 256 ) 
  v = eqtb [1206567L + curval ].hh .v.RH ;
  else {
      
    findsaelement ( 4 , curval , false ) ;
    if ( curptr == -268435455L ) 
    v = -268435455L ;
    else v = mem [curptr + 1 ].hh .v.RH ;
  } 
  flushnodelist ( discptr [3 ]) ;
  discptr [3 ]= -268435455L ;
  if ( saroot [7 ]!= -268435455L ) {
      
    if ( domarks ( 0 , 0 , saroot [7 ]) ) 
    saroot [7 ]= -268435455L ;
  } 
  if ( curmark [3 ]!= -268435455L ) 
  {
    deletetokenref ( curmark [3 ]) ;
    curmark [3 ]= -268435455L ;
    deletetokenref ( curmark [4 ]) ;
    curmark [4 ]= -268435455L ;
  } 
  if ( v == -268435455L ) 
  {
    Result = -268435455L ;
    return Result ;
  } 
  if ( mem [v ].hh.b0 != 1 ) 
  {
    {
      if ( interaction == 3 ) 
      ;
      if ( filelineerrorstylep ) 
      printfileline () ;
      else printnl ( 65544L ) ;
      print ( 65545L ) ;
    } 
    printesc ( 66402L ) ;
    print ( 66403L ) ;
    printesc ( 66404L ) ;
    {
      helpptr = 2 ;
      helpline [1 ]= 66405L ;
      helpline [0 ]= 66406L ;
    } 
    error () ;
    Result = -268435455L ;
    return Result ;
  } 
  q = vertbreak ( mem [v + 5 ].hh .v.RH , h , eqtb [9006726L ].cint ) ;
  p = mem [v + 5 ].hh .v.RH ;
  if ( p == q ) 
  mem [v + 5 ].hh .v.RH = -268435455L ;
  else while ( true ) {
      
    if ( mem [p ].hh.b0 == 4 ) {
	
      if ( mem [p + 1 ].hh .v.LH != 0 ) 
      {
	findsaelement ( 7 , mem [p + 1 ].hh .v.LH , true ) ;
	if ( mem [curptr + 2 ].hh .v.RH == -268435455L ) 
	{
	  mem [curptr + 2 ].hh .v.RH = mem [p + 1 ].hh .v.RH ;
	  incr ( mem [mem [p + 1 ].hh .v.RH ].hh .v.LH ) ;
	} 
	else deletetokenref ( mem [curptr + 3 ].hh .v.LH ) ;
	mem [curptr + 3 ].hh .v.LH = mem [p + 1 ].hh .v.RH ;
	incr ( mem [mem [p + 1 ].hh .v.RH ].hh .v.LH ) ;
      } 
      else if ( curmark [3 ]== -268435455L ) 
      {
	curmark [3 ]= mem [p + 1 ].hh .v.RH ;
	curmark [4 ]= curmark [3 ];
	mem [curmark [3 ]].hh .v.LH = mem [curmark [3 ]].hh .v.LH + 2 
	;
      } 
      else {
	  
	deletetokenref ( curmark [4 ]) ;
	curmark [4 ]= mem [p + 1 ].hh .v.RH ;
	incr ( mem [curmark [4 ]].hh .v.LH ) ;
      } 
    } 
    if ( mem [p ].hh .v.RH == q ) 
    {
      mem [p ].hh .v.RH = -268435455L ;
      goto lab30 ;
    } 
    p = mem [p ].hh .v.RH ;
  } 
  lab30: ;
  q = prunepagetop ( q , eqtb [7892332L ].cint > 0 ) ;
  p = mem [v + 5 ].hh .v.RH ;
  freenode ( v , 8 ) ;
  if ( q != -268435455L ) 
  q = vpackage ( q , 0 , 1 , 1073741823L ) ;
  if ( curval < 256 ) 
  eqtb [1206567L + curval ].hh .v.RH = q ;
  else {
      
    findsaelement ( 4 , curval , false ) ;
    if ( curptr != -268435455L ) 
    {
      mem [curptr + 1 ].hh .v.RH = q ;
      incr ( mem [curptr + 1 ].hh .v.LH ) ;
      deletesaref ( curptr ) ;
    } 
  } 
  Result = vpackage ( p , h , 0 , eqtb [9006726L ].cint ) ;
  return Result ;
} 
void 
printtotals ( void ) 
{
  printtotals_regmem 
  printscaled ( pagesofar [1 ]) ;
  if ( pagesofar [2 ]!= 0 ) 
  {
    print ( 65600L ) ;
    printscaled ( pagesofar [2 ]) ;
    print ( 65545L ) ;
  } 
  if ( pagesofar [3 ]!= 0 ) 
  {
    print ( 65600L ) ;
    printscaled ( pagesofar [3 ]) ;
    print ( 65599L ) ;
  } 
  if ( pagesofar [4 ]!= 0 ) 
  {
    print ( 65600L ) ;
    printscaled ( pagesofar [4 ]) ;
    print ( 66415L ) ;
  } 
  if ( pagesofar [5 ]!= 0 ) 
  {
    print ( 65600L ) ;
    printscaled ( pagesofar [5 ]) ;
    print ( 66416L ) ;
  } 
  if ( pagesofar [6 ]!= 0 ) 
  {
    print ( 65601L ) ;
    printscaled ( pagesofar [6 ]) ;
  } 
} 
void 
zfreezepagespecs ( smallnumber s ) 
{
  freezepagespecs_regmem 
  pagecontents = s ;
  pagesofar [0 ]= eqtb [9006724L ].cint ;
  pagemaxdepth = eqtb [9006725L ].cint ;
  pagesofar [7 ]= 0 ;
  pagesofar [1 ]= 0 ;
  pagesofar [2 ]= 0 ;
  pagesofar [3 ]= 0 ;
  pagesofar [4 ]= 0 ;
  pagesofar [5 ]= 0 ;
  pagesofar [6 ]= 0 ;
  leastpagecost = 1073741823L ;
	;
#ifdef STAT
  if ( eqtb [7892297L ].cint > 0 ) 
  {
    begindiagnostic () ;
    printnl ( 66424L ) ;
    printscaled ( pagesofar [0 ]) ;
    print ( 66425L ) ;
    printscaled ( pagemaxdepth ) ;
    enddiagnostic ( false ) ;
  } 
#endif /* STAT */
} 
void 
zboxerror ( eightbits n ) 
{
  boxerror_regmem 
  error () ;
  begindiagnostic () ;
  printnl ( 66239L ) ;
  showbox ( eqtb [1206567L + n ].hh .v.RH ) ;
  enddiagnostic ( true ) ;
  flushnodelist ( eqtb [1206567L + n ].hh .v.RH ) ;
  eqtb [1206567L + n ].hh .v.RH = -268435455L ;
} 
void 
zensurevbox ( eightbits n ) 
{
  ensurevbox_regmem 
  halfword p  ;
  p = eqtb [1206567L + n ].hh .v.RH ;
  if ( p != -268435455L ) {
      
    if ( mem [p ].hh.b0 == 0 ) 
    {
      {
	if ( interaction == 3 ) 
	;
	if ( filelineerrorstylep ) 
	printfileline () ;
	else printnl ( 65544L ) ;
	print ( 66426L ) ;
      } 
      {
	helpptr = 3 ;
	helpline [2 ]= 66427L ;
	helpline [1 ]= 66428L ;
	helpline [0 ]= 66429L ;
      } 
      boxerror ( n ) ;
    } 
  } 
} 
void 
zfireup ( halfword c ) 
{
  /* 10 */ fireup_regmem 
  halfword p, q, r, s  ;
  halfword prevp  ;
  unsigned char n  ;
  boolean wait  ;
  integer savevbadness  ;
  scaled savevfuzz  ;
  halfword savesplittopskip  ;
  if ( mem [bestpagebreak ].hh.b0 == 12 ) 
  {
    geqworddefine ( 7892303L , mem [bestpagebreak + 1 ].cint ) ;
    mem [bestpagebreak + 1 ].cint = 10000 ;
  } 
  else geqworddefine ( 7892303L , 10000 ) ;
  if ( saroot [7 ]!= -268435455L ) {
      
    if ( domarks ( 1 , 0 , saroot [7 ]) ) 
    saroot [7 ]= -268435455L ;
  } 
  if ( curmark [2 ]!= -268435455L ) 
  {
    if ( curmark [0 ]!= -268435455L ) 
    deletetokenref ( curmark [0 ]) ;
    curmark [0 ]= curmark [2 ];
    incr ( mem [curmark [0 ]].hh .v.LH ) ;
    deletetokenref ( curmark [1 ]) ;
    curmark [1 ]= -268435455L ;
  } 
  if ( c == bestpagebreak ) 
  bestpagebreak = -268435455L ;
  if ( eqtb [1206822L ].hh .v.RH != -268435455L ) 
  {
    {
      if ( interaction == 3 ) 
      ;
      if ( filelineerrorstylep ) 
      printfileline () ;
      else printnl ( 65544L ) ;
      print ( 65545L ) ;
    } 
    printesc ( 65710L ) ;
    print ( 66440L ) ;
    {
      helpptr = 2 ;
      helpline [1 ]= 66441L ;
      helpline [0 ]= 66429L ;
    } 
    boxerror ( 255 ) ;
  } 
  insertpenalties = 0 ;
  savesplittopskip = eqtb [1205774L ].hh .v.RH ;
  if ( eqtb [7892317L ].cint <= 0 ) 
  {
    r = mem [memtop ].hh .v.RH ;
    while ( r != memtop ) {
	
      if ( mem [r + 2 ].hh .v.LH != -268435455L ) 
      {
	n = mem [r ].hh.b1 ;
	ensurevbox ( n ) ;
	if ( eqtb [1206567L + n ].hh .v.RH == -268435455L ) 
	eqtb [1206567L + n ].hh .v.RH = newnullbox () ;
	p = eqtb [1206567L + n ].hh .v.RH + 5 ;
	while ( mem [p ].hh .v.RH != -268435455L ) p = mem [p ].hh .v.RH ;
	mem [r + 2 ].hh .v.RH = p ;
      } 
      r = mem [r ].hh .v.RH ;
    } 
  } 
  q = memtop - 4 ;
  mem [q ].hh .v.RH = -268435455L ;
  prevp = memtop - 2 ;
  p = mem [prevp ].hh .v.RH ;
  while ( p != bestpagebreak ) {
      
    if ( mem [p ].hh.b0 == 3 ) 
    {
      if ( eqtb [7892317L ].cint <= 0 ) 
      {
	r = mem [memtop ].hh .v.RH ;
	while ( mem [r ].hh.b1 != mem [p ].hh.b1 ) r = mem [r ].hh .v.RH 
	;
	if ( mem [r + 2 ].hh .v.LH == -268435455L ) 
	wait = true ;
	else {
	    
	  wait = false ;
	  s = mem [r + 2 ].hh .v.RH ;
	  mem [s ].hh .v.RH = mem [p + 4 ].hh .v.LH ;
	  if ( mem [r + 2 ].hh .v.LH == p ) 
	  {
	    if ( mem [r ].hh.b0 == 1 ) {
		
	      if ( ( mem [r + 1 ].hh .v.LH == p ) && ( mem [r + 1 ].hh 
	      .v.RH != -268435455L ) ) 
	      {
		while ( mem [s ].hh .v.RH != mem [r + 1 ].hh .v.RH ) s = 
		mem [s ].hh .v.RH ;
		mem [s ].hh .v.RH = -268435455L ;
		eqtb [1205774L ].hh .v.RH = mem [p + 4 ].hh .v.RH ;
		mem [p + 4 ].hh .v.LH = prunepagetop ( mem [r + 1 ].hh 
		.v.RH , false ) ;
		if ( mem [p + 4 ].hh .v.LH != -268435455L ) 
		{
		  tempptr = vpackage ( mem [p + 4 ].hh .v.LH , 0 , 1 , 
		  1073741823L ) ;
		  mem [p + 3 ].cint = mem [tempptr + 3 ].cint + mem [
		  tempptr + 2 ].cint ;
		  freenode ( tempptr , 8 ) ;
		  wait = true ;
		} 
	      } 
	    } 
	    mem [r + 2 ].hh .v.LH = -268435455L ;
	    n = mem [r ].hh.b1 ;
	    tempptr = mem [eqtb [1206567L + n ].hh .v.RH + 5 ].hh .v.RH ;
	    freenode ( eqtb [1206567L + n ].hh .v.RH , 8 ) ;
	    eqtb [1206567L + n ].hh .v.RH = vpackage ( tempptr , 0 , 1 , 
	    1073741823L ) ;
	  } 
	  else {
	      
	    while ( mem [s ].hh .v.RH != -268435455L ) s = mem [s ].hh 
	    .v.RH ;
	    mem [r + 2 ].hh .v.RH = s ;
	  } 
	} 
	mem [prevp ].hh .v.RH = mem [p ].hh .v.RH ;
	mem [p ].hh .v.RH = -268435455L ;
	if ( wait ) 
	{
	  mem [q ].hh .v.RH = p ;
	  q = p ;
	  incr ( insertpenalties ) ;
	} 
	else {
	    
	  deleteglueref ( mem [p + 4 ].hh .v.RH ) ;
	  freenode ( p , 5 ) ;
	} 
	p = prevp ;
      } 
    } 
    else if ( mem [p ].hh.b0 == 4 ) {
	
      if ( mem [p + 1 ].hh .v.LH != 0 ) 
      {
	findsaelement ( 7 , mem [p + 1 ].hh .v.LH , true ) ;
	if ( mem [curptr + 1 ].hh .v.RH == -268435455L ) 
	{
	  mem [curptr + 1 ].hh .v.RH = mem [p + 1 ].hh .v.RH ;
	  incr ( mem [mem [p + 1 ].hh .v.RH ].hh .v.LH ) ;
	} 
	if ( mem [curptr + 2 ].hh .v.LH != -268435455L ) 
	deletetokenref ( mem [curptr + 2 ].hh .v.LH ) ;
	mem [curptr + 2 ].hh .v.LH = mem [p + 1 ].hh .v.RH ;
	incr ( mem [mem [p + 1 ].hh .v.RH ].hh .v.LH ) ;
      } 
      else {
	  
	if ( curmark [1 ]== -268435455L ) 
	{
	  curmark [1 ]= mem [p + 1 ].hh .v.RH ;
	  incr ( mem [curmark [1 ]].hh .v.LH ) ;
	} 
	if ( curmark [2 ]!= -268435455L ) 
	deletetokenref ( curmark [2 ]) ;
	curmark [2 ]= mem [p + 1 ].hh .v.RH ;
	incr ( mem [curmark [2 ]].hh .v.LH ) ;
      } 
    } 
    prevp = p ;
    p = mem [prevp ].hh .v.RH ;
  } 
  eqtb [1205774L ].hh .v.RH = savesplittopskip ;
  if ( p != -268435455L ) 
  {
    if ( mem [memtop - 1 ].hh .v.RH == -268435455L ) {
	
      if ( nestptr == 0 ) 
      curlist .tailfield = pagetail ;
      else nest [0 ].tailfield = pagetail ;
    } 
    mem [pagetail ].hh .v.RH = mem [memtop - 1 ].hh .v.RH ;
    mem [memtop - 1 ].hh .v.RH = p ;
    mem [prevp ].hh .v.RH = -268435455L ;
  } 
  savevbadness = eqtb [7892291L ].cint ;
  eqtb [7892291L ].cint = 10000 ;
  savevfuzz = eqtb [9006729L ].cint ;
  eqtb [9006729L ].cint = 1073741823L ;
  eqtb [1206822L ].hh .v.RH = vpackage ( mem [memtop - 2 ].hh .v.RH , 
  bestsize , 0 , pagemaxdepth ) ;
  eqtb [7892291L ].cint = savevbadness ;
  eqtb [9006729L ].cint = savevfuzz ;
  if ( lastglue != 1073741823L ) 
  deleteglueref ( lastglue ) ;
  pagecontents = 0 ;
  pagetail = memtop - 2 ;
  mem [memtop - 2 ].hh .v.RH = -268435455L ;
  lastglue = 1073741823L ;
  lastpenalty = 0 ;
  lastkern = 0 ;
  lastnodetype = -1 ;
  pagesofar [7 ]= 0 ;
  pagemaxdepth = 0 ;
  if ( q != memtop - 4 ) 
  {
    mem [memtop - 2 ].hh .v.RH = mem [memtop - 4 ].hh .v.RH ;
    pagetail = q ;
  } 
  r = mem [memtop ].hh .v.RH ;
  while ( r != memtop ) {
      
    q = mem [r ].hh .v.RH ;
    freenode ( r , 4 ) ;
    r = q ;
  } 
  mem [memtop ].hh .v.RH = memtop ;
  if ( saroot [7 ]!= -268435455L ) {
      
    if ( domarks ( 2 , 0 , saroot [7 ]) ) 
    saroot [7 ]= -268435455L ;
  } 
  if ( ( curmark [0 ]!= -268435455L ) && ( curmark [1 ]== -268435455L ) ) 
  {
    curmark [1 ]= curmark [0 ];
    incr ( mem [curmark [0 ]].hh .v.LH ) ;
  } 
  if ( eqtb [1206296L ].hh .v.RH != -268435455L ) {
      
    if ( deadcycles >= eqtb [7892304L ].cint ) 
    {
      {
	if ( interaction == 3 ) 
	;
	if ( filelineerrorstylep ) 
	printfileline () ;
	else printnl ( 65544L ) ;
	print ( 66442L ) ;
      } 
      printint ( deadcycles ) ;
      print ( 66443L ) ;
      {
	helpptr = 3 ;
	helpline [2 ]= 66444L ;
	helpline [1 ]= 66445L ;
	helpline [0 ]= 66446L ;
      } 
      error () ;
    } 
    else {
	
      outputactive = true ;
      incr ( deadcycles ) ;
      pushnest () ;
      curlist .modefield = -1 ;
      curlist .auxfield .cint = -65536000L ;
      curlist .mlfield = - (integer) line ;
      begintokenlist ( eqtb [1206296L ].hh .v.RH , 7 ) ;
      newsavelevel ( 8 ) ;
      normalparagraph () ;
      scanleftbrace () ;
      return ;
    } 
  } 
  {
    if ( mem [memtop - 2 ].hh .v.RH != -268435455L ) 
    {
      if ( mem [memtop - 1 ].hh .v.RH == -268435455L ) {
	  
	if ( nestptr == 0 ) 
	curlist .tailfield = pagetail ;
	else nest [0 ].tailfield = pagetail ;
      } 
      else mem [pagetail ].hh .v.RH = mem [memtop - 1 ].hh .v.RH ;
      mem [memtop - 1 ].hh .v.RH = mem [memtop - 2 ].hh .v.RH ;
      mem [memtop - 2 ].hh .v.RH = -268435455L ;
      pagetail = memtop - 2 ;
    } 
    flushnodelist ( discptr [2 ]) ;
    discptr [2 ]= -268435455L ;
    shipout ( eqtb [1206822L ].hh .v.RH ) ;
    eqtb [1206822L ].hh .v.RH = -268435455L ;
  } 
} 
void 
buildpage ( void ) 
{
  /* 10 30 31 22 80 90 */ buildpage_regmem 
  halfword p  ;
  halfword q, r  ;
  integer b, c  ;
  integer pi  ;
  unsigned char n  ;
  scaled delta, h, w  ;
  if ( ( mem [memtop - 1 ].hh .v.RH == -268435455L ) || outputactive ) 
  return ;
  do {
      lab22: p = mem [memtop - 1 ].hh .v.RH ;
    if ( lastglue != 1073741823L ) 
    deleteglueref ( lastglue ) ;
    lastpenalty = 0 ;
    lastkern = 0 ;
    lastnodetype = mem [p ].hh.b0 + 1 ;
    if ( mem [p ].hh.b0 == 10 ) 
    {
      lastglue = mem [p + 1 ].hh .v.LH ;
      incr ( mem [lastglue ].hh .v.RH ) ;
    } 
    else {
	
      lastglue = 1073741823L ;
      if ( mem [p ].hh.b0 == 12 ) 
      lastpenalty = mem [p + 1 ].cint ;
      else if ( mem [p ].hh.b0 == 11 ) 
      lastkern = mem [p + 1 ].cint ;
    } 
    switch ( mem [p ].hh.b0 ) 
    {case 0 : 
    case 1 : 
    case 2 : 
      if ( pagecontents < 2 ) 
      {
	if ( pagecontents == 0 ) 
	freezepagespecs ( 2 ) ;
	else pagecontents = 2 ;
	q = newskipparam ( 9 ) ;
	if ( ( eqtb [7892341L ].cint > 0 ) ) 
	{
	  if ( mem [tempptr + 1 ].cint > mem [p + 2 ].cint ) 
	  mem [tempptr + 1 ].cint = mem [tempptr + 1 ].cint - mem [p + 2 
	  ].cint ;
	  else mem [tempptr + 1 ].cint = 0 ;
	} 
	else {
	    
	  if ( mem [tempptr + 1 ].cint > mem [p + 3 ].cint ) 
	  mem [tempptr + 1 ].cint = mem [tempptr + 1 ].cint - mem [p + 3 
	  ].cint ;
	  else mem [tempptr + 1 ].cint = 0 ;
	} 
	mem [q ].hh .v.RH = p ;
	mem [memtop - 1 ].hh .v.RH = q ;
	goto lab22 ;
      } 
      else {
	  
	pagesofar [1 ]= pagesofar [1 ]+ pagesofar [7 ]+ mem [p + 3 ]
	.cint ;
	pagesofar [7 ]= mem [p + 2 ].cint ;
	goto lab80 ;
      } 
      break ;
    case 8 : 
      {
	if ( ( mem [p ].hh.b1 == 43 ) || ( mem [p ].hh.b1 == 44 ) ) 
	{
	  pagesofar [1 ]= pagesofar [1 ]+ pagesofar [7 ]+ mem [p + 3 ]
	  .cint ;
	  pagesofar [7 ]= mem [p + 2 ].cint ;
	} 
	goto lab80 ;
      } 
      break ;
    case 10 : 
      if ( pagecontents < 2 ) 
      goto lab31 ;
      else if ( ( mem [pagetail ].hh.b0 < 9 ) ) 
      pi = 0 ;
      else goto lab90 ;
      break ;
    case 11 : 
      if ( pagecontents < 2 ) 
      goto lab31 ;
      else if ( mem [p ].hh .v.RH == -268435455L ) 
      return ;
      else if ( mem [mem [p ].hh .v.RH ].hh.b0 == 10 ) 
      pi = 0 ;
      else goto lab90 ;
      break ;
    case 12 : 
      if ( pagecontents < 2 ) 
      goto lab31 ;
      else pi = mem [p + 1 ].cint ;
      break ;
    case 4 : 
      goto lab80 ;
      break ;
    case 3 : 
      {
	if ( pagecontents == 0 ) 
	freezepagespecs ( 1 ) ;
	n = mem [p ].hh.b1 ;
	r = memtop ;
	while ( n >= mem [mem [r ].hh .v.RH ].hh.b1 ) r = mem [r ].hh 
	.v.RH ;
	n = n ;
	if ( mem [r ].hh.b1 != n ) 
	{
	  q = getnode ( 4 ) ;
	  mem [q ].hh .v.RH = mem [r ].hh .v.RH ;
	  mem [r ].hh .v.RH = q ;
	  r = q ;
	  mem [r ].hh.b1 = n ;
	  mem [r ].hh.b0 = 0 ;
	  ensurevbox ( n ) ;
	  if ( eqtb [1206567L + n ].hh .v.RH == -268435455L ) 
	  mem [r + 3 ].cint = 0 ;
	  else mem [r + 3 ].cint = mem [eqtb [1206567L + n ].hh .v.RH + 3 
	  ].cint + mem [eqtb [1206567L + n ].hh .v.RH + 2 ].cint ;
	  mem [r + 2 ].hh .v.LH = -268435455L ;
	  q = eqtb [1205783L + n ].hh .v.RH ;
	  if ( eqtb [7892352L + n ].cint == 1000 ) 
	  h = mem [r + 3 ].cint ;
	  else h = xovern ( mem [r + 3 ].cint , 1000 ) * eqtb [7892352L + n 
	  ].cint ;
	  pagesofar [0 ]= pagesofar [0 ]- h - mem [q + 1 ].cint ;
	  pagesofar [2 + mem [q ].hh.b0 ]= pagesofar [2 + mem [q ]
	  .hh.b0 ]+ mem [q + 2 ].cint ;
	  pagesofar [6 ]= pagesofar [6 ]+ mem [q + 3 ].cint ;
	  if ( ( mem [q ].hh.b1 != 0 ) && ( mem [q + 3 ].cint != 0 ) ) 
	  {
	    {
	      if ( interaction == 3 ) 
	      ;
	      if ( filelineerrorstylep ) 
	      printfileline () ;
	      else printnl ( 65544L ) ;
	      print ( 66435L ) ;
	    } 
	    printesc ( 65696L ) ;
	    printint ( n ) ;
	    {
	      helpptr = 3 ;
	      helpline [2 ]= 66436L ;
	      helpline [1 ]= 66437L ;
	      helpline [0 ]= 66351L ;
	    } 
	    error () ;
	  } 
	} 
	if ( mem [r ].hh.b0 == 1 ) 
	insertpenalties = insertpenalties + mem [p + 1 ].cint ;
	else {
	    
	  mem [r + 2 ].hh .v.RH = p ;
	  delta = pagesofar [0 ]- pagesofar [1 ]- pagesofar [7 ]+ 
	  pagesofar [6 ];
	  if ( eqtb [7892352L + n ].cint == 1000 ) 
	  h = mem [p + 3 ].cint ;
	  else h = xovern ( mem [p + 3 ].cint , 1000 ) * eqtb [7892352L + n 
	  ].cint ;
	  if ( ( ( h <= 0 ) || ( h <= delta ) ) && ( mem [p + 3 ].cint + mem 
	  [r + 3 ].cint <= eqtb [9006743L + n ].cint ) ) 
	  {
	    pagesofar [0 ]= pagesofar [0 ]- h ;
	    mem [r + 3 ].cint = mem [r + 3 ].cint + mem [p + 3 ].cint ;
	  } 
	  else {
	      
	    if ( eqtb [7892352L + n ].cint <= 0 ) 
	    w = 1073741823L ;
	    else {
		
	      w = pagesofar [0 ]- pagesofar [1 ]- pagesofar [7 ];
	      if ( eqtb [7892352L + n ].cint != 1000 ) 
	      w = xovern ( w , eqtb [7892352L + n ].cint ) * 1000 ;
	    } 
	    if ( w > eqtb [9006743L + n ].cint - mem [r + 3 ].cint ) 
	    w = eqtb [9006743L + n ].cint - mem [r + 3 ].cint ;
	    q = vertbreak ( mem [p + 4 ].hh .v.LH , w , mem [p + 2 ].cint 
	    ) ;
	    mem [r + 3 ].cint = mem [r + 3 ].cint + bestheightplusdepth ;
	;
#ifdef STAT
	    if ( eqtb [7892297L ].cint > 0 ) 
	    {
	      begindiagnostic () ;
	      printnl ( 66438L ) ;
	      printint ( n ) ;
	      print ( 66439L ) ;
	      printscaled ( w ) ;
	      printchar ( 44 ) ;
	      printscaled ( bestheightplusdepth ) ;
	      print ( 66366L ) ;
	      if ( q == -268435455L ) 
	      printint ( -10000 ) ;
	      else if ( mem [q ].hh.b0 == 12 ) 
	      printint ( mem [q + 1 ].cint ) ;
	      else printchar ( 48 ) ;
	      enddiagnostic ( false ) ;
	    } 
#endif /* STAT */
	    if ( eqtb [7892352L + n ].cint != 1000 ) 
	    bestheightplusdepth = xovern ( bestheightplusdepth , 1000 ) * eqtb 
	    [7892352L + n ].cint ;
	    pagesofar [0 ]= pagesofar [0 ]- bestheightplusdepth ;
	    mem [r ].hh.b0 = 1 ;
	    mem [r + 1 ].hh .v.RH = q ;
	    mem [r + 1 ].hh .v.LH = p ;
	    if ( q == -268435455L ) 
	    insertpenalties = insertpenalties - 10000 ;
	    else if ( mem [q ].hh.b0 == 12 ) 
	    insertpenalties = insertpenalties + mem [q + 1 ].cint ;
	  } 
	} 
	goto lab80 ;
      } 
      break ;
      default: 
      confusion ( 66430L ) ;
      break ;
    } 
    if ( pi < 10000 ) 
    {
      if ( pagesofar [1 ]< pagesofar [0 ]) {
	  
	if ( ( pagesofar [3 ]!= 0 ) || ( pagesofar [4 ]!= 0 ) || ( 
	pagesofar [5 ]!= 0 ) ) 
	b = 0 ;
	else b = badness ( pagesofar [0 ]- pagesofar [1 ], pagesofar [2 ]
	) ;
      } 
      else if ( pagesofar [1 ]- pagesofar [0 ]> pagesofar [6 ]) 
      b = 1073741823L ;
      else b = badness ( pagesofar [1 ]- pagesofar [0 ], pagesofar [6 ]) 
      ;
      if ( b < 1073741823L ) {
	  
	if ( pi <= -10000 ) 
	c = pi ;
	else if ( b < 10000 ) 
	c = b + pi + insertpenalties ;
	else c = 100000L ;
      } 
      else c = b ;
      if ( insertpenalties >= 10000 ) 
      c = 1073741823L ;
	;
#ifdef STAT
      if ( eqtb [7892297L ].cint > 0 ) 
      {
	begindiagnostic () ;
	printnl ( 37 ) ;
	print ( 66362L ) ;
	printtotals () ;
	print ( 66433L ) ;
	printscaled ( pagesofar [0 ]) ;
	print ( 66365L ) ;
	if ( b == 1073741823L ) 
	printchar ( 42 ) ;
	else printint ( b ) ;
	print ( 66366L ) ;
	printint ( pi ) ;
	print ( 66434L ) ;
	if ( c == 1073741823L ) 
	printchar ( 42 ) ;
	else printint ( c ) ;
	if ( c <= leastpagecost ) 
	printchar ( 35 ) ;
	enddiagnostic ( false ) ;
      } 
#endif /* STAT */
      if ( c <= leastpagecost ) 
      {
	bestpagebreak = p ;
	bestsize = pagesofar [0 ];
	leastpagecost = c ;
	r = mem [memtop ].hh .v.RH ;
	while ( r != memtop ) {
	    
	  mem [r + 2 ].hh .v.LH = mem [r + 2 ].hh .v.RH ;
	  r = mem [r ].hh .v.RH ;
	} 
      } 
      if ( ( c == 1073741823L ) || ( pi <= -10000 ) ) 
      {
	fireup ( p ) ;
	if ( outputactive ) 
	return ;
	goto lab30 ;
      } 
    } 
    if ( ( mem [p ].hh.b0 < 10 ) || ( mem [p ].hh.b0 > 11 ) ) 
    goto lab80 ;
    lab90: if ( mem [p ].hh.b0 == 11 ) 
    q = p ;
    else {
	
      q = mem [p + 1 ].hh .v.LH ;
      pagesofar [2 + mem [q ].hh.b0 ]= pagesofar [2 + mem [q ].hh.b0 ]
      + mem [q + 2 ].cint ;
      pagesofar [6 ]= pagesofar [6 ]+ mem [q + 3 ].cint ;
      if ( ( mem [q ].hh.b1 != 0 ) && ( mem [q + 3 ].cint != 0 ) ) 
      {
	{
	  if ( interaction == 3 ) 
	  ;
	  if ( filelineerrorstylep ) 
	  printfileline () ;
	  else printnl ( 65544L ) ;
	  print ( 66431L ) ;
	} 
	{
	  helpptr = 4 ;
	  helpline [3 ]= 66432L ;
	  helpline [2 ]= 66400L ;
	  helpline [1 ]= 66401L ;
	  helpline [0 ]= 66351L ;
	} 
	error () ;
	r = newspec ( q ) ;
	mem [r ].hh.b1 = 0 ;
	deleteglueref ( q ) ;
	mem [p + 1 ].hh .v.LH = r ;
	q = r ;
      } 
    } 
    pagesofar [1 ]= pagesofar [1 ]+ pagesofar [7 ]+ mem [q + 1 ].cint 
    ;
    pagesofar [7 ]= 0 ;
    lab80: if ( pagesofar [7 ]> pagemaxdepth ) 
    {
      pagesofar [1 ]= pagesofar [1 ]+ pagesofar [7 ]- pagemaxdepth ;
      pagesofar [7 ]= pagemaxdepth ;
    } 
    mem [pagetail ].hh .v.RH = p ;
    pagetail = p ;
    mem [memtop - 1 ].hh .v.RH = mem [p ].hh .v.RH ;
    mem [p ].hh .v.RH = -268435455L ;
    goto lab30 ;
    lab31: mem [memtop - 1 ].hh .v.RH = mem [p ].hh .v.RH ;
    mem [p ].hh .v.RH = -268435455L ;
    if ( eqtb [7892332L ].cint > 0 ) 
    {
      if ( discptr [2 ]== -268435455L ) 
      discptr [2 ]= p ;
      else mem [discptr [1 ]].hh .v.RH = p ;
      discptr [1 ]= p ;
    } 
    else flushnodelist ( p ) ;
    lab30: ;
  } while ( ! ( mem [memtop - 1 ].hh .v.RH == -268435455L ) ) ;
  if ( nestptr == 0 ) 
  curlist .tailfield = memtop - 1 ;
  else nest [0 ].tailfield = memtop - 1 ;
} 
void 
appspace ( void ) 
{
  appspace_regmem 
  halfword q  ;
  if ( ( curlist .auxfield .hh .v.LH >= 2000 ) && ( eqtb [1205777L ].hh 
  .v.RH != membot ) ) 
  q = newparamglue ( 13 ) ;
  else {
      
    if ( eqtb [1205776L ].hh .v.RH != membot ) 
    mainp = eqtb [1205776L ].hh .v.RH ;
    else {
	
      mainp = fontglue [eqtb [1206823L ].hh .v.RH ];
      if ( mainp == -268435455L ) 
      {
	mainp = newspec ( membot ) ;
	maink = parambase [eqtb [1206823L ].hh .v.RH ]+ 2 ;
	mem [mainp + 1 ].cint = fontinfo [maink ].cint ;
	mem [mainp + 2 ].cint = fontinfo [maink + 1 ].cint ;
	mem [mainp + 3 ].cint = fontinfo [maink + 2 ].cint ;
	fontglue [eqtb [1206823L ].hh .v.RH ]= mainp ;
      } 
    } 
    mainp = newspec ( mainp ) ;
    if ( curlist .auxfield .hh .v.LH >= 2000 ) 
    mem [mainp + 1 ].cint = mem [mainp + 1 ].cint + fontinfo [7 + 
    parambase [eqtb [1206823L ].hh .v.RH ]].cint ;
    mem [mainp + 2 ].cint = xnoverd ( mem [mainp + 2 ].cint , curlist 
    .auxfield .hh .v.LH , 1000 ) ;
    mem [mainp + 3 ].cint = xnoverd ( mem [mainp + 3 ].cint , 1000 , 
    curlist .auxfield .hh .v.LH ) ;
    q = newglue ( mainp ) ;
    mem [mainp ].hh .v.RH = -268435455L ;
  } 
  mem [curlist .tailfield ].hh .v.RH = q ;
  curlist .tailfield = q ;
} 
void 
insertdollarsign ( void ) 
{
  insertdollarsign_regmem 
  backinput () ;
  curtok = 6291492L ;
  {
    if ( interaction == 3 ) 
    ;
    if ( filelineerrorstylep ) 
    printfileline () ;
    else printnl ( 65544L ) ;
    print ( 66453L ) ;
  } 
  {
    helpptr = 2 ;
    helpline [1 ]= 66454L ;
    helpline [0 ]= 66455L ;
  } 
  inserror () ;
} 
void 
youcant ( void ) 
{
  youcant_regmem 
  {
    if ( interaction == 3 ) 
    ;
    if ( filelineerrorstylep ) 
    printfileline () ;
    else printnl ( 65544L ) ;
    print ( 66035L ) ;
  } 
  printcmdchr ( curcmd , curchr ) ;
  printinmode ( curlist .modefield ) ;
} 
void 
reportillegalcase ( void ) 
{
  reportillegalcase_regmem 
  youcant () ;
  {
    helpptr = 4 ;
    helpline [3 ]= 66456L ;
    helpline [2 ]= 66457L ;
    helpline [1 ]= 66458L ;
    helpline [0 ]= 66459L ;
  } 
  error () ;
} 
boolean 
privileged ( void ) 
{
  register boolean Result; privileged_regmem 
  if ( curlist .modefield > 0 ) 
  Result = true ;
  else {
      
    reportillegalcase () ;
    Result = false ;
  } 
  return Result ;
} 
boolean 
itsallover ( void ) 
{
  /* 10 */ register boolean Result; itsallover_regmem 
  if ( privileged () ) 
  {
    if ( ( memtop - 2 == pagetail ) && ( curlist .headfield == curlist 
    .tailfield ) && ( deadcycles == 0 ) ) 
    {
      Result = true ;
      return Result ;
    } 
    backinput () ;
    {
      mem [curlist .tailfield ].hh .v.RH = newnullbox () ;
      curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
    } 
    mem [curlist .tailfield + 1 ].cint = eqtb [9006723L ].cint ;
    {
      mem [curlist .tailfield ].hh .v.RH = newglue ( membot + 8 ) ;
      curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
    } 
    {
      mem [curlist .tailfield ].hh .v.RH = newpenalty ( -1073741824L ) ;
      curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
    } 
    buildpage () ;
  } 
  Result = false ;
  return Result ;
} 
void 
appendglue ( void ) 
{
  appendglue_regmem 
  smallnumber s  ;
  s = curchr ;
  switch ( s ) 
  {case 0 : 
    curval = membot + 4 ;
    break ;
  case 1 : 
    curval = membot + 8 ;
    break ;
  case 2 : 
    curval = membot + 12 ;
    break ;
  case 3 : 
    curval = membot + 16 ;
    break ;
  case 4 : 
    scanglue ( 2 ) ;
    break ;
  case 5 : 
    scanglue ( 3 ) ;
    break ;
  } 
  {
    mem [curlist .tailfield ].hh .v.RH = newglue ( curval ) ;
    curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
  } 
  if ( s >= 4 ) 
  {
    decr ( mem [curval ].hh .v.RH ) ;
    if ( s > 4 ) 
    mem [curlist .tailfield ].hh.b1 = 99 ;
  } 
} 
void 
appendkern ( void ) 
{
  appendkern_regmem 
  quarterword s  ;
  s = curchr ;
  scandimen ( s == 99 , false , false ) ;
  {
    mem [curlist .tailfield ].hh .v.RH = newkern ( curval ) ;
    curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
  } 
  mem [curlist .tailfield ].hh.b1 = s ;
} 
void 
offsave ( void ) 
{
  offsave_regmem 
  halfword p  ;
  if ( curgroup == 0 ) 
  {
    {
      if ( interaction == 3 ) 
      ;
      if ( filelineerrorstylep ) 
      printfileline () ;
      else printnl ( 65544L ) ;
      print ( 66169L ) ;
    } 
    printcmdchr ( curcmd , curchr ) ;
    {
      helpptr = 1 ;
      helpline [0 ]= 66477L ;
    } 
    error () ;
  } 
  else {
      
    backinput () ;
    p = getavail () ;
    mem [memtop - 3 ].hh .v.RH = p ;
    {
      if ( interaction == 3 ) 
      ;
      if ( filelineerrorstylep ) 
      printfileline () ;
      else printnl ( 65544L ) ;
      print ( 65959L ) ;
    } 
    switch ( curgroup ) 
    {case 14 : 
      {
	mem [p ].hh .v.LH = 34749083L ;
	printesc ( 65832L ) ;
      } 
      break ;
    case 15 : 
      {
	mem [p ].hh .v.LH = 6291492L ;
	printchar ( 36 ) ;
      } 
      break ;
    case 16 : 
      {
	mem [p ].hh .v.LH = 34749084L ;
	mem [p ].hh .v.RH = getavail () ;
	p = mem [p ].hh .v.RH ;
	mem [p ].hh .v.LH = 25165870L ;
	printesc ( 66476L ) ;
      } 
      break ;
      default: 
      {
	mem [p ].hh .v.LH = 4194429L ;
	printchar ( 125 ) ;
      } 
      break ;
    } 
    print ( 65960L ) ;
    begintokenlist ( mem [memtop - 3 ].hh .v.RH , 5 ) ;
    {
      helpptr = 5 ;
      helpline [4 ]= 66471L ;
      helpline [3 ]= 66472L ;
      helpline [2 ]= 66473L ;
      helpline [1 ]= 66474L ;
      helpline [0 ]= 66475L ;
    } 
    error () ;
  } 
} 
void 
extrarightbrace ( void ) 
{
  extrarightbrace_regmem 
  {
    if ( interaction == 3 ) 
    ;
    if ( filelineerrorstylep ) 
    printfileline () ;
    else printnl ( 65544L ) ;
    print ( 66482L ) ;
  } 
  switch ( curgroup ) 
  {case 14 : 
    printesc ( 65832L ) ;
    break ;
  case 15 : 
    printchar ( 36 ) ;
    break ;
  case 16 : 
    printesc ( 66288L ) ;
    break ;
  } 
  {
    helpptr = 5 ;
    helpline [4 ]= 66483L ;
    helpline [3 ]= 66484L ;
    helpline [2 ]= 66485L ;
    helpline [1 ]= 66486L ;
    helpline [0 ]= 66487L ;
  } 
  error () ;
  incr ( alignstate ) ;
} 
void 
normalparagraph ( void ) 
{
  normalparagraph_regmem 
  if ( eqtb [7892283L ].cint != 0 ) 
  eqworddefine ( 7892283L , 0 ) ;
  if ( eqtb [9006737L ].cint != 0 ) 
  eqworddefine ( 9006737L , 0 ) ;
  if ( eqtb [7892305L ].cint != 1 ) 
  eqworddefine ( 7892305L , 1 ) ;
  if ( eqtb [1206295L ].hh .v.RH != -268435455L ) 
  eqdefine ( 1206295L , 121 , -268435455L ) ;
  if ( eqtb [1206563L ].hh .v.RH != -268435455L ) 
  eqdefine ( 1206563L , 121 , -268435455L ) ;
} 
void 
zboxend ( integer boxcontext ) 
{
  boxend_regmem 
  halfword p  ;
  smallnumber a  ;
  if ( boxcontext < 1073741824L ) 
  {
    if ( curbox != -268435455L ) 
    {
      mem [curbox + 4 ].cint = boxcontext ;
      if ( abs ( curlist .modefield ) == 1 ) 
      {
	if ( preadjusttail != -268435455L ) 
	{
	  if ( memtop - 14 != preadjusttail ) 
	  {
	    mem [curlist .tailfield ].hh .v.RH = mem [memtop - 14 ].hh 
	    .v.RH ;
	    curlist .tailfield = preadjusttail ;
	  } 
	  preadjusttail = -268435455L ;
	} 
	appendtovlist ( curbox ) ;
	if ( adjusttail != -268435455L ) 
	{
	  if ( memtop - 5 != adjusttail ) 
	  {
	    mem [curlist .tailfield ].hh .v.RH = mem [memtop - 5 ].hh 
	    .v.RH ;
	    curlist .tailfield = adjusttail ;
	  } 
	  adjusttail = -268435455L ;
	} 
	if ( curlist .modefield > 0 ) 
	buildpage () ;
      } 
      else {
	  
	if ( abs ( curlist .modefield ) == 105 ) 
	curlist .auxfield .hh .v.LH = 1000 ;
	else {
	    
	  p = newnoad () ;
	  mem [p + 1 ].hh .v.RH = 2 ;
	  mem [p + 1 ].hh .v.LH = curbox ;
	  curbox = p ;
	} 
	mem [curlist .tailfield ].hh .v.RH = curbox ;
	curlist .tailfield = curbox ;
      } 
    } 
  } 
  else if ( boxcontext < 1073807360L ) 
  {
    if ( boxcontext < 1073774592L ) 
    {
      curval = boxcontext - 1073741824L ;
      a = 0 ;
    } 
    else {
	
      curval = boxcontext - 1073774592L ;
      a = 4 ;
    } 
    if ( curval < 256 ) {
	
      if ( ( a >= 4 ) ) 
      geqdefine ( 1206567L + curval , 122 , curbox ) ;
      else eqdefine ( 1206567L + curval , 122 , curbox ) ;
    } 
    else {
	
      findsaelement ( 4 , curval , true ) ;
      if ( ( a >= 4 ) ) 
      gsadef ( curptr , curbox ) ;
      else sadef ( curptr , curbox ) ;
    } 
  } 
  else if ( curbox != -268435455L ) {
      
    if ( boxcontext > 1073807360L ) 
    {
      do {
	  getxtoken () ;
      } while ( ! ( ( curcmd != 10 ) && ( curcmd != 0 ) ) ) ;
      if ( ( ( curcmd == 26 ) && ( abs ( curlist .modefield ) != 1 ) ) || ( ( 
      curcmd == 27 ) && ( abs ( curlist .modefield ) == 1 ) ) ) 
      {
	appendglue () ;
	mem [curlist .tailfield ].hh.b1 = boxcontext - ( 1073807261L ) ;
	mem [curlist .tailfield + 1 ].hh .v.RH = curbox ;
      } 
      else {
	  
	{
	  if ( interaction == 3 ) 
	  ;
	  if ( filelineerrorstylep ) 
	  printfileline () ;
	  else printnl ( 65544L ) ;
	  print ( 66500L ) ;
	} 
	{
	  helpptr = 3 ;
	  helpline [2 ]= 66501L ;
	  helpline [1 ]= 66502L ;
	  helpline [0 ]= 66503L ;
	} 
	backerror () ;
	flushnodelist ( curbox ) ;
      } 
    } 
    else shipout ( curbox ) ;
  } 
} 
void 
zbeginbox ( integer boxcontext ) 
{
  /* 10 30 */ beginbox_regmem 
  halfword p, q  ;
  halfword r  ;
  boolean fm  ;
  halfword tx  ;
  quarterword m  ;
  halfword k  ;
  halfword n  ;
  switch ( curchr ) 
  {case 0 : 
    {
      scanregisternum () ;
      if ( curval < 256 ) 
      curbox = eqtb [1206567L + curval ].hh .v.RH ;
      else {
	  
	findsaelement ( 4 , curval , false ) ;
	if ( curptr == -268435455L ) 
	curbox = -268435455L ;
	else curbox = mem [curptr + 1 ].hh .v.RH ;
      } 
      if ( curval < 256 ) 
      eqtb [1206567L + curval ].hh .v.RH = -268435455L ;
      else {
	  
	findsaelement ( 4 , curval , false ) ;
	if ( curptr != -268435455L ) 
	{
	  mem [curptr + 1 ].hh .v.RH = -268435455L ;
	  incr ( mem [curptr + 1 ].hh .v.LH ) ;
	  deletesaref ( curptr ) ;
	} 
      } 
    } 
    break ;
  case 1 : 
    {
      scanregisternum () ;
      if ( curval < 256 ) 
      q = eqtb [1206567L + curval ].hh .v.RH ;
      else {
	  
	findsaelement ( 4 , curval , false ) ;
	if ( curptr == -268435455L ) 
	q = -268435455L ;
	else q = mem [curptr + 1 ].hh .v.RH ;
      } 
      curbox = copynodelist ( q ) ;
    } 
    break ;
  case 2 : 
    {
      curbox = -268435455L ;
      if ( abs ( curlist .modefield ) == 209 ) 
      {
	youcant () ;
	{
	  helpptr = 1 ;
	  helpline [0 ]= 66505L ;
	} 
	error () ;
      } 
      else if ( ( curlist .modefield == 1 ) && ( curlist .headfield == curlist 
      .tailfield ) ) 
      {
	youcant () ;
	{
	  helpptr = 2 ;
	  helpline [1 ]= 66506L ;
	  helpline [0 ]= 66507L ;
	} 
	error () ;
      } 
      else {
	  
	tx = curlist .tailfield ;
	if ( ! ( tx >= himemmin ) ) {
	    
	  if ( ( mem [tx ].hh.b0 == 9 ) && ( mem [tx ].hh.b1 == 3 ) ) 
	  {
	    r = curlist .headfield ;
	    do {
		q = r ;
	      r = mem [q ].hh .v.RH ;
	    } while ( ! ( r == tx ) ) ;
	    tx = q ;
	  } 
	} 
	if ( ! ( tx >= himemmin ) ) {
	    
	  if ( ( mem [tx ].hh.b0 == 0 ) || ( mem [tx ].hh.b0 == 1 ) ) 
	  {
	    q = curlist .headfield ;
	    p = -268435455L ;
	    do {
		r = p ;
	      p = q ;
	      fm = false ;
	      if ( ! ( q >= himemmin ) ) {
		  
		if ( mem [q ].hh.b0 == 7 ) 
		{
		  {register integer for_end; m = 1 ;for_end = mem [q ]
		  .hh.b1 ; if ( m <= for_end) do 
		    p = mem [p ].hh .v.RH ;
		  while ( m++ < for_end ) ;} 
		  if ( p == tx ) 
		  goto lab30 ;
		} 
		else if ( ( mem [q ].hh.b0 == 9 ) && ( mem [q ].hh.b1 == 2 
		) ) 
		fm = true ;
	      } 
	      q = mem [p ].hh .v.RH ;
	    } while ( ! ( q == tx ) ) ;
	    q = mem [tx ].hh .v.RH ;
	    mem [p ].hh .v.RH = q ;
	    mem [tx ].hh .v.RH = -268435455L ;
	    if ( q == -268435455L ) {
		
	      if ( fm ) 
	      confusion ( 66504L ) ;
	      else curlist .tailfield = p ;
	    } 
	    else if ( fm ) 
	    {
	      curlist .tailfield = r ;
	      mem [r ].hh .v.RH = -268435455L ;
	      flushnodelist ( p ) ;
	    } 
	    curbox = tx ;
	    mem [curbox + 4 ].cint = 0 ;
	  } 
	} 
	lab30: ;
      } 
    } 
    break ;
  case 3 : 
    {
      scanregisternum () ;
      n = curval ;
      if ( ! scankeyword ( 66252L ) ) 
      {
	{
	  if ( interaction == 3 ) 
	  ;
	  if ( filelineerrorstylep ) 
	  printfileline () ;
	  else printnl ( 65544L ) ;
	  print ( 66508L ) ;
	} 
	{
	  helpptr = 2 ;
	  helpline [1 ]= 66509L ;
	  helpline [0 ]= 66510L ;
	} 
	error () ;
      } 
      scandimen ( false , false , false ) ;
      curbox = vsplit ( n , curval ) ;
    } 
    break ;
    default: 
    {
      k = curchr - 4 ;
      savestack [saveptr + 0 ].cint = boxcontext ;
      if ( k == 105 ) {
	  
	if ( ( boxcontext < 1073741824L ) && ( abs ( curlist .modefield ) == 1 
	) ) 
	scanspec ( 3 , true ) ;
	else scanspec ( 2 , true ) ;
      } 
      else {
	  
	if ( k == 1 ) 
	scanspec ( 4 , true ) ;
	else {
	    
	  scanspec ( 5 , true ) ;
	  k = 1 ;
	} 
	normalparagraph () ;
      } 
      pushnest () ;
      curlist .modefield = - (integer) k ;
      if ( k == 1 ) 
      {
	curlist .auxfield .cint = -65536000L ;
	if ( eqtb [1206301L ].hh .v.RH != -268435455L ) 
	begintokenlist ( eqtb [1206301L ].hh .v.RH , 12 ) ;
      } 
      else {
	  
	curlist .auxfield .hh .v.LH = 1000 ;
	if ( eqtb [1206300L ].hh .v.RH != -268435455L ) 
	begintokenlist ( eqtb [1206300L ].hh .v.RH , 11 ) ;
      } 
      return ;
    } 
    break ;
  } 
  boxend ( boxcontext ) ;
} 
void 
zscanbox ( integer boxcontext ) 
{
  scanbox_regmem 
  do {
      getxtoken () ;
  } while ( ! ( ( curcmd != 10 ) && ( curcmd != 0 ) ) ) ;
  if ( curcmd == 20 ) 
  beginbox ( boxcontext ) ;
  else if ( ( boxcontext >= 1073807361L ) && ( ( curcmd == 36 ) || ( curcmd == 
  35 ) ) ) 
  {
    curbox = scanrulespec () ;
    boxend ( boxcontext ) ;
  } 
  else {
      
    {
      if ( interaction == 3 ) 
      ;
      if ( filelineerrorstylep ) 
      printfileline () ;
      else printnl ( 65544L ) ;
      print ( 66511L ) ;
    } 
    {
      helpptr = 3 ;
      helpline [2 ]= 66512L ;
      helpline [1 ]= 66513L ;
      helpline [0 ]= 66514L ;
    } 
    backerror () ;
  } 
} 
void 
zpackage ( smallnumber c ) 
{
  package_regmem 
  scaled h  ;
  halfword p  ;
  scaled d  ;
  integer u, v  ;
  d = eqtb [9006727L ].cint ;
  u = eqtb [7892341L ].cint ;
  unsave () ;
  saveptr = saveptr - 3 ;
  v = eqtb [7892341L ].cint ;
  eqtb [7892341L ].cint = u ;
  if ( curlist .modefield == -105 ) 
  curbox = hpack ( mem [curlist .headfield ].hh .v.RH , savestack [saveptr 
  + 2 ].cint , savestack [saveptr + 1 ].cint ) ;
  else {
      
    curbox = vpackage ( mem [curlist .headfield ].hh .v.RH , savestack [
    saveptr + 2 ].cint , savestack [saveptr + 1 ].cint , d ) ;
    if ( c == 4 ) 
    {
      h = 0 ;
      p = mem [curbox + 5 ].hh .v.RH ;
      if ( p != -268435455L ) {
	  
	if ( mem [p ].hh.b0 <= 2 ) 
	h = mem [p + 3 ].cint ;
      } 
      mem [curbox + 2 ].cint = mem [curbox + 2 ].cint - h + mem [curbox + 
      3 ].cint ;
      mem [curbox + 3 ].cint = h ;
    } 
  } 
  eqtb [7892341L ].cint = v ;
  popnest () ;
  boxend ( savestack [saveptr + 0 ].cint ) ;
} 
smallnumber 
znormmin ( integer h ) 
{
  register smallnumber Result; normmin_regmem 
  if ( h <= 0 ) 
  Result = 1 ;
  else if ( h >= 63 ) 
  Result = 63 ;
  else Result = h ;
  return Result ;
} 
void 
znewgraf ( boolean indented ) 
{
  newgraf_regmem 
  curlist .pgfield = 0 ;
  if ( ( curlist .modefield == 1 ) || ( curlist .headfield != curlist 
  .tailfield ) ) 
  {
    mem [curlist .tailfield ].hh .v.RH = newparamglue ( 2 ) ;
    curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
  } 
  pushnest () ;
  curlist .modefield = 105 ;
  curlist .auxfield .hh .v.LH = 1000 ;
  if ( eqtb [7892314L ].cint <= 0 ) 
  curlang = 0 ;
  else if ( eqtb [7892314L ].cint > 255 ) 
  curlang = 0 ;
  else curlang = eqtb [7892314L ].cint ;
  curlist .auxfield .hh .v.RH = curlang ;
  curlist .pgfield = ( normmin ( eqtb [7892315L ].cint ) * 64 + normmin ( 
  eqtb [7892316L ].cint ) ) * 65536L + curlang ;
  if ( indented ) 
  {
    curlist .tailfield = newnullbox () ;
    mem [curlist .headfield ].hh .v.RH = curlist .tailfield ;
    mem [curlist .tailfield + 1 ].cint = eqtb [9006720L ].cint ;
    if ( ( insertsrcspecialeverypar ) ) 
    insertsrcspecial () ;
  } 
  if ( eqtb [1206297L ].hh .v.RH != -268435455L ) 
  begintokenlist ( eqtb [1206297L ].hh .v.RH , 8 ) ;
  if ( nestptr == 1 ) 
  buildpage () ;
} 
void 
indentinhmode ( void ) 
{
  indentinhmode_regmem 
  halfword p, q  ;
  if ( curchr > 0 ) 
  {
    p = newnullbox () ;
    mem [p + 1 ].cint = eqtb [9006720L ].cint ;
    if ( abs ( curlist .modefield ) == 105 ) 
    curlist .auxfield .hh .v.LH = 1000 ;
    else {
	
      q = newnoad () ;
      mem [q + 1 ].hh .v.RH = 2 ;
      mem [q + 1 ].hh .v.LH = p ;
      p = q ;
    } 
    {
      mem [curlist .tailfield ].hh .v.RH = p ;
      curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
    } 
  } 
} 
void 
headforvmode ( void ) 
{
  headforvmode_regmem 
  if ( curlist .modefield < 0 ) {
      
    if ( curcmd != 36 ) 
    offsave () ;
    else {
	
      {
	if ( interaction == 3 ) 
	;
	if ( filelineerrorstylep ) 
	printfileline () ;
	else printnl ( 65544L ) ;
	print ( 66035L ) ;
      } 
      printesc ( 65837L ) ;
      print ( 66517L ) ;
      {
	helpptr = 2 ;
	helpline [1 ]= 66518L ;
	helpline [0 ]= 66519L ;
      } 
      error () ;
    } 
  } 
  else {
      
    backinput () ;
    curtok = partoken ;
    backinput () ;
    curinput .indexfield = 5 ;
  } 
} 
void 
endgraf ( void ) 
{
  endgraf_regmem 
  if ( curlist .modefield == 105 ) 
  {
    if ( curlist .headfield == curlist .tailfield ) 
    popnest () ;
    else linebreak ( false ) ;
    if ( curlist .eTeXauxfield != -268435455L ) 
    {
      flushlist ( curlist .eTeXauxfield ) ;
      curlist .eTeXauxfield = -268435455L ;
    } 
    normalparagraph () ;
    errorcount = 0 ;
  } 
} 
void 
begininsertoradjust ( void ) 
{
  begininsertoradjust_regmem 
  if ( curcmd == 38 ) 
  curval = 255 ;
  else {
      
    scaneightbitint () ;
    if ( curval == 255 ) 
    {
      {
	if ( interaction == 3 ) 
	;
	if ( filelineerrorstylep ) 
	printfileline () ;
	else printnl ( 65544L ) ;
	print ( 66520L ) ;
      } 
      printesc ( 65620L ) ;
      printint ( 255 ) ;
      {
	helpptr = 1 ;
	helpline [0 ]= 66521L ;
      } 
      error () ;
      curval = 0 ;
    } 
  } 
  savestack [saveptr + 0 ].cint = curval ;
  if ( ( curcmd == 38 ) && scankeyword ( 66522L ) ) 
  savestack [saveptr + 1 ].cint = 1 ;
  else savestack [saveptr + 1 ].cint = 0 ;
  saveptr = saveptr + 2 ;
  newsavelevel ( 11 ) ;
  scanleftbrace () ;
  normalparagraph () ;
  pushnest () ;
  curlist .modefield = -1 ;
  curlist .auxfield .cint = -65536000L ;
} 
void 
makemark ( void ) 
{
  makemark_regmem 
  halfword p  ;
  halfword c  ;
  if ( curchr == 0 ) 
  c = 0 ;
  else {
      
    scanregisternum () ;
    c = curval ;
  } 
  p = scantoks ( false , true ) ;
  p = getnode ( 2 ) ;
  mem [p + 1 ].hh .v.LH = c ;
  mem [p ].hh.b0 = 4 ;
  mem [p ].hh.b1 = 0 ;
  mem [p + 1 ].hh .v.RH = defref ;
  mem [curlist .tailfield ].hh .v.RH = p ;
  curlist .tailfield = p ;
} 
void 
appendpenalty ( void ) 
{
  appendpenalty_regmem 
  scanint () ;
  {
    mem [curlist .tailfield ].hh .v.RH = newpenalty ( curval ) ;
    curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
  } 
  if ( curlist .modefield == 1 ) 
  buildpage () ;
} 
void 
deletelast ( void ) 
{
  /* 10 */ deletelast_regmem 
  halfword p, q  ;
  halfword r  ;
  boolean fm  ;
  halfword tx  ;
  quarterword m  ;
  if ( ( curlist .modefield == 1 ) && ( curlist .tailfield == curlist 
  .headfield ) ) 
  {
    if ( ( curchr != 10 ) || ( lastglue != 1073741823L ) ) 
    {
      youcant () ;
      {
	helpptr = 2 ;
	helpline [1 ]= 66506L ;
	helpline [0 ]= 66523L ;
      } 
      if ( curchr == 11 ) 
      helpline [0 ]= ( 66524L ) ;
      else if ( curchr != 10 ) 
      helpline [0 ]= ( 66525L ) ;
      error () ;
    } 
  } 
  else {
      
    tx = curlist .tailfield ;
    if ( ! ( tx >= himemmin ) ) {
	
      if ( ( mem [tx ].hh.b0 == 9 ) && ( mem [tx ].hh.b1 == 3 ) ) 
      {
	r = curlist .headfield ;
	do {
	    q = r ;
	  r = mem [q ].hh .v.RH ;
	} while ( ! ( r == tx ) ) ;
	tx = q ;
      } 
    } 
    if ( ! ( tx >= himemmin ) ) {
	
      if ( mem [tx ].hh.b0 == curchr ) 
      {
	q = curlist .headfield ;
	p = -268435455L ;
	do {
	    r = p ;
	  p = q ;
	  fm = false ;
	  if ( ! ( q >= himemmin ) ) {
	      
	    if ( mem [q ].hh.b0 == 7 ) 
	    {
	      {register integer for_end; m = 1 ;for_end = mem [q ].hh.b1 
	      ; if ( m <= for_end) do 
		p = mem [p ].hh .v.RH ;
	      while ( m++ < for_end ) ;} 
	      if ( p == tx ) 
	      return ;
	    } 
	    else if ( ( mem [q ].hh.b0 == 9 ) && ( mem [q ].hh.b1 == 2 ) ) 
	    fm = true ;
	  } 
	  q = mem [p ].hh .v.RH ;
	} while ( ! ( q == tx ) ) ;
	q = mem [tx ].hh .v.RH ;
	mem [p ].hh .v.RH = q ;
	mem [tx ].hh .v.RH = -268435455L ;
	if ( q == -268435455L ) {
	    
	  if ( fm ) 
	  confusion ( 66504L ) ;
	  else curlist .tailfield = p ;
	} 
	else if ( fm ) 
	{
	  curlist .tailfield = r ;
	  mem [r ].hh .v.RH = -268435455L ;
	  flushnodelist ( p ) ;
	} 
	flushnodelist ( tx ) ;
      } 
    } 
  } 
} 
void 
unpackage ( void ) 
{
  /* 30 10 */ unpackage_regmem 
  halfword p  ;
  halfword r  ;
  unsigned char c  ;
  if ( curchr > 1 ) 
  {
    mem [curlist .tailfield ].hh .v.RH = discptr [curchr ];
    discptr [curchr ]= -268435455L ;
    goto lab30 ;
  } 
  c = curchr ;
  scanregisternum () ;
  if ( curval < 256 ) 
  p = eqtb [1206567L + curval ].hh .v.RH ;
  else {
      
    findsaelement ( 4 , curval , false ) ;
    if ( curptr == -268435455L ) 
    p = -268435455L ;
    else p = mem [curptr + 1 ].hh .v.RH ;
  } 
  if ( p == -268435455L ) 
  return ;
  if ( ( abs ( curlist .modefield ) == 209 ) || ( ( abs ( curlist .modefield ) 
  == 1 ) && ( mem [p ].hh.b0 != 1 ) ) || ( ( abs ( curlist .modefield ) == 
  105 ) && ( mem [p ].hh.b0 != 0 ) ) ) 
  {
    {
      if ( interaction == 3 ) 
      ;
      if ( filelineerrorstylep ) 
      printfileline () ;
      else printnl ( 65544L ) ;
      print ( 66533L ) ;
    } 
    {
      helpptr = 3 ;
      helpline [2 ]= 66534L ;
      helpline [1 ]= 66535L ;
      helpline [0 ]= 66536L ;
    } 
    error () ;
    return ;
  } 
  if ( c == 1 ) 
  mem [curlist .tailfield ].hh .v.RH = copynodelist ( mem [p + 5 ].hh 
  .v.RH ) ;
  else {
      
    mem [curlist .tailfield ].hh .v.RH = mem [p + 5 ].hh .v.RH ;
    if ( curval < 256 ) 
    eqtb [1206567L + curval ].hh .v.RH = -268435455L ;
    else {
	
      findsaelement ( 4 , curval , false ) ;
      if ( curptr != -268435455L ) 
      {
	mem [curptr + 1 ].hh .v.RH = -268435455L ;
	incr ( mem [curptr + 1 ].hh .v.LH ) ;
	deletesaref ( curptr ) ;
      } 
    } 
    freenode ( p , 8 ) ;
  } 
  lab30: while ( mem [curlist .tailfield ].hh .v.RH != -268435455L ) {
      
    r = mem [curlist .tailfield ].hh .v.RH ;
    if ( ! ( r >= himemmin ) && ( mem [r ].hh.b0 == 40 ) ) 
    {
      mem [curlist .tailfield ].hh .v.RH = mem [r ].hh .v.RH ;
      freenode ( r , 3 ) ;
    } 
    curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
  } 
} 
void 
appenditaliccorrection ( void ) 
{
  /* 10 */ appenditaliccorrection_regmem 
  halfword p  ;
  internalfontnumber f  ;
  if ( curlist .tailfield != curlist .headfield ) 
  {
    if ( ( curlist .tailfield >= himemmin ) ) 
    p = curlist .tailfield ;
    else if ( mem [curlist .tailfield ].hh.b0 == 6 ) 
    p = curlist .tailfield + 1 ;
    else if ( ( mem [curlist .tailfield ].hh.b0 == 8 ) ) 
    {
      if ( ( ( mem [curlist .tailfield ].hh.b1 >= 40 ) && ( mem [curlist 
      .tailfield ].hh.b1 <= 41 ) ) ) 
      {
	{
	  mem [curlist .tailfield ].hh .v.RH = newkern ( 
	  getnativeitaliccorrection ( curlist .tailfield ) ) ;
	  curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
	} 
	mem [curlist .tailfield ].hh.b1 = 1 ;
      } 
      else if ( ( mem [curlist .tailfield ].hh.b1 == 42 ) ) 
      {
	{
	  mem [curlist .tailfield ].hh .v.RH = newkern ( 
	  getnativeglyphitaliccorrection ( curlist .tailfield ) ) ;
	  curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
	} 
	mem [curlist .tailfield ].hh.b1 = 1 ;
      } 
      return ;
    } 
    else return ;
    f = mem [p ].hh.b0 ;
    {
      mem [curlist .tailfield ].hh .v.RH = newkern ( fontinfo [italicbase [
      f ]+ ( fontinfo [charbase [f ]+ effectivechar ( true , f , mem [p ]
      .hh.b1 ) ].qqqq .b2 ) / 4 ].cint ) ;
      curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
    } 
    mem [curlist .tailfield ].hh.b1 = 1 ;
  } 
} 
void 
appenddiscretionary ( void ) 
{
  appenddiscretionary_regmem 
  integer c  ;
  {
    mem [curlist .tailfield ].hh .v.RH = newdisc () ;
    curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
  } 
  if ( curchr == 1 ) 
  {
    c = hyphenchar [eqtb [1206823L ].hh .v.RH ];
    if ( c >= 0 ) {
	
      if ( c <= 65535L ) 
      mem [curlist .tailfield + 1 ].hh .v.LH = newcharacter ( eqtb [
      1206823L ].hh .v.RH , c ) ;
    } 
  } 
  else {
      
    incr ( saveptr ) ;
    savestack [saveptr - 1 ].cint = 0 ;
    newsavelevel ( 10 ) ;
    scanleftbrace () ;
    pushnest () ;
    curlist .modefield = -105 ;
    curlist .auxfield .hh .v.LH = 1000 ;
  } 
} 
void 
builddiscretionary ( void ) 
{
  /* 30 10 */ builddiscretionary_regmem 
  halfword p, q  ;
  integer n  ;
  unsave () ;
  q = curlist .headfield ;
  p = mem [q ].hh .v.RH ;
  n = 0 ;
  while ( p != -268435455L ) {
      
    if ( ! ( p >= himemmin ) ) {
	
      if ( mem [p ].hh.b0 > 2 ) {
	  
	if ( mem [p ].hh.b0 != 11 ) {
	    
	  if ( mem [p ].hh.b0 != 6 ) {
	      
	    if ( ( mem [p ].hh.b0 != 8 ) || ( ! ( ( mem [p ].hh.b1 >= 40 ) 
	    && ( mem [p ].hh.b1 <= 41 ) ) && ( mem [p ].hh.b1 != 42 ) ) ) 
	    {
	      {
		if ( interaction == 3 ) 
		;
		if ( filelineerrorstylep ) 
		printfileline () ;
		else printnl ( 65544L ) ;
		print ( 66543L ) ;
	      } 
	      {
		helpptr = 1 ;
		helpline [0 ]= 66544L ;
	      } 
	      error () ;
	      begindiagnostic () ;
	      printnl ( 66545L ) ;
	      showbox ( p ) ;
	      enddiagnostic ( true ) ;
	      flushnodelist ( p ) ;
	      mem [q ].hh .v.RH = -268435455L ;
	      goto lab30 ;
	    } 
	  } 
	} 
      } 
    } 
    q = p ;
    p = mem [q ].hh .v.RH ;
    incr ( n ) ;
  } 
  lab30: ;
  p = mem [curlist .headfield ].hh .v.RH ;
  popnest () ;
  switch ( savestack [saveptr - 1 ].cint ) 
  {case 0 : 
    mem [curlist .tailfield + 1 ].hh .v.LH = p ;
    break ;
  case 1 : 
    mem [curlist .tailfield + 1 ].hh .v.RH = p ;
    break ;
  case 2 : 
    {
      if ( ( n > 0 ) && ( abs ( curlist .modefield ) == 209 ) ) 
      {
	{
	  if ( interaction == 3 ) 
	  ;
	  if ( filelineerrorstylep ) 
	  printfileline () ;
	  else printnl ( 65544L ) ;
	  print ( 66537L ) ;
	} 
	printesc ( 65640L ) ;
	{
	  helpptr = 2 ;
	  helpline [1 ]= 66538L ;
	  helpline [0 ]= 66539L ;
	} 
	flushnodelist ( p ) ;
	n = 0 ;
	error () ;
      } 
      else mem [curlist .tailfield ].hh .v.RH = p ;
      if ( n <= 65535L ) 
      mem [curlist .tailfield ].hh.b1 = n ;
      else {
	  
	{
	  if ( interaction == 3 ) 
	  ;
	  if ( filelineerrorstylep ) 
	  printfileline () ;
	  else printnl ( 65544L ) ;
	  print ( 66540L ) ;
	} 
	{
	  helpptr = 2 ;
	  helpline [1 ]= 66541L ;
	  helpline [0 ]= 66542L ;
	} 
	error () ;
      } 
      if ( n > 0 ) 
      curlist .tailfield = q ;
      decr ( saveptr ) ;
      return ;
    } 
    break ;
  } 
  incr ( savestack [saveptr - 1 ].cint ) ;
  newsavelevel ( 10 ) ;
  scanleftbrace () ;
  pushnest () ;
  curlist .modefield = -105 ;
  curlist .auxfield .hh .v.LH = 1000 ;
} 
void 
makeaccent ( void ) 
{
  makeaccent_regmem 
  real s, t  ;
  halfword p, q, r  ;
  internalfontnumber f  ;
  scaled a, h, x, w, delta, lsb, rsb  ;
  fourquarters i  ;
  scancharnum () ;
  f = eqtb [1206823L ].hh .v.RH ;
  p = newcharacter ( f , curval ) ;
  if ( p != -268435455L ) 
  {
    x = fontinfo [5 + parambase [f ]].cint ;
    s = fontinfo [1 + parambase [f ]].cint / ((double) 65536.0 ) ;
    if ( ( ( fontarea [f ]== 65535L ) || ( fontarea [f ]== 65534L ) ) ) 
    {
      a = mem [p + 1 ].cint ;
      if ( a == 0 ) 
      getnativecharsidebearings ( f , curval , addressof ( lsb ) , addressof ( 
      rsb ) ) ;
    } 
    else a = fontinfo [widthbase [f ]+ fontinfo [charbase [f ]+ 
    effectivechar ( true , f , mem [p ].hh.b1 ) ].qqqq .b0 ].cint ;
    doassignments () ;
    q = -268435455L ;
    f = eqtb [1206823L ].hh .v.RH ;
    if ( ( curcmd == 11 ) || ( curcmd == 12 ) || ( curcmd == 68 ) ) 
    {
      q = newcharacter ( f , curchr ) ;
      curval = curchr ;
    } 
    else if ( curcmd == 16 ) 
    {
      scancharnum () ;
      q = newcharacter ( f , curval ) ;
    } 
    else backinput () ;
    if ( q != -268435455L ) 
    {
      t = fontinfo [1 + parambase [f ]].cint / ((double) 65536.0 ) ;
      if ( ( ( fontarea [f ]== 65535L ) || ( fontarea [f ]== 65534L ) ) ) 
      {
	w = mem [q + 1 ].cint ;
	getnativecharheightdepth ( f , curval , addressof ( h ) , addressof ( 
	delta ) ) ;
      } 
      else {
	  
	i = fontinfo [charbase [f ]+ effectivechar ( true , f , mem [q ]
	.hh.b1 ) ].qqqq ;
	w = fontinfo [widthbase [f ]+ i .b0 ].cint ;
	h = fontinfo [heightbase [f ]+ ( i .b1 ) / 16 ].cint ;
      } 
      if ( h != x ) 
      {
	p = hpack ( p , 0 , 1 ) ;
	mem [p + 4 ].cint = x - h ;
      } 
      if ( ( ( fontarea [f ]== 65535L ) || ( fontarea [f ]== 65534L ) ) && 
      ( a == 0 ) ) 
      delta = round ( ( w - lsb + rsb ) / ((double) 2.0 ) + h * t - x * s ) ;
      else delta = round ( ( w - a ) / ((double) 2.0 ) + h * t - x * s ) ;
      r = newkern ( delta ) ;
      mem [r ].hh.b1 = 2 ;
      mem [curlist .tailfield ].hh .v.RH = r ;
      mem [r ].hh .v.RH = p ;
      curlist .tailfield = newkern ( - (integer) a - delta ) ;
      mem [curlist .tailfield ].hh.b1 = 2 ;
      mem [p ].hh .v.RH = curlist .tailfield ;
      p = q ;
    } 
    mem [curlist .tailfield ].hh .v.RH = p ;
    curlist .tailfield = p ;
    curlist .auxfield .hh .v.LH = 1000 ;
  } 
} 
void 
alignerror ( void ) 
{
  alignerror_regmem 
  if ( abs ( alignstate ) > 2 ) 
  {
    {
      if ( interaction == 3 ) 
      ;
      if ( filelineerrorstylep ) 
      printfileline () ;
      else printnl ( 65544L ) ;
      print ( 66550L ) ;
    } 
    printcmdchr ( curcmd , curchr ) ;
    if ( curtok == 8388646L ) 
    {
      {
	helpptr = 6 ;
	helpline [5 ]= 66551L ;
	helpline [4 ]= 66552L ;
	helpline [3 ]= 66553L ;
	helpline [2 ]= 66554L ;
	helpline [1 ]= 66555L ;
	helpline [0 ]= 66556L ;
      } 
    } 
    else {
	
      {
	helpptr = 5 ;
	helpline [4 ]= 66551L ;
	helpline [3 ]= 66557L ;
	helpline [2 ]= 66554L ;
	helpline [1 ]= 66555L ;
	helpline [0 ]= 66556L ;
      } 
    } 
    error () ;
  } 
  else {
      
    backinput () ;
    if ( alignstate < 0 ) 
    {
      {
	if ( interaction == 3 ) 
	;
	if ( filelineerrorstylep ) 
	printfileline () ;
	else printnl ( 65544L ) ;
	print ( 65991L ) ;
      } 
      incr ( alignstate ) ;
      curtok = 2097275L ;
    } 
    else {
	
      {
	if ( interaction == 3 ) 
	;
	if ( filelineerrorstylep ) 
	printfileline () ;
	else printnl ( 65544L ) ;
	print ( 66546L ) ;
      } 
      decr ( alignstate ) ;
      curtok = 4194429L ;
    } 
    {
      helpptr = 3 ;
      helpline [2 ]= 66547L ;
      helpline [1 ]= 66548L ;
      helpline [0 ]= 66549L ;
    } 
    inserror () ;
  } 
} 
void 
noalignerror ( void ) 
{
  noalignerror_regmem 
  {
    if ( interaction == 3 ) 
    ;
    if ( filelineerrorstylep ) 
    printfileline () ;
    else printnl ( 65544L ) ;
    print ( 66550L ) ;
  } 
  printesc ( 65849L ) ;
  {
    helpptr = 2 ;
    helpline [1 ]= 66558L ;
    helpline [0 ]= 66559L ;
  } 
  error () ;
} 
void 
omiterror ( void ) 
{
  omiterror_regmem 
  {
    if ( interaction == 3 ) 
    ;
    if ( filelineerrorstylep ) 
    printfileline () ;
    else printnl ( 65544L ) ;
    print ( 66550L ) ;
  } 
  printesc ( 65852L ) ;
  {
    helpptr = 2 ;
    helpline [1 ]= 66560L ;
    helpline [0 ]= 66559L ;
  } 
  error () ;
} 
void 
doendv ( void ) 
{
  doendv_regmem 
  baseptr = inputptr ;
  inputstack [baseptr ]= curinput ;
  while ( ( inputstack [baseptr ].indexfield != 2 ) && ( inputstack [
  baseptr ].locfield == -268435455L ) && ( inputstack [baseptr ].statefield 
  == 0 ) ) decr ( baseptr ) ;
  if ( ( inputstack [baseptr ].indexfield != 2 ) || ( inputstack [baseptr ]
  .locfield != -268435455L ) || ( inputstack [baseptr ].statefield != 0 ) ) 
  fatalerror ( 65925L ) ;
  if ( curgroup == 6 ) 
  {
    endgraf () ;
    if ( fincol () ) 
    finrow () ;
  } 
  else offsave () ;
} 
void 
cserror ( void ) 
{
  cserror_regmem 
  {
    if ( interaction == 3 ) 
    ;
    if ( filelineerrorstylep ) 
    printfileline () ;
    else printnl ( 65544L ) ;
    print ( 66169L ) ;
  } 
  printesc ( 65819L ) ;
  {
    helpptr = 1 ;
    helpline [0 ]= 66562L ;
  } 
  error () ;
} 
void 
zpushmath ( groupcode c ) 
{
  pushmath_regmem 
  pushnest () ;
  curlist .modefield = -209 ;
  curlist .auxfield .cint = -268435455L ;
  newsavelevel ( c ) ;
} 
void 
zjustcopy ( halfword p , halfword h , halfword t ) 
{
  /* 40 45 */ justcopy_regmem 
  halfword r  ;
  unsigned char words  ;
  while ( p != -268435455L ) {
      
    words = 1 ;
    if ( ( p >= himemmin ) ) 
    r = getavail () ;
    else switch ( mem [p ].hh.b0 ) 
    {case 0 : 
    case 1 : 
      {
	r = getnode ( 8 ) ;
	mem [r + 7 ].hh .v.LH = mem [p + 7 ].hh .v.LH ;
	mem [r + 7 ].hh .v.RH = mem [p + 7 ].hh .v.RH ;
	mem [r + 6 ]= mem [p + 6 ];
	mem [r + 5 ]= mem [p + 5 ];
	words = 5 ;
	mem [r + 5 ].hh .v.RH = -268435455L ;
      } 
      break ;
    case 2 : 
      {
	r = getnode ( 5 ) ;
	words = 5 ;
      } 
      break ;
    case 6 : 
      {
	r = getavail () ;
	mem [r ]= mem [p + 1 ];
	goto lab40 ;
      } 
      break ;
    case 11 : 
    case 9 : 
      {
	words = 3 ;
	r = getnode ( words ) ;
      } 
      break ;
    case 10 : 
      {
	r = getnode ( 3 ) ;
	incr ( mem [mem [p + 1 ].hh .v.LH ].hh .v.RH ) ;
	mem [r + 2 ].hh .v.LH = mem [p + 2 ].hh .v.LH ;
	mem [r + 2 ].hh .v.RH = mem [p + 2 ].hh .v.RH ;
	mem [r + 1 ].hh .v.LH = mem [p + 1 ].hh .v.LH ;
	mem [r + 1 ].hh .v.RH = -268435455L ;
      } 
      break ;
    case 8 : 
      switch ( mem [p ].hh.b1 ) 
      {case 0 : 
	{
	  r = getnode ( 3 ) ;
	  words = 3 ;
	} 
	break ;
      case 1 : 
      case 3 : 
      case 4 : 
	{
	  r = getnode ( 2 ) ;
	  incr ( mem [mem [p + 1 ].hh .v.RH ].hh .v.LH ) ;
	  words = 2 ;
	} 
	break ;
      case 2 : 
      case 5 : 
	{
	  r = getnode ( 2 ) ;
	  words = 2 ;
	} 
	break ;
      case 40 : 
      case 41 : 
	{
	  words = mem [p + 4 ].qqqq .b0 ;
	  r = getnode ( words ) ;
	  while ( words > 0 ) {
	      
	    decr ( words ) ;
	    mem [r + words ]= mem [p + words ];
	  } 
	  mem [r + 5 ].ptr = nullptr ;
	  mem [r + 4 ].qqqq .b3 = 0 ;
	  copynativeglyphinfo ( p , r ) ;
	} 
	break ;
      case 42 : 
	{
	  r = getnode ( 5 ) ;
	  words = 5 ;
	} 
	break ;
      case 43 : 
      case 44 : 
	{
	  words = ( 9 + ( mem [p + 4 ].hh.b0 + sizeof ( memoryword ) - 1 ) / 
	  sizeof ( memoryword ) ) ;
	  r = getnode ( words ) ;
	} 
	break ;
      case 23 : 
	r = getnode ( 2 ) ;
	break ;
	default: 
	confusion ( 66771L ) ;
	break ;
      } 
      break ;
      default: 
      goto lab45 ;
      break ;
    } 
    while ( words > 0 ) {
	
      decr ( words ) ;
      mem [r + words ]= mem [p + words ];
    } 
    lab40: mem [h ].hh .v.RH = r ;
    h = r ;
    lab45: p = mem [p ].hh .v.RH ;
  } 
  mem [h ].hh .v.RH = t ;
} 
void 
zjustreverse ( halfword p ) 
{
  /* 30 */ justreverse_regmem 
  halfword l  ;
  halfword t  ;
  halfword q  ;
  halfword m, n  ;
  m = -268435455L ;
  n = -268435455L ;
  if ( mem [memtop - 3 ].hh .v.RH == -268435455L ) 
  {
    justcopy ( mem [p ].hh .v.RH , memtop - 3 , -268435455L ) ;
    q = mem [memtop - 3 ].hh .v.RH ;
  } 
  else {
      
    q = mem [p ].hh .v.RH ;
    mem [p ].hh .v.RH = -268435455L ;
    flushnodelist ( mem [memtop - 3 ].hh .v.RH ) ;
  } 
  t = newedge ( curdir , 0 ) ;
  l = t ;
  curdir = 1 - curdir ;
  while ( q != -268435455L ) if ( ( q >= himemmin ) ) 
  do {
      p = q ;
    q = mem [p ].hh .v.RH ;
    mem [p ].hh .v.RH = l ;
    l = p ;
  } while ( ! ( ! ( q >= himemmin ) ) ) ;
  else {
      
    p = q ;
    q = mem [p ].hh .v.RH ;
    if ( mem [p ].hh.b0 == 9 ) {
	
      if ( odd ( mem [p ].hh.b1 ) ) {
	  
	if ( mem [LRptr ].hh .v.LH != ( 4 * ( mem [p ].hh.b1 / 4 ) + 3 ) ) 
	{
	  mem [p ].hh.b0 = 11 ;
	  incr ( LRproblems ) ;
	} 
	else {
	    
	  {
	    tempptr = LRptr ;
	    LRptr = mem [tempptr ].hh .v.RH ;
	    {
	      mem [tempptr ].hh .v.RH = avail ;
	      avail = tempptr ;
	;
#ifdef STAT
	      decr ( dynused ) ;
#endif /* STAT */
	    } 
	  } 
	  if ( n > -268435455L ) 
	  {
	    decr ( n ) ;
	    decr ( mem [p ].hh.b1 ) ;
	  } 
	  else {
	      
	    if ( m > -268435455L ) 
	    decr ( m ) ;
	    else {
		
	      mem [t + 1 ].cint = mem [p + 1 ].cint ;
	      mem [t ].hh .v.RH = q ;
	      freenode ( p , 3 ) ;
	      goto lab30 ;
	    } 
	    mem [p ].hh.b0 = 11 ;
	  } 
	} 
      } 
      else {
	  
	{
	  tempptr = getavail () ;
	  mem [tempptr ].hh .v.LH = ( 4 * ( mem [p ].hh.b1 / 4 ) + 3 ) ;
	  mem [tempptr ].hh .v.RH = LRptr ;
	  LRptr = tempptr ;
	} 
	if ( ( n > -268435455L ) || ( ( mem [p ].hh.b1 / 8 ) != curdir ) ) 
	{
	  incr ( n ) ;
	  incr ( mem [p ].hh.b1 ) ;
	} 
	else {
	    
	  mem [p ].hh.b0 = 11 ;
	  incr ( m ) ;
	} 
      } 
    } 
    mem [p ].hh .v.RH = l ;
    l = p ;
  } 
  goto lab30 ;
  mem [t + 1 ].cint = mem [p + 1 ].cint ;
  mem [t ].hh .v.RH = q ;
  freenode ( p , 2 ) ;
  lab30: mem [memtop - 3 ].hh .v.RH = l ;
} 
void 
initmath ( void ) 
{
  /* 21 40 45 30 */ initmath_regmem 
  scaled w  ;
  halfword j  ;
  integer x  ;
  scaled l  ;
  scaled s  ;
  halfword p  ;
  halfword q  ;
  internalfontnumber f  ;
  integer n  ;
  scaled v  ;
  scaled d  ;
  gettoken () ;
  if ( ( curcmd == 3 ) && ( curlist .modefield > 0 ) ) 
  {
    j = -268435455L ;
    w = -1073741823L ;
    if ( curlist .headfield == curlist .tailfield ) 
    {
      popnest () ;
      if ( curlist .eTeXauxfield == -268435455L ) 
      x = 0 ;
      else if ( mem [curlist .eTeXauxfield ].hh .v.LH >= 8 ) 
      x = -1 ;
      else x = 1 ;
    } 
    else {
	
      linebreak ( true ) ;
      if ( ( eTeXmode == 1 ) ) 
      {
	if ( eqtb [1205772L ].hh .v.RH == membot ) 
	j = newkern ( 0 ) ;
	else j = newparamglue ( 8 ) ;
	if ( eqtb [1205771L ].hh .v.RH == membot ) 
	p = newkern ( 0 ) ;
	else p = newparamglue ( 7 ) ;
	mem [p ].hh .v.RH = j ;
	j = newnullbox () ;
	mem [j + 1 ].cint = mem [justbox + 1 ].cint ;
	mem [j + 4 ].cint = mem [justbox + 4 ].cint ;
	mem [j + 5 ].hh .v.RH = p ;
	mem [j + 5 ].hh.b1 = mem [justbox + 5 ].hh.b1 ;
	mem [j + 5 ].hh.b0 = mem [justbox + 5 ].hh.b0 ;
	mem [j + 6 ].gr = mem [justbox + 6 ].gr ;
      } 
      v = mem [justbox + 4 ].cint ;
      if ( curlist .eTeXauxfield == -268435455L ) 
      x = 0 ;
      else if ( mem [curlist .eTeXauxfield ].hh .v.LH >= 8 ) 
      x = -1 ;
      else x = 1 ;
      if ( x >= 0 ) 
      {
	p = mem [justbox + 5 ].hh .v.RH ;
	mem [memtop - 3 ].hh .v.RH = -268435455L ;
      } 
      else {
	  
	v = - (integer) v - mem [justbox + 1 ].cint ;
	p = newmath ( 0 , 6 ) ;
	mem [memtop - 3 ].hh .v.RH = p ;
	justcopy ( mem [justbox + 5 ].hh .v.RH , p , newmath ( 0 , 7 ) ) ;
	curdir = 1 ;
      } 
      v = v + 2 * fontinfo [6 + parambase [eqtb [1206823L ].hh .v.RH ]]
      .cint ;
      if ( ( eqtb [7892339L ].cint > 0 ) ) 
      {
	tempptr = getavail () ;
	mem [tempptr ].hh .v.LH = 0 ;
	mem [tempptr ].hh .v.RH = LRptr ;
	LRptr = tempptr ;
      } 
      while ( p != -268435455L ) {
	  
	lab21: if ( ( p >= himemmin ) ) 
	{
	  f = mem [p ].hh.b0 ;
	  d = fontinfo [widthbase [f ]+ fontinfo [charbase [f ]+ 
	  effectivechar ( true , f , mem [p ].hh.b1 ) ].qqqq .b0 ].cint ;
	  goto lab40 ;
	} 
	switch ( mem [p ].hh.b0 ) 
	{case 0 : 
	case 1 : 
	case 2 : 
	  {
	    d = mem [p + 1 ].cint ;
	    goto lab40 ;
	  } 
	  break ;
	case 6 : 
	  {
	    mem [memtop - 12 ]= mem [p + 1 ];
	    mem [memtop - 12 ].hh .v.RH = mem [p ].hh .v.RH ;
	    p = memtop - 12 ;
	    xtxligaturepresent = true ;
	    goto lab21 ;
	  } 
	  break ;
	case 11 : 
	  d = mem [p + 1 ].cint ;
	  break ;
	case 40 : 
	  d = mem [p + 1 ].cint ;
	  break ;
	case 9 : 
	  {
	    d = mem [p + 1 ].cint ;
	    if ( ( eqtb [7892339L ].cint > 0 ) ) {
		
	      if ( odd ( mem [p ].hh.b1 ) ) 
	      {
		if ( mem [LRptr ].hh .v.LH == ( 4 * ( mem [p ].hh.b1 / 4 ) 
		+ 3 ) ) 
		{
		  tempptr = LRptr ;
		  LRptr = mem [tempptr ].hh .v.RH ;
		  {
		    mem [tempptr ].hh .v.RH = avail ;
		    avail = tempptr ;
	;
#ifdef STAT
		    decr ( dynused ) ;
#endif /* STAT */
		  } 
		} 
		else if ( mem [p ].hh.b1 > 4 ) 
		{
		  w = 1073741823L ;
		  goto lab30 ;
		} 
	      } 
	      else {
		  
		{
		  tempptr = getavail () ;
		  mem [tempptr ].hh .v.LH = ( 4 * ( mem [p ].hh.b1 / 4 ) + 
		  3 ) ;
		  mem [tempptr ].hh .v.RH = LRptr ;
		  LRptr = tempptr ;
		} 
		if ( ( mem [p ].hh.b1 / 8 ) != curdir ) 
		{
		  justreverse ( p ) ;
		  p = memtop - 3 ;
		} 
	      } 
	    } 
	    else if ( mem [p ].hh.b1 >= 4 ) 
	    {
	      w = 1073741823L ;
	      goto lab30 ;
	    } 
	  } 
	  break ;
	case 14 : 
	  {
	    d = mem [p + 1 ].cint ;
	    curdir = mem [p ].hh.b1 ;
	  } 
	  break ;
	case 10 : 
	  {
	    q = mem [p + 1 ].hh .v.LH ;
	    d = mem [q + 1 ].cint ;
	    if ( mem [justbox + 5 ].hh.b0 == 1 ) 
	    {
	      if ( ( mem [justbox + 5 ].hh.b1 == mem [q ].hh.b0 ) && ( mem 
	      [q + 2 ].cint != 0 ) ) 
	      v = 1073741823L ;
	    } 
	    else if ( mem [justbox + 5 ].hh.b0 == 2 ) 
	    {
	      if ( ( mem [justbox + 5 ].hh.b1 == mem [q ].hh.b1 ) && ( mem 
	      [q + 3 ].cint != 0 ) ) 
	      v = 1073741823L ;
	    } 
	    if ( mem [p ].hh.b1 >= 100 ) 
	    goto lab40 ;
	  } 
	  break ;
	case 8 : 
	  if ( ( ( ( mem [p ].hh.b1 >= 40 ) && ( mem [p ].hh.b1 <= 41 ) ) 
	  ) || ( mem [p ].hh.b1 == 42 ) || ( mem [p ].hh.b1 == 43 ) || ( 
	  mem [p ].hh.b1 == 44 ) ) 
	  {
	    d = mem [p + 1 ].cint ;
	    goto lab40 ;
	  } 
	  else d = 0 ;
	  break ;
	  default: 
	  d = 0 ;
	  break ;
	} 
	if ( v < 1073741823L ) 
	v = v + d ;
	goto lab45 ;
	lab40: if ( v < 1073741823L ) 
	{
	  v = v + d ;
	  w = v ;
	} 
	else {
	    
	  w = 1073741823L ;
	  goto lab30 ;
	} 
	lab45: p = mem [p ].hh .v.RH ;
      } 
      lab30: if ( ( eqtb [7892339L ].cint > 0 ) ) 
      {
	while ( LRptr != -268435455L ) {
	    
	  tempptr = LRptr ;
	  LRptr = mem [tempptr ].hh .v.RH ;
	  {
	    mem [tempptr ].hh .v.RH = avail ;
	    avail = tempptr ;
	;
#ifdef STAT
	    decr ( dynused ) ;
#endif /* STAT */
	  } 
	} 
	if ( LRproblems != 0 ) 
	{
	  w = 1073741823L ;
	  LRproblems = 0 ;
	} 
      } 
      curdir = 0 ;
      flushnodelist ( mem [memtop - 3 ].hh .v.RH ) ;
    } 
    if ( eqtb [1206295L ].hh .v.RH == -268435455L ) {
	
      if ( ( eqtb [9006737L ].cint != 0 ) && ( ( ( eqtb [7892305L ].cint 
      >= 0 ) && ( curlist .pgfield + 2 > eqtb [7892305L ].cint ) ) || ( 
      curlist .pgfield + 1 < - (integer) eqtb [7892305L ].cint ) ) ) 
      {
	l = eqtb [9006723L ].cint - abs ( eqtb [9006737L ].cint ) ;
	if ( eqtb [9006737L ].cint > 0 ) 
	s = eqtb [9006737L ].cint ;
	else s = 0 ;
      } 
      else {
	  
	l = eqtb [9006723L ].cint ;
	s = 0 ;
      } 
    } 
    else {
	
      n = mem [eqtb [1206295L ].hh .v.RH ].hh .v.LH ;
      if ( curlist .pgfield + 2 >= n ) 
      p = eqtb [1206295L ].hh .v.RH + 2 * n ;
      else p = eqtb [1206295L ].hh .v.RH + 2 * ( curlist .pgfield + 2 ) ;
      s = mem [p - 1 ].cint ;
      l = mem [p ].cint ;
    } 
    pushmath ( 15 ) ;
    curlist .modefield = 209 ;
    eqworddefine ( 7892308L , -1 ) ;
    eqworddefine ( 9006733L , w ) ;
    curlist .eTeXauxfield = j ;
    if ( ( eTeXmode == 1 ) ) 
    eqworddefine ( 7892330L , x ) ;
    eqworddefine ( 9006734L , l ) ;
    eqworddefine ( 9006735L , s ) ;
    if ( eqtb [1206299L ].hh .v.RH != -268435455L ) 
    begintokenlist ( eqtb [1206299L ].hh .v.RH , 10 ) ;
    if ( nestptr == 1 ) 
    buildpage () ;
  } 
  else {
      
    backinput () ;
    {
      pushmath ( 15 ) ;
      eqworddefine ( 7892308L , -1 ) ;
      if ( ( insertsrcspecialeverymath ) ) 
      insertsrcspecial () ;
      if ( eqtb [1206298L ].hh .v.RH != -268435455L ) 
      begintokenlist ( eqtb [1206298L ].hh .v.RH , 9 ) ;
    } 
  } 
} 
void 
starteqno ( void ) 
{
  starteqno_regmem 
  savestack [saveptr + 0 ].cint = curchr ;
  incr ( saveptr ) ;
  {
    pushmath ( 15 ) ;
    eqworddefine ( 7892308L , -1 ) ;
    if ( ( insertsrcspecialeverymath ) ) 
    insertsrcspecial () ;
    if ( eqtb [1206298L ].hh .v.RH != -268435455L ) 
    begintokenlist ( eqtb [1206298L ].hh .v.RH , 9 ) ;
  } 
} 
void 
zscanmath ( halfword p ) 
{
  /* 20 21 10 */ scanmath_regmem 
  integer c  ;
  lab20: do {
      getxtoken () ;
  } while ( ! ( ( curcmd != 10 ) && ( curcmd != 0 ) ) ) ;
  lab21: switch ( curcmd ) 
  {case 11 : 
  case 12 : 
  case 68 : 
    {
      c = eqtb [5664040L + curchr ].hh .v.RH ;
      if ( mathcharfield ( c ) == 2097151L ) 
      {
	{
	  curcs = curchr + 1 ;
	  curcmd = eqtb [curcs ].hh.b0 ;
	  curchr = eqtb [curcs ].hh .v.RH ;
	  xtoken () ;
	  backinput () ;
	} 
	goto lab20 ;
      } 
    } 
    break ;
  case 16 : 
    {
      scancharnum () ;
      curchr = curval ;
      curcmd = 68 ;
      goto lab21 ;
    } 
    break ;
  case 17 : 
    if ( curchr == 2 ) 
    {
      scanmathclassint () ;
      c = setclassfield ( curval ) ;
      scanmathfamint () ;
      c = c + setfamilyfield ( curval ) ;
      scanusvnum () ;
      c = c + curval ;
    } 
    else if ( curchr == 1 ) 
    {
      scanxetexmathcharint () ;
      c = curval ;
    } 
    else {
	
      scanfifteenbitint () ;
      c = setclassfield ( curval / 4096 ) + setfamilyfield ( ( curval % 4096 ) 
      / 256 ) + ( curval % 256 ) ;
    } 
    break ;
  case 69 : 
    {
      c = setclassfield ( curchr / 4096 ) + setfamilyfield ( ( curchr % 4096 ) 
      / 256 ) + ( curchr % 256 ) ;
    } 
    break ;
  case 70 : 
    c = curchr ;
    break ;
  case 15 : 
    {
      if ( curchr == 1 ) 
      {
	scanmathclassint () ;
	c = setclassfield ( curval ) ;
	scanmathfamint () ;
	c = c + setfamilyfield ( curval ) ;
	scanusvnum () ;
	c = c + curval ;
      } 
      else {
	  
	scandelimiterint () ;
	c = curval / 4096 ;
	c = setclassfield ( c / 4096 ) + setfamilyfield ( ( c % 4096 ) / 256 ) 
	+ ( c % 256 ) ;
      } 
    } 
    break ;
    default: 
    {
      backinput () ;
      scanleftbrace () ;
      savestack [saveptr + 0 ].cint = p ;
      incr ( saveptr ) ;
      pushmath ( 9 ) ;
      return ;
    } 
    break ;
  } 
  mem [p ].hh .v.RH = 1 ;
  mem [p ].hh.b1 = c % 65536L ;
  if ( ( mathclassfield ( c ) == 7 ) && ( ( eqtb [7892308L ].cint >= 0 ) && 
  ( eqtb [7892308L ].cint < 256 ) ) ) 
  mem [p ].hh.b0 = eqtb [7892308L ].cint ;
  else mem [p ].hh.b0 = ( mathfamfield ( c ) ) ;
  mem [p ].hh.b0 = mem [p ].hh.b0 + ( mathcharfield ( c ) / 65536L ) * 256 
  ;
} 
void 
zsetmathchar ( integer c ) 
{
  setmathchar_regmem 
  halfword p  ;
  UnicodeScalar ch  ;
  if ( mathcharfield ( c ) == 2097151L ) 
  {
    curcs = curchr + 1 ;
    curcmd = eqtb [curcs ].hh.b0 ;
    curchr = eqtb [curcs ].hh .v.RH ;
    xtoken () ;
    backinput () ;
  } 
  else {
      
    p = newnoad () ;
    mem [p + 1 ].hh .v.RH = 1 ;
    ch = mathcharfield ( c ) ;
    mem [p + 1 ].hh.b1 = ch % 65536L ;
    mem [p + 1 ].hh.b0 = mathfamfield ( c ) ;
    if ( mathclassfield ( c ) == 7 ) 
    {
      if ( ( ( eqtb [7892308L ].cint >= 0 ) && ( eqtb [7892308L ].cint < 
      256 ) ) ) 
      mem [p + 1 ].hh.b0 = eqtb [7892308L ].cint ;
      mem [p ].hh.b0 = 16 ;
    } 
    else mem [p ].hh.b0 = 16 + mathclassfield ( c ) ;
    mem [p + 1 ].hh.b0 = mem [p + 1 ].hh.b0 + ( ch / 65536L ) * 256 ;
    mem [curlist .tailfield ].hh .v.RH = p ;
    curlist .tailfield = p ;
  } 
} 
void 
mathlimitswitch ( void ) 
{
  /* 10 */ mathlimitswitch_regmem 
  if ( curlist .headfield != curlist .tailfield ) {
      
    if ( mem [curlist .tailfield ].hh.b0 == 17 ) 
    {
      mem [curlist .tailfield ].hh.b1 = curchr ;
      return ;
    } 
  } 
  {
    if ( interaction == 3 ) 
    ;
    if ( filelineerrorstylep ) 
    printfileline () ;
    else printnl ( 65544L ) ;
    print ( 66566L ) ;
  } 
  {
    helpptr = 1 ;
    helpline [0 ]= 66567L ;
  } 
  error () ;
} 
void 
zscandelimiter ( halfword p , boolean r ) 
{
  scandelimiter_regmem 
  if ( r ) 
  {
    if ( curchr == 1 ) 
    {
      curval1 = 1073741824L ;
      scanmathfamint () ;
      curval1 = curval1 + curval * 2097152L ;
      scanusvnum () ;
      curval = curval1 + curval ;
    } 
    else scandelimiterint () ;
  } 
  else {
      
    do {
	getxtoken () ;
    } while ( ! ( ( curcmd != 10 ) && ( curcmd != 0 ) ) ) ;
    switch ( curcmd ) 
    {case 11 : 
    case 12 : 
      {
	curval = eqtb [7892608L + curchr ].cint ;
      } 
      break ;
    case 15 : 
      if ( curchr == 1 ) 
      {
	curval1 = 1073741824L ;
	scanmathclassint () ;
	scanmathfamint () ;
	curval1 = curval1 + curval * 2097152L ;
	scanusvnum () ;
	curval = curval1 + curval ;
      } 
      else scandelimiterint () ;
      break ;
      default: 
      {
	curval = -1 ;
      } 
      break ;
    } 
  } 
  if ( curval < 0 ) 
  {
    {
      {
	if ( interaction == 3 ) 
	;
	if ( filelineerrorstylep ) 
	printfileline () ;
	else printnl ( 65544L ) ;
	print ( 66568L ) ;
      } 
      {
	helpptr = 6 ;
	helpline [5 ]= 66569L ;
	helpline [4 ]= 66570L ;
	helpline [3 ]= 66571L ;
	helpline [2 ]= 66572L ;
	helpline [1 ]= 66573L ;
	helpline [0 ]= 66574L ;
      } 
      backerror () ;
      curval = 0 ;
    } 
  } 
  if ( curval >= 1073741824L ) 
  {
    mem [p ].qqqq .b0 = ( ( curval % 2097152L ) / 65536L ) * 256 + ( curval 
    / 2097152L ) % 256 ;
    mem [p ].qqqq .b1 = curval % 65536L ;
    mem [p ].qqqq .b2 = 0 ;
    mem [p ].qqqq .b3 = 0 ;
  } 
  else {
      
    mem [p ].qqqq .b0 = ( curval / 1048576L ) % 16 ;
    mem [p ].qqqq .b1 = ( curval / 4096 ) % 256 ;
    mem [p ].qqqq .b2 = ( curval / 256 ) % 16 ;
    mem [p ].qqqq .b3 = curval % 256 ;
  } 
} 
void 
mathradical ( void ) 
{
  mathradical_regmem 
  {
    mem [curlist .tailfield ].hh .v.RH = getnode ( 5 ) ;
    curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
  } 
  mem [curlist .tailfield ].hh.b0 = 24 ;
  mem [curlist .tailfield ].hh.b1 = 0 ;
  mem [curlist .tailfield + 1 ].hh = emptyfield ;
  mem [curlist .tailfield + 3 ].hh = emptyfield ;
  mem [curlist .tailfield + 2 ].hh = emptyfield ;
  scandelimiter ( curlist .tailfield + 4 , true ) ;
  scanmath ( curlist .tailfield + 1 ) ;
} 
void 
mathac ( void ) 
{
  mathac_regmem 
  integer c  ;
  if ( curcmd == 45 ) 
  {
    {
      if ( interaction == 3 ) 
      ;
      if ( filelineerrorstylep ) 
      printfileline () ;
      else printnl ( 65544L ) ;
      print ( 66577L ) ;
    } 
    printesc ( 65839L ) ;
    print ( 66578L ) ;
    {
      helpptr = 2 ;
      helpline [1 ]= 66579L ;
      helpline [0 ]= 66580L ;
    } 
    error () ;
  } 
  {
    mem [curlist .tailfield ].hh .v.RH = getnode ( 5 ) ;
    curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
  } 
  mem [curlist .tailfield ].hh.b0 = 28 ;
  mem [curlist .tailfield ].hh.b1 = 0 ;
  mem [curlist .tailfield + 1 ].hh = emptyfield ;
  mem [curlist .tailfield + 3 ].hh = emptyfield ;
  mem [curlist .tailfield + 2 ].hh = emptyfield ;
  mem [curlist .tailfield + 4 ].hh .v.RH = 1 ;
  if ( curchr == 1 ) 
  {
    if ( scankeyword ( 66575L ) ) 
    mem [curlist .tailfield ].hh.b1 = 1 ;
    else if ( scankeyword ( 66576L ) ) 
    {
      if ( scankeyword ( 66575L ) ) 
      mem [curlist .tailfield ].hh.b1 = 3 ;
      else mem [curlist .tailfield ].hh.b1 = 2 ;
    } 
    scanmathclassint () ;
    c = setclassfield ( curval ) ;
    scanmathfamint () ;
    c = c + setfamilyfield ( curval ) ;
    scanusvnum () ;
    curval = curval + c ;
  } 
  else {
      
    scanfifteenbitint () ;
    curval = setclassfield ( curval / 4096 ) + setfamilyfield ( ( curval % 
    4096 ) / 256 ) + ( curval % 256 ) ;
  } 
  mem [curlist .tailfield + 4 ].hh.b1 = curval % 65536L ;
  if ( ( mathclassfield ( curval ) == 7 ) && ( ( eqtb [7892308L ].cint >= 0 
  ) && ( eqtb [7892308L ].cint < 256 ) ) ) 
  mem [curlist .tailfield + 4 ].hh.b0 = eqtb [7892308L ].cint ;
  else mem [curlist .tailfield + 4 ].hh.b0 = mathfamfield ( curval ) ;
  mem [curlist .tailfield + 4 ].hh.b0 = mem [curlist .tailfield + 4 ]
  .hh.b0 + ( mathcharfield ( curval ) / 65536L ) * 256 ;
  scanmath ( curlist .tailfield + 1 ) ;
} 
void 
appendchoices ( void ) 
{
  appendchoices_regmem 
  {
    mem [curlist .tailfield ].hh .v.RH = newchoice () ;
    curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
  } 
  incr ( saveptr ) ;
  savestack [saveptr - 1 ].cint = 0 ;
  pushmath ( 13 ) ;
  scanleftbrace () ;
} 
halfword 
zfinmlist ( halfword p ) 
{
  register halfword Result; finmlist_regmem 
  halfword q  ;
  if ( curlist .auxfield .cint != -268435455L ) 
  {
    mem [curlist .auxfield .cint + 3 ].hh .v.RH = 3 ;
    mem [curlist .auxfield .cint + 3 ].hh .v.LH = mem [curlist .headfield ]
    .hh .v.RH ;
    if ( p == -268435455L ) 
    q = curlist .auxfield .cint ;
    else {
	
      q = mem [curlist .auxfield .cint + 2 ].hh .v.LH ;
      if ( ( mem [q ].hh.b0 != 30 ) || ( curlist .eTeXauxfield == 
      -268435455L ) ) 
      confusion ( 66288L ) ;
      mem [curlist .auxfield .cint + 2 ].hh .v.LH = mem [curlist 
      .eTeXauxfield ].hh .v.RH ;
      mem [curlist .eTeXauxfield ].hh .v.RH = curlist .auxfield .cint ;
      mem [curlist .auxfield .cint ].hh .v.RH = p ;
    } 
  } 
  else {
      
    mem [curlist .tailfield ].hh .v.RH = p ;
    q = mem [curlist .headfield ].hh .v.RH ;
  } 
  popnest () ;
  Result = q ;
  return Result ;
} 
void 
buildchoices ( void ) 
{
  /* 10 */ buildchoices_regmem 
  halfword p  ;
  unsave () ;
  p = finmlist ( -268435455L ) ;
  switch ( savestack [saveptr - 1 ].cint ) 
  {case 0 : 
    mem [curlist .tailfield + 1 ].hh .v.LH = p ;
    break ;
  case 1 : 
    mem [curlist .tailfield + 1 ].hh .v.RH = p ;
    break ;
  case 2 : 
    mem [curlist .tailfield + 2 ].hh .v.LH = p ;
    break ;
  case 3 : 
    {
      mem [curlist .tailfield + 2 ].hh .v.RH = p ;
      decr ( saveptr ) ;
      return ;
    } 
    break ;
  } 
  incr ( savestack [saveptr - 1 ].cint ) ;
  pushmath ( 13 ) ;
  scanleftbrace () ;
} 
void 
subsup ( void ) 
{
  subsup_regmem 
  smallnumber t  ;
  halfword p  ;
  t = 0 ;
  p = -268435455L ;
  if ( curlist .tailfield != curlist .headfield ) {
      
    if ( ( mem [curlist .tailfield ].hh.b0 >= 16 ) && ( mem [curlist 
    .tailfield ].hh.b0 < 30 ) ) 
    {
      p = curlist .tailfield + 2 + curcmd - 7 ;
      t = mem [p ].hh .v.RH ;
    } 
  } 
  if ( ( p == -268435455L ) || ( t != 0 ) ) 
  {
    {
      mem [curlist .tailfield ].hh .v.RH = newnoad () ;
      curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
    } 
    p = curlist .tailfield + 2 + curcmd - 7 ;
    if ( t != 0 ) 
    {
      if ( curcmd == 7 ) 
      {
	{
	  if ( interaction == 3 ) 
	  ;
	  if ( filelineerrorstylep ) 
	  printfileline () ;
	  else printnl ( 65544L ) ;
	  print ( 66581L ) ;
	} 
	{
	  helpptr = 1 ;
	  helpline [0 ]= 66582L ;
	} 
      } 
      else {
	  
	{
	  if ( interaction == 3 ) 
	  ;
	  if ( filelineerrorstylep ) 
	  printfileline () ;
	  else printnl ( 65544L ) ;
	  print ( 66583L ) ;
	} 
	{
	  helpptr = 1 ;
	  helpline [0 ]= 66584L ;
	} 
      } 
      error () ;
    } 
  } 
  scanmath ( p ) ;
} 
void 
mathfraction ( void ) 
{
  mathfraction_regmem 
  smallnumber c  ;
  c = curchr ;
  if ( curlist .auxfield .cint != -268435455L ) 
  {
    if ( c >= 3 ) 
    {
      scandelimiter ( memtop - 12 , false ) ;
      scandelimiter ( memtop - 12 , false ) ;
    } 
    if ( c % 3 == 0 ) 
    scandimen ( false , false , false ) ;
    {
      if ( interaction == 3 ) 
      ;
      if ( filelineerrorstylep ) 
      printfileline () ;
      else printnl ( 65544L ) ;
      print ( 66591L ) ;
    } 
    {
      helpptr = 3 ;
      helpline [2 ]= 66592L ;
      helpline [1 ]= 66593L ;
      helpline [0 ]= 66594L ;
    } 
    error () ;
  } 
  else {
      
    curlist .auxfield .cint = getnode ( 6 ) ;
    mem [curlist .auxfield .cint ].hh.b0 = 25 ;
    mem [curlist .auxfield .cint ].hh.b1 = 0 ;
    mem [curlist .auxfield .cint + 2 ].hh .v.RH = 3 ;
    mem [curlist .auxfield .cint + 2 ].hh .v.LH = mem [curlist .headfield ]
    .hh .v.RH ;
    mem [curlist .auxfield .cint + 3 ].hh = emptyfield ;
    mem [curlist .auxfield .cint + 4 ].qqqq = nulldelimiter ;
    mem [curlist .auxfield .cint + 5 ].qqqq = nulldelimiter ;
    mem [curlist .headfield ].hh .v.RH = -268435455L ;
    curlist .tailfield = curlist .headfield ;
    if ( c >= 3 ) 
    {
      scandelimiter ( curlist .auxfield .cint + 4 , false ) ;
      scandelimiter ( curlist .auxfield .cint + 5 , false ) ;
    } 
    switch ( c % 3 ) 
    {case 0 : 
      {
	scandimen ( false , false , false ) ;
	mem [curlist .auxfield .cint + 1 ].cint = curval ;
      } 
      break ;
    case 1 : 
      mem [curlist .auxfield .cint + 1 ].cint = 1073741824L ;
      break ;
    case 2 : 
      mem [curlist .auxfield .cint + 1 ].cint = 0 ;
      break ;
    } 
  } 
} 
void 
mathleftright ( void ) 
{
  mathleftright_regmem 
  smallnumber t  ;
  halfword p  ;
  halfword q  ;
  t = curchr ;
  if ( ( t != 30 ) && ( curgroup != 16 ) ) 
  {
    if ( curgroup == 15 ) 
    {
      scandelimiter ( memtop - 12 , false ) ;
      {
	if ( interaction == 3 ) 
	;
	if ( filelineerrorstylep ) 
	printfileline () ;
	else printnl ( 65544L ) ;
	print ( 66169L ) ;
      } 
      if ( t == 1 ) 
      {
	printesc ( 66289L ) ;
	{
	  helpptr = 1 ;
	  helpline [0 ]= 66595L ;
	} 
      } 
      else {
	  
	printesc ( 66288L ) ;
	{
	  helpptr = 1 ;
	  helpline [0 ]= 66596L ;
	} 
      } 
      error () ;
    } 
    else offsave () ;
  } 
  else {
      
    p = newnoad () ;
    mem [p ].hh.b0 = t ;
    scandelimiter ( p + 1 , false ) ;
    if ( t == 1 ) 
    {
      mem [p ].hh.b0 = 31 ;
      mem [p ].hh.b1 = 1 ;
    } 
    if ( t == 30 ) 
    q = p ;
    else {
	
      q = finmlist ( p ) ;
      unsave () ;
    } 
    if ( t != 31 ) 
    {
      pushmath ( 16 ) ;
      mem [curlist .headfield ].hh .v.RH = q ;
      curlist .tailfield = p ;
      curlist .eTeXauxfield = p ;
    } 
    else {
	
      {
	mem [curlist .tailfield ].hh .v.RH = newnoad () ;
	curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
      } 
      mem [curlist .tailfield ].hh.b0 = 23 ;
      mem [curlist .tailfield + 1 ].hh .v.RH = 3 ;
      mem [curlist .tailfield + 1 ].hh .v.LH = q ;
    } 
  } 
} 
void 
zappdisplay ( halfword j , halfword b , scaled d ) 
{
  appdisplay_regmem 
  scaled z  ;
  scaled s  ;
  scaled e  ;
  integer x  ;
  halfword p, q, r, t, u  ;
  s = eqtb [9006735L ].cint ;
  x = eqtb [7892330L ].cint ;
  if ( x == 0 ) 
  mem [b + 4 ].cint = s + d ;
  else {
      
    z = eqtb [9006734L ].cint ;
    p = b ;
    if ( x > 0 ) 
    e = z - d - mem [p + 1 ].cint ;
    else {
	
      e = d ;
      d = z - e - mem [p + 1 ].cint ;
    } 
    if ( j != -268435455L ) 
    {
      b = copynodelist ( j ) ;
      mem [b + 3 ].cint = mem [p + 3 ].cint ;
      mem [b + 2 ].cint = mem [p + 2 ].cint ;
      s = s - mem [b + 4 ].cint ;
      d = d + s ;
      e = e + mem [b + 1 ].cint - z - s ;
    } 
    if ( ( mem [p ].hh.b1 ) == 2 ) 
    q = p ;
    else {
	
      r = mem [p + 5 ].hh .v.RH ;
      freenode ( p , 8 ) ;
      if ( r == -268435455L ) 
      confusion ( 66933L ) ;
      if ( x > 0 ) 
      {
	p = r ;
	do {
	    q = r ;
	  r = mem [r ].hh .v.RH ;
	} while ( ! ( r == -268435455L ) ) ;
      } 
      else {
	  
	p = -268435455L ;
	q = r ;
	do {
	    t = mem [r ].hh .v.RH ;
	  mem [r ].hh .v.RH = p ;
	  p = r ;
	  r = t ;
	} while ( ! ( r == -268435455L ) ) ;
      } 
    } 
    if ( j == -268435455L ) 
    {
      r = newkern ( 0 ) ;
      t = newkern ( 0 ) ;
    } 
    else {
	
      r = mem [b + 5 ].hh .v.RH ;
      t = mem [r ].hh .v.RH ;
    } 
    u = newmath ( 0 , 3 ) ;
    if ( mem [t ].hh.b0 == 10 ) 
    {
      j = newskipparam ( 8 ) ;
      mem [q ].hh .v.RH = j ;
      mem [j ].hh .v.RH = u ;
      j = mem [t + 1 ].hh .v.LH ;
      mem [tempptr ].hh.b0 = mem [j ].hh.b0 ;
      mem [tempptr ].hh.b1 = mem [j ].hh.b1 ;
      mem [tempptr + 1 ].cint = e - mem [j + 1 ].cint ;
      mem [tempptr + 2 ].cint = - (integer) mem [j + 2 ].cint ;
      mem [tempptr + 3 ].cint = - (integer) mem [j + 3 ].cint ;
      mem [u ].hh .v.RH = t ;
    } 
    else {
	
      mem [t + 1 ].cint = e ;
      mem [t ].hh .v.RH = u ;
      mem [q ].hh .v.RH = t ;
    } 
    u = newmath ( 0 , 2 ) ;
    if ( mem [r ].hh.b0 == 10 ) 
    {
      j = newskipparam ( 7 ) ;
      mem [u ].hh .v.RH = j ;
      mem [j ].hh .v.RH = p ;
      j = mem [r + 1 ].hh .v.LH ;
      mem [tempptr ].hh.b0 = mem [j ].hh.b0 ;
      mem [tempptr ].hh.b1 = mem [j ].hh.b1 ;
      mem [tempptr + 1 ].cint = d - mem [j + 1 ].cint ;
      mem [tempptr + 2 ].cint = - (integer) mem [j + 2 ].cint ;
      mem [tempptr + 3 ].cint = - (integer) mem [j + 3 ].cint ;
      mem [r ].hh .v.RH = u ;
    } 
    else {
	
      mem [r + 1 ].cint = d ;
      mem [r ].hh .v.RH = p ;
      mem [u ].hh .v.RH = r ;
      if ( j == -268435455L ) 
      {
	b = hpack ( u , 0 , 1 ) ;
	mem [b + 4 ].cint = s ;
      } 
      else mem [b + 5 ].hh .v.RH = u ;
    } 
  } 
  appendtovlist ( b ) ;
} 
void 
aftermath ( void ) 
{
  aftermath_regmem 
  boolean l  ;
  boolean danger  ;
  integer m  ;
  halfword p  ;
  halfword a  ;
  halfword b  ;
  scaled w  ;
  scaled z  ;
  scaled e  ;
  scaled q  ;
  scaled d  ;
  scaled s  ;
  smallnumber g1, g2  ;
  halfword r  ;
  halfword t  ;
  halfword pret  ;
  halfword j  ;
  danger = false ;
  if ( curlist .modefield == 209 ) 
  j = curlist .eTeXauxfield ;
  if ( ( ( fontparams [eqtb [1206826L ].hh .v.RH ]< 22 ) && ( ! ( ( 
  fontarea [eqtb [1206826L ].hh .v.RH ]== 65534L ) && ( isOpenTypeMathFont 
  ( fontlayoutengine [eqtb [1206826L ].hh .v.RH ]) ) ) ) ) || ( ( 
  fontparams [eqtb [1207082L ].hh .v.RH ]< 22 ) && ( ! ( ( fontarea [eqtb 
  [1207082L ].hh .v.RH ]== 65534L ) && ( isOpenTypeMathFont ( 
  fontlayoutengine [eqtb [1207082L ].hh .v.RH ]) ) ) ) ) || ( ( fontparams 
  [eqtb [1207338L ].hh .v.RH ]< 22 ) && ( ! ( ( fontarea [eqtb [1207338L 
  ].hh .v.RH ]== 65534L ) && ( isOpenTypeMathFont ( fontlayoutengine [eqtb 
  [1207338L ].hh .v.RH ]) ) ) ) ) ) 
  {
    {
      if ( interaction == 3 ) 
      ;
      if ( filelineerrorstylep ) 
      printfileline () ;
      else printnl ( 65544L ) ;
      print ( 66597L ) ;
    } 
    {
      helpptr = 3 ;
      helpline [2 ]= 66598L ;
      helpline [1 ]= 66599L ;
      helpline [0 ]= 66600L ;
    } 
    error () ;
    flushmath () ;
    danger = true ;
  } 
  else if ( ( ( fontparams [eqtb [1206827L ].hh .v.RH ]< 13 ) && ( ! ( ( 
  fontarea [eqtb [1206827L ].hh .v.RH ]== 65534L ) && ( isOpenTypeMathFont 
  ( fontlayoutengine [eqtb [1206827L ].hh .v.RH ]) ) ) ) ) || ( ( 
  fontparams [eqtb [1207083L ].hh .v.RH ]< 13 ) && ( ! ( ( fontarea [eqtb 
  [1207083L ].hh .v.RH ]== 65534L ) && ( isOpenTypeMathFont ( 
  fontlayoutengine [eqtb [1207083L ].hh .v.RH ]) ) ) ) ) || ( ( fontparams 
  [eqtb [1207339L ].hh .v.RH ]< 13 ) && ( ! ( ( fontarea [eqtb [1207339L 
  ].hh .v.RH ]== 65534L ) && ( isOpenTypeMathFont ( fontlayoutengine [eqtb 
  [1207339L ].hh .v.RH ]) ) ) ) ) ) 
  {
    {
      if ( interaction == 3 ) 
      ;
      if ( filelineerrorstylep ) 
      printfileline () ;
      else printnl ( 65544L ) ;
      print ( 66601L ) ;
    } 
    {
      helpptr = 3 ;
      helpline [2 ]= 66602L ;
      helpline [1 ]= 66603L ;
      helpline [0 ]= 66604L ;
    } 
    error () ;
    flushmath () ;
    danger = true ;
  } 
  m = curlist .modefield ;
  l = false ;
  p = finmlist ( -268435455L ) ;
  if ( curlist .modefield == - (integer) m ) 
  {
    {
      getxtoken () ;
      if ( curcmd != 3 ) 
      {
	{
	  if ( interaction == 3 ) 
	  ;
	  if ( filelineerrorstylep ) 
	  printfileline () ;
	  else printnl ( 65544L ) ;
	  print ( 66605L ) ;
	} 
	{
	  helpptr = 2 ;
	  helpline [1 ]= 66606L ;
	  helpline [0 ]= 66607L ;
	} 
	backerror () ;
      } 
    } 
    curmlist = p ;
    curstyle = 2 ;
    mlistpenalties = false ;
    mlisttohlist () ;
    a = hpack ( mem [memtop - 3 ].hh .v.RH , 0 , 1 ) ;
    mem [a ].hh.b1 = 2 ;
    unsave () ;
    decr ( saveptr ) ;
    if ( savestack [saveptr + 0 ].cint == 1 ) 
    l = true ;
    danger = false ;
    if ( curlist .modefield == 209 ) 
    j = curlist .eTeXauxfield ;
    if ( ( ( fontparams [eqtb [1206826L ].hh .v.RH ]< 22 ) && ( ! ( ( 
    fontarea [eqtb [1206826L ].hh .v.RH ]== 65534L ) && ( 
    isOpenTypeMathFont ( fontlayoutengine [eqtb [1206826L ].hh .v.RH ]) ) 
    ) ) ) || ( ( fontparams [eqtb [1207082L ].hh .v.RH ]< 22 ) && ( ! ( ( 
    fontarea [eqtb [1207082L ].hh .v.RH ]== 65534L ) && ( 
    isOpenTypeMathFont ( fontlayoutengine [eqtb [1207082L ].hh .v.RH ]) ) 
    ) ) ) || ( ( fontparams [eqtb [1207338L ].hh .v.RH ]< 22 ) && ( ! ( ( 
    fontarea [eqtb [1207338L ].hh .v.RH ]== 65534L ) && ( 
    isOpenTypeMathFont ( fontlayoutengine [eqtb [1207338L ].hh .v.RH ]) ) 
    ) ) ) ) 
    {
      {
	if ( interaction == 3 ) 
	;
	if ( filelineerrorstylep ) 
	printfileline () ;
	else printnl ( 65544L ) ;
	print ( 66597L ) ;
      } 
      {
	helpptr = 3 ;
	helpline [2 ]= 66598L ;
	helpline [1 ]= 66599L ;
	helpline [0 ]= 66600L ;
      } 
      error () ;
      flushmath () ;
      danger = true ;
    } 
    else if ( ( ( fontparams [eqtb [1206827L ].hh .v.RH ]< 13 ) && ( ! ( ( 
    fontarea [eqtb [1206827L ].hh .v.RH ]== 65534L ) && ( 
    isOpenTypeMathFont ( fontlayoutengine [eqtb [1206827L ].hh .v.RH ]) ) 
    ) ) ) || ( ( fontparams [eqtb [1207083L ].hh .v.RH ]< 13 ) && ( ! ( ( 
    fontarea [eqtb [1207083L ].hh .v.RH ]== 65534L ) && ( 
    isOpenTypeMathFont ( fontlayoutengine [eqtb [1207083L ].hh .v.RH ]) ) 
    ) ) ) || ( ( fontparams [eqtb [1207339L ].hh .v.RH ]< 13 ) && ( ! ( ( 
    fontarea [eqtb [1207339L ].hh .v.RH ]== 65534L ) && ( 
    isOpenTypeMathFont ( fontlayoutengine [eqtb [1207339L ].hh .v.RH ]) ) 
    ) ) ) ) 
    {
      {
	if ( interaction == 3 ) 
	;
	if ( filelineerrorstylep ) 
	printfileline () ;
	else printnl ( 65544L ) ;
	print ( 66601L ) ;
      } 
      {
	helpptr = 3 ;
	helpline [2 ]= 66602L ;
	helpline [1 ]= 66603L ;
	helpline [0 ]= 66604L ;
      } 
      error () ;
      flushmath () ;
      danger = true ;
    } 
    m = curlist .modefield ;
    p = finmlist ( -268435455L ) ;
  } 
  else a = -268435455L ;
  if ( m < 0 ) 
  {
    {
      mem [curlist .tailfield ].hh .v.RH = newmath ( eqtb [9006721L ].cint 
      , 0 ) ;
      curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
    } 
    curmlist = p ;
    curstyle = 2 ;
    mlistpenalties = ( curlist .modefield > 0 ) ;
    mlisttohlist () ;
    mem [curlist .tailfield ].hh .v.RH = mem [memtop - 3 ].hh .v.RH ;
    while ( mem [curlist .tailfield ].hh .v.RH != -268435455L ) curlist 
    .tailfield = mem [curlist .tailfield ].hh .v.RH ;
    {
      mem [curlist .tailfield ].hh .v.RH = newmath ( eqtb [9006721L ].cint 
      , 1 ) ;
      curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
    } 
    curlist .auxfield .hh .v.LH = 1000 ;
    unsave () ;
  } 
  else {
      
    if ( a == -268435455L ) 
    {
      getxtoken () ;
      if ( curcmd != 3 ) 
      {
	{
	  if ( interaction == 3 ) 
	  ;
	  if ( filelineerrorstylep ) 
	  printfileline () ;
	  else printnl ( 65544L ) ;
	  print ( 66605L ) ;
	} 
	{
	  helpptr = 2 ;
	  helpline [1 ]= 66606L ;
	  helpline [0 ]= 66607L ;
	} 
	backerror () ;
      } 
    } 
    curmlist = p ;
    curstyle = 0 ;
    mlistpenalties = false ;
    mlisttohlist () ;
    p = mem [memtop - 3 ].hh .v.RH ;
    adjusttail = memtop - 5 ;
    preadjusttail = memtop - 14 ;
    b = hpack ( p , 0 , 1 ) ;
    p = mem [b + 5 ].hh .v.RH ;
    t = adjusttail ;
    adjusttail = -268435455L ;
    pret = preadjusttail ;
    preadjusttail = -268435455L ;
    w = mem [b + 1 ].cint ;
    z = eqtb [9006734L ].cint ;
    s = eqtb [9006735L ].cint ;
    if ( eqtb [7892330L ].cint < 0 ) 
    s = - (integer) s - z ;
    if ( ( a == -268435455L ) || danger ) 
    {
      e = 0 ;
      q = 0 ;
    } 
    else {
	
      e = mem [a + 1 ].cint ;
      q = e + mathquad ( 0 ) ;
    } 
    if ( w + q > z ) 
    {
      if ( ( e != 0 ) && ( ( w - totalshrink [0 ]+ q <= z ) || ( totalshrink 
      [1 ]!= 0 ) || ( totalshrink [2 ]!= 0 ) || ( totalshrink [3 ]!= 0 ) 
      ) ) 
      {
	freenode ( b , 8 ) ;
	b = hpack ( p , z - q , 0 ) ;
      } 
      else {
	  
	e = 0 ;
	if ( w > z ) 
	{
	  freenode ( b , 8 ) ;
	  b = hpack ( p , z , 0 ) ;
	} 
      } 
      w = mem [b + 1 ].cint ;
    } 
    mem [b ].hh.b1 = 2 ;
    d = half ( z - w ) ;
    if ( ( e > 0 ) && ( d < 2 * e ) ) 
    {
      d = half ( z - w - e ) ;
      if ( p != -268435455L ) {
	  
	if ( ! ( p >= himemmin ) ) {
	    
	  if ( mem [p ].hh.b0 == 10 ) 
	  d = 0 ;
	} 
      } 
    } 
    {
      mem [curlist .tailfield ].hh .v.RH = newpenalty ( eqtb [7892275L ]
      .cint ) ;
      curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
    } 
    if ( ( d + s <= eqtb [9006733L ].cint ) || l ) 
    {
      g1 = 3 ;
      g2 = 4 ;
    } 
    else {
	
      g1 = 5 ;
      g2 = 6 ;
    } 
    if ( l && ( e == 0 ) ) 
    {
      appdisplay ( j , a , 0 ) ;
      {
	mem [curlist .tailfield ].hh .v.RH = newpenalty ( 10000 ) ;
	curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
      } 
    } 
    else {
	
      mem [curlist .tailfield ].hh .v.RH = newparamglue ( g1 ) ;
      curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
    } 
    if ( e != 0 ) 
    {
      r = newkern ( z - w - e - d ) ;
      if ( l ) 
      {
	mem [a ].hh .v.RH = r ;
	mem [r ].hh .v.RH = b ;
	b = a ;
	d = 0 ;
      } 
      else {
	  
	mem [b ].hh .v.RH = r ;
	mem [r ].hh .v.RH = a ;
      } 
      b = hpack ( b , 0 , 1 ) ;
    } 
    appdisplay ( j , b , d ) ;
    if ( ( a != -268435455L ) && ( e == 0 ) && ! l ) 
    {
      {
	mem [curlist .tailfield ].hh .v.RH = newpenalty ( 10000 ) ;
	curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
      } 
      appdisplay ( j , a , z - mem [a + 1 ].cint ) ;
      g2 = 0 ;
    } 
    if ( t != memtop - 5 ) 
    {
      mem [curlist .tailfield ].hh .v.RH = mem [memtop - 5 ].hh .v.RH ;
      curlist .tailfield = t ;
    } 
    if ( pret != memtop - 14 ) 
    {
      mem [curlist .tailfield ].hh .v.RH = mem [memtop - 14 ].hh .v.RH ;
      curlist .tailfield = pret ;
    } 
    {
      mem [curlist .tailfield ].hh .v.RH = newpenalty ( eqtb [7892276L ]
      .cint ) ;
      curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
    } 
    if ( g2 > 0 ) 
    {
      mem [curlist .tailfield ].hh .v.RH = newparamglue ( g2 ) ;
      curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
    } 
    flushnodelist ( j ) ;
    resumeafterdisplay () ;
  } 
} 
void 
resumeafterdisplay ( void ) 
{
  resumeafterdisplay_regmem 
  if ( curgroup != 15 ) 
  confusion ( 66608L ) ;
  unsave () ;
  curlist .pgfield = curlist .pgfield + 3 ;
  pushnest () ;
  curlist .modefield = 105 ;
  curlist .auxfield .hh .v.LH = 1000 ;
  if ( eqtb [7892314L ].cint <= 0 ) 
  curlang = 0 ;
  else if ( eqtb [7892314L ].cint > 255 ) 
  curlang = 0 ;
  else curlang = eqtb [7892314L ].cint ;
  curlist .auxfield .hh .v.RH = curlang ;
  curlist .pgfield = ( normmin ( eqtb [7892315L ].cint ) * 64 + normmin ( 
  eqtb [7892316L ].cint ) ) * 65536L + curlang ;
  {
    getxtoken () ;
    if ( curcmd != 10 ) 
    backinput () ;
  } 
  if ( nestptr == 1 ) 
  buildpage () ;
} 
void 
getrtoken ( void ) 
{
  /* 20 */ getrtoken_regmem 
  lab20: do {
      gettoken () ;
  } while ( ! ( curtok != 20971552L ) ) ;
  if ( ( curcs == 0 ) || ( curcs > eqtbtop ) || ( ( curcs > 1194650L ) && ( 
  curcs <= 9006998L ) ) ) 
  {
    {
      if ( interaction == 3 ) 
      ;
      if ( filelineerrorstylep ) 
      printfileline () ;
      else printnl ( 65544L ) ;
      print ( 66626L ) ;
    } 
    {
      helpptr = 5 ;
      helpline [4 ]= 66627L ;
      helpline [3 ]= 66628L ;
      helpline [2 ]= 66629L ;
      helpline [1 ]= 66630L ;
      helpline [0 ]= 66631L ;
    } 
    if ( curcs == 0 ) 
    backinput () ;
    curtok = 34749081L ;
    inserror () ;
    goto lab20 ;
  } 
} 
void 
trapzeroglue ( void ) 
{
  trapzeroglue_regmem 
  if ( ( mem [curval + 1 ].cint == 0 ) && ( mem [curval + 2 ].cint == 0 ) 
  && ( mem [curval + 3 ].cint == 0 ) ) 
  {
    incr ( mem [membot ].hh .v.RH ) ;
    deleteglueref ( curval ) ;
    curval = membot ;
  } 
} 
void 
zdoregistercommand ( smallnumber a ) 
{
  /* 40 10 */ doregistercommand_regmem 
  halfword l, q, r, s  ;
  unsigned char p  ;
  boolean e  ;
  integer w  ;
  q = curcmd ;
  e = false ;
  {
    if ( q != 91 ) 
    {
      getxtoken () ;
      if ( ( curcmd >= 74 ) && ( curcmd <= 77 ) ) 
      {
	l = curchr ;
	p = curcmd - 74 ;
	goto lab40 ;
      } 
      if ( curcmd != 91 ) 
      {
	{
	  if ( interaction == 3 ) 
	  ;
	  if ( filelineerrorstylep ) 
	  printfileline () ;
	  else printnl ( 65544L ) ;
	  print ( 66035L ) ;
	} 
	printcmdchr ( curcmd , curchr ) ;
	print ( 66036L ) ;
	printcmdchr ( q , 0 ) ;
	{
	  helpptr = 1 ;
	  helpline [0 ]= 66667L ;
	} 
	error () ;
	return ;
      } 
    } 
    if ( ( curchr < membot ) || ( curchr > membot + 19 ) ) 
    {
      l = curchr ;
      p = ( mem [l ].hh.b0 / 64 ) ;
      e = true ;
    } 
    else {
	
      p = curchr - membot ;
      scanregisternum () ;
      if ( curval > 255 ) 
      {
	findsaelement ( p , curval , true ) ;
	l = curptr ;
	e = true ;
      } 
      else switch ( p ) 
      {case 0 : 
	l = curval + 7892352L ;
	break ;
      case 1 : 
	l = curval + 9006743L ;
	break ;
      case 2 : 
	l = curval + 1205783L ;
	break ;
      case 3 : 
	l = curval + 1206039L ;
	break ;
      } 
    } 
  } 
  lab40: if ( p < 2 ) {
      
    if ( e ) 
    w = mem [l + 2 ].cint ;
    else w = eqtb [l ].cint ;
  } 
  else if ( e ) 
  s = mem [l + 1 ].hh .v.RH ;
  else s = eqtb [l ].hh .v.RH ;
  if ( q == 91 ) 
  scanoptionalequals () ;
  else if ( scankeyword ( 66663L ) ) 
  ;
  aritherror = false ;
  if ( q < 93 ) {
      
    if ( p < 2 ) 
    {
      if ( p == 0 ) 
      scanint () ;
      else scandimen ( false , false , false ) ;
      if ( q == 92 ) 
      curval = curval + w ;
    } 
    else {
	
      scanglue ( p ) ;
      if ( q == 92 ) 
      {
	q = newspec ( curval ) ;
	r = s ;
	deleteglueref ( curval ) ;
	mem [q + 1 ].cint = mem [q + 1 ].cint + mem [r + 1 ].cint ;
	if ( mem [q + 2 ].cint == 0 ) 
	mem [q ].hh.b0 = 0 ;
	if ( mem [q ].hh.b0 == mem [r ].hh.b0 ) 
	mem [q + 2 ].cint = mem [q + 2 ].cint + mem [r + 2 ].cint ;
	else if ( ( mem [q ].hh.b0 < mem [r ].hh.b0 ) && ( mem [r + 2 ]
	.cint != 0 ) ) 
	{
	  mem [q + 2 ].cint = mem [r + 2 ].cint ;
	  mem [q ].hh.b0 = mem [r ].hh.b0 ;
	} 
	if ( mem [q + 3 ].cint == 0 ) 
	mem [q ].hh.b1 = 0 ;
	if ( mem [q ].hh.b1 == mem [r ].hh.b1 ) 
	mem [q + 3 ].cint = mem [q + 3 ].cint + mem [r + 3 ].cint ;
	else if ( ( mem [q ].hh.b1 < mem [r ].hh.b1 ) && ( mem [r + 3 ]
	.cint != 0 ) ) 
	{
	  mem [q + 3 ].cint = mem [r + 3 ].cint ;
	  mem [q ].hh.b1 = mem [r ].hh.b1 ;
	} 
	curval = q ;
      } 
    } 
  } 
  else {
      
    scanint () ;
    if ( p < 2 ) {
	
      if ( q == 93 ) {
	  
	if ( p == 0 ) 
	curval = multandadd ( w , curval , 0 , 2147483647L ) ;
	else curval = multandadd ( w , curval , 0 , 1073741823L ) ;
      } 
      else curval = xovern ( w , curval ) ;
    } 
    else {
	
      r = newspec ( s ) ;
      if ( q == 93 ) 
      {
	mem [r + 1 ].cint = multandadd ( mem [s + 1 ].cint , curval , 0 , 
	1073741823L ) ;
	mem [r + 2 ].cint = multandadd ( mem [s + 2 ].cint , curval , 0 , 
	1073741823L ) ;
	mem [r + 3 ].cint = multandadd ( mem [s + 3 ].cint , curval , 0 , 
	1073741823L ) ;
      } 
      else {
	  
	mem [r + 1 ].cint = xovern ( mem [s + 1 ].cint , curval ) ;
	mem [r + 2 ].cint = xovern ( mem [s + 2 ].cint , curval ) ;
	mem [r + 3 ].cint = xovern ( mem [s + 3 ].cint , curval ) ;
      } 
      curval = r ;
    } 
  } 
  if ( aritherror ) 
  {
    {
      if ( interaction == 3 ) 
      ;
      if ( filelineerrorstylep ) 
      printfileline () ;
      else printnl ( 65544L ) ;
      print ( 66664L ) ;
    } 
    {
      helpptr = 2 ;
      helpline [1 ]= 66665L ;
      helpline [0 ]= 66666L ;
    } 
    if ( p >= 2 ) 
    deleteglueref ( curval ) ;
    error () ;
    return ;
  } 
  if ( p < 2 ) {
      
    if ( e ) {
	
      if ( ( a >= 4 ) ) 
      gsawdef ( l , curval ) ;
      else sawdef ( l , curval ) ;
    } 
    else if ( ( a >= 4 ) ) 
    geqworddefine ( l , curval ) ;
    else eqworddefine ( l , curval ) ;
  } 
  else {
      
    trapzeroglue () ;
    if ( e ) {
	
      if ( ( a >= 4 ) ) 
      gsadef ( l , curval ) ;
      else sadef ( l , curval ) ;
    } 
    else if ( ( a >= 4 ) ) 
    geqdefine ( l , 120 , curval ) ;
    else eqdefine ( l , 120 , curval ) ;
  } 
} 
void 
alteraux ( void ) 
{
  alteraux_regmem 
  halfword c  ;
  if ( curchr != abs ( curlist .modefield ) ) 
  reportillegalcase () ;
  else {
      
    c = curchr ;
    scanoptionalequals () ;
    if ( c == 1 ) 
    {
      scandimen ( false , false , false ) ;
      curlist .auxfield .cint = curval ;
    } 
    else {
	
      scanint () ;
      if ( ( curval <= 0 ) || ( curval > 32767 ) ) 
      {
	{
	  if ( interaction == 3 ) 
	  ;
	  if ( filelineerrorstylep ) 
	  printfileline () ;
	  else printnl ( 65544L ) ;
	  print ( 66670L ) ;
	} 
	{
	  helpptr = 1 ;
	  helpline [0 ]= 66671L ;
	} 
	interror ( curval ) ;
      } 
      else curlist .auxfield .hh .v.LH = curval ;
    } 
  } 
} 
void 
alterprevgraf ( void ) 
{
  alterprevgraf_regmem 
  integer p  ;
  nest [nestptr ]= curlist ;
  p = nestptr ;
  while ( abs ( nest [p ].modefield ) != 1 ) decr ( p ) ;
  scanoptionalequals () ;
  scanint () ;
  if ( curval < 0 ) 
  {
    {
      if ( interaction == 3 ) 
      ;
      if ( filelineerrorstylep ) 
      printfileline () ;
      else printnl ( 65544L ) ;
      print ( 66392L ) ;
    } 
    printesc ( 65855L ) ;
    {
      helpptr = 1 ;
      helpline [0 ]= 66672L ;
    } 
    interror ( curval ) ;
  } 
  else {
      
    nest [p ].pgfield = curval ;
    curlist = nest [nestptr ];
  } 
} 
void 
alterpagesofar ( void ) 
{
  alterpagesofar_regmem 
  unsigned char c  ;
  c = curchr ;
  scanoptionalequals () ;
  scandimen ( false , false , false ) ;
  pagesofar [c ]= curval ;
} 
void 
alterinteger ( void ) 
{
  alterinteger_regmem 
  smallnumber c  ;
  c = curchr ;
  scanoptionalequals () ;
  scanint () ;
  if ( c == 0 ) 
  deadcycles = curval ;
  else if ( c == 2 ) 
  {
    if ( ( curval < 0 ) || ( curval > 3 ) ) 
    {
      {
	if ( interaction == 3 ) 
	;
	if ( filelineerrorstylep ) 
	printfileline () ;
	else printnl ( 65544L ) ;
	print ( 66908L ) ;
      } 
      {
	helpptr = 2 ;
	helpline [1 ]= 66909L ;
	helpline [0 ]= 66910L ;
      } 
      interror ( curval ) ;
    } 
    else {
	
      curchr = curval ;
      newinteraction () ;
    } 
  } 
  else insertpenalties = curval ;
} 
void 
alterboxdimen ( void ) 
{
  alterboxdimen_regmem 
  smallnumber c  ;
  halfword b  ;
  c = curchr ;
  scanregisternum () ;
  if ( curval < 256 ) 
  b = eqtb [1206567L + curval ].hh .v.RH ;
  else {
      
    findsaelement ( 4 , curval , false ) ;
    if ( curptr == -268435455L ) 
    b = -268435455L ;
    else b = mem [curptr + 1 ].hh .v.RH ;
  } 
  scanoptionalequals () ;
  scandimen ( false , false , false ) ;
  if ( b != -268435455L ) 
  mem [b + c ].cint = curval ;
} 
void 
znewfont ( smallnumber a ) 
{
  /* 50 */ newfont_regmem 
  halfword u  ;
  scaled s  ;
  internalfontnumber f  ;
  strnumber t  ;
  unsigned char oldsetting  ;
  if ( jobname == 0 ) 
  openlogfile () ;
  getrtoken () ;
  u = curcs ;
  if ( u >= 1179650L ) 
  t = hash [u ].v.RH ;
  else if ( u >= 1114113L ) {
      
    if ( u == 1179649L ) 
    t = 66678L ;
    else t = u - 1114113L ;
  } 
  else {
      
    oldsetting = selector ;
    selector = 21 ;
    print ( 66678L ) ;
    print ( u - 1 ) ;
    selector = oldsetting ;
    {
      if ( poolptr + 1 > poolsize ) 
      overflow ( 65539L , poolsize - initpoolptr ) ;
    } 
    t = makestring () ;
  } 
  if ( ( a >= 4 ) ) 
  geqdefine ( u , 89 , 0 ) ;
  else eqdefine ( u , 89 , 0 ) ;
  scanoptionalequals () ;
  scanfilename () ;
  nameinprogress = true ;
  if ( scankeyword ( 66679L ) ) 
  {
    scandimen ( false , false , false ) ;
    s = curval ;
    if ( ( s <= 0 ) || ( s >= 134217728L ) ) 
    {
      {
	if ( interaction == 3 ) 
	;
	if ( filelineerrorstylep ) 
	printfileline () ;
	else printnl ( 65544L ) ;
	print ( 66681L ) ;
      } 
      printscaled ( s ) ;
      print ( 66682L ) ;
      {
	helpptr = 2 ;
	helpline [1 ]= 66683L ;
	helpline [0 ]= 66684L ;
      } 
      error () ;
      s = 10 * 65536L ;
    } 
  } 
  else if ( scankeyword ( 66680L ) ) 
  {
    scanint () ;
    s = - (integer) curval ;
    if ( ( curval <= 0 ) || ( curval > 32768L ) ) 
    {
      {
	if ( interaction == 3 ) 
	;
	if ( filelineerrorstylep ) 
	printfileline () ;
	else printnl ( 65544L ) ;
	print ( 65881L ) ;
      } 
      {
	helpptr = 1 ;
	helpline [0 ]= 65882L ;
      } 
      interror ( curval ) ;
      s = -1000 ;
    } 
  } 
  else s = -1000 ;
  nameinprogress = false ;
  {register integer for_end; f = 1 ;for_end = fontptr ; if ( f <= for_end) 
  do 
    {
      if ( streqstr ( fontname [f ], curname ) && ( ( ( curarea == 65545L ) 
      && ( ( fontarea [f ]== 65535L ) || ( fontarea [f ]== 65534L ) ) ) || 
      streqstr ( fontarea [f ], curarea ) ) ) 
      {
	if ( s > 0 ) 
	{
	  if ( s == fontsize [f ]) 
	  goto lab50 ;
	} 
	else {
	    
	  aritherror = false ;
	  if ( fontsize [f ]== xnoverd ( fontdsize [f ], - (integer) s , 
	  1000 ) ) {
	      
	    if ( ! aritherror ) 
	    goto lab50 ;
	  } 
	} 
      } 
      appendstr ( curarea ) ;
      appendstr ( curname ) ;
      appendstr ( curext ) ;
      if ( streqstr ( fontname [f ], makestring () ) ) 
      {
	{
	  decr ( strptr ) ;
	  poolptr = strstart [( strptr ) - 65536L ];
	} 
	if ( ( ( fontarea [f ]== 65535L ) || ( fontarea [f ]== 65534L ) ) 
	) 
	{
	  if ( s > 0 ) 
	  {
	    if ( s == fontsize [f ]) 
	    goto lab50 ;
	  } 
	  else if ( fontsize [f ]== xnoverd ( fontdsize [f ], - (integer) 
	  s , 1000 ) ) 
	  goto lab50 ;
	} 
      } 
      else {
	  
	decr ( strptr ) ;
	poolptr = strstart [( strptr ) - 65536L ];
      } 
    } 
  while ( f++ < for_end ) ;} 
  f = readfontinfo ( u , curname , curarea , s ) ;
  lab50: if ( ( a >= 4 ) ) 
  geqdefine ( u , 89 , f ) ;
  else eqdefine ( u , 89 , f ) ;
  eqtb [1196762L + f ]= eqtb [u ];
  hash [1196762L + f ].v.RH = t ;
} 
void 
newinteraction ( void ) 
{
  newinteraction_regmem 
  println () ;
  interaction = curchr ;
  if ( interaction == 0 ) 
  kpsemaketexdiscarderrors = 1 ;
  else kpsemaketexdiscarderrors = 0 ;
  if ( interaction == 0 ) 
  selector = 16 ;
  else selector = 17 ;
  if ( logopened ) 
  selector = selector + 2 ;
} 
void 
doassignments ( void ) 
{
  /* 10 */ doassignments_regmem 
  while ( true ) {
      
    do {
	getxtoken () ;
    } while ( ! ( ( curcmd != 10 ) && ( curcmd != 0 ) ) ) ;
    if ( curcmd <= 71 ) 
    return ;
    setboxallowed = false ;
    prefixedcommand () ;
    setboxallowed = true ;
  } 
} 
void 
openorclosein ( void ) 
{
  openorclosein_regmem 
  unsigned char c  ;
  unsigned char n  ;
  integer k  ;
  c = curchr ;
  scanfourbitint () ;
  n = curval ;
  if ( readopen [n ]!= 2 ) 
  {
    uclose ( readfile [n ]) ;
    readopen [n ]= 2 ;
  } 
  if ( c != 0 ) 
  {
    scanoptionalequals () ;
    scanfilename () ;
    packfilename ( curname , curarea , curext ) ;
    texinputtype = 0 ;
    if ( kpseinnameok ( stringcast ( nameoffile + 1 ) ) && uopenin ( readfile 
    [n ], kpsetexformat , eqtb [7892345L ].cint , eqtb [7892346L ].cint 
    ) ) 
    {
      makeutf16name () ;
      nameinprogress = true ;
      beginname () ;
      stopatspace = false ;
      k = 0 ;
      while ( ( k < namelength16 ) && ( morename ( nameoffile16 [k ]) ) ) 
      incr ( k ) ;
      stopatspace = true ;
      endname () ;
      nameinprogress = false ;
      readopen [n ]= 1 ;
    } 
  } 
} 
void 
issuemessage ( void ) 
{
  issuemessage_regmem 
  unsigned char oldsetting  ;
  unsigned char c  ;
  strnumber s  ;
  c = curchr ;
  mem [memtop - 12 ].hh .v.RH = scantoks ( false , true ) ;
  oldsetting = selector ;
  selector = 21 ;
  tokenshow ( defref ) ;
  selector = oldsetting ;
  flushlist ( defref ) ;
  {
    if ( poolptr + 1 > poolsize ) 
    overflow ( 65539L , poolsize - initpoolptr ) ;
  } 
  s = makestring () ;
  if ( c == 0 ) 
  {
    if ( termoffset + length ( s ) > maxprintline - 2 ) 
    println () ;
    else if ( ( termoffset > 0 ) || ( fileoffset > 0 ) ) 
    printchar ( 32 ) ;
    print ( s ) ;
    fflush ( stdout ) ;
  } 
  else {
      
    {
      if ( interaction == 3 ) 
      ;
      if ( filelineerrorstylep ) 
      printfileline () ;
      else printnl ( 65544L ) ;
      print ( 65545L ) ;
    } 
    print ( s ) ;
    if ( eqtb [1206304L ].hh .v.RH != -268435455L ) 
    useerrhelp = true ;
    else if ( longhelpseen ) 
    {
      helpptr = 1 ;
      helpline [0 ]= 66691L ;
    } 
    else {
	
      if ( interaction < 3 ) 
      longhelpseen = true ;
      {
	helpptr = 4 ;
	helpline [3 ]= 66692L ;
	helpline [2 ]= 66693L ;
	helpline [1 ]= 66694L ;
	helpline [0 ]= 66695L ;
      } 
    } 
    error () ;
    useerrhelp = false ;
  } 
  {
    decr ( strptr ) ;
    poolptr = strstart [( strptr ) - 65536L ];
  } 
} 
void 
shiftcase ( void ) 
{
  shiftcase_regmem 
  halfword b  ;
  halfword p  ;
  halfword t  ;
  integer c  ;
  b = curchr ;
  p = scantoks ( false , false ) ;
  p = mem [defref ].hh .v.RH ;
  while ( p != -268435455L ) {
      
    t = mem [p ].hh .v.LH ;
    if ( t < 34668544L ) 
    {
      c = t % 2097152L ;
      if ( eqtb [b + c ].hh .v.RH != 0 ) 
      mem [p ].hh .v.LH = t - c + eqtb [b + c ].hh .v.RH ;
    } 
    p = mem [p ].hh .v.RH ;
  } 
  begintokenlist ( mem [defref ].hh .v.RH , 3 ) ;
  {
    mem [defref ].hh .v.RH = avail ;
    avail = defref ;
	;
#ifdef STAT
    decr ( dynused ) ;
#endif /* STAT */
  } 
} 
void 
showwhatever ( void ) 
{
  /* 50 */ showwhatever_regmem 
  halfword p  ;
  smallnumber t  ;
  unsigned char m  ;
  integer l  ;
  integer n  ;
  switch ( curchr ) 
  {case 3 : 
    {
      if ( ( eqtb [7892324L ].cint >= 0 ) && ( eqtb [7892324L ].cint < 16 
      ) && writeopen [eqtb [7892324L ].cint ]) 
      selector = eqtb [7892324L ].cint ;
      begindiagnostic () ;
      showactivities () ;
    } 
    break ;
  case 1 : 
    {
      scanregisternum () ;
      if ( curval < 256 ) 
      p = eqtb [1206567L + curval ].hh .v.RH ;
      else {
	  
	findsaelement ( 4 , curval , false ) ;
	if ( curptr == -268435455L ) 
	p = -268435455L ;
	else p = mem [curptr + 1 ].hh .v.RH ;
      } 
      if ( ( eqtb [7892324L ].cint >= 0 ) && ( eqtb [7892324L ].cint < 16 
      ) && writeopen [eqtb [7892324L ].cint ]) 
      selector = eqtb [7892324L ].cint ;
      begindiagnostic () ;
      printnl ( 66711L ) ;
      printint ( curval ) ;
      printchar ( 61 ) ;
      if ( p == -268435455L ) 
      print ( 65711L ) ;
      else showbox ( p ) ;
    } 
    break ;
  case 0 : 
    {
      gettoken () ;
      if ( ( eqtb [7892324L ].cint >= 0 ) && ( eqtb [7892324L ].cint < 16 
      ) && writeopen [eqtb [7892324L ].cint ]) 
      selector = eqtb [7892324L ].cint ;
      if ( interaction == 3 ) 
      ;
      printnl ( 66707L ) ;
      if ( curcs != 0 ) 
      {
	sprintcs ( curcs ) ;
	printchar ( 61 ) ;
      } 
      printmeaning () ;
      goto lab50 ;
    } 
    break ;
  case 4 : 
    {
      if ( ( eqtb [7892324L ].cint >= 0 ) && ( eqtb [7892324L ].cint < 16 
      ) && writeopen [eqtb [7892324L ].cint ]) 
      selector = eqtb [7892324L ].cint ;
      begindiagnostic () ;
      showsavegroups () ;
    } 
    break ;
  case 6 : 
    {
      if ( ( eqtb [7892324L ].cint >= 0 ) && ( eqtb [7892324L ].cint < 16 
      ) && writeopen [eqtb [7892324L ].cint ]) 
      selector = eqtb [7892324L ].cint ;
      begindiagnostic () ;
      printnl ( 65545L ) ;
      println () ;
      if ( condptr == -268435455L ) 
      {
	printnl ( 65662L ) ;
	print ( 66905L ) ;
      } 
      else {
	  
	p = condptr ;
	n = 0 ;
	do {
	    incr ( n ) ;
	  p = mem [p ].hh .v.RH ;
	} while ( ! ( p == -268435455L ) ) ;
	p = condptr ;
	t = curif ;
	l = ifline ;
	m = iflimit ;
	do {
	    printnl ( 66906L ) ;
	  printint ( n ) ;
	  print ( 65595L ) ;
	  printcmdchr ( 108 , t ) ;
	  if ( m == 2 ) 
	  printesc ( 66168L ) ;
	  if ( l != 0 ) 
	  {
	    print ( 66904L ) ;
	    printint ( l ) ;
	  } 
	  decr ( n ) ;
	  t = mem [p ].hh.b1 ;
	  l = mem [p + 1 ].cint ;
	  m = mem [p ].hh.b0 ;
	  p = mem [p ].hh .v.RH ;
	} while ( ! ( p == -268435455L ) ) ;
      } 
    } 
    break ;
    default: 
    {
      p = thetoks () ;
      if ( ( eqtb [7892324L ].cint >= 0 ) && ( eqtb [7892324L ].cint < 16 
      ) && writeopen [eqtb [7892324L ].cint ]) 
      selector = eqtb [7892324L ].cint ;
      if ( interaction == 3 ) 
      ;
      printnl ( 66707L ) ;
      tokenshow ( memtop - 3 ) ;
      flushlist ( mem [memtop - 3 ].hh .v.RH ) ;
      goto lab50 ;
    } 
    break ;
  } 
  enddiagnostic ( true ) ;
  {
    if ( interaction == 3 ) 
    ;
    if ( filelineerrorstylep ) 
    printfileline () ;
    else printnl ( 65544L ) ;
    print ( 66712L ) ;
  } 
  if ( selector == 19 ) {
      
    if ( eqtb [7892293L ].cint <= 0 ) 
    {
      selector = 17 ;
      print ( 66713L ) ;
      selector = 19 ;
    } 
  } 
  lab50: if ( selector < 16 ) 
  {
    println () ;
    if ( interaction == 0 ) 
    selector = 16 ;
    else selector = 17 ;
    if ( logopened ) 
    selector = selector + 2 ;
  } 
  else {
      
    if ( interaction < 3 ) 
    {
      helpptr = 0 ;
      decr ( errorcount ) ;
    } 
    else if ( eqtb [7892293L ].cint > 0 ) 
    {
      {
	helpptr = 3 ;
	helpline [2 ]= 66702L ;
	helpline [1 ]= 66703L ;
	helpline [0 ]= 66704L ;
      } 
    } 
    else {
	
      {
	helpptr = 5 ;
	helpline [4 ]= 66702L ;
	helpline [3 ]= 66703L ;
	helpline [2 ]= 66704L ;
	helpline [1 ]= 66705L ;
	helpline [0 ]= 66706L ;
      } 
    } 
    error () ;
  } 
} 
void 
znewwhatsit ( smallnumber s , smallnumber w ) 
{
  newwhatsit_regmem 
  halfword p  ;
  p = getnode ( w ) ;
  mem [p ].hh.b0 = 8 ;
  mem [p ].hh.b1 = s ;
  mem [curlist .tailfield ].hh .v.RH = p ;
  curlist .tailfield = p ;
} 
void 
znewwritewhatsit ( smallnumber w ) 
{
  newwritewhatsit_regmem 
  newwhatsit ( curchr , w ) ;
  if ( w != 2 ) 
  scanfourbitint () ;
  else {
      
    scanint () ;
    if ( curval < 0 ) 
    curval = 17 ;
    else if ( ( curval > 15 ) && ( curval != 18 ) ) 
    curval = 16 ;
  } 
  mem [curlist .tailfield + 1 ].hh .v.LH = curval ;
} 
void 
zloadpicture ( boolean ispdf ) 
{
  loadpicture_regmem 
  char * picpath  ;
  realrect bounds  ;
  transform t, t2  ;
  realpoint corners[4]  ;
  real xsizereq, ysizereq  ;
  boolean checkkeywords  ;
  real xmin, xmax, ymin, ymax  ;
  smallnumber i  ;
  integer page  ;
  integer pdfboxtype  ;
  integer result  ;
  scanfilename () ;
  packfilename ( curname , curarea , curext ) ;
  pdfboxtype = 0 ;
  page = 0 ;
  if ( ispdf ) 
  {
    if ( scankeyword ( 66430L ) ) 
    {
      scanint () ;
      page = curval ;
    } 
    pdfboxtype = 6 ;
    if ( scankeyword ( 66797L ) ) 
    pdfboxtype = 1 ;
    else if ( scankeyword ( 66798L ) ) 
    pdfboxtype = 2 ;
    else if ( scankeyword ( 66799L ) ) 
    pdfboxtype = 3 ;
    else if ( scankeyword ( 66800L ) ) 
    pdfboxtype = 4 ;
    else if ( scankeyword ( 66801L ) ) 
    pdfboxtype = 5 ;
  } 
  if ( pdfboxtype == 6 ) 
  result = findpicfile ( addressof ( picpath ) , addressof ( bounds ) , 1 , 
  page ) ;
  else result = findpicfile ( addressof ( picpath ) , addressof ( bounds ) , 
  pdfboxtype , page ) ;
  setPoint ( corners [0 ], xField ( bounds ) , yField ( bounds ) ) ;
  setPoint ( corners [1 ], xField ( corners [0 ]) , yField ( bounds ) + 
  htField ( bounds ) ) ;
  setPoint ( corners [2 ], xField ( bounds ) + wdField ( bounds ) , yField ( 
  corners [1 ]) ) ;
  setPoint ( corners [3 ], xField ( corners [2 ]) , yField ( corners [0 ]
  ) ) ;
  xsizereq = 0.0 ;
  ysizereq = 0.0 ;
  makeidentity ( addressof ( t ) ) ;
  checkkeywords = true ;
  while ( checkkeywords ) {
      
    if ( scankeyword ( 66680L ) ) 
    {
      scanint () ;
      if ( ( xsizereq == 0.0 ) && ( ysizereq == 0.0 ) ) 
      {
	makescale ( addressof ( t2 ) , curval / ((double) 1000.0 ) , curval 
	/ ((double) 1000.0 ) ) ;
	{register integer for_end; i = 0 ;for_end = 3 ; if ( i <= for_end) 
	do 
	  transformpoint ( addressof ( corners [i ]) , addressof ( t2 ) ) ;
	while ( i++ < for_end ) ;} 
	transformconcat ( addressof ( t ) , addressof ( t2 ) ) ;
      } 
    } 
    else if ( scankeyword ( 66802L ) ) 
    {
      scanint () ;
      if ( ( xsizereq == 0.0 ) && ( ysizereq == 0.0 ) ) 
      {
	makescale ( addressof ( t2 ) , curval / ((double) 1000.0 ) , 1.0 ) ;
	{register integer for_end; i = 0 ;for_end = 3 ; if ( i <= for_end) 
	do 
	  transformpoint ( addressof ( corners [i ]) , addressof ( t2 ) ) ;
	while ( i++ < for_end ) ;} 
	transformconcat ( addressof ( t ) , addressof ( t2 ) ) ;
      } 
    } 
    else if ( scankeyword ( 66803L ) ) 
    {
      scanint () ;
      if ( ( xsizereq == 0.0 ) && ( ysizereq == 0.0 ) ) 
      {
	makescale ( addressof ( t2 ) , 1.0 , curval / ((double) 1000.0 ) ) ;
	{register integer for_end; i = 0 ;for_end = 3 ; if ( i <= for_end) 
	do 
	  transformpoint ( addressof ( corners [i ]) , addressof ( t2 ) ) ;
	while ( i++ < for_end ) ;} 
	transformconcat ( addressof ( t ) , addressof ( t2 ) ) ;
      } 
    } 
    else if ( scankeyword ( 66094L ) ) 
    {
      scandimen ( false , false , false ) ;
      if ( curval <= 0 ) 
      {
	{
	  if ( interaction == 3 ) 
	  ;
	  if ( filelineerrorstylep ) 
	  printfileline () ;
	  else printnl ( 65544L ) ;
	  print ( 66804L ) ;
	} 
	print ( 66805L ) ;
	printscaled ( curval ) ;
	print ( 66806L ) ;
	{
	  helpptr = 2 ;
	  helpline [1 ]= 66807L ;
	  helpline [0 ]= 66808L ;
	} 
	error () ;
      } 
      else xsizereq = Fix2D ( curval ) ;
    } 
    else if ( scankeyword ( 66095L ) ) 
    {
      scandimen ( false , false , false ) ;
      if ( curval <= 0 ) 
      {
	{
	  if ( interaction == 3 ) 
	  ;
	  if ( filelineerrorstylep ) 
	  printfileline () ;
	  else printnl ( 65544L ) ;
	  print ( 66804L ) ;
	} 
	print ( 66805L ) ;
	printscaled ( curval ) ;
	print ( 66806L ) ;
	{
	  helpptr = 2 ;
	  helpline [1 ]= 66807L ;
	  helpline [0 ]= 66808L ;
	} 
	error () ;
      } 
      else ysizereq = Fix2D ( curval ) ;
    } 
    else if ( scankeyword ( 66809L ) ) 
    {
      scandecimal () ;
      if ( ( xsizereq != 0.0 ) || ( ysizereq != 0.0 ) ) 
      {
	{
	  xmin = 1000000.0 ;
	  xmax = - (integer) xmin ;
	  ymin = xmin ;
	  ymax = xmax ;
	  {register integer for_end; i = 0 ;for_end = 3 ; if ( i <= for_end) 
	  do 
	    {
	      if ( xCoord ( corners [i ]) < xmin ) 
	      xmin = xCoord ( corners [i ]) ;
	      if ( xCoord ( corners [i ]) > xmax ) 
	      xmax = xCoord ( corners [i ]) ;
	      if ( yCoord ( corners [i ]) < ymin ) 
	      ymin = yCoord ( corners [i ]) ;
	      if ( yCoord ( corners [i ]) > ymax ) 
	      ymax = yCoord ( corners [i ]) ;
	    } 
	  while ( i++ < for_end ) ;} 
	} 
	if ( xsizereq == 0.0 ) 
	{
	  makescale ( addressof ( t2 ) , ysizereq / ((double) ( ymax - ymin ) 
	  ) , ysizereq / ((double) ( ymax - ymin ) ) ) ;
	} 
	else if ( ysizereq == 0.0 ) 
	{
	  makescale ( addressof ( t2 ) , xsizereq / ((double) ( xmax - xmin ) 
	  ) , xsizereq / ((double) ( xmax - xmin ) ) ) ;
	} 
	else {
	    
	  makescale ( addressof ( t2 ) , xsizereq / ((double) ( xmax - xmin ) 
	  ) , ysizereq / ((double) ( ymax - ymin ) ) ) ;
	} 
	{register integer for_end; i = 0 ;for_end = 3 ; if ( i <= for_end) 
	do 
	  transformpoint ( addressof ( corners [i ]) , addressof ( t2 ) ) ;
	while ( i++ < for_end ) ;} 
	xsizereq = 0.0 ;
	ysizereq = 0.0 ;
	transformconcat ( addressof ( t ) , addressof ( t2 ) ) ;
      } 
      makerotation ( addressof ( t2 ) , Fix2D ( curval ) * 3.141592653589793 
      / ((double) 180.0 ) ) ;
      {register integer for_end; i = 0 ;for_end = 3 ; if ( i <= for_end) do 
	transformpoint ( addressof ( corners [i ]) , addressof ( t2 ) ) ;
      while ( i++ < for_end ) ;} 
      {
	xmin = 1000000.0 ;
	xmax = - (integer) xmin ;
	ymin = xmin ;
	ymax = xmax ;
	{register integer for_end; i = 0 ;for_end = 3 ; if ( i <= for_end) 
	do 
	  {
	    if ( xCoord ( corners [i ]) < xmin ) 
	    xmin = xCoord ( corners [i ]) ;
	    if ( xCoord ( corners [i ]) > xmax ) 
	    xmax = xCoord ( corners [i ]) ;
	    if ( yCoord ( corners [i ]) < ymin ) 
	    ymin = yCoord ( corners [i ]) ;
	    if ( yCoord ( corners [i ]) > ymax ) 
	    ymax = yCoord ( corners [i ]) ;
	  } 
	while ( i++ < for_end ) ;} 
      } 
      setPoint ( corners [0 ], xmin , ymin ) ;
      setPoint ( corners [1 ], xmin , ymax ) ;
      setPoint ( corners [2 ], xmax , ymax ) ;
      setPoint ( corners [3 ], xmax , ymin ) ;
      transformconcat ( addressof ( t ) , addressof ( t2 ) ) ;
    } 
    else checkkeywords = false ;
  } 
  if ( ( xsizereq != 0.0 ) || ( ysizereq != 0.0 ) ) 
  {
    {
      xmin = 1000000.0 ;
      xmax = - (integer) xmin ;
      ymin = xmin ;
      ymax = xmax ;
      {register integer for_end; i = 0 ;for_end = 3 ; if ( i <= for_end) do 
	{
	  if ( xCoord ( corners [i ]) < xmin ) 
	  xmin = xCoord ( corners [i ]) ;
	  if ( xCoord ( corners [i ]) > xmax ) 
	  xmax = xCoord ( corners [i ]) ;
	  if ( yCoord ( corners [i ]) < ymin ) 
	  ymin = yCoord ( corners [i ]) ;
	  if ( yCoord ( corners [i ]) > ymax ) 
	  ymax = yCoord ( corners [i ]) ;
	} 
      while ( i++ < for_end ) ;} 
    } 
    if ( xsizereq == 0.0 ) 
    {
      makescale ( addressof ( t2 ) , ysizereq / ((double) ( ymax - ymin ) ) , 
      ysizereq / ((double) ( ymax - ymin ) ) ) ;
    } 
    else if ( ysizereq == 0.0 ) 
    {
      makescale ( addressof ( t2 ) , xsizereq / ((double) ( xmax - xmin ) ) , 
      xsizereq / ((double) ( xmax - xmin ) ) ) ;
    } 
    else {
	
      makescale ( addressof ( t2 ) , xsizereq / ((double) ( xmax - xmin ) ) , 
      ysizereq / ((double) ( ymax - ymin ) ) ) ;
    } 
    {register integer for_end; i = 0 ;for_end = 3 ; if ( i <= for_end) do 
      transformpoint ( addressof ( corners [i ]) , addressof ( t2 ) ) ;
    while ( i++ < for_end ) ;} 
    xsizereq = 0.0 ;
    ysizereq = 0.0 ;
    transformconcat ( addressof ( t ) , addressof ( t2 ) ) ;
  } 
  {
    xmin = 1000000.0 ;
    xmax = - (integer) xmin ;
    ymin = xmin ;
    ymax = xmax ;
    {register integer for_end; i = 0 ;for_end = 3 ; if ( i <= for_end) do 
      {
	if ( xCoord ( corners [i ]) < xmin ) 
	xmin = xCoord ( corners [i ]) ;
	if ( xCoord ( corners [i ]) > xmax ) 
	xmax = xCoord ( corners [i ]) ;
	if ( yCoord ( corners [i ]) < ymin ) 
	ymin = yCoord ( corners [i ]) ;
	if ( yCoord ( corners [i ]) > ymax ) 
	ymax = yCoord ( corners [i ]) ;
      } 
    while ( i++ < for_end ) ;} 
  } 
  maketranslation ( addressof ( t2 ) , - (integer) xmin * 72 / ((double) 72.27 
  ) , - (integer) ymin * 72 / ((double) 72.27 ) ) ;
  transformconcat ( addressof ( t ) , addressof ( t2 ) ) ;
  if ( result == 0 ) 
  {
    newwhatsit ( 43 , 9 + ( strlen ( picpath ) + sizeof ( memoryword ) - 1 ) / 
    sizeof ( memoryword ) ) ;
    if ( ispdf ) 
    {
      mem [curlist .tailfield ].hh.b1 = 44 ;
    } 
    mem [curlist .tailfield + 4 ].hh.b0 = strlen ( picpath ) ;
    mem [curlist .tailfield + 4 ].hh.b1 = page ;
    mem [curlist .tailfield + 8 ].hh.b0 = pdfboxtype ;
    mem [curlist .tailfield + 1 ].cint = D2Fix ( xmax - xmin ) ;
    mem [curlist .tailfield + 3 ].cint = D2Fix ( ymax - ymin ) ;
    mem [curlist .tailfield + 2 ].cint = 0 ;
    mem [curlist .tailfield + 5 ].hh .v.LH = D2Fix ( aField ( t ) ) ;
    mem [curlist .tailfield + 5 ].hh .v.RH = D2Fix ( bField ( t ) ) ;
    mem [curlist .tailfield + 6 ].hh .v.LH = D2Fix ( cField ( t ) ) ;
    mem [curlist .tailfield + 6 ].hh .v.RH = D2Fix ( dField ( t ) ) ;
    mem [curlist .tailfield + 7 ].hh .v.LH = D2Fix ( xField ( t ) ) ;
    mem [curlist .tailfield + 7 ].hh .v.RH = D2Fix ( yField ( t ) ) ;
    memcpy ( addressof ( mem [curlist .tailfield + 9 ]) , picpath , strlen ( 
    picpath ) ) ;
    libcfree ( picpath ) ;
  } 
  else {
      
    {
      if ( interaction == 3 ) 
      ;
      if ( filelineerrorstylep ) 
      printfileline () ;
      else printnl ( 65544L ) ;
      print ( 66810L ) ;
    } 
    printfilename ( curname , curarea , curext ) ;
    print ( 39 ) ;
    if ( result == -43 ) 
    {
      {
	helpptr = 2 ;
	helpline [1 ]= 66811L ;
	helpline [0 ]= 66812L ;
      } 
    } 
    else {
	
      {
	helpptr = 2 ;
	helpline [1 ]= 66811L ;
	helpline [0 ]= 66813L ;
      } 
    } 
    error () ;
  } 
} 
void 
scanandpackname ( void ) 
{
  scanandpackname_regmem 
  scanfilename () ;
  packfilename ( curname , curarea , curext ) ;
} 
void 
doextension ( void ) 
{
  doextension_regmem 
  integer i, j, k  ;
  halfword p  ;
  switch ( curchr ) 
  {case 0 : 
    {
      newwritewhatsit ( 3 ) ;
      scanoptionalequals () ;
      scanfilename () ;
      mem [curlist .tailfield + 1 ].hh .v.RH = curname ;
      mem [curlist .tailfield + 2 ].hh .v.LH = curarea ;
      mem [curlist .tailfield + 2 ].hh .v.RH = curext ;
    } 
    break ;
  case 1 : 
    {
      k = curcs ;
      newwritewhatsit ( 2 ) ;
      curcs = k ;
      p = scantoks ( false , false ) ;
      mem [curlist .tailfield + 1 ].hh .v.RH = defref ;
    } 
    break ;
  case 2 : 
    {
      newwritewhatsit ( 2 ) ;
      mem [curlist .tailfield + 1 ].hh .v.RH = -268435455L ;
    } 
    break ;
  case 3 : 
    {
      if ( scankeyword ( 66496L ) ) 
      {
	newwhatsit ( 4 , 2 ) ;
	mem [curlist .tailfield + 1 ].hh .v.LH = -268435455L ;
	p = scantoks ( false , false ) ;
	mem [curlist .tailfield + 1 ].hh .v.RH = defref ;
      } 
      else {
	  
	newwhatsit ( 3 , 2 ) ;
	mem [curlist .tailfield + 1 ].hh .v.LH = -268435455L ;
	p = scantoks ( false , true ) ;
	mem [curlist .tailfield + 1 ].hh .v.RH = defref ;
      } 
    } 
    break ;
  case 5 : 
    {
      getxtoken () ;
      if ( ( curcmd == 59 ) && ( curchr <= 2 ) ) 
      {
	p = curlist .tailfield ;
	doextension () ;
	outwhat ( curlist .tailfield ) ;
	flushnodelist ( curlist .tailfield ) ;
	curlist .tailfield = p ;
	mem [p ].hh .v.RH = -268435455L ;
      } 
      else backinput () ;
    } 
    break ;
  case 6 : 
    if ( abs ( curlist .modefield ) != 105 ) 
    reportillegalcase () ;
    else {
	
      newwhatsit ( 5 , 2 ) ;
      scanint () ;
      if ( curval <= 0 ) 
      curlist .auxfield .hh .v.RH = 0 ;
      else if ( curval > 255 ) 
      curlist .auxfield .hh .v.RH = 0 ;
      else curlist .auxfield .hh .v.RH = curval ;
      mem [curlist .tailfield + 1 ].hh .v.RH = curlist .auxfield .hh .v.RH ;
      mem [curlist .tailfield + 1 ].hh.b0 = normmin ( eqtb [7892315L ]
      .cint ) ;
      mem [curlist .tailfield + 1 ].hh.b1 = normmin ( eqtb [7892316L ]
      .cint ) ;
    } 
    break ;
  case 23 : 
    {
      newwhatsit ( 23 , 2 ) ;
    } 
    break ;
  case 33 : 
    {
      secondsandmicros ( epochseconds , microseconds ) ;
    } 
    break ;
  case 35 : 
    {
      scanint () ;
      if ( curval < 0 ) 
      curval = - (integer) curval ;
      randomseed = curval ;
      initrandoms ( randomseed ) ;
    } 
    break ;
  case 41 : 
    if ( abs ( curlist .modefield ) == 209 ) 
    reportillegalcase () ;
    else loadpicture ( false ) ;
    break ;
  case 42 : 
    if ( abs ( curlist .modefield ) == 209 ) 
    reportillegalcase () ;
    else loadpicture ( true ) ;
    break ;
  case 43 : 
    {
      if ( abs ( curlist .modefield ) == 1 ) 
      {
	backinput () ;
	newgraf ( true ) ;
      } 
      else if ( abs ( curlist .modefield ) == 209 ) 
      reportillegalcase () ;
      else {
	  
	if ( ( ( fontarea [eqtb [1206823L ].hh .v.RH ]== 65535L ) || ( 
	fontarea [eqtb [1206823L ].hh .v.RH ]== 65534L ) ) ) 
	{
	  newwhatsit ( 42 , 5 ) ;
	  scanint () ;
	  if ( ( curval < 0 ) || ( curval > 65535L ) ) 
	  {
	    {
	      if ( interaction == 3 ) 
	      ;
	      if ( filelineerrorstylep ) 
	      printfileline () ;
	      else printnl ( 65544L ) ;
	      print ( 66795L ) ;
	    } 
	    {
	      helpptr = 2 ;
	      helpline [1 ]= 66796L ;
	      helpline [0 ]= 66006L ;
	    } 
	    interror ( curval ) ;
	    curval = 0 ;
	  } 
	  mem [curlist .tailfield + 4 ].qqqq .b1 = eqtb [1206823L ].hh 
	  .v.RH ;
	  mem [curlist .tailfield + 4 ].qqqq .b2 = curval ;
	  setnativeglyphmetrics ( curlist .tailfield , ( eqtb [7892342L ]
	  .cint > 0 ) ) ;
	} 
	else notnativefonterror ( 59 , 43 , eqtb [1206823L ].hh .v.RH ) ;
      } 
    } 
    break ;
  case 44 : 
    {
      scanandpackname () ;
      i = getencodingmodeandinfo ( addressof ( j ) ) ;
      if ( i == 0 ) 
      {
	{
	  if ( interaction == 3 ) 
	  ;
	  if ( filelineerrorstylep ) 
	  printfileline () ;
	  else printnl ( 65544L ) ;
	  print ( 66814L ) ;
	} 
	{
	  helpptr = 2 ;
	  helpline [1 ]= 66815L ;
	  helpline [0 ]= 66816L ;
	} 
	error () ;
      } 
      else setinputfileencoding ( inputfile [inopen ], i , j ) ;
    } 
    break ;
  case 45 : 
    {
      scanandpackname () ;
      i = getencodingmodeandinfo ( addressof ( j ) ) ;
      eqtb [7892345L ].cint = i ;
      eqtb [7892346L ].cint = j ;
    } 
    break ;
  case 46 : 
    {
      scanfilename () ;
      if ( length ( curname ) == 0 ) 
      eqtb [7892336L ].cint = 0 ;
      else eqtb [7892336L ].cint = curname ;
    } 
    break ;
    default: 
    confusion ( 66765L ) ;
    break ;
  } 
} 
void 
fixlanguage ( void ) 
{
  fixlanguage_regmem 
  UTF16code l  ;
  if ( eqtb [7892314L ].cint <= 0 ) 
  l = 0 ;
  else if ( eqtb [7892314L ].cint > 255 ) 
  l = 0 ;
  else l = eqtb [7892314L ].cint ;
  if ( l != curlist .auxfield .hh .v.RH ) 
  {
    newwhatsit ( 5 , 2 ) ;
    mem [curlist .tailfield + 1 ].hh .v.RH = l ;
    curlist .auxfield .hh .v.RH = l ;
    mem [curlist .tailfield + 1 ].hh.b0 = normmin ( eqtb [7892315L ].cint 
    ) ;
    mem [curlist .tailfield + 1 ].hh.b1 = normmin ( eqtb [7892316L ].cint 
    ) ;
  } 
} 
void 
insertsrcspecial ( void ) 
{
  insertsrcspecial_regmem 
  halfword toklist, p, q  ;
  if ( ( sourcefilenamestack [inopen ]> 0 && isnewsource ( 
  sourcefilenamestack [inopen ], line ) ) ) 
  {
    toklist = getavail () ;
    p = toklist ;
    mem [p ].hh .v.LH = 34749091L ;
    mem [p ].hh .v.RH = getavail () ;
    p = mem [p ].hh .v.RH ;
    mem [p ].hh .v.LH = 2097275L ;
    q = strtoks ( makesrcspecial ( sourcefilenamestack [inopen ], line ) ) ;
    mem [p ].hh .v.RH = mem [memtop - 3 ].hh .v.RH ;
    p = q ;
    mem [p ].hh .v.RH = getavail () ;
    p = mem [p ].hh .v.RH ;
    mem [p ].hh .v.LH = 4194429L ;
    begintokenlist ( toklist , 5 ) ;
    remembersourceinfo ( sourcefilenamestack [inopen ], line ) ;
  } 
} 
void 
appendsrcspecial ( void ) 
{
  appendsrcspecial_regmem 
  halfword q  ;
  if ( ( sourcefilenamestack [inopen ]> 0 && isnewsource ( 
  sourcefilenamestack [inopen ], line ) ) ) 
  {
    newwhatsit ( 3 , 2 ) ;
    mem [curlist .tailfield + 1 ].hh .v.LH = 0 ;
    defref = getavail () ;
    mem [defref ].hh .v.LH = -268435455L ;
    q = strtoks ( makesrcspecial ( sourcefilenamestack [inopen ], line ) ) ;
    mem [defref ].hh .v.RH = mem [memtop - 3 ].hh .v.RH ;
    mem [curlist .tailfield + 1 ].hh .v.RH = defref ;
    remembersourceinfo ( sourcefilenamestack [inopen ], line ) ;
  } 
} 
void 
handlerightbrace ( void ) 
{
  handlerightbrace_regmem 
  halfword p, q  ;
  scaled d  ;
  integer f  ;
  switch ( curgroup ) 
  {case 1 : 
    unsave () ;
    break ;
  case 0 : 
    {
      {
	if ( interaction == 3 ) 
	;
	if ( filelineerrorstylep ) 
	printfileline () ;
	else printnl ( 65544L ) ;
	print ( 66478L ) ;
      } 
      {
	helpptr = 2 ;
	helpline [1 ]= 66479L ;
	helpline [0 ]= 66480L ;
      } 
      error () ;
    } 
    break ;
  case 14 : 
  case 15 : 
  case 16 : 
    extrarightbrace () ;
    break ;
  case 2 : 
    package ( 0 ) ;
    break ;
  case 3 : 
    {
      adjusttail = memtop - 5 ;
      preadjusttail = memtop - 14 ;
      package ( 0 ) ;
    } 
    break ;
  case 4 : 
    if ( ( eqtb [7892323L ].cint > 0 ) && ( curlist .modefield == 105 ) ) 
    {
      backinput () ;
      curtok = partoken ;
      backinput () ;
      curinput .indexfield = 5 ;
    } 
    else {
	
      endgraf () ;
      package ( 0 ) ;
    } 
    break ;
  case 5 : 
    if ( ( eqtb [7892323L ].cint > 0 ) && ( curlist .modefield == 105 ) ) 
    {
      backinput () ;
      curtok = partoken ;
      backinput () ;
      curinput .indexfield = 5 ;
    } 
    else {
	
      endgraf () ;
      package ( 4 ) ;
    } 
    break ;
  case 11 : 
    if ( ( eqtb [7892323L ].cint > 1 ) && ( curlist .modefield == 105 ) ) 
    {
      backinput () ;
      curtok = partoken ;
      backinput () ;
      curinput .indexfield = 5 ;
    } 
    else {
	
      endgraf () ;
      q = eqtb [1205774L ].hh .v.RH ;
      incr ( mem [q ].hh .v.RH ) ;
      d = eqtb [9006726L ].cint ;
      f = eqtb [7892306L ].cint ;
      unsave () ;
      saveptr = saveptr - 2 ;
      p = vpackage ( mem [curlist .headfield ].hh .v.RH , 0 , 1 , 
      1073741823L ) ;
      popnest () ;
      if ( savestack [saveptr + 0 ].cint < 255 ) 
      {
	{
	  mem [curlist .tailfield ].hh .v.RH = getnode ( 5 ) ;
	  curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
	} 
	mem [curlist .tailfield ].hh.b0 = 3 ;
	mem [curlist .tailfield ].hh.b1 = savestack [saveptr + 0 ].cint ;
	mem [curlist .tailfield + 3 ].cint = mem [p + 3 ].cint + mem [p + 
	2 ].cint ;
	mem [curlist .tailfield + 4 ].hh .v.LH = mem [p + 5 ].hh .v.RH ;
	mem [curlist .tailfield + 4 ].hh .v.RH = q ;
	mem [curlist .tailfield + 2 ].cint = d ;
	mem [curlist .tailfield + 1 ].cint = f ;
      } 
      else {
	  
	{
	  mem [curlist .tailfield ].hh .v.RH = getnode ( 2 ) ;
	  curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
	} 
	mem [curlist .tailfield ].hh.b0 = 5 ;
	mem [curlist .tailfield ].hh.b1 = savestack [saveptr + 1 ].cint ;
	mem [curlist .tailfield + 1 ].cint = mem [p + 5 ].hh .v.RH ;
	deleteglueref ( q ) ;
      } 
      freenode ( p , 8 ) ;
      if ( nestptr == 0 ) 
      buildpage () ;
    } 
    break ;
  case 8 : 
    if ( ( eqtb [7892323L ].cint > 1 ) && ( curlist .modefield == 105 ) ) 
    {
      backinput () ;
      curtok = partoken ;
      backinput () ;
      curinput .indexfield = 5 ;
    } 
    else {
	
      while ( ( curinput .statefield == 0 ) && ( curinput .locfield == 
      -268435455L ) && ( curinput .indexfield == 3 ) ) endtokenlist () ;
      if ( ( curinput .statefield != 0 ) || ( curinput .locfield != 
      -268435455L ) || ( curinput .indexfield != 7 ) ) 
      {
	{
	  if ( interaction == 3 ) 
	  ;
	  if ( filelineerrorstylep ) 
	  printfileline () ;
	  else printnl ( 65544L ) ;
	  print ( 65924L ) ;
	} 
	{
	  helpptr = 2 ;
	  helpline [1 ]= 66447L ;
	  helpline [0 ]= 66448L ;
	} 
	error () ;
	do {
	    gettoken () ;
	} while ( ! ( curinput .locfield == -268435455L ) ) ;
      } 
      outputcanend = true ;
      endtokenlist () ;
      outputcanend = false ;
      endgraf () ;
      unsave () ;
      outputactive = false ;
      insertpenalties = 0 ;
      if ( eqtb [1206822L ].hh .v.RH != -268435455L ) 
      {
	{
	  if ( interaction == 3 ) 
	  ;
	  if ( filelineerrorstylep ) 
	  printfileline () ;
	  else printnl ( 65544L ) ;
	  print ( 66449L ) ;
	} 
	printesc ( 65710L ) ;
	printint ( 255 ) ;
	{
	  helpptr = 3 ;
	  helpline [2 ]= 66450L ;
	  helpline [1 ]= 66451L ;
	  helpline [0 ]= 66452L ;
	} 
	boxerror ( 255 ) ;
      } 
      if ( curlist .tailfield != curlist .headfield ) 
      {
	mem [pagetail ].hh .v.RH = mem [curlist .headfield ].hh .v.RH ;
	pagetail = curlist .tailfield ;
      } 
      if ( mem [memtop - 2 ].hh .v.RH != -268435455L ) 
      {
	if ( mem [memtop - 1 ].hh .v.RH == -268435455L ) 
	nest [0 ].tailfield = pagetail ;
	mem [pagetail ].hh .v.RH = mem [memtop - 1 ].hh .v.RH ;
	mem [memtop - 1 ].hh .v.RH = mem [memtop - 2 ].hh .v.RH ;
	mem [memtop - 2 ].hh .v.RH = -268435455L ;
	pagetail = memtop - 2 ;
      } 
      flushnodelist ( discptr [2 ]) ;
      discptr [2 ]= -268435455L ;
      popnest () ;
      buildpage () ;
    } 
    break ;
  case 10 : 
    builddiscretionary () ;
    break ;
  case 6 : 
    {
      backinput () ;
      curtok = 34749082L ;
      {
	if ( interaction == 3 ) 
	;
	if ( filelineerrorstylep ) 
	printfileline () ;
	else printnl ( 65544L ) ;
	print ( 65959L ) ;
      } 
      printesc ( 66328L ) ;
      print ( 65960L ) ;
      {
	helpptr = 1 ;
	helpline [0 ]= 66561L ;
      } 
      inserror () ;
    } 
    break ;
  case 7 : 
    if ( ( eqtb [7892323L ].cint > 1 ) && ( curlist .modefield == 105 ) ) 
    {
      backinput () ;
      curtok = partoken ;
      backinput () ;
      curinput .indexfield = 5 ;
    } 
    else {
	
      endgraf () ;
      unsave () ;
      alignpeek () ;
    } 
    break ;
  case 12 : 
    if ( ( eqtb [7892323L ].cint > 0 ) && ( curlist .modefield == 105 ) ) 
    {
      backinput () ;
      curtok = partoken ;
      backinput () ;
      curinput .indexfield = 5 ;
    } 
    else {
	
      endgraf () ;
      unsave () ;
      saveptr = saveptr - 2 ;
      p = vpackage ( mem [curlist .headfield ].hh .v.RH , savestack [
      saveptr + 1 ].cint , savestack [saveptr + 0 ].cint , 1073741823L ) ;
      popnest () ;
      {
	mem [curlist .tailfield ].hh .v.RH = newnoad () ;
	curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
      } 
      mem [curlist .tailfield ].hh.b0 = 29 ;
      mem [curlist .tailfield + 1 ].hh .v.RH = 2 ;
      mem [curlist .tailfield + 1 ].hh .v.LH = p ;
    } 
    break ;
  case 13 : 
    buildchoices () ;
    break ;
  case 9 : 
    {
      unsave () ;
      decr ( saveptr ) ;
      mem [savestack [saveptr + 0 ].cint ].hh .v.RH = 3 ;
      p = finmlist ( -268435455L ) ;
      mem [savestack [saveptr + 0 ].cint ].hh .v.LH = p ;
      if ( p != -268435455L ) {
	  
	if ( mem [p ].hh .v.RH == -268435455L ) {
	    
	  if ( mem [p ].hh.b0 == 16 ) 
	  {
	    if ( mem [p + 3 ].hh .v.RH == 0 ) {
		
	      if ( mem [p + 2 ].hh .v.RH == 0 ) 
	      {
		mem [savestack [saveptr + 0 ].cint ].hh = mem [p + 1 ]
		.hh ;
		freenode ( p , 4 ) ;
	      } 
	    } 
	  } 
	  else if ( mem [p ].hh.b0 == 28 ) {
	      
	    if ( savestack [saveptr + 0 ].cint == curlist .tailfield + 1 ) {
		
	      if ( mem [curlist .tailfield ].hh.b0 == 16 ) 
	      {
		q = curlist .headfield ;
		while ( mem [q ].hh .v.RH != curlist .tailfield ) q = mem [
		q ].hh .v.RH ;
		mem [q ].hh .v.RH = p ;
		freenode ( curlist .tailfield , 4 ) ;
		curlist .tailfield = p ;
	      } 
	    } 
	  } 
	} 
      } 
    } 
    break ;
    default: 
    confusion ( 66481L ) ;
    break ;
  } 
} 
void 
maincontrol ( void ) 
{
  /* 60 21 70 80 90 91 92 95 100 101 110 111 112 71 72 120 10 */ 
  maincontrol_regmem 
  integer t  ;
  if ( eqtb [1206302L ].hh .v.RH != -268435455L ) 
  begintokenlist ( eqtb [1206302L ].hh .v.RH , 13 ) ;
  lab60: getxtoken () ;
  lab21: if ( interrupt != 0 ) {
      
    if ( OKtointerrupt ) 
    {
      backinput () ;
      {
	if ( interrupt != 0 ) 
	pauseforinstructions () ;
      } 
      goto lab60 ;
    } 
  } 
	;
#ifdef TEXMF_DEBUG
  if ( panicking ) 
  checkmem ( false ) ;
#endif /* TEXMF_DEBUG */
  if ( eqtb [7892300L ].cint > 0 ) 
  showcurcmdchr () ;
  switch ( abs ( curlist .modefield ) + curcmd ) 
  {case 116 : 
  case 117 : 
  case 173 : 
    goto lab70 ;
    break ;
  case 121 : 
    {
      scanusvnum () ;
      curchr = curval ;
      goto lab70 ;
    } 
    break ;
  case 170 : 
    {
      getxtoken () ;
      if ( ( curcmd == 11 ) || ( curcmd == 12 ) || ( curcmd == 68 ) || ( 
      curcmd == 16 ) ) 
      cancelboundary = true ;
      goto lab21 ;
    } 
    break ;
    default: 
    {
      if ( abs ( curlist .modefield ) == 105 ) {
	  
	if ( ( eqtb [7892343L ].cint > 0 ) && ( spaceclass != 4096 ) && ( 
	prevclass != ( 4095 ) ) ) 
	{
	  prevclass = ( 4095 ) ;
	  findsaelement ( 6 , spaceclass * 4096 + ( 4095 ) , false ) ;
	  if ( ( curptr != -268435455L ) && ( mem [curptr + 1 ].hh .v.RH != 
	  -268435455L ) ) 
	  {
	    if ( curcs == 0 ) 
	    {
	      if ( curcmd == 16 ) 
	      curcmd = 12 ;
	      curtok = ( curcmd * 2097152L ) + curchr ;
	    } 
	    else curtok = 33554431L + curcs ;
	    backinput () ;
	    begintokenlist ( mem [curptr + 1 ].hh .v.RH , 17 ) ;
	    goto lab60 ;
	  } 
	} 
      } 
      switch ( abs ( curlist .modefield ) + curcmd ) 
      {case 115 : 
	if ( curlist .auxfield .hh .v.LH == 1000 ) 
	goto lab120 ;
	else appspace () ;
	break ;
      case 169 : 
      case 273 : 
	goto lab120 ;
	break ;
      case 1 : 
      case 105 : 
      case 209 : 
      case 11 : 
      case 219 : 
      case 274 : 
	;
	break ;
      case 40 : 
      case 144 : 
      case 248 : 
	{
	  if ( curchr == 0 ) 
	  {
	    do {
		getxtoken () ;
	    } while ( ! ( curcmd != 10 ) ) ;
	    goto lab21 ;
	  } 
	  else {
	      
	    t = scannerstatus ;
	    scannerstatus = 0 ;
	    getnext () ;
	    scannerstatus = t ;
	    if ( curcs < 1179650L ) 
	    curcs = primlookup ( curcs - 1114113L ) ;
	    else curcs = primlookup ( hash [curcs ].v.RH ) ;
	    if ( curcs != 0 ) 
	    {
	      curcmd = eqtb [1194662L + curcs ].hh.b0 ;
	      curchr = eqtb [1194662L + curcs ].hh .v.RH ;
	      curtok = 34749093L + curcs ;
	      goto lab21 ;
	    } 
	  } 
	} 
	break ;
      case 15 : 
	if ( itsallover () ) 
	return ;
	break ;
      case 23 : 
      case 126 : 
      case 230 : 
      case 72 : 
      case 176 : 
      case 280 : 
      case 39 : 
      case 45 : 
      case 49 : 
      case 153 : 
      case 7 : 
      case 111 : 
      case 215 : 
	reportillegalcase () ;
	break ;
      case 8 : 
      case 112 : 
      case 9 : 
      case 113 : 
      case 18 : 
      case 122 : 
      case 70 : 
      case 174 : 
      case 71 : 
      case 175 : 
      case 51 : 
      case 155 : 
      case 16 : 
      case 120 : 
      case 50 : 
      case 154 : 
      case 53 : 
      case 157 : 
      case 67 : 
      case 171 : 
      case 54 : 
      case 158 : 
      case 55 : 
      case 159 : 
      case 57 : 
      case 161 : 
      case 56 : 
      case 160 : 
      case 31 : 
      case 135 : 
      case 52 : 
      case 156 : 
      case 29 : 
      case 133 : 
      case 47 : 
      case 151 : 
      case 218 : 
      case 222 : 
      case 223 : 
      case 236 : 
      case 233 : 
      case 242 : 
      case 245 : 
	insertdollarsign () ;
	break ;
      case 37 : 
      case 140 : 
      case 244 : 
	{
	  {
	    mem [curlist .tailfield ].hh .v.RH = scanrulespec () ;
	    curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
	  } 
	  if ( abs ( curlist .modefield ) == 1 ) 
	  curlist .auxfield .cint = -65536000L ;
	  else if ( abs ( curlist .modefield ) == 105 ) 
	  curlist .auxfield .hh .v.LH = 1000 ;
	} 
	break ;
      case 28 : 
      case 131 : 
      case 235 : 
      case 237 : 
	appendglue () ;
	break ;
      case 30 : 
      case 134 : 
      case 238 : 
      case 239 : 
	appendkern () ;
	break ;
      case 2 : 
      case 106 : 
	newsavelevel ( 1 ) ;
	break ;
      case 62 : 
      case 166 : 
      case 270 : 
	newsavelevel ( 14 ) ;
	break ;
      case 63 : 
      case 167 : 
      case 271 : 
	if ( curgroup == 14 ) 
	unsave () ;
	else offsave () ;
	break ;
      case 3 : 
      case 107 : 
      case 211 : 
	handlerightbrace () ;
	break ;
      case 22 : 
      case 127 : 
      case 231 : 
	{
	  t = curchr ;
	  scandimen ( false , false , false ) ;
	  if ( t == 0 ) 
	  scanbox ( curval ) ;
	  else scanbox ( - (integer) curval ) ;
	} 
	break ;
      case 32 : 
      case 136 : 
      case 240 : 
	scanbox ( 1073807261L + curchr ) ;
	break ;
      case 21 : 
      case 125 : 
      case 229 : 
	beginbox ( 0 ) ;
	break ;
      case 44 : 
	newgraf ( curchr > 0 ) ;
	break ;
      case 12 : 
      case 13 : 
      case 17 : 
      case 69 : 
      case 4 : 
      case 24 : 
      case 36 : 
      case 46 : 
      case 48 : 
      case 27 : 
      case 34 : 
      case 65 : 
      case 66 : 
	{
	  backinput () ;
	  newgraf ( true ) ;
	} 
	break ;
      case 148 : 
      case 252 : 
	indentinhmode () ;
	break ;
      case 14 : 
	{
	  normalparagraph () ;
	  if ( curlist .modefield > 0 ) 
	  buildpage () ;
	} 
	break ;
      case 118 : 
	{
	  if ( alignstate < 0 ) 
	  offsave () ;
	  endgraf () ;
	  if ( curlist .modefield == 1 ) 
	  buildpage () ;
	} 
	break ;
      case 119 : 
      case 132 : 
      case 141 : 
      case 129 : 
      case 137 : 
	headforvmode () ;
	break ;
      case 38 : 
      case 142 : 
      case 246 : 
      case 143 : 
      case 247 : 
	begininsertoradjust () ;
	break ;
      case 19 : 
      case 123 : 
      case 227 : 
	makemark () ;
	break ;
      case 43 : 
      case 147 : 
      case 251 : 
	appendpenalty () ;
	break ;
      case 26 : 
      case 130 : 
      case 234 : 
	deletelast () ;
	break ;
      case 25 : 
      case 128 : 
      case 232 : 
	unpackage () ;
	break ;
      case 149 : 
	appenditaliccorrection () ;
	break ;
      case 253 : 
	{
	  mem [curlist .tailfield ].hh .v.RH = newkern ( 0 ) ;
	  curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
	} 
	break ;
      case 152 : 
      case 256 : 
	appenddiscretionary () ;
	break ;
      case 150 : 
	makeaccent () ;
	break ;
      case 6 : 
      case 110 : 
      case 214 : 
      case 5 : 
      case 109 : 
      case 213 : 
	alignerror () ;
	break ;
      case 35 : 
      case 139 : 
      case 243 : 
	noalignerror () ;
	break ;
      case 64 : 
      case 168 : 
      case 272 : 
	omiterror () ;
	break ;
      case 33 : 
	initalign () ;
	break ;
      case 138 : 
	if ( curchr > 0 ) 
	{
	  if ( eTeXenabled ( ( eqtb [7892339L ].cint > 0 ) , curcmd , curchr 
	  ) ) 
	  {
	    mem [curlist .tailfield ].hh .v.RH = newmath ( 0 , curchr ) ;
	    curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
	  } 
	} 
	else initalign () ;
	break ;
      case 241 : 
	if ( privileged () ) {
	    
	  if ( curgroup == 15 ) 
	  initalign () ;
	  else offsave () ;
	} 
	break ;
      case 10 : 
      case 114 : 
	if ( ( eqtb [7892323L ].cint > 1 ) && ( curlist .modefield == 105 ) 
	) 
	{
	  backinput () ;
	  curtok = partoken ;
	  backinput () ;
	  curinput .indexfield = 5 ;
	} 
	else doendv () ;
	break ;
      case 68 : 
      case 172 : 
      case 276 : 
	cserror () ;
	break ;
      case 108 : 
	initmath () ;
	break ;
      case 257 : 
	if ( privileged () ) {
	    
	  if ( curgroup == 15 ) 
	  starteqno () ;
	  else offsave () ;
	} 
	break ;
      case 210 : 
	{
	  {
	    mem [curlist .tailfield ].hh .v.RH = newnoad () ;
	    curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
	  } 
	  backinput () ;
	  scanmath ( curlist .tailfield + 1 ) ;
	} 
	break ;
      case 220 : 
      case 221 : 
      case 277 : 
	setmathchar ( eqtb [5664040L + curchr ].hh .v.RH ) ;
	break ;
      case 225 : 
	{
	  scancharnum () ;
	  curchr = curval ;
	  setmathchar ( eqtb [5664040L + curchr ].hh .v.RH ) ;
	} 
	break ;
      case 226 : 
	if ( curchr == 2 ) 
	{
	  scanmathclassint () ;
	  t = setclassfield ( curval ) ;
	  scanmathfamint () ;
	  t = t + setfamilyfield ( curval ) ;
	  scanusvnum () ;
	  t = t + curval ;
	  setmathchar ( t ) ;
	} 
	else if ( curchr == 1 ) 
	{
	  scanxetexmathcharint () ;
	  setmathchar ( curval ) ;
	} 
	else {
	    
	  scanfifteenbitint () ;
	  setmathchar ( setclassfield ( curval / 4096 ) + setfamilyfield ( ( 
	  curval % 4096 ) / 256 ) + ( curval % 256 ) ) ;
	} 
	break ;
      case 278 : 
	{
	  setmathchar ( setclassfield ( curchr / 4096 ) + setfamilyfield ( ( 
	  curchr % 4096 ) / 256 ) + ( curchr % 256 ) ) ;
	} 
	break ;
      case 279 : 
	setmathchar ( curchr ) ;
	break ;
      case 224 : 
	{
	  if ( curchr == 1 ) 
	  {
	    scanmathclassint () ;
	    t = setclassfield ( curval ) ;
	    scanmathfamint () ;
	    t = t + setfamilyfield ( curval ) ;
	    scanusvnum () ;
	    t = t + curval ;
	    setmathchar ( t ) ;
	  } 
	  else {
	      
	    scandelimiterint () ;
	    curval = curval / 4096 ;
	    setmathchar ( setclassfield ( curval / 4096 ) + setfamilyfield ( ( 
	    curval % 4096 ) / 256 ) + ( curval % 256 ) ) ;
	  } 
	} 
	break ;
      case 259 : 
	{
	  {
	    mem [curlist .tailfield ].hh .v.RH = newnoad () ;
	    curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
	  } 
	  mem [curlist .tailfield ].hh.b0 = curchr ;
	  scanmath ( curlist .tailfield + 1 ) ;
	} 
	break ;
      case 260 : 
	mathlimitswitch () ;
	break ;
      case 275 : 
	mathradical () ;
	break ;
      case 254 : 
      case 255 : 
	mathac () ;
	break ;
      case 265 : 
	{
	  scanspec ( 12 , false ) ;
	  normalparagraph () ;
	  pushnest () ;
	  curlist .modefield = -1 ;
	  curlist .auxfield .cint = -65536000L ;
	  if ( ( insertsrcspecialeveryvbox ) ) 
	  insertsrcspecial () ;
	  if ( eqtb [1206301L ].hh .v.RH != -268435455L ) 
	  begintokenlist ( eqtb [1206301L ].hh .v.RH , 12 ) ;
	} 
	break ;
      case 262 : 
	{
	  mem [curlist .tailfield ].hh .v.RH = newstyle ( curchr ) ;
	  curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
	} 
	break ;
      case 264 : 
	{
	  {
	    mem [curlist .tailfield ].hh .v.RH = newglue ( membot ) ;
	    curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
	  } 
	  mem [curlist .tailfield ].hh.b1 = 98 ;
	} 
	break ;
      case 263 : 
	appendchoices () ;
	break ;
      case 217 : 
      case 216 : 
	subsup () ;
	break ;
      case 261 : 
	mathfraction () ;
	break ;
      case 258 : 
	mathleftright () ;
	break ;
      case 212 : 
	if ( curgroup == 15 ) 
	aftermath () ;
	else offsave () ;
	break ;
      case 73 : 
      case 177 : 
      case 281 : 
      case 74 : 
      case 178 : 
      case 282 : 
      case 75 : 
      case 179 : 
      case 283 : 
      case 76 : 
      case 180 : 
      case 284 : 
      case 77 : 
      case 181 : 
      case 285 : 
      case 78 : 
      case 182 : 
      case 286 : 
      case 79 : 
      case 183 : 
      case 287 : 
      case 80 : 
      case 184 : 
      case 288 : 
      case 81 : 
      case 185 : 
      case 289 : 
      case 82 : 
      case 186 : 
      case 290 : 
      case 83 : 
      case 187 : 
      case 291 : 
      case 84 : 
      case 188 : 
      case 292 : 
      case 85 : 
      case 189 : 
      case 293 : 
      case 86 : 
      case 190 : 
      case 294 : 
      case 87 : 
      case 191 : 
      case 295 : 
      case 88 : 
      case 192 : 
      case 296 : 
      case 89 : 
      case 193 : 
      case 297 : 
      case 90 : 
      case 194 : 
      case 298 : 
      case 91 : 
      case 195 : 
      case 299 : 
      case 92 : 
      case 196 : 
      case 300 : 
      case 93 : 
      case 197 : 
      case 301 : 
      case 94 : 
      case 198 : 
      case 302 : 
      case 95 : 
      case 199 : 
      case 303 : 
      case 96 : 
      case 200 : 
      case 304 : 
      case 97 : 
      case 201 : 
      case 305 : 
      case 98 : 
      case 202 : 
      case 306 : 
      case 99 : 
      case 203 : 
      case 307 : 
      case 100 : 
      case 204 : 
      case 308 : 
      case 101 : 
      case 205 : 
      case 309 : 
      case 102 : 
      case 206 : 
      case 310 : 
      case 103 : 
      case 207 : 
      case 311 : 
	prefixedcommand () ;
	break ;
      case 41 : 
      case 145 : 
      case 249 : 
	{
	  gettoken () ;
	  aftertoken = curtok ;
	} 
	break ;
      case 42 : 
      case 146 : 
      case 250 : 
	{
	  gettoken () ;
	  saveforafter ( curtok ) ;
	} 
	break ;
      case 104 : 
      case 208 : 
      case 312 : 
	{
	  gettoken () ;
	  if ( curcs > 0 ) 
	  {
	    parloc = curcs ;
	    partoken = curtok ;
	  } 
	} 
	break ;
      case 61 : 
      case 165 : 
      case 269 : 
	openorclosein () ;
	break ;
      case 59 : 
      case 163 : 
      case 267 : 
	issuemessage () ;
	break ;
      case 58 : 
      case 162 : 
      case 266 : 
	shiftcase () ;
	break ;
      case 20 : 
      case 124 : 
      case 228 : 
	showwhatever () ;
	break ;
      case 60 : 
      case 164 : 
      case 268 : 
	doextension () ;
	break ;
      } 
    } 
    break ;
  } 
  goto lab60 ;
  lab70: if ( ( ( curlist .headfield == curlist .tailfield ) && ( curlist 
  .modefield > 0 ) ) ) 
  {
    if ( ( insertsrcspecialauto ) ) 
    appendsrcspecial () ;
  } 
  prevclass = ( 4095 ) ;
  if ( ( ( fontarea [eqtb [1206823L ].hh .v.RH ]== 65535L ) || ( fontarea 
  [eqtb [1206823L ].hh .v.RH ]== 65534L ) ) ) 
  {
    if ( curlist .modefield > 0 ) {
	
      if ( eqtb [7892314L ].cint != curlist .auxfield .hh .v.RH ) 
      fixlanguage () ;
    } 
    mainh = 0 ;
    mainf = eqtb [1206823L ].hh .v.RH ;
    nativelen = 0 ;
    lab71: mains = eqtb [4549928L + curchr ].hh .v.RH % 65536L ;
    if ( mains == 1000 ) 
    curlist .auxfield .hh .v.LH = 1000 ;
    else if ( mains < 1000 ) 
    {
      if ( mains > 0 ) 
      curlist .auxfield .hh .v.LH = mains ;
    } 
    else if ( curlist .auxfield .hh .v.LH < 1000 ) 
    curlist .auxfield .hh .v.LH = 1000 ;
    else curlist .auxfield .hh .v.LH = mains ;
    curptr = -268435455L ;
    spaceclass = eqtb [4549928L + curchr ].hh .v.RH / 65536L ;
    if ( ( eqtb [7892343L ].cint > 0 ) && spaceclass != 4096 ) 
    {
      if ( prevclass == ( 4095 ) ) 
      {
	if ( ( curinput .statefield != 0 ) || ( curinput .indexfield != 4 ) ) 
	{
	  findsaelement ( 6 , ( 4095 ) * 4096 + spaceclass , false ) ;
	  if ( ( curptr != -268435455L ) && ( mem [curptr + 1 ].hh .v.RH != 
	  -268435455L ) ) 
	  {
	    if ( curcmd != 11 ) 
	    curcmd = 12 ;
	    curtok = ( curcmd * 2097152L ) + curchr ;
	    backinput () ;
	    curinput .indexfield = 4 ;
	    begintokenlist ( mem [curptr + 1 ].hh .v.RH , 17 ) ;
	    goto lab60 ;
	  } 
	} 
      } 
      else {
	  
	findsaelement ( 6 , prevclass * 4096 + spaceclass , false ) ;
	if ( ( curptr != -268435455L ) && ( mem [curptr + 1 ].hh .v.RH != 
	-268435455L ) ) 
	{
	  if ( curcmd != 11 ) 
	  curcmd = 12 ;
	  curtok = ( curcmd * 2097152L ) + curchr ;
	  backinput () ;
	  curinput .indexfield = 4 ;
	  begintokenlist ( mem [curptr + 1 ].hh .v.RH , 17 ) ;
	  prevclass = ( 4095 ) ;
	  goto lab72 ;
	} 
      } 
      prevclass = spaceclass ;
    } 
    if ( ( curchr > 65535L ) ) 
    {
      while ( nativetextsize <= nativelen + 2 ) {
	  
	nativetextsize = nativetextsize + 128 ;
	nativetext = xrealloc ( nativetext , nativetextsize * sizeof ( 
	UTF16code ) ) ;
      } 
      {
	nativetext [nativelen ]= ( curchr - 65536L ) / 1024 + 55296L ;
	incr ( nativelen ) ;
      } 
      {
	nativetext [nativelen ]= ( curchr - 65536L ) % 1024 + 56320L ;
	incr ( nativelen ) ;
      } 
    } 
    else {
	
      while ( nativetextsize <= nativelen + 1 ) {
	  
	nativetextsize = nativetextsize + 128 ;
	nativetext = xrealloc ( nativetext , nativetextsize * sizeof ( 
	UTF16code ) ) ;
      } 
      {
	nativetext [nativelen ]= curchr ;
	incr ( nativelen ) ;
      } 
    } 
    ishyph = ( curchr == hyphenchar [mainf ]) || ( ( eqtb [7892340L ].cint 
    > 0 ) && ( ( curchr == 8212 ) || ( curchr == 8211 ) ) ) ;
    if ( ( mainh == 0 ) && ishyph ) 
    mainh = nativelen ;
    getnext () ;
    if ( ( curcmd == 11 ) || ( curcmd == 12 ) || ( curcmd == 68 ) ) 
    goto lab71 ;
    xtoken () ;
    if ( ( curcmd == 11 ) || ( curcmd == 12 ) || ( curcmd == 68 ) ) 
    goto lab71 ;
    if ( curcmd == 16 ) 
    {
      scanusvnum () ;
      curchr = curval ;
      goto lab71 ;
    } 
    if ( ( eqtb [7892343L ].cint > 0 ) && ( spaceclass != 4096 ) && ( 
    prevclass != ( 4095 ) ) ) 
    {
      prevclass = ( 4095 ) ;
      findsaelement ( 6 , spaceclass * 4096 + ( 4095 ) , false ) ;
      if ( ( curptr != -268435455L ) && ( mem [curptr + 1 ].hh .v.RH != 
      -268435455L ) ) 
      {
	if ( curcs == 0 ) 
	{
	  if ( curcmd == 16 ) 
	  curcmd = 12 ;
	  curtok = ( curcmd * 2097152L ) + curchr ;
	} 
	else curtok = 33554431L + curcs ;
	backinput () ;
	begintokenlist ( mem [curptr + 1 ].hh .v.RH , 17 ) ;
	goto lab72 ;
      } 
    } 
    lab72: if ( ( fontmapping [mainf ]!= 0 ) ) 
    {
      maink = applymapping ( fontmapping [mainf ], nativetext , nativelen ) 
      ;
      nativelen = 0 ;
      while ( nativetextsize <= nativelen + maink ) {
	  
	nativetextsize = nativetextsize + 128 ;
	nativetext = xrealloc ( nativetext , nativetextsize * sizeof ( 
	UTF16code ) ) ;
      } 
      mainh = 0 ;
      {register integer for_end; mainp = 0 ;for_end = maink - 1 ; if ( mainp 
      <= for_end) do 
	{
	  {
	    nativetext [nativelen ]= mappedtext [mainp ];
	    incr ( nativelen ) ;
	  } 
	  if ( ( mainh == 0 ) && ( ( mappedtext [mainp ]== hyphenchar [
	  mainf ]) || ( ( eqtb [7892340L ].cint > 0 ) && ( ( mappedtext [
	  mainp ]== 8212 ) || ( mappedtext [mainp ]== 8211 ) ) ) ) ) 
	  mainh = nativelen ;
	} 
      while ( mainp++ < for_end ) ;} 
    } 
    if ( eqtb [7892299L ].cint > 0 ) 
    {
      tempptr = 0 ;
      while ( ( tempptr < nativelen ) ) {
	  
	maink = nativetext [tempptr ];
	incr ( tempptr ) ;
	if ( ( maink >= 55296L ) && ( maink < 56320L ) ) 
	{
	  maink = 65536L + ( maink - 55296L ) * 1024 ;
	  maink = maink + nativetext [tempptr ]- 56320L ;
	  incr ( tempptr ) ;
	} 
	if ( mapchartoglyph ( mainf , maink ) == 0 ) 
	charwarning ( mainf , maink ) ;
      } 
    } 
    maink = nativelen ;
    mainpp = curlist .tailfield ;
    if ( curlist .modefield == 105 ) 
    {
      mainppp = curlist .headfield ;
      while ( ( mainppp != mainpp ) && ( mem [mainppp ].hh .v.RH != mainpp ) 
      ) {
	  
	if ( ( ! ( mainppp >= himemmin ) ) && ( mem [mainppp ].hh.b0 == 7 ) 
	) 
	{
	  tempptr = mainppp ;
	  {register integer for_end; mainp = 1 ;for_end = mem [tempptr ]
	  .hh.b1 ; if ( mainp <= for_end) do 
	    mainppp = mem [mainppp ].hh .v.RH ;
	  while ( mainp++ < for_end ) ;} 
	} 
	if ( mainppp != mainpp ) 
	mainppp = mem [mainppp ].hh .v.RH ;
      } 
      tempptr = 0 ;
      do {
	  if ( mainh == 0 ) 
	mainh = maink ;
	if ( ( ( ( mainpp ) != -268435455L ) && ( ! ( mainpp >= himemmin ) ) 
	&& ( mem [mainpp ].hh.b0 == 8 ) && ( ( ( mem [mainpp ].hh.b1 >= 40 
	) && ( mem [mainpp ].hh.b1 <= 41 ) ) ) ) && ( mem [mainpp + 4 ]
	.qqqq .b1 == mainf ) && ( mainppp != mainpp ) && ( ! ( mainppp >= 
	himemmin ) ) && ( mem [mainppp ].hh.b0 != 7 ) ) 
	{
	  maink = mainh + mem [mainpp + 4 ].qqqq .b2 ;
	  while ( nativetextsize <= nativelen + maink ) {
	      
	    nativetextsize = nativetextsize + 128 ;
	    nativetext = xrealloc ( nativetext , nativetextsize * sizeof ( 
	    UTF16code ) ) ;
	  } 
	  savenativelen = nativelen ;
	  {register integer for_end; mainp = 0 ;for_end = mem [mainpp + 4 ]
	  .qqqq .b2 - 1 ; if ( mainp <= for_end) do 
	    {
	      nativetext [nativelen ]= getnativechar ( mainpp , mainp ) ;
	      incr ( nativelen ) ;
	    } 
	  while ( mainp++ < for_end ) ;} 
	  {register integer for_end; mainp = 0 ;for_end = mainh - 1 ; if ( 
	  mainp <= for_end) do 
	    {
	      nativetext [nativelen ]= nativetext [tempptr + mainp ];
	      incr ( nativelen ) ;
	    } 
	  while ( mainp++ < for_end ) ;} 
	  dolocalelinebreaks ( savenativelen , maink ) ;
	  nativelen = savenativelen ;
	  maink = nativelen - mainh - tempptr ;
	  tempptr = mainh ;
	  mainh = 0 ;
	  while ( ( mainh < maink ) && ( nativetext [tempptr + mainh ]!= 
	  hyphenchar [mainf ]) && ( ( ! ( eqtb [7892340L ].cint > 0 ) ) || 
	  ( ( nativetext [tempptr + mainh ]!= 8212 ) && ( nativetext [
	  tempptr + mainh ]!= 8211 ) ) ) ) incr ( mainh ) ;
	  if ( ( mainh < maink ) ) 
	  incr ( mainh ) ;
	  mem [mainppp ].hh .v.RH = mem [mainpp ].hh .v.RH ;
	  mem [mainpp ].hh .v.RH = -268435455L ;
	  flushnodelist ( mainpp ) ;
	  mainpp = curlist .tailfield ;
	  while ( ( mem [mainppp ].hh .v.RH != mainpp ) ) mainppp = mem [
	  mainppp ].hh .v.RH ;
	} 
	else {
	    
	  dolocalelinebreaks ( tempptr , mainh ) ;
	  tempptr = tempptr + mainh ;
	  maink = maink - mainh ;
	  mainh = 0 ;
	  while ( ( mainh < maink ) && ( nativetext [tempptr + mainh ]!= 
	  hyphenchar [mainf ]) && ( ( ! ( eqtb [7892340L ].cint > 0 ) ) || 
	  ( ( nativetext [tempptr + mainh ]!= 8212 ) && ( nativetext [
	  tempptr + mainh ]!= 8211 ) ) ) ) incr ( mainh ) ;
	  if ( ( mainh < maink ) ) 
	  incr ( mainh ) ;
	} 
	if ( ( maink > 0 ) || ishyph ) 
	{
	  {
	    mem [curlist .tailfield ].hh .v.RH = newdisc () ;
	    curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
	  } 
	  mainpp = curlist .tailfield ;
	} 
      } while ( ! ( maink == 0 ) ) ;
    } 
    else {
	
      mainppp = curlist .headfield ;
      while ( ( mainppp != mainpp ) && ( mem [mainppp ].hh .v.RH != mainpp ) 
      ) {
	  
	if ( ( ! ( mainppp >= himemmin ) ) && ( mem [mainppp ].hh.b0 == 7 ) 
	) 
	{
	  tempptr = mainppp ;
	  {register integer for_end; mainp = 1 ;for_end = mem [tempptr ]
	  .hh.b1 ; if ( mainp <= for_end) do 
	    mainppp = mem [mainppp ].hh .v.RH ;
	  while ( mainp++ < for_end ) ;} 
	} 
	if ( mainppp != mainpp ) 
	mainppp = mem [mainppp ].hh .v.RH ;
      } 
      if ( ( ( ( mainpp ) != -268435455L ) && ( ! ( mainpp >= himemmin ) ) && 
      ( mem [mainpp ].hh.b0 == 8 ) && ( ( ( mem [mainpp ].hh.b1 >= 40 ) && 
      ( mem [mainpp ].hh.b1 <= 41 ) ) ) ) && ( mem [mainpp + 4 ].qqqq .b1 
      == mainf ) && ( mainppp != mainpp ) && ( ! ( mainppp >= himemmin ) ) && 
      ( mem [mainppp ].hh.b0 != 7 ) ) 
      {
	mem [mainpp ].hh .v.RH = newnativewordnode ( mainf , maink + mem [
	mainpp + 4 ].qqqq .b2 ) ;
	curlist .tailfield = mem [mainpp ].hh .v.RH ;
	{register integer for_end; mainp = 0 ;for_end = mem [mainpp + 4 ]
	.qqqq .b2 - 1 ; if ( mainp <= for_end) do 
	  setnativechar ( curlist .tailfield , mainp , getnativechar ( mainpp 
	  , mainp ) ) ;
	while ( mainp++ < for_end ) ;} 
	{register integer for_end; mainp = 0 ;for_end = maink - 1 ; if ( 
	mainp <= for_end) do 
	  setnativechar ( curlist .tailfield , mainp + mem [mainpp + 4 ]
	  .qqqq .b2 , nativetext [mainp ]) ;
	while ( mainp++ < for_end ) ;} 
	setnativemetrics ( curlist .tailfield , ( eqtb [7892342L ].cint > 0 
	) ) ;
	mainp = curlist .headfield ;
	if ( mainp != mainpp ) 
	while ( mem [mainp ].hh .v.RH != mainpp ) mainp = mem [mainp ].hh 
	.v.RH ;
	mem [mainp ].hh .v.RH = mem [mainpp ].hh .v.RH ;
	mem [mainpp ].hh .v.RH = -268435455L ;
	flushnodelist ( mainpp ) ;
      } 
      else {
	  
	mem [mainpp ].hh .v.RH = newnativewordnode ( mainf , maink ) ;
	curlist .tailfield = mem [mainpp ].hh .v.RH ;
	{register integer for_end; mainp = 0 ;for_end = maink - 1 ; if ( 
	mainp <= for_end) do 
	  setnativechar ( curlist .tailfield , mainp , nativetext [mainp ]) 
	  ;
	while ( mainp++ < for_end ) ;} 
	setnativemetrics ( curlist .tailfield , ( eqtb [7892342L ].cint > 0 
	) ) ;
      } 
    } 
    if ( eqtb [7892348L ].cint > 0 ) 
    {
      mainp = curlist .headfield ;
      mainpp = -268435455L ;
      while ( mainp != curlist .tailfield ) {
	  
	if ( ( ( ( mainp ) != -268435455L ) && ( ! ( mainp >= himemmin ) ) && 
	( mem [mainp ].hh.b0 == 8 ) && ( ( ( mem [mainp ].hh.b1 >= 40 ) && 
	( mem [mainp ].hh.b1 <= 41 ) ) ) ) ) 
	mainpp = mainp ;
	mainp = mem [mainp ].hh .v.RH ;
      } 
      if ( ( mainpp != -268435455L ) ) 
      {
	if ( ( mem [mainpp + 4 ].qqqq .b1 == mainf ) ) 
	{
	  mainp = mem [mainpp ].hh .v.RH ;
	  while ( ! ( mainp >= himemmin ) && ( ( mem [mainp ].hh.b0 == 12 ) 
	  || ( mem [mainp ].hh.b0 == 3 ) || ( mem [mainp ].hh.b0 == 4 ) || 
	  ( mem [mainp ].hh.b0 == 5 ) || ( ( mem [mainp ].hh.b0 == 8 ) && 
	  ( mem [mainp ].hh.b1 <= 4 ) ) ) ) mainp = mem [mainp ].hh .v.RH 
	  ;
	  if ( ! ( mainp >= himemmin ) && ( mem [mainp ].hh.b0 == 10 ) ) 
	  {
	    mainppp = mem [mainp ].hh .v.RH ;
	    while ( ! ( mainppp >= himemmin ) && ( ( mem [mainppp ].hh.b0 == 
	    12 ) || ( mem [mainppp ].hh.b0 == 3 ) || ( mem [mainppp ]
	    .hh.b0 == 4 ) || ( mem [mainppp ].hh.b0 == 5 ) || ( ( mem [
	    mainppp ].hh.b0 == 8 ) && ( mem [mainppp ].hh.b1 <= 4 ) ) ) ) 
	    mainppp = mem [mainppp ].hh .v.RH ;
	    if ( mainppp == curlist .tailfield ) 
	    {
	      tempptr = newnativewordnode ( mainf , mem [mainpp + 4 ].qqqq 
	      .b2 + 1 + mem [curlist .tailfield + 4 ].qqqq .b2 ) ;
	      maink = 0 ;
	      {register integer for_end; t = 0 ;for_end = mem [mainpp + 4 ]
	      .qqqq .b2 - 1 ; if ( t <= for_end) do 
		{
		  setnativechar ( tempptr , maink , getnativechar ( mainpp , t 
		  ) ) ;
		  incr ( maink ) ;
		} 
	      while ( t++ < for_end ) ;} 
	      setnativechar ( tempptr , maink , 32 ) ;
	      incr ( maink ) ;
	      {register integer for_end; t = 0 ;for_end = mem [curlist 
	      .tailfield + 4 ].qqqq .b2 - 1 ; if ( t <= for_end) do 
		{
		  setnativechar ( tempptr , maink , getnativechar ( curlist 
		  .tailfield , t ) ) ;
		  incr ( maink ) ;
		} 
	      while ( t++ < for_end ) ;} 
	      setnativemetrics ( tempptr , ( eqtb [7892342L ].cint > 0 ) ) ;
	      t = mem [tempptr + 1 ].cint - mem [mainpp + 1 ].cint - mem [
	      curlist .tailfield + 1 ].cint ;
	      freenode ( tempptr , mem [tempptr + 4 ].qqqq .b0 ) ;
	      if ( t != mem [fontglue [mainf ]+ 1 ].cint ) 
	      {
		tempptr = newkern ( t - mem [fontglue [mainf ]+ 1 ].cint ) 
		;
		mem [tempptr ].hh.b1 = 3 ;
		mem [tempptr ].hh .v.RH = mem [mainp ].hh .v.RH ;
		mem [mainp ].hh .v.RH = tempptr ;
	      } 
	    } 
	  } 
	} 
      } 
    } 
    if ( curptr != -268435455L ) 
    goto lab60 ;
    else goto lab21 ;
  } 
  mains = eqtb [4549928L + curchr ].hh .v.RH % 65536L ;
  if ( mains == 1000 ) 
  curlist .auxfield .hh .v.LH = 1000 ;
  else if ( mains < 1000 ) 
  {
    if ( mains > 0 ) 
    curlist .auxfield .hh .v.LH = mains ;
  } 
  else if ( curlist .auxfield .hh .v.LH < 1000 ) 
  curlist .auxfield .hh .v.LH = 1000 ;
  else curlist .auxfield .hh .v.LH = mains ;
  curptr = -268435455L ;
  spaceclass = eqtb [4549928L + curchr ].hh .v.RH / 65536L ;
  if ( ( eqtb [7892343L ].cint > 0 ) && spaceclass != 4096 ) 
  {
    if ( prevclass == ( 4095 ) ) 
    {
      if ( ( curinput .statefield != 0 ) || ( curinput .indexfield != 4 ) ) 
      {
	findsaelement ( 6 , ( 4095 ) * 4096 + spaceclass , false ) ;
	if ( ( curptr != -268435455L ) && ( mem [curptr + 1 ].hh .v.RH != 
	-268435455L ) ) 
	{
	  if ( curcmd != 11 ) 
	  curcmd = 12 ;
	  curtok = ( curcmd * 2097152L ) + curchr ;
	  backinput () ;
	  curinput .indexfield = 4 ;
	  begintokenlist ( mem [curptr + 1 ].hh .v.RH , 17 ) ;
	  goto lab60 ;
	} 
      } 
    } 
    else {
	
      findsaelement ( 6 , prevclass * 4096 + spaceclass , false ) ;
      if ( ( curptr != -268435455L ) && ( mem [curptr + 1 ].hh .v.RH != 
      -268435455L ) ) 
      {
	if ( curcmd != 11 ) 
	curcmd = 12 ;
	curtok = ( curcmd * 2097152L ) + curchr ;
	backinput () ;
	curinput .indexfield = 4 ;
	begintokenlist ( mem [curptr + 1 ].hh .v.RH , 17 ) ;
	prevclass = ( 4095 ) ;
	goto lab60 ;
      } 
    } 
    prevclass = spaceclass ;
  } 
  mainf = eqtb [1206823L ].hh .v.RH ;
  bchar = fontbchar [mainf ];
  falsebchar = fontfalsebchar [mainf ];
  if ( curlist .modefield > 0 ) {
      
    if ( eqtb [7892314L ].cint != curlist .auxfield .hh .v.RH ) 
    fixlanguage () ;
  } 
  {
    ligstack = avail ;
    if ( ligstack == -268435455L ) 
    ligstack = getavail () ;
    else {
	
      avail = mem [ligstack ].hh .v.RH ;
      mem [ligstack ].hh .v.RH = -268435455L ;
	;
#ifdef STAT
      incr ( dynused ) ;
#endif /* STAT */
    } 
  } 
  mem [ligstack ].hh.b0 = mainf ;
  curl = curchr ;
  mem [ligstack ].hh.b1 = curl ;
  curq = curlist .tailfield ;
  if ( cancelboundary ) 
  {
    cancelboundary = false ;
    maink = 0 ;
  } 
  else maink = bcharlabel [mainf ];
  if ( maink == 0 ) 
  goto lab92 ;
  curr = curl ;
  curl = 65536L ;
  goto lab111 ;
  lab80: if ( curl < 65536L ) 
  {
    if ( mem [curq ].hh .v.RH > -268435455L ) {
	
      if ( mem [curlist .tailfield ].hh.b1 == hyphenchar [mainf ]) 
      insdisc = true ;
    } 
    if ( ligaturepresent ) 
    {
      mainp = newligature ( mainf , curl , mem [curq ].hh .v.RH ) ;
      if ( lfthit ) 
      {
	mem [mainp ].hh.b1 = 2 ;
	lfthit = false ;
      } 
      if ( rthit ) {
	  
	if ( ligstack == -268435455L ) 
	{
	  incr ( mem [mainp ].hh.b1 ) ;
	  rthit = false ;
	} 
      } 
      mem [curq ].hh .v.RH = mainp ;
      curlist .tailfield = mainp ;
      ligaturepresent = false ;
    } 
    if ( insdisc ) 
    {
      insdisc = false ;
      if ( curlist .modefield > 0 ) 
      {
	mem [curlist .tailfield ].hh .v.RH = newdisc () ;
	curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
      } 
    } 
  } 
  lab90: if ( ligstack == -268435455L ) 
  goto lab21 ;
  curq = curlist .tailfield ;
  curl = mem [ligstack ].hh.b1 ;
  lab91: if ( ! ( ligstack >= himemmin ) ) 
  goto lab95 ;
  lab92: if ( ( effectivechar ( false , mainf , curchr ) > fontec [mainf ]) 
  || ( effectivechar ( false , mainf , curchr ) < fontbc [mainf ]) ) 
  {
    charwarning ( mainf , curchr ) ;
    {
      mem [ligstack ].hh .v.RH = avail ;
      avail = ligstack ;
	;
#ifdef STAT
      decr ( dynused ) ;
#endif /* STAT */
    } 
    goto lab60 ;
  } 
  maini = effectivecharinfo ( mainf , curl ) ;
  if ( ! ( maini .b0 > 0 ) ) 
  {
    charwarning ( mainf , curchr ) ;
    {
      mem [ligstack ].hh .v.RH = avail ;
      avail = ligstack ;
	;
#ifdef STAT
      decr ( dynused ) ;
#endif /* STAT */
    } 
    goto lab60 ;
  } 
  mem [curlist .tailfield ].hh .v.RH = ligstack ;
  curlist .tailfield = ligstack ;
  lab100: getnext () ;
  if ( curcmd == 11 ) 
  goto lab101 ;
  if ( curcmd == 12 ) 
  goto lab101 ;
  if ( curcmd == 68 ) 
  goto lab101 ;
  xtoken () ;
  if ( curcmd == 11 ) 
  goto lab101 ;
  if ( curcmd == 12 ) 
  goto lab101 ;
  if ( curcmd == 68 ) 
  goto lab101 ;
  if ( curcmd == 16 ) 
  {
    scancharnum () ;
    curchr = curval ;
    goto lab101 ;
  } 
  if ( curcmd == 65 ) 
  bchar = 65536L ;
  curr = bchar ;
  ligstack = -268435455L ;
  goto lab110 ;
  lab101: mains = eqtb [4549928L + curchr ].hh .v.RH % 65536L ;
  if ( mains == 1000 ) 
  curlist .auxfield .hh .v.LH = 1000 ;
  else if ( mains < 1000 ) 
  {
    if ( mains > 0 ) 
    curlist .auxfield .hh .v.LH = mains ;
  } 
  else if ( curlist .auxfield .hh .v.LH < 1000 ) 
  curlist .auxfield .hh .v.LH = 1000 ;
  else curlist .auxfield .hh .v.LH = mains ;
  curptr = -268435455L ;
  spaceclass = eqtb [4549928L + curchr ].hh .v.RH / 65536L ;
  if ( ( eqtb [7892343L ].cint > 0 ) && spaceclass != 4096 ) 
  {
    if ( prevclass == ( 4095 ) ) 
    {
      if ( ( curinput .statefield != 0 ) || ( curinput .indexfield != 4 ) ) 
      {
	findsaelement ( 6 , ( 4095 ) * 4096 + spaceclass , false ) ;
	if ( ( curptr != -268435455L ) && ( mem [curptr + 1 ].hh .v.RH != 
	-268435455L ) ) 
	{
	  if ( curcmd != 11 ) 
	  curcmd = 12 ;
	  curtok = ( curcmd * 2097152L ) + curchr ;
	  backinput () ;
	  curinput .indexfield = 4 ;
	  begintokenlist ( mem [curptr + 1 ].hh .v.RH , 17 ) ;
	  goto lab60 ;
	} 
      } 
    } 
    else {
	
      findsaelement ( 6 , prevclass * 4096 + spaceclass , false ) ;
      if ( ( curptr != -268435455L ) && ( mem [curptr + 1 ].hh .v.RH != 
      -268435455L ) ) 
      {
	if ( curcmd != 11 ) 
	curcmd = 12 ;
	curtok = ( curcmd * 2097152L ) + curchr ;
	backinput () ;
	curinput .indexfield = 4 ;
	begintokenlist ( mem [curptr + 1 ].hh .v.RH , 17 ) ;
	prevclass = ( 4095 ) ;
	goto lab60 ;
      } 
    } 
    prevclass = spaceclass ;
  } 
  {
    ligstack = avail ;
    if ( ligstack == -268435455L ) 
    ligstack = getavail () ;
    else {
	
      avail = mem [ligstack ].hh .v.RH ;
      mem [ligstack ].hh .v.RH = -268435455L ;
	;
#ifdef STAT
      incr ( dynused ) ;
#endif /* STAT */
    } 
  } 
  mem [ligstack ].hh.b0 = mainf ;
  curr = curchr ;
  mem [ligstack ].hh.b1 = curr ;
  if ( curr == falsebchar ) 
  curr = 65536L ;
  lab110: if ( ( ( maini .b2 ) % 4 ) != 1 ) 
  goto lab80 ;
  if ( curr == 65536L ) 
  goto lab80 ;
  maink = ligkernbase [mainf ]+ maini .b3 ;
  mainj = fontinfo [maink ].qqqq ;
  if ( mainj .b0 <= 128 ) 
  goto lab112 ;
  maink = ligkernbase [mainf ]+ 256 * mainj .b2 + mainj .b3 + 32768L - 256 * 
  ( 128 ) ;
  lab111: mainj = fontinfo [maink ].qqqq ;
  lab112: if ( mainj .b1 == curr ) {
      
    if ( mainj .b0 <= 128 ) 
    {
      if ( mainj .b2 >= 128 ) 
      {
	if ( curl < 65536L ) 
	{
	  if ( mem [curq ].hh .v.RH > -268435455L ) {
	      
	    if ( mem [curlist .tailfield ].hh.b1 == hyphenchar [mainf ]) 
	    insdisc = true ;
	  } 
	  if ( ligaturepresent ) 
	  {
	    mainp = newligature ( mainf , curl , mem [curq ].hh .v.RH ) ;
	    if ( lfthit ) 
	    {
	      mem [mainp ].hh.b1 = 2 ;
	      lfthit = false ;
	    } 
	    if ( rthit ) {
		
	      if ( ligstack == -268435455L ) 
	      {
		incr ( mem [mainp ].hh.b1 ) ;
		rthit = false ;
	      } 
	    } 
	    mem [curq ].hh .v.RH = mainp ;
	    curlist .tailfield = mainp ;
	    ligaturepresent = false ;
	  } 
	  if ( insdisc ) 
	  {
	    insdisc = false ;
	    if ( curlist .modefield > 0 ) 
	    {
	      mem [curlist .tailfield ].hh .v.RH = newdisc () ;
	      curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
	    } 
	  } 
	} 
	{
	  mem [curlist .tailfield ].hh .v.RH = newkern ( fontinfo [kernbase 
	  [mainf ]+ 256 * mainj .b2 + mainj .b3 ].cint ) ;
	  curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
	} 
	goto lab90 ;
      } 
      if ( curl == 65536L ) 
      lfthit = true ;
      else if ( ligstack == -268435455L ) 
      rthit = true ;
      {
	if ( interrupt != 0 ) 
	pauseforinstructions () ;
      } 
      switch ( mainj .b2 ) 
      {case 1 : 
      case 5 : 
	{
	  curl = mainj .b3 ;
	  maini = fontinfo [charbase [mainf ]+ effectivechar ( true , mainf 
	  , curl ) ].qqqq ;
	  ligaturepresent = true ;
	} 
	break ;
      case 2 : 
      case 6 : 
	{
	  curr = mainj .b3 ;
	  if ( ligstack == -268435455L ) 
	  {
	    ligstack = newligitem ( curr ) ;
	    bchar = 65536L ;
	  } 
	  else if ( ( ligstack >= himemmin ) ) 
	  {
	    mainp = ligstack ;
	    ligstack = newligitem ( curr ) ;
	    mem [ligstack + 1 ].hh .v.RH = mainp ;
	  } 
	  else mem [ligstack ].hh.b1 = curr ;
	} 
	break ;
      case 3 : 
	{
	  curr = mainj .b3 ;
	  mainp = ligstack ;
	  ligstack = newligitem ( curr ) ;
	  mem [ligstack ].hh .v.RH = mainp ;
	} 
	break ;
      case 7 : 
      case 11 : 
	{
	  if ( curl < 65536L ) 
	  {
	    if ( mem [curq ].hh .v.RH > -268435455L ) {
		
	      if ( mem [curlist .tailfield ].hh.b1 == hyphenchar [mainf ]) 
	      insdisc = true ;
	    } 
	    if ( ligaturepresent ) 
	    {
	      mainp = newligature ( mainf , curl , mem [curq ].hh .v.RH ) ;
	      if ( lfthit ) 
	      {
		mem [mainp ].hh.b1 = 2 ;
		lfthit = false ;
	      } 
	      if ( false ) {
		  
		if ( ligstack == -268435455L ) 
		{
		  incr ( mem [mainp ].hh.b1 ) ;
		  rthit = false ;
		} 
	      } 
	      mem [curq ].hh .v.RH = mainp ;
	      curlist .tailfield = mainp ;
	      ligaturepresent = false ;
	    } 
	    if ( insdisc ) 
	    {
	      insdisc = false ;
	      if ( curlist .modefield > 0 ) 
	      {
		mem [curlist .tailfield ].hh .v.RH = newdisc () ;
		curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
	      } 
	    } 
	  } 
	  curq = curlist .tailfield ;
	  curl = mainj .b3 ;
	  maini = fontinfo [charbase [mainf ]+ effectivechar ( true , mainf 
	  , curl ) ].qqqq ;
	  ligaturepresent = true ;
	} 
	break ;
	default: 
	{
	  curl = mainj .b3 ;
	  ligaturepresent = true ;
	  if ( ligstack == -268435455L ) 
	  goto lab80 ;
	  else goto lab91 ;
	} 
	break ;
      } 
      if ( mainj .b2 > 4 ) {
	  
	if ( mainj .b2 != 7 ) 
	goto lab80 ;
      } 
      if ( curl < 65536L ) 
      goto lab110 ;
      maink = bcharlabel [mainf ];
      goto lab111 ;
    } 
  } 
  if ( mainj .b0 == 0 ) 
  incr ( maink ) ;
  else {
      
    if ( mainj .b0 >= 128 ) 
    goto lab80 ;
    maink = maink + mainj .b0 + 1 ;
  } 
  goto lab111 ;
  lab95: mainp = mem [ligstack + 1 ].hh .v.RH ;
  if ( mainp > -268435455L ) 
  {
    mem [curlist .tailfield ].hh .v.RH = mainp ;
    curlist .tailfield = mem [curlist .tailfield ].hh .v.RH ;
  } 
  tempptr = ligstack ;
  ligstack = mem [tempptr ].hh .v.RH ;
  freenode ( tempptr , 2 ) ;
  maini = fontinfo [charbase [mainf ]+ effectivechar ( true , mainf , curl 
  ) ].qqqq ;
  ligaturepresent = true ;
  if ( ligstack == -268435455L ) {
      
    if ( mainp > -268435455L ) 
    goto lab100 ;
    else curr = bchar ;
  } 
  else curr = mem [ligstack ].hh.b1 ;
  goto lab110 ;
  lab120: if ( ( eqtb [7892343L ].cint > 0 ) && ( spaceclass != 4096 ) && ( 
  prevclass != ( 4095 ) ) ) 
  {
    prevclass = ( 4095 ) ;
    findsaelement ( 6 , spaceclass * 4096 + ( 4095 ) , false ) ;
    if ( ( curptr != -268435455L ) && ( mem [curptr + 1 ].hh .v.RH != 
    -268435455L ) ) 
    {
      if ( curcs == 0 ) 
      {
	if ( curcmd == 16 ) 
	curcmd = 12 ;
	curtok = ( curcmd * 2097152L ) + curchr ;
      } 
      else curtok = 33554431L + curcs ;
      backinput () ;
      begintokenlist ( mem [curptr + 1 ].hh .v.RH , 17 ) ;
      goto lab60 ;
    } 
  } 
  if ( eqtb [1205776L ].hh .v.RH == membot ) 
  {
    {
      mainp = fontglue [eqtb [1206823L ].hh .v.RH ];
      if ( mainp == -268435455L ) 
      {
	mainp = newspec ( membot ) ;
	maink = parambase [eqtb [1206823L ].hh .v.RH ]+ 2 ;
	mem [mainp + 1 ].cint = fontinfo [maink ].cint ;
	mem [mainp + 2 ].cint = fontinfo [maink + 1 ].cint ;
	mem [mainp + 3 ].cint = fontinfo [maink + 2 ].cint ;
	fontglue [eqtb [1206823L ].hh .v.RH ]= mainp ;
      } 
    } 
    tempptr = newglue ( mainp ) ;
  } 
  else tempptr = newparamglue ( 12 ) ;
  mem [curlist .tailfield ].hh .v.RH = tempptr ;
  curlist .tailfield = tempptr ;
  goto lab60 ;
} 
void 
giveerrhelp ( void ) 
{
  giveerrhelp_regmem 
  tokenshow ( eqtb [1206304L ].hh .v.RH ) ;
} 
boolean 
openfmtfile ( void ) 
{
  /* 40 10 */ register boolean Result; openfmtfile_regmem 
  integer j  ;
  j = curinput .locfield ;
  if ( buffer [curinput .locfield ]== 38 ) 
  {
    incr ( curinput .locfield ) ;
    j = curinput .locfield ;
    buffer [last ]= 32 ;
    while ( buffer [j ]!= 32 ) incr ( j ) ;
    packbufferedname ( 0 , curinput .locfield , j - 1 ) ;
    if ( wopenin ( fmtfile ) ) 
    goto lab40 ;
    Fputs ( stdout ,  "Sorry, I can't find the format `" ) ;
    fputs ( stringcast ( nameoffile + 1 ) , stdout ) ;
    Fputs ( stdout ,  "'; will try `" ) ;
    fputs ( TEXformatdefault + 1 , stdout ) ;
    fprintf ( stdout , "%s\n",  "'." ) ;
    fflush ( stdout ) ;
  } 
  packbufferedname ( formatdefaultlength - 4 , 1 , 0 ) ;
  if ( ! wopenin ( fmtfile ) ) 
  {
    ;
    Fputs ( stdout ,  "I can't find the format file `" ) ;
    fputs ( TEXformatdefault + 1 , stdout ) ;
    fprintf ( stdout , "%s\n",  "'!" ) ;
    Result = false ;
    return Result ;
  } 
  lab40: curinput .locfield = j ;
  Result = true ;
  return Result ;
} 
void 
closefilesandterminate ( void ) 
{
  closefilesandterminate_regmem 
  integer k  ;
  terminatefontmanager () ;
  {register integer for_end; k = 0 ;for_end = 15 ; if ( k <= for_end) do 
    if ( writeopen [k ]) 
    aclose ( writefile [k ]) ;
  while ( k++ < for_end ) ;} 
  eqtb [7892313L ].cint = -1 ;
	;
#ifdef STAT
  if ( eqtb [7892295L ].cint > 0 ) {
      
    if ( logopened ) 
    {
      { putc ( ' ' ,  logfile );  putc ( '\n',  logfile ); }
      fprintf ( logfile , "%s%s\n",  "Here is how much of TeX's memory" , " you used:" ) 
      ;
      fprintf ( logfile , "%c%ld%s",  ' ' , (long)strptr - initstrptr , " string" ) ;
      if ( strptr != initstrptr + 1 ) 
      putc ( 's' ,  logfile );
      fprintf ( logfile , "%s%ld\n",  " out of " , (long)maxstrings - initstrptr ) ;
      fprintf ( logfile , "%c%ld%s%ld\n",  ' ' , (long)poolptr - initpoolptr ,       " string characters out of " , (long)poolsize - initpoolptr ) ;
      fprintf ( logfile , "%c%ld%s%ld\n",  ' ' , (long)lomemmax - memmin + memend - himemmin + 2 ,       " words of memory out of " , (long)memend + 1 - memmin ) ;
      fprintf ( logfile , "%c%ld%s%ld%c%ld\n",  ' ' , (long)cscount ,       " multiletter control sequences out of " , (long)15000 , '+' , (long)hashextra ) ;
      fprintf ( logfile , "%c%ld%s%ld%s",  ' ' , (long)fmemptr , " words of font info for " , (long)fontptr -       0 , " font" ) ;
      if ( fontptr != 1 ) 
      putc ( 's' ,  logfile );
      fprintf ( logfile , "%s%ld%s%ld\n",  ", out of " , (long)fontmemsize , " for " , (long)fontmax - 0 ) 
      ;
      fprintf ( logfile , "%c%ld%s",  ' ' , (long)hyphcount , " hyphenation exception" ) ;
      if ( hyphcount != 1 ) 
      putc ( 's' ,  logfile );
      fprintf ( logfile , "%s%ld\n",  " out of " , (long)hyphsize ) ;
      fprintf ( logfile , "%c%ld%s%ld%s%ld%s%ld%s%ld%s%ld%s%ld%s%ld%s%ld%s%ld%c\n",  ' ' , (long)maxinstack , "i," , (long)maxneststack , "n," ,       (long)maxparamstack , "p," , (long)maxbufstack + 1 , "b," , (long)maxsavestack + 6 ,       "s stack positions out of " , (long)stacksize , "i," , (long)nestsize , "n," ,       (long)paramsize , "p," , (long)bufsize , "b," , (long)savesize , 's' ) ;
    } 
  } 
#endif /* STAT */
  while ( curs > -1 ) {
      
    if ( curs > 0 ) 
    {
      dvibuf [dviptr ]= 142 ;
      incr ( dviptr ) ;
      if ( dviptr == dvilimit ) 
      dviswap () ;
    } 
    else {
	
      {
	dvibuf [dviptr ]= 140 ;
	incr ( dviptr ) ;
	if ( dviptr == dvilimit ) 
	dviswap () ;
      } 
      incr ( totalpages ) ;
    } 
    decr ( curs ) ;
  } 
  if ( totalpages == 0 ) 
  printnl ( 66240L ) ;
  else if ( curs != -2 ) 
  {
    {
      dvibuf [dviptr ]= 248 ;
      incr ( dviptr ) ;
      if ( dviptr == dvilimit ) 
      dviswap () ;
    } 
    dvifour ( lastbop ) ;
    lastbop = dvioffset + dviptr - 5 ;
    dvifour ( 25400000L ) ;
    dvifour ( 473628672L ) ;
    preparemag () ;
    dvifour ( eqtb [7892281L ].cint ) ;
    dvifour ( maxv ) ;
    dvifour ( maxh ) ;
    {
      dvibuf [dviptr ]= maxpush / 256 ;
      incr ( dviptr ) ;
      if ( dviptr == dvilimit ) 
      dviswap () ;
    } 
    {
      dvibuf [dviptr ]= maxpush % 256 ;
      incr ( dviptr ) ;
      if ( dviptr == dvilimit ) 
      dviswap () ;
    } 
    {
      dvibuf [dviptr ]= ( totalpages / 256 ) % 256 ;
      incr ( dviptr ) ;
      if ( dviptr == dvilimit ) 
      dviswap () ;
    } 
    {
      dvibuf [dviptr ]= totalpages % 256 ;
      incr ( dviptr ) ;
      if ( dviptr == dvilimit ) 
      dviswap () ;
    } 
    while ( fontptr > 0 ) {
	
      if ( fontused [fontptr ]) 
      dvifontdef ( fontptr ) ;
      decr ( fontptr ) ;
    } 
    {
      dvibuf [dviptr ]= 249 ;
      incr ( dviptr ) ;
      if ( dviptr == dvilimit ) 
      dviswap () ;
    } 
    dvifour ( lastbop ) ;
    {
      dvibuf [dviptr ]= 7 ;
      incr ( dviptr ) ;
      if ( dviptr == dvilimit ) 
      dviswap () ;
    } 
	;
#ifdef IPC
    k = 7 - ( ( 3 + dvioffset + dviptr ) % 4 ) ;
#endif /* IPC */
	;
#ifndef IPC
    k = 4 + ( ( dvibufsize - dviptr ) % 4 ) ;
#endif /* not IPC */
    while ( k > 0 ) {
	
      {
	dvibuf [dviptr ]= 223 ;
	incr ( dviptr ) ;
	if ( dviptr == dvilimit ) 
	dviswap () ;
      } 
      decr ( k ) ;
    } 
    if ( dvilimit == halfbuf ) 
    writedvi ( halfbuf , dvibufsize - 1 ) ;
    if ( dviptr > ( 2147483647L - dvioffset ) ) 
    {
      curs = -2 ;
      fatalerror ( 66227L ) ;
    } 
    if ( dviptr > 0 ) 
    writedvi ( 0 , dviptr - 1 ) ;
    k = dviclose ( dvifile ) ;
    if ( k == 0 ) 
    {
      printnl ( 66241L ) ;
      print ( outputfilename ) ;
      print ( 65568L ) ;
      printint ( totalpages ) ;
      if ( totalpages != 1 ) 
      print ( 66242L ) ;
      else print ( 66243L ) ;
      if ( nopdfoutput ) 
      {
	print ( 66244L ) ;
	printint ( dvioffset + dviptr ) ;
	print ( 66245L ) ;
      } 
      else print ( 66246L ) ;
    } 
    else {
	
      printnl ( 66247L ) ;
      printint ( k ) ;
      print ( 65568L ) ;
      if ( nopdfoutput ) 
      printcstring ( strerror ( k ) ) ;
      else print ( 66248L ) ;
      print ( 66249L ) ;
      printnl ( 66250L ) ;
      print ( outputfilename ) ;
      print ( 66251L ) ;
      history = 4 ;
    } 
  } 
  synctexterminate ( logopened ) ;
  if ( logopened ) 
  {
    putc ('\n',  logfile );
    aclose ( logfile ) ;
    selector = selector - 2 ;
    if ( selector == 17 ) 
    {
      printnl ( 66739L ) ;
      print ( texmflogname ) ;
      printchar ( 46 ) ;
    } 
  } 
  println () ;
  if ( ( editnamestart != 0 ) && ( interaction > 0 ) ) 
  calledit ( strpool , editnamestart , editnamelength , editline ) ;
} 
#ifdef TEXMF_DEBUG
void 
debughelp ( void ) 
{
  /* 888 10 */ debughelp_regmem 
  integer k, l, m, n  ;
  while ( true ) {
      
    ;
    printnl ( 66748L ) ;
    fflush ( stdout ) ;
    read ( termin , m ) ;
    if ( m < 0 ) 
    return ;
    else if ( m == 0 ) 
    dumpcore () ;
    else {
	
      read ( termin , n ) ;
      switch ( m ) 
      {case 1 : 
	printword ( mem [n ]) ;
	break ;
      case 2 : 
	printint ( mem [n ].hh .v.LH ) ;
	break ;
      case 3 : 
	printint ( mem [n ].hh .v.RH ) ;
	break ;
      case 4 : 
	printword ( eqtb [n ]) ;
	break ;
      case 5 : 
	{
	  printscaled ( fontinfo [n ].cint ) ;
	  printchar ( 32 ) ;
	  printint ( fontinfo [n ].qqqq .b0 ) ;
	  printchar ( 58 ) ;
	  printint ( fontinfo [n ].qqqq .b1 ) ;
	  printchar ( 58 ) ;
	  printint ( fontinfo [n ].qqqq .b2 ) ;
	  printchar ( 58 ) ;
	  printint ( fontinfo [n ].qqqq .b3 ) ;
	} 
	break ;
      case 6 : 
	printword ( savestack [n ]) ;
	break ;
      case 7 : 
	showbox ( n ) ;
	break ;
      case 8 : 
	{
	  breadthmax = 10000 ;
	  depththreshold = poolsize - poolptr - 10 ;
	  shownodelist ( n ) ;
	} 
	break ;
      case 9 : 
	showtokenlist ( n , -268435455L , 1000 ) ;
	break ;
      case 10 : 
	print ( n ) ;
	break ;
      case 11 : 
	checkmem ( n > 0 ) ;
	break ;
      case 12 : 
	searchmem ( n ) ;
	break ;
      case 13 : 
	{
	  read ( termin , l ) ;
	  printcmdchr ( n , l ) ;
	} 
	break ;
      case 14 : 
	{register integer for_end; k = 0 ;for_end = n ; if ( k <= for_end) 
	do 
	  print ( buffer [k ]) ;
	while ( k++ < for_end ) ;} 
	break ;
      case 15 : 
	{
	  fontinshortdisplay = 0 ;
	  shortdisplay ( n ) ;
	} 
	break ;
      case 16 : 
	panicking = ! panicking ;
	break ;
	default: 
	print ( 63 ) ;
	break ;
      } 
    } 
  } 
} 
#endif /* TEXMF_DEBUG */
void 
zflushstr ( strnumber s ) 
{
  flushstr_regmem 
  if ( ( s == strptr - 1 ) ) 
  {
    decr ( strptr ) ;
    poolptr = strstart [( strptr ) - 65536L ];
  } 
} 
strnumber 
ztokenstostring ( halfword p ) 
{
  register strnumber Result; tokenstostring_regmem 
  if ( selector == 21 ) 
  pdferror ( 66119L , 66120L ) ;
  oldsetting = selector ;
  selector = 21 ;
  showtokenlist ( mem [p ].hh .v.RH , -268435455L , poolsize - poolptr ) ;
  selector = oldsetting ;
  Result = makestring () ;
  return Result ;
} 
void 
scanpdfexttoks ( void ) 
{
  scanpdfexttoks_regmem 
  {
    if ( scantoks ( false , true ) != 0 ) 
    ;
  } 
} 
void 
comparestrings ( void ) 
{
  /* 30 */ comparestrings_regmem 
  strnumber s1, s2  ;
  poolpointer i1, i2, j1, j2  ;
  halfword savecurcs  ;
  savecurcs = curcs ;
  {
    if ( scantoks ( false , true ) != 0 ) 
    ;
  } 
  s1 = tokenstostring ( defref ) ;
  deletetokenref ( defref ) ;
  curcs = savecurcs ;
  {
    if ( scantoks ( false , true ) != 0 ) 
    ;
  } 
  s2 = tokenstostring ( defref ) ;
  deletetokenref ( defref ) ;
  i1 = strstart [( s1 ) - 65536L ];
  j1 = strstart [( s1 + 1 ) - 65536L ];
  i2 = strstart [( s2 ) - 65536L ];
  j2 = strstart [( s2 + 1 ) - 65536L ];
  while ( ( i1 < j1 ) && ( i2 < j2 ) ) {
      
    if ( strpool [i1 ]< strpool [i2 ]) 
    {
      curval = -1 ;
      goto lab30 ;
    } 
    if ( strpool [i1 ]> strpool [i2 ]) 
    {
      curval = 1 ;
      goto lab30 ;
    } 
    incr ( i1 ) ;
    incr ( i2 ) ;
  } 
  if ( ( i1 == j1 ) && ( i2 == j2 ) ) 
  curval = 0 ;
  else if ( i1 < j1 ) 
  curval = 1 ;
  else curval = -1 ;
  lab30: flushstr ( s2 ) ;
  flushstr ( s1 ) ;
  curvallevel = 0 ;
} 
void 
scanfilenamebraced ( void ) 
{
  scanfilenamebraced_regmem 
  smallnumber savescannerstatus  ;
  halfword savedefref  ;
  halfword savecurcs  ;
  strnumber s  ;
  halfword p  ;
  integer i  ;
  boolean savestopatspace  ;
  boolean dummy  ;
  savescannerstatus = scannerstatus ;
  savedefref = defref ;
  savecurcs = curcs ;
  curcs = warningindex ;
  if ( scantoks ( false , true ) != 0 ) 
  ;
  oldsetting = selector ;
  selector = 21 ;
  showtokenlist ( mem [defref ].hh .v.RH , -268435455L , poolsize - poolptr 
  ) ;
  selector = oldsetting ;
  s = makestring () ;
  deletetokenref ( defref ) ;
  defref = savedefref ;
  curcs = savecurcs ;
  scannerstatus = savescannerstatus ;
  savestopatspace = stopatspace ;
  stopatspace = false ;
  beginname () ;
  {register integer for_end; i = strstart [( s ) - 65536L ];for_end = 
  strstart [( s + 1 ) - 65536L ]- 1 ; if ( i <= for_end) do 
    dummy = morename ( strpool [i ]) ;
  while ( i++ < for_end ) ;} 
  stopatspace = savestopatspace ;
} 
strnumber 
getnullstr ( void ) 
{
  register strnumber Result; getnullstr_regmem 
  Result = 65545L ;
  return Result ;
} 
