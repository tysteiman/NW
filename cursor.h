#ifndef NW_CURSOR_H
#define NW_CURSOR_H

/**
 * @TODO when thinking about how our front end(s) will work with our file back end
 *       we need to think about how we'll dispatch front end events i.e. if the x
 *       position changes we should automatically update the front end instead of
 *       doing them separately. That's why it may be a good idea to never update
 *       backend cursor values without using some layer of abstraction to dispatch
 *       those events together. I'm thinking we can have a general movement() function
 *       where we can update the cursor position and just 'click' the front end into
 *       that position.
 */
typedef struct {
    int x;                         /* Current cursor x pos */
    int xSnap;                     /* Value we should snap back to when moving */
    int y;                         /* Current cursor y pos */
} cursor_t;

#endif
