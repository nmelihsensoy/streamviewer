plugins {
    alias(libs.plugins.android.application)
}

android {
    namespace = "org.nmelihsensoy.streamviewer"
    compileSdk = 35

    defaultConfig {
        applicationId = "org.nmelihsensoy.streamviewer"
        minSdk = 24
        targetSdk = 35
        versionCode = 1
        versionName = "1.0"

        testInstrumentationRunner = "androidx.test.runner.AndroidJUnitRunner"

        externalNativeBuild {
            cmake {
                val gstDevelRoot: String = project.findProperty("gstAndroidDevelRoot") as String?
                    ?: throw GradleException(
                        "\"gstAndroidDevelRoot\" must be defined in your gradle.properties " +
                                "in the top-level directory of the unpacked universal GStreamer Android binaries"
                    )

                val gstRuntimeRoot: String = project.findProperty("gstAndroidRuntimeRoot") as String?
                    ?: throw GradleException(
                        "\"gstAndroidRuntimeRoot\" must be defined in your gradle.properties " +
                                "in the top-level directory of the unpacked universal GStreamer Android binaries"
                    )

                arguments(
                    "-DANDROID_STL=c++_shared",
                    "-DGSTREAMER_DEVEL_ANDROID=$gstDevelRoot",
                    "-DGSTREAMER_RUNTIME_ANDROID=$gstRuntimeRoot"
                )
            }
        }
    }

    sourceSets {
        getByName("main") {
            assets.srcDirs("src/main/assets")
        }
    }

    buildTypes {
        release {
            isMinifyEnabled = false
            proguardFiles(
                getDefaultProguardFile("proguard-android-optimize.txt"),
                "proguard-rules.pro"
            )
        }
    }
    externalNativeBuild {
        cmake {
            path = file("src/main/cpp/CMakeLists.txt")
            version = "3.22.1"
        }
    }
    buildFeatures {
        viewBinding = true
    }
    ndkVersion = "27.0.12077973"
}

dependencies {

    implementation(libs.appcompat)
    implementation(libs.material)
    implementation(libs.constraintlayout)
    testImplementation(libs.junit)
    androidTestImplementation(libs.ext.junit)
    androidTestImplementation(libs.espresso.core)
}