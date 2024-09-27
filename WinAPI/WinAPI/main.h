#pragma once

#include "main.g.h"

namespace winrt::WinAPI::implementation
{
    struct main : mainT<main>
    {
        main() 
        {
            // Xaml objects should not call InitializeComponent during construction.
            // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
        }

        int32_t MyProperty();
        void MyProperty(int32_t value);

        void ClickHandler(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::RoutedEventArgs const& args);
    };
}

namespace winrt::WinAPI::factory_implementation
{
    struct main : mainT<main, implementation::main>
    {
    };
}
