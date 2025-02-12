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
                arguments(
                    "-DANDROID_STL=c++_shared"
                )
            }
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
    // Core Media3 ExoPlayer
    implementation(libs.media3.exoplayer)

    // Media3 UI for video playback controls (optional)
    implementation(libs.media3.ui)

    // Media3 session support (optional, for media session handling)
    implementation(libs.media3.session)
    implementation(libs.media3.exoplayer.hls)

    // Media3 decoder extensions (optional, if you need AV1 or FFmpeg support)
    //implementation(libs.media3.exoplayer.dash)
}