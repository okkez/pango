/*
 * $XFree86: xc/lib/MiniXft/xftinit.c,v 1.2 2000/12/15 17:12:53 keithp Exp $
 *
 * Copyright � 2000 Keith Packard, member of The XFree86 Project, Inc.
 *
 * Permission to use, copy, modify, distribute, and sell this software and its
 * documentation for any purpose is hereby granted without fee, provided that
 * the above copyright notice appear in all copies and that both that
 * copyright notice and this permission notice appear in supporting
 * documentation, and that the name of Keith Packard not be used in
 * advertising or publicity pertaining to distribution of the software without
 * specific, written prior permission.  Keith Packard makes no
 * representations about the suitability of this software for any purpose.  It
 * is provided "as is" without express or implied warranty.
 *
 * KEITH PACKARD DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE,
 * INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO
 * EVENT SHALL KEITH PACKARD BE LIABLE FOR ANY SPECIAL, INDIRECT OR
 * CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE,
 * DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 * TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 */

#include <stdlib.h>

#ifdef _WIN32
#include <stdio.h>
#endif

#include "minixftint.h"

MiniXftFontSet  *_MiniXftFontSet;
Bool	    _MiniXftConfigInitialized;

Bool
MiniXftInit (char *config)
{
    if (_MiniXftConfigInitialized)
	return True;
    _MiniXftConfigInitialized = True;
    if (!config)
    {
	config = getenv ("XFT_CONFIG");
	if (!config)
	    config = XFT_DEFAULT_PATH;
    }
    if (MiniXftConfigLexFile (config))
    {
	MiniXftConfigparse ();
    }
    return True;
}

#ifdef _WIN32
char *
get_xft_default_path (void)
{
  static char *result = NULL;
  extern char *pango_get_sysconf_subdirectory (void);
  char *p;

  if (result)
    return result;

  p = pango_get_sysconf_subdirectory ();
  result = malloc (strlen (p) + 20);

  sprintf (result, "%s\\..\\XftConfig", p);

  return result;
}
#endif
