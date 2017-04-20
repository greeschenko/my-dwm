/* See LICENSE file for copyright and license details. */

/* appearance */
static const char *fonts[] = {
    "Droid Sans Mono Slashed for Powerline:size=10",
    "FontAwesome:size=10"
};
static const char dmenufont[]       = "Droid Sans Mono Slashed for Powerline:size=16";
static const char normbordercolor[] = "#002f50";
static const char normbgcolor[]     = "#002f50";
static const char normfgcolor[]     = "#bbcada";
static const char selbordercolor[]  = "#002f50";
static const char selbgcolor[]      = "#002f50";
static const char selfgcolor[]      = "#ffff4a";
static const unsigned int borderpx  = 0;        /* border pixel of windows */
static const unsigned int snap      = 15;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */

/* tagging */
static const char *tags[] = {
    "1", "2", "3", "4",
    "5", "6", "7", "8", "9"
};

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
    { "Gimp",     NULL,       NULL,       1 << 5,       False,        -1 },
    { "Firefox",  NULL,       NULL,       1 << 8,       False,       -1 },
    { "Chromium", NULL,       NULL,       1 << 2,       False,       -1 },
    { "MPlayer",  NULL,       NULL,       ~0,           True,       -1 },
};

#define NUMCOLORS        6
static const char colors[NUMCOLORS][MAXCOLORS][8] = {
    // border   foreground background
    { "#002f50", "#bbcada", "#002f50" },  // normal
    { "#002f50", "#ffff4a", "#002f50" },  // selected
    { "#ffff4a", "#002f50", "#ffff4a" },  // urgent/warning  (black on yellow)
    { "#ff5555", "#ffffff", "#ff5555" },  // error (white on red)
    { "#004d76", "#bbcada", "#004d76" },  // primary
    { "#2ca000", "#ffffff", "#2ca000" },  // success
    // add more here
};

/* layout(s) */
static const float mfact     = 0.8; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = {
    "dmenu_run", "-fn", dmenufont, "-nb",
    normbgcolor, "-nf", normfgcolor, "-sb", "#ff5555", "-w", "904",
    "-x", "226", "-y", "300", NULL
};
static const char *termcmd[]     = { "st", NULL };
static const char *vimcmd[]      = { "st", "-e", "vim", NULL };
static const char *mccmd[]       = { "st", "-e", "mc", NULL };
static const char *rangercmd[]   = { "st", "-e", "ranger", NULL };
static const char *rootcmd[]     = { "st", "-e", "su", NULL };

static const char *apluscmd[]    = { "amixer", "sset", "Master", "5%+", NULL };
static const char *aminuscmd[]   = { "amixer", "sset", "Master", "5%-", NULL };
static const char *atogglecmd[]  = { "amixer", "sset", "Master", "toggle", NULL };

static const char *sleepcmd[]    = {"sudo", "pm-suspend", NULL };
static const char *shutdowncmd[] = {"sudo", "shutdown", "-h", "now", NULL };

static const char *screencmd[]   = { "xset", "dpms", "force", "off", NULL };
static const char *lupcmd[]      = { "xbacklight", "-inc", "5", NULL };
static const char *ldowncmd[]    = { "xbacklight", "-dec", "5", NULL };

static const char *scrotcmd[]    = { "getscreenshot", NULL};

static const char *gopomidor[]   = { "pomidor", "1500", "300", NULL};

static const char *setenkb[]     = { "setxkbmap", "us", NULL};
static const char *setrukb[]     = { "setxkbmap", "ru", NULL};
static const char *setuakb[]     = { "setxkbmap", "ua", NULL};

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
    { MODKEY|ShiftMask,             XK_v,      spawn,          {.v = vimcmd } },
    { MODKEY|ShiftMask,             XK_m,      spawn,          {.v = mccmd } },
    { MODKEY|ShiftMask,             XK_r,      spawn,          {.v = rangercmd } },
    { MODKEY|ShiftMask,             XK_s,      spawn,          {.v = rootcmd } },
    { MODKEY|ShiftMask,             XK_t,      spawn,          {.v = gopomidor } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
    { 0,                            0x1008ff13,   spawn,	   {.v = apluscmd } },
    { 0,                            0x1008ff11,   spawn,	   {.v = aminuscmd } },
    { 0,                            0x1008ff12,   spawn,	   {.v = atogglecmd } },
    { 0,                            0x1008ff2f,   spawn,	   {.v = sleepcmd } },
    { MODKEY,                       0x1008ff2f,   spawn,	   {.v = shutdowncmd } },
    { 0,                            0x1008ff59,   spawn,	   {.v = screencmd } },
    { 0,                            0x1008ff03,   spawn,	   {.v = ldowncmd } },
    { 0,                            0x1008ff02,   spawn,	   {.v = lupcmd } },
    { 0,				            XK_Print,  	  spawn,       {.v = scrotcmd } },
    { ControlMask,			        XK_4,  	    spawn,         {.v = setenkb } },
    { ControlMask,			        XK_3,  	    spawn,         {.v = setrukb } },
    { ControlMask,			        XK_2,  	    spawn,         {.v = setuakb } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

