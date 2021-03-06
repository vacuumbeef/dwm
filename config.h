/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 8;       /* snap pixel */
static const char *tagfile          = "/tmp/dwm_tags";
static const int barheight          = 0;        /* 0 means bottom bar */
static const char *sepchar          = ":";
static const unsigned int gappih    = 5;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 5;       /* vert inner gap between windows */
static const unsigned int gappoh    = 10;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 10;       /* vert outer gap between windows and screen edge */
static const int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 0;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "monospace:size=10" };
static const char dmenufont[]       = "monospace:size=10";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class          instance    title       tags mask     isfloating   monitor    float x,y,w,h         floatborderpx   scratch key*/
	{ "Gimp",         NULL,       NULL,       0,            0,           -1,        50,50,500,500,        1,              0  },
	{ "Firefox",      NULL,       NULL,       1 << 8,       0,           -1,        50,50,500,500,        1,              0  },
	{ "reaper",       NULL,       NULL,       1 << 7,       0,           -1,        50,50,500,500,        1,              0  },
	{ "QjackCtl",     NULL,       NULL,       0,       	1,           -1,        889,651,460,100,      1,             'j'  },
	{ "PatchMatrix",  NULL,       NULL,       0,       	1,           -1,        42,15,1280,500,       1,             'p'  },
	{ NULL,           NULL,   "scratchpad",   0,            1,           -1,        50,50,500,500,        1,             's' },
	{ NULL,           NULL,   "weepad",       0,            1,           -1,        15,15,330,420,        1,             'c' },
	{ NULL,           NULL,   "vifmpad",      0,            0,           -1,        50,50,500,500,        1,             'v' },
	{ NULL,           NULL,   "newsboatpad",  0,            0,           -1,        50,50,500,500,        1,             'n' },
	{ NULL,           NULL,   "wikipad",      0,            0,           -1,        50,50,500,500,        1,             'w' },
	{ NULL,           NULL,   "mixerpad",     0,            0,           -1,        50,50,500,500,        1,             'm' },
	{ NULL,           NULL,   "mailpad",      0,            0,           -1,        50,50,500,500,        1,             'k' },
	{ NULL,           NULL,   "qutebrowser",  0,            0,           -1,        50,50,500,500,        1,             'b' },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define ALTKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "st", NULL };
static const char *scratchpadcmd[] = {"s", "st", "-t", "scratchpad", NULL};
static const char *wikiscratch[] = {"w", "st", "-t", "wikipad", "-e", "wiki_open", NULL};
static const char *weechatscratch[] = {"c", "st", "-t", "weepad", "-e", "weechat", NULL};
static const char *vifmscratch[] = {"v", "st", "-t", "vifmpad", "-e", "vifmrun", NULL};
static const char *newsboatscratch[] = {"n", "st", "-t", "newsboatpad", "-e", "newsboat", NULL};
static const char *mixerscratch[] = {"m", "st", "-t", "mixerpad", "-e", "pulsemixer", NULL};
static const char *mailscratch[] = {"k", "st", "-t", "mailpad", "-e", "neomutt", NULL};
static const char *browserscratch[] = {"b", "qutebrowser", NULL};
static const char *qjackscratch[] = {"j", "qjackctl", NULL};
static const char *patchmatscratch[] = {"p", "patchmatrix", NULL};

