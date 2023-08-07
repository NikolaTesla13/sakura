#include "core/application.h"
#include "sandbox/sandbox.h"

using namespace Sakura;

int main() {
   auto app = CreateRef<Application>(ApplicationDescriptor {
       .Width = 900,
       .Height = 600,
       .Name = "Sakura Sandbox"
   });

   app->PushLayer(new Sandbox());

   return app->Run();
}
