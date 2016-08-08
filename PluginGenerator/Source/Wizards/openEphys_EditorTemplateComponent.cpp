/*
   ------------------------------------------------------------------

   This file is part of the Open Ephys GUI
   Copyright (C) 2016 Open Ephys

   ------------------------------------------------------------------

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef __OPEN_EPHYS_EDITOR_TEMPLATE_COMPONENT_CPP__
#define __OPEN_EPHYS_EDITOR_TEMPLATE_COMPONENT_CPP__

#include "openEphys_EditorTemplateComponent.h"


class TemplateChoicerButtonLookAndFeel   : public LookAndFeel_V2
{
public:
    TemplateChoicerButtonLookAndFeel()
    {
        setColour (TextButton::buttonOnColourId,    Colours::green);
        setColour (TextButton::buttonColourId,      Colours::black);
        setColour (TextButton::textColourOnId,      Colours::black);
        setColour (TextButton::textColourOffId,     Colours::black);
    }

    void drawButtonBackground (Graphics& g,
                               Button& button,
                               const Colour& backgroundColour,
                               bool isMouseOverButton, bool isButtonDown)   override
    {
        // Fill all component with orange bg
        g.setColour (isMouseOverButton ? Colours::orange.darker() : Colours::orange);
        g.fillRoundedRectangle (button.getLocalBounds().toFloat(), 5.f);

        // Draw black bg for content
        auto contentBounds = button.getLocalBounds().reduced (5);
        contentBounds.removeFromTop (25);
        g.setColour (Colours::black);
        g.fillRect (contentBounds.toFloat());

        g.setColour (backgroundColour);
        g.fillEllipse (8, 8, 12, 12);
    }


    void drawButtonText (Graphics& g,
                         TextButton& button,
                         bool isMouseOverButton, bool isButtonDown) override
    {
        const auto textColour = button.getToggleState()
                                    ? findColour (TextButton::textColourOnId)
                                    : findColour (TextButton::textColourOffId);
        g.setColour (textColour);
        g.setFont (14.f);

        g.drawSingleLineText (button.getButtonText(), 27, 19);
    }
};


EditorTemplateComponent::EditorTemplateComponent (const String& buttonName, const String& templateName, const String& toolTip)
    : TextButton                    (buttonName, toolTip)
    , m_templateName                (templateName)
    , m_templateComponentToDisplay  (new Component)
    , m_buttonLookAndFeel           (new TemplateChoicerButtonLookAndFeel)
    , m_contentLookAndFeel          (new LookAndFeel_V2)
{
    setLookAndFeel (m_buttonLookAndFeel);
}


void EditorTemplateComponent::resized()
{
    auto contentBounds = getLocalBounds().reduced (5);
    contentBounds.removeFromTop (25);

    m_templateComponentToDisplay->setBounds (contentBounds);
}


void EditorTemplateComponent::setContentComponent (Component* templateComponentToDisplay)
{
    m_templateComponentToDisplay = templateComponentToDisplay;
    m_templateComponentToDisplay->setLookAndFeel (m_contentLookAndFeel);
    addAndMakeVisible (m_templateComponentToDisplay);
}


void EditorTemplateComponent::setContentLookAndFeel (LookAndFeel* contentLookAndFeel)
{
    m_contentLookAndFeel = contentLookAndFeel;
    m_templateComponentToDisplay->setLookAndFeel (m_contentLookAndFeel);
}


void EditorTemplateComponent::setTemplateName (const String& newTemplateName)
{
    m_templateName = newTemplateName;
}


String EditorTemplateComponent::getTemplateName() const noexcept
{
    return m_templateName;
}

#endif // __OPEN_EPHYS_EDITOR_TEMPLATE_COMPONENT_CPP__

