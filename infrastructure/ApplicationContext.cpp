#include "ApplicationContext.h"
#include <string>

#include "ApplicationDatastore.h"
#include "infrastructure/Type.h"

ApplicationContext::ApplicationContext()
    :mDataStore(new ApplicationDatastore())
{
    connect(mDataStore.get(),
            SIGNAL(containerChanged(const std::shared_ptr<Type>&, ContainerChangeType)),
            this,
            SLOT(publishContainerChanged(std::shared_ptr<Type>,ContainerChangeType)));

    connect(mDataStore.get(),
            SIGNAL(modelObjectPropertyChanged(Type*,std::string)),
            this,
            SLOT(publishPropertyChanged(Type*,std::string)));
}

ApplicationContext::~ApplicationContext()
{}

ApplicationDatastore *ApplicationContext::dataStore()
{
    return mDataStore.get();
}

void ApplicationContext::setSelectedObject(Type *fSelectedObject)
{
    mSelectedObject = fSelectedObject;
}

Type *ApplicationContext::getSelectedObject()
{
    return mSelectedObject;
}
