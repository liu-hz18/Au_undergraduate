<template>
<el-dialog style="text-align: center" title="发表" :visible.sync="dialogVisible" :show-close=false :close-on-click-modal=false width="80%">
    <el-form label-width="80px">
        <el-form-item label="标题">
            <!--请修改这两行注释中间的代码来输入消息标题-->
            <el-input v-model="title" placeholder="please input title"></el-input>
            <!--请修改这两行注释中间的代码来输入消息标题-->
        </el-form-item>
        <el-form-item label="内容">
            <!--请修改这两行注释中间的代码来输入消息内容-->
            <el-input v-model="content" type="textarea" placeholder="please input message"></el-input>
            <!--请修改这两行注释中间的代码来输入消息内容-->
        </el-form-item>
        <el-form-item label="用户名">
            <!--请修改这两行注释中间的代码来输入用户名-->
            <el-input v-model="state.username" placeholder="please input you user name"></el-input>
            <!--请修改这两行注释中间的代码来输入用户名-->
            <span v-if="state.username_valid===false" style="color: red">请设置合法用户名!</span>
        </el-form-item>
    </el-form>
    <span slot="footer" class="dialog-footer">
        <!--请修改这两行注释中间的代码来产生相应按钮的点击事件-->
        <el-button v-on:click="onDialogClose">取 消</el-button>
        <el-button v-on:click="onDialogConfirm" type="primary" :disabled="state.username_valid===false">确 定</el-button>
        <!--请修改这两行注释中间的代码来产生相应按钮的点击事件-->
    </span>
</el-dialog>
</template>

<script>
import {
    getCookie
} from '@/utils/communication.js';
export default {
    name: "PostDialog",
    props: {
        dialogVisible: {
            type: Boolean,
            default: () => true
        },
        state: {
            type: Object,
            default: () => {
                return {
                    username: "",
                    username_valid: false
                }
            }
        }
    },
    // 请在下方设计自己的数据结构以及事件函数
    data() {
        return {
            title: "",
            content: "",
        }
    },
    methods: {
        onDialogClose: function () {
            this.$emit('close-dialog')
        },
        onDialogConfirm: function () {
            this.$emit('add-message-child', this.title, this.content, this.state.username)
            this.$emit('show-dialog', false)
            this.title = ""
            this.content = ""
            this.state.username = getCookie(document.cookie, 'user')
        }
    },
    created() {
        this.state.username = getCookie(document.cookie, 'user')
    },
    watch: { // 用于实时检测username是否合法
        "state.username": {
            handler(newName) {
                this.state.username_valid = /^[A-Za-z\u4e00-\u9fa5][-A-Za-z0-9\u4e00-\u9fa5_]*$/.test(newName)
            }
        }
    }
}
</script>
