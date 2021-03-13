#include <X11/Xlib.h>
#include <X11/Intrinsic.h>
#include <X11/extensions/XTest.h>
#include <unistd.h>

/* Send Fake Key Event */
static void SendKey(Display *disp, KeySym keysym, KeySym modsym)
{
    KeyCode keycode = 0, modcode = 0;
    keycode = XKeysymToKeycode(disp, keysym);
    if (keycode == 0) return;
    XTestGrabControl(disp, True);
    /* Generate modkey press */
    if (modsym != 0)
    {
        modcode = XKeysymToKeycode(disp, modsym);
        XTestFakeKeyEvent(disp, modcode, True, 0);
    }
    /* Generate regular key press and release */
    XTestFakeKeyEvent(disp, keycode, True, 0);
    XTestFakeKeyEvent(disp, keycode, False, 0);

    /* Generate modkey release */
    if (modsym != 0)
        XTestFakeKeyEvent(disp, modcode, False, 0);

    XSync(disp, False);
    XTestGrabControl(disp, False);
}

/* Main Function */
int main()
{
    Display *disp = XOpenDisplay(NULL);
    SendKey(disp, XK_v, XK_Control_L);
}
