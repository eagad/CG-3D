#include "Q3DSurfacesListWidget.h"
#include <QDebug>
#include "infrastructure/ApplicationContext.h"
#include "modelObjects/ThreeDObject.h"
#include "infrastructure/Type.h"

Q3DSurfacesListWidget::Q3DSurfacesListWidget(QListWidget* fParent)
    :QListWidget(fParent)
{
    setSelectionMode(QAbstractItemView::SingleSelection);
    QObject::connect(this, SIGNAL(itemSelectionChanged()),
                     this, SLOT(selectionChanged()));
}

Q3DSurfacesListWidget::~Q3DSurfacesListWidget()
{
    if (context())
    {
        unsubscribePropertyChangedOnType(ThreeDObjectType, context());
        unsubscribeToContainerChanged(context());
    }
}

void Q3DSurfacesListWidget::setContext(ApplicationContext *fContext)
{
    mContext = fContext;

    subscribePropertyChangedOnType(ThreeDObjectType, context());
    subscribeToContainerChanged(context());
}

void Q3DSurfacesListWidget::propertyChanged(Type *fSource, const std::string &fPropertyName)
{
    if (fSource->metaObject()->className() == ThreeDObjectType)
    {
        if (fPropertyName == NameType)
        {
            for (int i = 0; i < mSurfacesList.size(); ++i)
            {
                auto object = dynamic_cast<ThreeDObject*>(fSource);
                item(i)->setText(QString::fromStdString(object->getName()));
            }
        }
    }
}

void Q3DSurfacesListWidget::notifyContainerChanged(const std::shared_ptr<Type> &fObject, ContainerChangeType fChangeType)
{
    if (fObject->metaObject()->className() == ThreeDObjectType)
    {
        auto object = dynamic_cast<ThreeDObject*>(fObject.get());
        switch (fChangeType)
        {
        case ContainerChangeType::OBJECT_ADDED:
            mSurfacesList.push_back(fObject.get());
            insertItem(mSurfacesList.size() - 1, QString::fromStdString(object->getName()));
            break;
        case ContainerChangeType::OBJECT_REMOVED:
            for (int i = 0; i < mSurfacesList.size(); ++i)
            {
                if (fObject.get() == mSurfacesList[i])
                {
                    takeItem(i);
                    mSurfacesList.erase(mSurfacesList.begin() + i);
                }
            }
            break;
        }
    }
}

void Q3DSurfacesListWidget::selectionChanged()
{
    if (context())
    {
        for (auto index : selectionModel()->selectedIndexes())
        {
            context()->setSelectedObject(mSurfacesList[index.row()]);
        }
    }
}