#include "movestack.c"
static Key keys[] = {
	/* Apps */
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_d,      spawn,          SHCMD("drun") },
	{ MODKEY,                       XK_s,      spawn,          SHCMD("dzenstatus") },
	{ ALTKEY,                       XK_Return, spawn,          SHCMD("st") },
	{ MODKEY,                       XK_Return, spawn,          SHCMD("st") },
	{ ALTKEY|ShiftMask,             XK_F5, 	   spawn,          SHCMD("keepmenu") },
	{ 0, 	          XF86XK_AudioRaiseVolume, spawn,	   SHCMD("dzen_volume -i 5") },
	{ 0, 	          XF86XK_AudioLowerVolume, spawn,	   SHCMD("dzen_volume -d 5") },
	{ 0, 	                 XF86XK_AudioPrev, spawn,	   SHCMD("mpc prev") },
	{ 0, 	                 XF86XK_AudioNext, spawn,	   SHCMD("mpc next") },
	{ 0, 	                XF86XK_AudioPause, spawn,	   SHCMD("mpc pause") },
	{ 0, 	                 XF86XK_AudioPlay, spawn,	   SHCMD("mpc toggle") },
	{ 0, 	                 XF86XK_AudioStop, spawn,	   SHCMD("mpc stop") },
	{ ShiftMask, 	         XF86XK_AudioNext, spawn,	   SHCMD("mpc seekthrough +15") },
	{ ShiftMask, 	         XF86XK_AudioPrev, spawn,	   SHCMD("mpc seekthrough -15") },
	{ 0, 	           XF86XK_MonBrightnessUp, spawn,	   SHCMD("xbacklight -inc 5") },
	{ 0, 	         XF86XK_MonBrightnessDown, spawn,	   SHCMD("xbacklight -dec 5") },
	{ MODKEY|ControlMask,           XK_l,      spawn,          SHCMD("betterlockscreen -l") },
	{ 0,           			XK_Print,  spawn,          SHCMD("scrfull") },
	{ ControlMask,           	XK_Print,  spawn,          SHCMD("scrpart") },
	{ ControlMask|ShiftMask,        XK_Print,  spawn,          SHCMD("gifrecord") },
	{ ControlMask,        		XK_End,    spawn,          SHCMD("pkill -f 'x11grab'") },
	/* Scratchpads */
	/* modifier                     key        function        argument */
	{ ALTKEY,                       XK_grave,  togglescratch,  {.v = scratchpadcmd } },
	{ ALTKEY,                       XK_F1,     togglescratch,  {.v = wikiscratch } },
	{ ALTKEY,                       XK_w,      togglescratch,  {.v = weechatscratch } },
	{ ALTKEY,                       XK_f,      togglescratch,  {.v = vifmscratch } },
	{ ALTKEY,                       XK_n,      togglescratch,  {.v = newsboatscratch } },
	{ ALTKEY,                       XK_F10,    togglescratch,  {.v = mixerscratch } },
	{ ALTKEY,                       XK_b,      togglescratch,  {.v = browserscratch } },
	{ ALTKEY,                       XK_m,      togglescratch,  {.v = mailscratch } },
	{ ALTKEY,                       XK_F5,     togglescratch,  {.v = qjackscratch } },
	{ ALTKEY,                       XK_F6,     togglescratch,  {.v = patchmatscratch } },
	/* Windows */
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY|ShiftMask,             XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_j,      movestack,      {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,      movestack,      {.i = -1 } },
	{ MODKEY,                       XK_x,      transfer,       {0} },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_o,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,           		XK_g,      togglegaps,     {0} },
	{ MODKEY,                       XK_space,  zoom,           {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY|ControlMask,           XK_s,      togglesticky,   {0} },
	{ 0, 		                XK_F11,    togglefullscr,  {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_bracketright,      spawn,          SHCMD("move_to_corner rbot") },
	{ MODKEY|ShiftMask,             XK_bracketright,      spawn,          SHCMD("move_to_corner rtop") },
	{ MODKEY,                       XK_bracketleft,      spawn,          SHCMD("move_to_corner lbot") },
	{ MODKEY|ShiftMask,             XK_bracketleft,      spawn,          SHCMD("move_to_corner ltop") },
	{ MODKEY|ShiftMask,             XK_j,      moveresize,     {.v = "0x 25y 0w 0h" } },
	{ MODKEY|ShiftMask,             XK_k,      moveresize,     {.v = "0x -25y 0w 0h" } },
	{ MODKEY|ShiftMask,             XK_l,      moveresize,     {.v = "25x 0y 0w 0h" } },
	{ MODKEY|ShiftMask,             XK_h,      moveresize,     {.v = "-25x 0y 0w 0h" } },
	{ MODKEY|Mod1Mask,              XK_j,      moveresize,     {.v = "0x 0y 0w 25h" } },
	{ MODKEY|Mod1Mask,              XK_k,      moveresize,     {.v = "0x 0y 0w -25h" } },
	{ MODKEY|Mod1Mask,              XK_l,      moveresize,     {.v = "0x 0y 25w 0h" } },
	{ MODKEY|Mod1Mask,              XK_h,      moveresize,     {.v = "0x 0y -25w 0h" } },
	/* Tags */
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	/*{ MODKEY,                       XK_space,  setlayout,      {0} },*/
	/*{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },*/
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
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

void
setlayoutex(const Arg *arg)
{
	setlayout(&((Arg) { .v = &layouts[arg->i] }));
}

void
viewex(const Arg *arg)
{
	view(&((Arg) { .ui = 1 << arg->ui }));
}

void
viewall(const Arg *arg)
{
	view(&((Arg){.ui = ~0}));
}

void
toggleviewex(const Arg *arg)
{
	toggleview(&((Arg) { .ui = 1 << arg->ui }));
}

void
tagex(const Arg *arg)
{
	tag(&((Arg) { .ui = 1 << arg->ui }));
}

void
toggletagex(const Arg *arg)
{
	toggletag(&((Arg) { .ui = 1 << arg->ui }));
}

void
tagall(const Arg *arg)
{
	tag(&((Arg){.ui = ~0}));
}

/* signal definitions */
/* signum must be greater than 0 */
/* trigger signals using `xsetroot -name "fsignal:<signame> [<type> <value>]"` */
static Signal signals[] = {
	/* signum           function */
	{ "focusstack",     focusstack },
	{ "setmfact",       setmfact },
	{ "togglebar",      togglebar },
	{ "incnmaster",     incnmaster },
	{ "togglefloating", togglefloating },
	{ "moveresize",     moveresize },
	{ "focusmon",       focusmon },
	{ "tagmon",         tagmon },
	{ "zoom",           zoom },
	{ "view",           view },
	{ "viewall",        viewall },
	{ "viewex",         viewex },
	{ "toggleview",     view },
	{ "toggleviewex",   toggleviewex },
	{ "tag",            tag },
	{ "tagall",         tagall },
	{ "tagex",          tagex },
	{ "toggletag",      tag },
	{ "toggletagex",    toggletagex },
	{ "killclient",     killclient },
	{ "quit",           quit },
	{ "setlayout",      setlayout },
	{ "setlayoutex",    setlayoutex },
};
