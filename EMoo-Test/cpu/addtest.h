#ifndef ADDTEST_H
#define ADDTEST_H

#include <QTest>
#include "common.h"

MACHINE_AWARE

/**
 * @brief The AddTest class
 *  ADD     AL,ib	04 i0	 B	2	o---szap
    ADD     AX,iw	05 i0 i1	 W	3	o---szap
    ADD     rb,rmb	02 mr d0 d1	 B	2~4	o---szap
    ADD     rw,rmw	03 mr d0 d1	 W	2~4	o---szap
    ADD     rmb,ib	80 /0 d0 d1 i0	NB	3~5	o---szap
    ADD     rmw,iw	81 /0 d0 d1 i0 i1	NW	4~6	o---szap
    ADD     rmw,ib	83 /0 d0 d1 i0	EW	3~5	o---szap
    ADD     rmb,rb	00 mr d0 d1	 B	2~4	o---szap
    ADD     rmw,rw	01 mr d0 d1	 W	2~4	o---szap
 */
class AddTest : public QObject
{
    Q_OBJECT

public:
    AddTest();

private Q_SLOTS:
    void opAddRmbRb();

    void opAddRmwRw() {

    }

    void opAddRbRmb() {

    }

    void opAddRwRmw() {

    }

    void opAddAlIb() {

    }

    void opAddAxIw() {

    }

    void opAddRmbIb() {

    }

    void opAddRmwIw() {

    }

    void opAddRmwIb() {

    }
};
#endif // ADDTEST_H
