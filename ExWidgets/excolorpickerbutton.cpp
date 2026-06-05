#include "excolorpickerbutton.h"

#include "excolorpicker.h"

#include <QFrame>
#include <QHBoxLayout>
#include <QMenu>
#include <QMouseEvent>
#include <QPainter>
#include <QStyleOptionToolButton>
#include <QStylePainter>
#include <QVBoxLayout>
#include <QWidgetAction>

namespace
{
constexpr int kCheckerSize = 4;
constexpr QColor kCheckerColor(0x19, 0x80, 0x80, 0x80);
// FluentUI3: contentHMargin = 6, contentItemHMargin = 4
constexpr int kContentHMargin = 8;
constexpr int kContentItemHMargin = 5;
constexpr int kSwatchVerticalMargin = 5;

static const QChar kChevronDown = QChar(0xE70D);

QFont segoeIconFont(int pixelSize = 12)
{
    QFont font(QStringLiteral("Segoe Fluent Icons"), pixelSize);
    font.setStyleStrategy(QFont::NoFontMerging);
    return font;
}
} // namespace

ExColorPickerButton::ExColorPickerButton(QWidget *parent)
    : QToolButton(parent)
{
    setToolButtonStyle(Qt::ToolButtonTextOnly);
    setPopupMode(QToolButton::InstantPopup);
    setArrowType(Qt::DownArrow);
    setFixedSize(68, 32);
    ensurePopup();
    syncButtonAppearance();
}

QColor ExColorPickerButton::selectedColor() const
{
    if (m_picker)
        return m_picker->color();
    return m_selectedColor;
}

void ExColorPickerButton::setSelectedColor(const QColor &color)
{
    if (m_picker)
    {
        if (m_picker->color() == color)
            return;
        m_picker->setColor(color);
        m_selectedColor = m_picker->color();
    }
    else
    {
        if (m_selectedColor == color)
            return;
        m_selectedColor = color;
    }
    syncButtonAppearance();
    Q_EMIT selectedColorChanged(m_selectedColor);
}

ExColorPicker *ExColorPickerButton::colorPicker() const
{
    return m_picker;
}

void ExColorPickerButton::paintEvent(QPaintEvent *)
{
    QStylePainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QStyleOptionToolButton option;
    initStyleOption(&option);
    option.icon = QIcon();
    option.text.clear();
    option.arrowType = Qt::NoArrow;
    option.features &= ~QStyleOptionToolButton::HasMenu;
    painter.drawComplexControl(QStyle::CC_ToolButton, option);

    const int arrowWidth = style()->pixelMetric(QStyle::PM_MenuButtonIndicator, &option, this);
    QRect arrowArea(option.rect.right() - arrowWidth - 2,
                          option.rect.top(),
                          arrowWidth,
                          option.rect.height());

    QRect swatchRect = option.rect.adjusted(kContentHMargin, kSwatchVerticalMargin, -kContentHMargin, -kSwatchVerticalMargin);
    swatchRect.setRight(arrowArea.left() - kContentItemHMargin);

    painter.setPen(Qt::NoPen);
    painter.setBrush(QBrush(m_selectedColor));
    painter.drawRoundedRect(swatchRect, 3, 3);

    painter.setFont(segoeIconFont(9));
    const QColor arrowColor = option.state & QStyle::State_Enabled
                                  ? palette().color(QPalette::ButtonText)
                                  : palette().color(QPalette::Disabled, QPalette::ButtonText);
    painter.setPen(arrowColor);

    if (m_pressed)
        arrowArea.setTop(arrowArea.top() + 2);
    painter.drawText(arrowArea, Qt::AlignCenter, kChevronDown);
}

void ExColorPickerButton::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_pressed = true;
        update();
    }
    QToolButton::mousePressEvent(event);
}

void ExColorPickerButton::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && m_pressed)
    {
        m_pressed = false;
        update();
    }
    QToolButton::mouseReleaseEvent(event);
}

void ExColorPickerButton::syncButtonAppearance()
{
    setIcon(QIcon());
    setText(QString());
    update();
}

void ExColorPickerButton::ensurePopup()
{
    if (m_picker)
        return;

    auto *menu = new QMenu(this);
    menu->setWindowFlag(Qt::NoDropShadowWindowHint, false);

    auto *container = new QFrame(menu);
    container->setFrameShape(QFrame::NoFrame);
    auto *layout = new QVBoxLayout(container);
    layout->setContentsMargins(0, 0, 0, 0);

    m_picker = new ExColorPicker(container);
    m_picker->setColor(m_selectedColor);
    layout->addWidget(m_picker);

    auto *action = new QWidgetAction(menu);
    action->setDefaultWidget(container);
    menu->addAction(action);

    setMenu(menu);

    connect(menu, &QMenu::aboutToHide, this, [this]
            {
                if (!m_pressed)
                    return;
                m_pressed = false;
                update();
            });

    connect(m_picker, &ExColorPicker::colorChanged, this, [this](const QColor &)
            {
                const QColor color = m_picker->color();
                if (m_selectedColor == color)
                    return;
                m_selectedColor = color;
                syncButtonAppearance();
                Q_EMIT selectedColorChanged(color);
            });
}
