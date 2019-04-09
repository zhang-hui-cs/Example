define([
  "Cesium/Core/Cartesian3",
  "Cesium/Core/defined",
  "Cesium/Core/HeadingPitchRange",
  "Cesium/Core/Math",
  "Cesium/Core/ScreenSpaceEventHandler",
  "Cesium/Core/ScreenSpaceEventType",
  "Cesium/Scene/Camera",
  "Cesium/Scene/Cesium3DTileFeature",
  "Cesium/Scene/Cesium3DTileset",
  "Cesium/Widgets/Viewer/Viewer"
], function(
  Cartesian3,
  defined,
  HeadingPitchRange,
  CesiumMath,
  ScreenSpaceEventHandler,
  ScreenSpaceEventType,
  Camera,
  Cesium3DTileFeature,
  Cesium3DTileset,
  Viewer
) {
  "use strict";

  function Custom(viewer) {
    if (!defined(viewer)) {
      console.error("Custom.js :\tviewer is not defined");
      return;
    }

    this._mainViewer = viewer;

    this._mainViewer.scene.globe.show = true;
    this._mainViewer.timeline.container.style.display = "none";
    this._mainViewer.animation.container.style.display = "none";
    this._mainViewer.cesiumWidget.creditContainer.style.display = "none";
    this._mainViewer.scene.globe.depthTestAgainstTerrain = false;

    // var tileset = this._mainViewer.scene.primitives.add(
    //   new Cesium3DTileset({
    //     url: "http://localhost:2001/civilEngineering(1F-4F)/tileset.json"
    //   })
    // );

    // this._mainViewer.flyTo(tileset);

    this.initMouseHandler();
  }

  Custom.prototype.initMouseHandler = function() {
    const mouseHandler = new ScreenSpaceEventHandler(
      this._mainViewer.scene.canvas
    );
    // mouseHandler.setInputAction(
    //   event => this.onDoubleClick(event),
    //   ScreenSpaceEventType.LEFT_DOUBLE_CLICK
    // );

    mouseHandler.setInputAction(
      event => this.onLeftClick(event),
      ScreenSpaceEventType.LEFT_CLICK
    );
  };

  Custom.prototype.onLeftClick = function(event) {
    const theScene = this._mainViewer.scene;

    const pickedPosition = theScene.pickPosition(event.position);
    if (defined(pickedPosition)) {
      const cartographicPosition = theScene.globe.ellipsoid.cartesianToCartographic(
        pickedPosition
      );

      console.log("wc:\t" + JSON.stringify(pickedPosition));
      console.log("cartographic:\t" + JSON.stringify(cartographicPosition));
    }
  };

  /**
   * 双击的响应事件
   */
  Custom.prototype.onDoubleClick = function(event) {
    const theScene = this._mainViewer.scene;
    const theCamera = theScene.camera;

    const pickedPosition = theScene.pickPosition(event.position);
    if (defined(pickedPosition)) {
      const destination = new Cartesian3();
      Cartesian3.lerp(theCamera.positionWC, pickedPosition, 0.7, destination);

      const temp = new Cartesian3();
      Cartesian3.subtract(pickedPosition, theCamera.positionWC, temp);

      const direction = new Cartesian3();
      Cartesian3.normalize(temp, direction);

      theCamera.flyTo({
        destination,
        orientation: {
          direction,
          up: theCamera.up
        }
      });
    }
  };

  return Custom;
});
