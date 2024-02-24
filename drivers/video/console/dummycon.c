/*
 *  linux/drivers/video/dummycon.c -- A dummy console driver
 *
 *  To be used if there's no other console driver (e.g. for plain VGA text)
 *  available, usually until fbcon takes console over.
 */

#include <linux/types.h>
#include <linux/kdev_t.h>
#include <linux/console.h>
#include <linux/vt_kern.h>
#include <linux/screen_info.h>
#include <linux/init.h>
#include <linux/module.h>

/*
 *  Dummy console driver
 */

#if defined(__arm__)
#define DUMMY_COLUMNS	screen_info.orig_video_cols
#define DUMMY_ROWS	screen_info.orig_video_lines
#else
/* set by Kconfig. Use 80x25 for 640x480 and 160x64 for 1280x1024 */
#define DUMMY_COLUMNS	CONFIG_DUMMY_CONSOLE_COLUMNS
#define DUMMY_ROWS	CONFIG_DUMMY_CONSOLE_ROWS
#endif

static const char *dummycon_startup(void)
{
    return "dummy device";
}

static void dummycon_init(struct vc_data *vc, int init)
{
    vc->vc_can_do_color = 1;
    if (init) {
	vc->vc_cols = DUMMY_COLUMNS;
	vc->vc_rows = DUMMY_ROWS;
    } else
	vc_resize(vc, DUMMY_COLUMNS, DUMMY_ROWS);
}

static void dummycon_deinit(struct vc_data *vc)
{
}

static void dummycon_clear(struct vc_data *vc, int a, int b, int c, int d)
{
}

static void dummycon_putc(struct vc_data *vc, int a, int b, int c)
{
}

static void dummycon_putcs(struct vc_data *vc, const unsigned short *s, int a, int b, int c)
{
}

static void dummycon_cursor(struct vc_data *vc, int a)
{
}

static int dummycon_scroll(struct vc_data *vc, int a, int b, int c, int d)
{
    return 0;
}

static int dummycon_switch(struct vc_data *vc)
{
    return 0;
}

static int dummycon_blank(struct vc_data *vc, int a, int b)
{
    return 0;
}

static int dummycon_font_set(struct vc_data *vc, struct console_font *f, unsigned u)
{
    return 0;
}

static int dummycon_font_default(struct vc_data *vc, struct console_font *f, char *c)
{
    return 0;
}

static int dummycon_font_copy(struct vc_data *vc, int a)
{
    return 0;
}

/*
 *  The console `switch' structure for the dummy console
 *
 *  Most of the operations are dummies.
 */

const struct consw dummy_con = {
    .owner =		THIS_MODULE,
    .con_startup =	dummycon_startup,
    .con_init =		dummycon_init,
    .con_deinit =	DUMMY,
    .con_clear =	DUMMY,
    .con_putc =		DUMMY,
    .con_putcs =	DUMMY,
    .con_cursor =	DUMMY,
    .con_scroll =	DUMMY,
    .con_switch =	DUMMY,
    .con_blank =	DUMMY,
    .con_font_set =	DUMMY,
    .con_font_default =	DUMMY,
    .con_font_copy =	DUMMY,
};
EXPORT_SYMBOL_GPL(dummy_con);
