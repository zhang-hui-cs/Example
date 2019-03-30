define([
    'Cesium/Core/defined',
    'Cesium/Widgets/Viewer/Viewer',
    'Cesium/Scene/Camera'
], function (
    defined,
    Viewer,
    Camera) {
    'use strict';

    function Custom(viewer) {
        if (!defined(viewer)) {
            console.error('Custom.js :\tviewer is not defined');
            return;
        }


        this._mainViewer = viewer;

        this._mainViewer.scene.globe.show = true;
        this._mainViewer.timeline.container.style.display = 'none';
        this._mainViewer.animation.container.style.display = 'none';
        this._mainViewer.cesiumWidget.creditContainer.style.display = 'none';

        console.log(`view factor: ${Camera.DEFAULT_VIEW_FACTOR}`);
        Camera.DEFAULT_VIEW_FACTOR = -0.5;
        console.log(`view factor: ${Camera.DEFAULT_VIEW_FACTOR}`);
        this._mainViewer.scene.camera.flyHome(1);
    }

    return Custom;
})