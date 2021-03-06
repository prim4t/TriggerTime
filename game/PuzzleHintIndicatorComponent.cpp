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

#include "PuzzleHintIndicatorComponent.h"
#include "Renderer.h"
#include "SceneObject.h"
#include "Scene.h"
#include "SceneObjectFactory.h"
#include "Utils.h"
#include "AssetManager.h"
#include <boost/make_shared.hpp>

namespace af
{
    PuzzleHintIndicatorComponent::PuzzleHintIndicatorComponent(float length, int zOrder)
    : UIComponent(zOrder),
      length_(length),
      padding_(0.0f),
      color_(1.0f, 1.0f, 1.0f),
      dir_(b2Vec2(1.0f, 0.0f)),
      pos_(b2Vec2_zero),
      arrow_(assetManager.getImage("common1/hint_indicator_arrow.png")),
      circle_(assetManager.getImage("common1/hint_indicator_circle.png"))
    {
    }

    PuzzleHintIndicatorComponent::~PuzzleHintIndicatorComponent()
    {
    }

    void PuzzleHintIndicatorComponent::accept(ComponentVisitor& visitor)
    {
        visitor.visitUIComponent(shared_from_this());
    }

    void PuzzleHintIndicatorComponent::update(float dt)
    {
        if (color_.rgba[3] <= 0.0f) {
            return;
        }

        b2RayCastInput input;

        input.p1 = p1_;
        input.p2 = b2Vec2_zero;
        input.maxFraction = 1.0f;

        b2RayCastOutput output;

        b2Transform xf;
        xf.SetIdentity();

        bool res = boundary_.RayCast(&output, input, xf, 0);
        if (res) {
            pos_ = (output.fraction * b2Vec2_zero) + ((1.0f - output.fraction) * p1_);
            pos_ += b2Vec2(scene()->gameWidth() / 2.0f, scene()->gameHeight() / 2.0f);
        }
    }

    void PuzzleHintIndicatorComponent::render()
    {
        if (color_.rgba[3] <= 0.0f) {
            return;
        }

        renderQuad(arrow_, pos_,
            vec2angle(dir_),
            length_,
            length_ / arrow_.aspect(), color_);
        renderQuad(circle_, pos_ - b2Vec2(0.5f * (length_ / arrow_.aspect()), 0.0f) - 0.25f * (length_ / arrow_.aspect()) * dir_,
            0.0f,
            length_ / arrow_.aspect(),
            length_ / arrow_.aspect(), color_);
    }

    void PuzzleHintIndicatorComponent::setPadding(float value)
    {
        padding_ = value;

        if (!scene()) {
            return;
        }

        boundary_.SetAsBox(scene()->gameWidth() / 2.0f - padding_,
                           scene()->gameHeight() / 2.0f - padding_);
    }

    void PuzzleHintIndicatorComponent::setDirection(const b2Vec2& value)
    {
        dir_ = value;

        if (!scene()) {
            return;
        }

        p1_ = dir_;
        p1_.Normalize();
        dir_ = p1_;
        p1_ *= b2Vec2(scene()->gameWidth(), scene()->gameHeight()).Length();
    }

    void PuzzleHintIndicatorComponent::onRegister()
    {
        setPadding(padding_);
        setDirection(dir_);

        update(0);
    }

    void PuzzleHintIndicatorComponent::onUnregister()
    {
    }

    void PuzzleHintIndicatorComponent::renderQuad(const Image& image,
        const b2Vec2& pos,
        float angle,
        float width,
        float height,
        const Color& color)
    {
        b2Transform xf(pos, b2Rot(angle));

        renderer.setProgramDef(image.texture());

        RenderTriangleFan rop = renderer.renderTriangleFan();

        b2Vec2 tmp = b2Mul(xf, b2Vec2(0.0f, -height / 2.0f)); rop.addVertex(tmp.x, tmp.y);
        tmp = b2Mul(xf, b2Vec2(width, -height / 2.0f)); rop.addVertex(tmp.x, tmp.y);
        tmp = b2Mul(xf, b2Vec2(width, height / 2.0f)); rop.addVertex(tmp.x, tmp.y);
        tmp = b2Mul(xf, b2Vec2(0.0f, height / 2.0f)); rop.addVertex(tmp.x, tmp.y);

        rop.addTexCoords(image.texCoords(), 6);

        rop.addColors(color);
    }
}
