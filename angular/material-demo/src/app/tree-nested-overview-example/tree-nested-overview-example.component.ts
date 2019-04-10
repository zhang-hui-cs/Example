import { NestedTreeControl } from "@angular/cdk/tree";
import { Component } from "@angular/core";
import { MatTreeNestedDataSource } from "@angular/material/tree";
import { isDefined } from "@angular/compiler/src/util";

/**
 * Food data with nested structure.
 * Each node has a name and an optiona list of children.
 */
interface FoodNode {
  id: number;
  name: string;
  /**
   * -1: check_box_outline_blank
   *  0: indeterminate_check_box
   *  1: check_box
   * -1 -> 1, 0 -> 1, 1 -> -1
   */
  checkState?: number;
  children?: FoodNode[];
}

const TREE_DATA: FoodNode[] = [
  {
    id: 1,
    name: "Fruit",
    children: [
      { name: "Apple", id: 11 },
      { name: "Banana", id: 12 },
      { name: "Fruit loops", id: 13 }
    ]
  },
  {
    id: 2,
    name: "Vegetables",
    children: [
      {
        id: 3,
        name: "Green",
        children: [
          { id: 31, name: "Broccoli" },
          { id: 32, name: "Brussel sprouts" }
        ]
      },
      {
        id: 4,
        name: "Orange",
        children: [{ id: 41, name: "Pumpkins" }, { id: 42, name: "Carrots" }]
      }
    ]
  }
];

@Component({
  selector: "app-tree-nested-overview-example",
  templateUrl: "./tree-nested-overview-example.component.html",
  styleUrls: ["./tree-nested-overview-example.component.css"]
})
export class TreeNestedOverviewExampleComponent {
  treeControl = new NestedTreeControl<FoodNode>(node => node.children);
  dataSource = new MatTreeNestedDataSource<FoodNode>();

  constructor() {
    this.dataSource.data = TREE_DATA;
  }

  hasChild = (_: number, node: FoodNode) =>
    !!node.children && node.children.length > 0;

  changeCheckState(id: number) {
    console.log(`change check state: ${id}`);
    const item = this.getFoodNode(id);
    if (isDefined(item)) {
      if (item.checkState === 1) {
        item.checkState = -1;
      } else if (item.checkState === 0) {
        item.checkState = 1;
      } else {
        item.checkState = 1;
      }

      this.changeCheckStateDown(item);
      this.changeCheckStateUp(item);
    }
  }

  changeCheckStateDown(item: FoodNode) {
    const queue = new Array<FoodNode>();

    if (isDefined(item.children)) {
      for (const child of item.children) {
        queue.push(child);
      }
    }

    while (queue.length > 0) {
      const node = queue[0];
      queue.splice(0, 1);

      node.checkState = item.checkState;

      if (isDefined(node.children)) {
        for (const child of node.children) {
          queue.push(child);
        }
      }
    }
  }

  changeCheckStateUp(item: FoodNode) {
    const parentNode = this.getParentFoodNode(item.id);
    if (isDefined(parentNode)) {
      let cntUncheck = 0;
      let cntChecked = 0;
      let cntIndeterminate = 0;
      for (const child of parentNode.children) {
        if (child.checkState === 1) {
          cntChecked++;
        } else if (child.checkState === 0) {
          cntIndeterminate++;
        } else {
          cntUncheck++;
        }
      }

      let state = null;
      if (cntChecked === parentNode.children.length) {
        state = 1;
      } else if (cntUncheck === parentNode.children.length) {
        state = -1;
      } else {
        state = 0;
      }

      if (state !== parentNode.checkState) {
        parentNode.checkState = state;
        this.changeCheckStateUp(parentNode);
      }
    }
  }

  private getParentFoodNode(id: number): FoodNode {
    const queue = new Array<FoodNode>();
    for (const child of TREE_DATA) {
      queue.push(child);
    }

    while (queue.length > 0) {
      const node = queue[0];
      queue.splice(0, 1);

      if (isDefined(node.children)) {
        for (const child of node.children) {
          if (child.id === id) {
            return node;
          } else {
            queue.push(child);
          }
        }
      }
    }

    return null;
  }

  private getFoodNode(id: number): FoodNode {
    for (const item of TREE_DATA) {
      const resultItem = this.getFoodNodeInternal(item, id);
      if (isDefined(resultItem)) {
        return resultItem;
      }
    }

    return null;
  }

  private getFoodNodeInternal(item: FoodNode, id: number): FoodNode {
    if (isDefined(item)) {
      if (item.id === id) {
        return item;
      } else if (isDefined(item.children)) {
        for (const child of item.children) {
          const resultItem = this.getFoodNodeInternal(child, id);
          if (isDefined(resultItem)) {
            return resultItem;
          }
        }
      }
    }

    return null;
  }
}
