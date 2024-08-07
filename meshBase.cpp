#include "pch.h"
#include "meshBase.h"
#if __has_include("meshBase.g.cpp")
#include "meshBase.g.cpp"
#endif

using namespace winrt;
using namespace Windows::UI::Xaml;

namespace winrt::Rengine::implementation
{
    int32_t meshBase::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void meshBase::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }

    void meshBase::ClickHandler(IInspectable const&, RoutedEventArgs const&)
    {
        Button().Content(box_value(L"Clicked"));
    }
}
