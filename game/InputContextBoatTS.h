/*
 * Copyright (c) 2014, Stanislav Vorobiov
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef _INPUTCONTEXTBOATTS_H_
#define _INPUTCONTEXTBOATTS_H_

#include "InputContextBoat.h"
#include "KnobComponent.h"

namespace af
{
    class InputContextBoatTS : public InputContextBoat
    {
    public:
        explicit InputContextBoatTS(Scene* scene);
        ~InputContextBoatTS();

        virtual void update(float dt);

        virtual bool movePressed(b2Vec2& direction) const;

        virtual bool turnLeftPressed() const;

        virtual bool turnRightPressed() const;

        virtual bool forwardPressed() const;

        virtual bool backPressed() const;

        virtual bool lookPressed(b2Vec2& pos, bool& relative) const;

        virtual bool shootPressed(b2Vec2& direction) const;

    private:
        virtual void doActivate();

        virtual void doDeactivate();

        b2Vec2 movePos_;
        float moveRadius_;
        float moveHandleRadius_;
        int moveFinger_;
        b2Vec2 moveTouchPoint_;
        b2Vec2 moveDownPoint_;

        b2Vec2 shootPos_;
        float shootRadius_;
        float shootHandleRadius_;
        int shootFinger_;
        b2Vec2 shootTouchPoint_;
        b2Vec2 shootDownPoint_;

        KnobComponentPtr moveKnob_;
        KnobComponentPtr shootKnob_;

        Image shootImage_;
    };
}

#endif
