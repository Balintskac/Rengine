#pragma once

#include "meshBase.g.h"

namespace winrt::Rengine::implementation
{
    struct meshBase : meshBaseT<meshBase>
    {
        meshBase() 
        {
            // Xaml objects should not call InitializeComponent during construction.
            // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
        }

        int32_t MyProperty();
        void MyProperty(int32_t value);

        void ClickHandler(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::RoutedEventArgs const& args);
    };
}

namespace winrt::Rengine::factory_implementation
{
    struct meshBase : meshBaseT<meshBase, implementation::meshBase>
    {
    };
}
