package com.hesong.ipsc.busnetcli;

/**
 * BUS 客户端的回调函数集合接口类
 *
 * @author 雪彦
 */
public interface Callbacks {

    /**
     * 全局BUS连接状态变化回调
     *
     * @param unitId     产生连接状态变化的BUS节点的Unit ID
     * @param clientId   产生连接状态变化的BUS节点的Client ID。是node中心节点连接时，client id 值为 -1
     * @param clientType 产生连接状态变化的BUS节点的Client Type
     * @param status     产生连接状态变化的BUS节点的连接状态： 0 断开连接、1 新建连接、2 已有的连接
     * @param addInfo    产生连接状态变化的BUS节点的附加信息
     */
    void globalConnect(byte unitId, byte clientId, byte clientType, byte status, String addInfo);

    /**
     * 连接结果回调
     *
     * @param localClientId     连接结果产生变化的本地客户端的ID
     * @param accessPointUnitId 连接结果产生变化的本地客户端所连接的服务器的 UnitID
     * @param errorCode         错误编码。链接失败时返回。0建立连接成功、小于0表示连接失败
     */
    void connect(byte localClientId, int accessPointUnitId, int errorCode);

    /**
     * 断线回调
     *
     * @param localClientId 连接断开的本地客户端的ID
     */
    void disconnect(byte localClientId);

    /**
     * 收到数据回调
     *
     * @param head  数据收发者等信息
     * @param bytes 二进制数据
     */
    void data(Head head, byte[] bytes);

    /**
     * 收到日志输出的回调函数
     *
     * @param msg   日志内容
     * @param isErr 是否错误日志
     */
    void log(String msg, Boolean isErr);
}
