import { NgModule } from "@angular/core";
import { RouterModule, Routes } from "@angular/router";
import { FormFieldAppearanceExampleComponent } from "./form-field-appearance-example/form-field-appearance-example.component";
import { InputOverviewExampleComponent } from "./input-overview-example/input-overview-example.component";
import { TreeNestedOverviewExampleComponent } from "./tree-nested-overview-example/tree-nested-overview-example.component";

const routes: Routes = [
  {
    path: "form-field-appearance-example",
    component: FormFieldAppearanceExampleComponent
  },
  {
    path: "input-overview-example",
    component: InputOverviewExampleComponent
  },
  {
    path: "tree-nested-overview-example",
    component: TreeNestedOverviewExampleComponent
  }
];

@NgModule({
  imports: [RouterModule.forRoot(routes)],
  exports: [RouterModule]
})
export class AppRoutingModule {}
